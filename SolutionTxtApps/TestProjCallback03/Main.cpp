///////////////////////////////////////////////////////////////////////////////
//
// File:    Main.cpp
// version 1.1.1.1
// Project: TestProjCallback03- test and example for the sensor callback's
//                             
//
//
// 2020-08-15 (c)  ing.C van Leeuwen Btw. [TesCaWeb.nl]
//              |  June-July 2020  bij [CvL] 
//              |             tested with TXT firmware 4.6.0/4.7.0 pre-release
//              |             Solution update to MS-Visual Studio 2019 dialect C17++, Windows 10
//
///////////////////////////////////////////////////////////////////////////////
//
// This sample program does the following:
// - Open connection to TXT interface with IP 192.168.10.171 (NOTE the IP adress is static and only valid for a LAN,
//	not usable on WLAN)
// 
// - Start transfer

// The typical IP addresses / hostnames are:
// - 192.168.7.2 : online via USB
// - 192.168.8.2 : online via WLAN
// - 192.168.9.2 : online via Bluetooth
// - 192.168.178.21 : home network WLAN 
// - localhost   : download mode
///////////////////////////////////////////////////////////////////////////////



#include <iostream>
#include "conio.h"
#include <chrono>
#include <time.h>
#include <fstream>
#include <sstream>
#include "FtTxtLib.h"

using namespace std;
using namespace fischertechnik::txt::ids;
using  namespace fischertechnik::txt::remote::api;


/****************************************************************************/
/// <summary>
/// Adjust for your own situation
/// </summary>
const std::string MyIP = "192.168.10.171";//Todo: fille in your IP
const std::string TaPort = "65000";
const std::string logMap = "H:\\workspaceVS\\txt_demo_c_online.git\\SolutionTxtApps\\";//Todo: fill in your map for the internal log file
/****************************************************************************/

const  Motor IdMotorA = Motor::M1, IdMotorB = Motor::M2, IdMotorC = Motor::M3;
const  Counter IdCntA = Counter::C1, IdCntB = Counter::C2;
const  Input IdSensorUltra = Input::I6, IdSensorSwitch = Input::I1;


const int speedMax = 512, speedLow = 200;
const  int counterA = 400, counterB = 400;




/// <summary>
/// Command handler 
/// </summary>
ftIF2013TransferAreaComHandlerEx2* ComHandler;
char input = ' ';
bool stopWhile = false;
volatile FISH_X1_TRANSFER* TransArea;

/*************************************************************************************************************************/
/*    example callbacks  */
/*************************************************************************************************************************/

	/// <summary>
	/// 
	/// </summary>
	/// <param name="o"></param>
	/// <param name="shmId"></param>
	/// <param name="id"></param>
	/// <param name="state"></param>
void MyUniInCallback(ftIF2013TransferAreaComHandlerEx2* o, ShmIfId_TXT shmId, Input id, bool state) {
	cout << " MyUniInCallback [" << shmId << ":" << (uint16_t)id << " ] state=" << ((state) ? "true" : "false") << endl;
}

/// <summary>
/// 
/// </summary>
/// <param name="o"></param>
/// <param name="shmId"></param>
/// <param name="id"></param>
/// <param name="position"></param>
/// <param name="messageId"></param>
void MyMotorReached(ftIF2013TransferAreaComHandlerEx2* o, ShmIfId_TXT shmId, Motor id, uint16_t position, uint16_t messageId) {
	cout << "MyMotorReachedCallback [" << shmId << ":" << (uint16_t)id << " => " << position << "] id=" << messageId << endl;
}

//or as lambda expression
ftIF2013TransferAreaComHandlerEx2::tCbMotorReached LaMotorReached = [](ftIF2013TransferAreaComHandlerEx2* o, ShmIfId_TXT shmId, Motor id, uint16_t position, uint16_t messageId) {
	cout << "MotorReachedCallback lambda expression  [" << shmId << ":" << (uint16_t)id << " => " << position << "] id=" << messageId << endl;
};

/// <summary>
/// 
/// </summary>
/// <param name="o"></param>
/// <param name="shmId"></param>
/// <param name="id"></param>
/// <param name="count"></param>
void MyCount(ftIF2013TransferAreaComHandlerEx2* o, ShmIfId_TXT shmId, Counter id, uint16_t count) {
	cout << "MyCount [" << shmId << ":" << (uint16_t)id << " => " << count << "]" << endl;
}

/// <summary>
/// 
/// </summary>
/// <param name="o"></param>
/// <param name="shmId"></param>
/// <param name="id"></param>
/// <param name="messageId"></param>
void MyCntResetReady(ftIF2013TransferAreaComHandlerEx2* o, ShmIfId_TXT shmId, Counter id, uint16_t messageId) {
	cout << " MyCntResetReady [" << shmId << ":" << (uint16_t)id << " ] id=" << messageId << endl;
}

//==============================================================================================================




int main()
{
	ComHandler = new ftIF2013TransferAreaComHandlerEx2(IF_TXT_MAX, MyIP.c_str(), TaPort.c_str(), logMap.c_str(), LogLevel::LvLOG);
	if (ComHandler == nullptr) {
		cerr << "Main: ComHandler nullptr" << endl;
		return -3;
	}

	TransArea = ComHandler->GetTransferAreasArrayAddr();

	ComHandler->SetTransferMode(true);
	/****************************************************************************/
	/* setup the communication thread with the TXT */
	/* Setup the configuration first*/
	/****************************************************************************/
	ComHandler->SetFtUniConfig(ShmIfId_TXT::LOCAL_IO, Input::I2, InputMode::MODE_R, true);

	//lambda expression as callback
	//Switch I1 to end the program
	ComHandler->SetFtUniConfig(ShmIfId_TXT::LOCAL_IO, IdSensorSwitch, InputMode::MODE_R
		, [](ftIF2013TransferAreaComHandlerEx2* o, ShmIfId_TXT shmId, Input id, bool state)->void {
		cout << " UniInCallback lambda expression [" << shmId << ":" << (uint16_t)id << " ] state=" << ((state) ? "true" : "false") << endl;
		if (state) stopWhile = true;
		}
		//std::bind(&MyUniInCallback, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
	);

	ComHandler->SetFtUniConfig(ShmIfId_TXT::LOCAL_IO, IdSensorUltra, InputMode::MODE_ULTRASONIC,false);

	ComHandler->SetFtMotorConfig(ShmIfId_TXT::LOCAL_IO, IdMotorA, true
		,LaMotorReached //, MyMotorReached
	);//As full bridge (M functionality) (default)
	// lambda expression direct in the methode
	ComHandler->SetFtMotorConfig(ShmIfId_TXT::LOCAL_IO, IdMotorB, true
		, [](ftIF2013TransferAreaComHandlerEx2* o, ShmIfId_TXT shmId, Motor id, uint16_t position, uint16_t messageId) {
			cout << "MotorReachedCallback lambda expression 2 [" << shmId << ":" << (uint16_t)id << " => " << position << "] id=" << messageId << endl;
		}
		//, MyMotorReached
	); 

	
	ComHandler->SetFtCntConfig(ShmIfId_TXT::LOCAL_IO, IdCntA, false 
		, [](ftIF2013TransferAreaComHandlerEx2* o, ShmIfId_TXT shmId, Counter id, uint16_t count) {
			cout << "Count lambda expression [" << shmId << ":" << (uint16_t)id << " => " << count << "]" << endl;
		}
		//,std::bind(&MyCount, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)
	);
	ComHandler->SetFtCntConfig(ShmIfId_TXT::LOCAL_IO, IdCntB, true
		,nullptr
		, [](ftIF2013TransferAreaComHandlerEx2* o, ShmIfId_TXT shmId, Counter id, uint16_t messageId) {
			cout << " CntResetReady lambda expression [" << shmId << ":" << (uint16_t)id << " ] id=" << messageId << endl;
		}
		//,std::bind(&MyCntResetReady, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)
		);


	/*********************************************************************************/
	//start the communication thread, includes update configuration.
	/****************************************************************************/
	ComHandler->SetTransferMode(true);
	if (!ComHandler->ftxStartTransferArea() == FtErrors::FTLIB_ERR_SUCCESS)
	{
		cout << "Main: Error: ftxStartTransferArear" << endl;
		do
		{
			cerr << '\n' << "Press a key to continue...";
		} while (cin.get() != '\n');
		return false;
	}
	/*********************************************************************************/
	// ready to start the main loop
	/****************************************************************************/
	int iLoop = 0;
	printf("Two encoder motors [on M1/C1 and M2/C2] \n");
	int16_t r = 0, l = 0;
	int16_t factor = (512) / 15;//transformation from Joystick (-15..0..15) to motor (-512..0..512)
	ComHandler->StartMotorExCmd(ShmIfId_TXT::LOCAL_IO, Motor::M1,400,Direction::CW, Motor::M2, Direction::CW,100);

	while (!(ComHandler->IsMotorExReady(ShmIfId_TXT::LOCAL_IO, Motor::M1) && ComHandler->IsMotorExReady(ShmIfId_TXT::LOCAL_IO, Motor::M2))) {

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	ComHandler->StopMotorExCmd(ShmIfId_TXT::LOCAL_IO, Motor::M1);
	ComHandler->StopMotorExCmd(ShmIfId_TXT::LOCAL_IO, Motor::M2);

	
	while (!stopWhile)
	{
		try {
			r = ComHandler->GetJoystickFull(ShmIfId_TXT::LOCAL_IO, IrDev::IR_ON_OFF, IrAxisF::JoyLeftX);
			l = ComHandler->GetJoystickFull(ShmIfId_TXT::LOCAL_IO, IrDev::IR_ON_OFF, IrAxisF::JoyRightX);
			cout << "Joystick id="<< IrDev::IR_ON_OFF <<" l:r=" << l<<":"<<r << '\n';
			ComHandler->SetOutMotorValues(ShmIfId_TXT::LOCAL_IO, Motor::M1, r * factor);
			ComHandler->SetOutMotorValues(ShmIfId_TXT::LOCAL_IO, Motor::M2, l * factor);
			//if (ComHandler->GetInIOValueBinary(ShmIfId_TXT::LOCAL_IO, Input::I1)) stopWhile = true;//see callback
		}
		catch (exception& ex) {
			cout << ex.what() << '\n';
			stopWhile = true;
		}//end try

		std::this_thread::sleep_for(std::chrono::milliseconds(20));

	} //end while
	/*********************************************************************************/
	cout << endl << "Main: normal end, transfers done iLoop=" << iLoop << endl;
	/*********************************************************************************/
	std::cout << "Asking Thread to Stop" << std::endl;
	ComHandler->ftxStopTransferArea();
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	std::cout << "End" << std::endl;
	if (ComHandler != nullptr) delete ComHandler;	// Delete transfer area and communication area
	std::cout << "pause 1" << std::endl;
	std::system("pause");
	return 0;
}

