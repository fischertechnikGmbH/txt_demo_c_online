<!-- TOC depthFrom:1 depthTo:6 withLinks:1 updateOnSave:1 orderedList:0 -->

- [Information about the use of the SolutionTxtApps.](#information-about-the-use-of-the-solutiontxtapps)
	- [1 Technical Information.](#1-technical-information)
		- [1.2 About the remote TXT API functionality](#12-about-the-remote-txt-api-functionality)
	- [2 Overview of the FtTxt library and the accompanying include files.](#2-overview-of-the-fttxt-library-and-the-accompanying-include-files)
		- [2.1 How to incorporate these lib, dll and includes in your projects?](#21-how-to-incorporate-these-lib-dll-and-includes-in-your-projects)
			- [2.1.1 Add the Ft Txt includes to your project.<br/>](#211-add-the-ft-txt-includes-to-your-projectbr)
			- [2.1.2 Add the Ft Txt additional library path to your project.](#212-add-the-ft-txt-additional-library-path-to-your-project)
			- [2.1.3 Add the ```FtTxtLib.lib``` (static) or ```FtTxtLibDll.lib``` (DLL) to your project.<br/>](#213-add-the-fttxtliblib-static-or-fttxtlibdlllib-dll-to-your-projectbr)
	- [3 Overview of the example](#3-overview-of-the-example)
		- [3.1 project ```TestProj02``` (static library)](#31-project-testproj02-static-library)
		- [3.2 project ```Camera``` (dynamic link library)](#32-project-camera-dynamic-link-library)
		- [3.3 project ```motorOnOffSwitch``` (dynamic link library)](#33-project-motoronoffswitch-dynamic-link-library)
		- [3.4 project about callbacks](#34-project-about-callbacks)
			- [3.4.1 project ```TestProjCallback```](#341-project-testprojcallback)
			- [3.4.2 project ```TestProjCallback02```](#342-project-testprojcallback02)
			- [3.4.3 project ```TestProjCallback03```](#343-project-testprojcallback03)
- [Document history](#document-history)

<!-- /TOC -->
# Information about the use of the SolutionTxtApps.

This Visual Studio solution contains some examples about remote programming for the fischertechnik TXT controller. This with the use of the FtTxtLib. The FtTxtLib can be used as static or as dynamic (dll) library. Switching between static and dynamic library is not too difficult.<br/>
This FtTxtLib has been extended with the communication thread and a set of higher level API's. 
With this approach, the structure that was in use with the TX-Controler and the Robo-Interface is similar now.


## 1 Technical Information.
The examples has been compiled with MS-Visual Studio 2019 (v142).<br/>
Windows SDK version: 10.0.18362.0.<br/>
C++ language standard: ISO C++17 Standard (std:c++17).<br/>

![project properties  ](./docs/Lib(01).png)

### 1.2 About the remote TXT API functionality

See: [remote TXT API user manual](./API-user-manual/0-Start-remote-TXT-API(FtTxtLib-FtTxtLibDll).md)
for the functionality of the `fischertechnik::txt::remote::api::ftIF2013TransferAreaComHandlerEx2`. 

The projects:
- `TestProj01`, 
- `TestProjCallback`, 
- `Camera`,
- `MotorOnOffSwitch` 
- `TestProjIrControl`

gives examples of the use of the remote TXT API's. 

## 2 Overview of the FtTxt library and the accompanying include files. 

The FtTxt library files are present in the solution root directory `FtLibs`. There is a `Release` and a `Debug` version.<br/>
![typical FtLib set  ](./docs/Lib(03).png)

If a application is using the DLL version, the FtTxtLibDll.dll needs to be present in the same directory as the application (`.exe`).<br/>
The accompanying include files are present in the solution root directory `Includes`.<br/>
![Includes  ](./docs/Lib(02).png)

### 2.1 How to incorporate these lib, dll and includes in your projects?
The `FtTxtLib.h` is multi functional. The static library FtTxtLib.lib will be used if `_LIB` has been defined in C/C++ Preprocessor definition.<br/>
 ![Includes  ](./docs/Lib(04).png)

 
The FtTxtLib.h needs to be included in the project and contains the next sections:
 
```C
 #ifdef _LIB
 #define  FtPro_API 
 #else
 #ifdef FTTXTLIB_EXPORTS
 #define FtPro_API __declspec(dllexport)
 #else
 #define  FtPro_API __declspec(dllimport)
 #endif
 #endif
```

#### 2.1.1 Add the Ft Txt includes to your project.<br/>
$(SolutionDir)Includes;<br/>

 ![Includes  ](./docs/Lib(05).png)
 
#### 2.1.2 Add the Ft Txt additional library path to your project.
 ```$(SolutionDir)FtLibs\$(Configuration)\``` $(Configuration) takes care for the Release or Debug version. <br/

![Additional Lib path  ](./docs/Lib(06).png)

#### 2.1.3 Add the ```FtTxtLib.lib``` (static) or ```FtTxtLibDll.lib``` (DLL) to your project.<br/>  
![Additional library  ](./docs/Lib(07).png)
  


## 3 Overview of the example
Note: All project can used with static or dynamic link library.

### 3.1 project ```TestProj02``` (static library)
Show the use of the communication thread and give some examples about testing the enhanced motor control functionality with keyboard commands.

![Additional library  ](./docs/TestProj02_1.png)

### 3.2 project ```Camera``` (dynamic link library)
Is the same as the original solution but now with the use of the ```FtTxtLib```.  
Save a stream of images to a directory.<br/>  
(no communication thread)

![Additional library  ](./docs/Camera_1.png)

### 3.3 project ```motorOnOffSwitch``` (dynamic link library)
Is the same as the original solution but now with the use of the ```FtTxtLib```.<br/>  
Show to use of an actuator and a sensor.<br/>  
(no communication thread)

![Additional library  ](./docs/MotorOnOffSwitch_1.png)

### 3.4 project about callbacks
> See also [callbacks user manual](./SolutionTxtApps/API-user-manual/8-events.md). 
#### 3.4.1 project ```TestProjCallback```
Example with the C-functions or static methods.

#### 3.4.2 project ```TestProjCallback02```
Example with object methods, use of ```std::bind``` and ```std::placeholders```.

#### 3.4.3 project ```TestProjCallback03```
Example with object methods, use of `lambda expressions`.



# Document history
- 2020-08-30 API with callbacks (events) 466.1.2
- (c) 2020-07-14/31 TesCaWeb.nl [C van Leeuwen] 466.1.1 new

