# TXT C/C++ Remote (on-line mode) examples

## Contact 
> If you have any questions, problems or suggestions, please contact us: fischertechnik-technik@fischer.de

Replacement for the original TXT-C-Programming-Kit-4-1-6

## Overview
This programming kit for the development of remote applications for the fischertechnik TXT controller contains a library which takes for the communication with the TXT and offers a rich set of higher level API to the end-user. But is also still possible to program directly on TA (transfer area) level.


### Which tools I need?
The `solutions` and `projects` are developed and tested with 
[MS-Visual Studio Community 2019](https://visualstudio.microsoft.com/vs/community/) 
which is free to download and use.<br/>

The original `SolutionOnlineSamples` is using the **C14++ dialect** and can also be used with the Eclipse 2020-06 workbench.<br/> 
The new split-up version (into a solution for the library and a solution for the applications) is using the **C17++ dialect**.<br/>
After downloading a solution, it is directly usable with MS Visual Studio 2019.<br/>

### Overview of the available MS-Visual Studio solutions.
The original `OnlineSamples` structure contains a mixer of the low level library stuff and end-user applications and has been split up into a library solution and a application solution now.
The library has been extended with similar higher level functions as there were available in the ROBO-interface and TC-controller programming kits.
The end-user needs only `SolutionTxtApps` and can add his projects to it; this solution is also to download directly as .zip file.<br/>

1.  [`SolutionTxtApps`](./SolutionTxtApps/README.md) 

  Some examples which are using the `FtTxtLib` or `FtTxtLibDll` library, including these libs, updates of the original example applications and some test examples.<br/> 
  - The library supports the communication thread.
  - It also support a set of higher level API functions as they were also present in the TX-C and Robo-interface programming kits. Like (part of the class `ftIF2013TransferAreaComHandlerEx2`):
    - `ftxStartTransferArea`, `ftxStopTransferArea`, `ftxIsTransferActiv`, `GetTransferAreasArrayAddr`
    - `StartMotorExCmd`,  `IsMotorExReady`
    - `SetOutMotorValues`, `GetOutMotorValues`, `SetOutMotorInverse`
    - `SetOutPwmValues`, `GetOutPwmValues`
    - `SetFtUniConfig`, `SetFtMotorConfig`, `SetFtCntConfig`
    - `GetInIOValue`
    - `SetSound, IsSoundReady`
    - `GetMicLin`, `GetMicLog`
  
   [See also the API user manual](./SolutionTxtLib/API-user-manual/0-Start-remote-TXT-API(FtTxtLib-FtTxtLibDll).md) 
     
1. [`SolutionTxtLib`](./SolutionTxtLib/README.md) 
  
  The project to create the static library `FtTxtLib`  and a dynamic link library (DLL) `FtTxtLibDll`. <br/>

  >  Will be come available later. 

1. [`SolutionOnlineSamples`](./SolutionOnlineSamples/README.md)
    
    The original `OnlineSamples`.
    

# History
- 2020-07-16/30/31 [(c) CvL, TesCaweb.nl]

**TXT-C-Programming-Kit-4-6-6_beta-04**
Re-development of the solution structure.
Re-introduction of a set of higher level API functions. 
  
- 2020-06-28 [(c) CvL, TesCaweb.nl]

The `TA communication` thread has been moved from the application to the Txt Lib.
See also example `TestProg2`.
``` C
  /// <summary>
  /// 3.1 start the communication thread and configure the Motor/Outputs, Inputs and Counters.
  /// </summary>
  /// <remarks> The configurations need to be set before!  </remarks>
  /// <returns>success or error</returns>
  FtErrors ftxStartTransferArea();

  /// <summary>
  /// 3.2 stop the communication thread
  /// </summary>
  /// <returns>success or error </returns>
  FtErrors ftxStopTransferArea();

   /// <summary>
   /// 3.3 Is the communication thread still running?
   /// </summary>
   /// <returns>Is runningr</returns>
  bool   ftxIsTransferActiv();
```
- 2020-06-27 [CvL]

Published **beta version** for RoboPro 4.6.6/4.7.0 pre-release: 
**TXT-C-Programming-Kit-4-6-6_beta-03**

- 2020-06-24 [CvL]

Published  **draft version** for RoboPro 4.6.6: 
**TXT-C-Programming-Kit-4-6-6_beta-02**

Tested with firmware 4.6.6 and on MS-Windows 10 (64 bits)

> Development environment: MS-Visual Studio community 2019,<br/>
  C++ Dialect: C14++

> Added: TestProj02 - example about the use of the enhanced motor control (black box)<br/>
  with the communication between PC and TXT (TA) as thread.
  
> Choice between Compress mode and Simple as setting.<br/>
  
> Test console output conditional with TEST as C++ pre-processor definition. 

> Renamed FtShmem.h into FtShmemTxt.h, add some TXT related comment.<br/>
  Limited the TA size to master + 1 slave, this because the TXT can only work with 1 slave.
  
> I2C communication is not implemented yet because the protocol for send and responds the I2C communication is not available.

- 2019-10-13 [CvL]

> The problem  with the Compressed mode has been resolved.

- 2018-09-18 [CvL]

> The Windows 10 problem around the WinSocket time out settings has been resolved.  

> Note: Don't forget to fill in the right ip-address

> Some additional text output for debugging has also been added.
> 
- 2016 

Original solution published as `TXT-C-Programming-Kit-4.1.6`. 



