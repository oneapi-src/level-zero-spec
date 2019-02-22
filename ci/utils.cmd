@echo off

::---------------------------------------------
:: Parse args
::---------------------------------------------
set UTIL_LABEL=%1
call :PopArgs 1 CMD_ARGS %*

::---------------------------------------------
:: Dispatch
::---------------------------------------------
if "%UTIL_LABEL%" == "" goto Usage
call %UTIL_LABEL% %CMD_ARGS%
exit /b

::---------------------------------------------
:: Usage
::---------------------------------------------
:Usage
echo:Usage:
echo: call %~nx0 <FunctionToCall> [FunctionArgs]
exit /b 1

::=============================================
:: Utility Functions
::=============================================

::---------------------------------------------
:: GetTempFile <RetValName>
::
:: Generate a unique file name and return the
:: name in RetValName
::
:: Arguments:
::
::  RetValName: Name of environment variable
::          to return file name in
::---------------------------------------------
:GetTempFile RetValName
setlocal
:getUniqueFileLoop
for /f %%A in ('"%~dp0deps\getparentproc\getparentproc.exe"') do set _parentproc=%%A
set rtn=%TEMP%\.util.%RANDOM%.%_parentproc%.tmp
if exist "%rtn%" (
  goto :getUniqueFileLoop
) else (
  dir "%~dp0" >"%rtn%" || goto :getUniqueFileLoop
)
endlocal & set "%~1=%rtn%"
exit /b

::---------------------------------------------
:: PopArgs <n> <RetValName> ...
::
:: Remove the first <n> arguments from ...
:: Return the remaining args in <argval>
::
:: Arguments:
::  n:      Integer number of arguments to
::          remove from args
::
::  argval: Name of environment variable
::          to return remaining args in.
::
::  ...:    Original argument list
::---------------------------------------------
:PopArgs
set _PopArgsCount=%1
set _PopArgsValue=%2
if "%_PopArgsCount%" == "" (
    echo:Invalid argument count for :PopArgs
    exit /b 1
)
if "%_PopArgsValue%" == "" (
    echo:Invalid return value name for :PopArgs
    exit /b 1
)

:: Pop the requested amount + the 2 used locally
set /a _PopArgsCount+=2

:: Must use temp file, otherwise '=' is treated as arg delimeter - I hate MSFT.
:Again
call :GetTempFile TmpFile
echo %* > %TmpFile%

:: Use for loop to strip requested number of arguments
for /f "usebackq tokens=%_PopArgsCount%,*" %%i in ("%TmpFile%") do set %_PopArgsValue%=%%j
del %TmpFile% > nul

:: echo:_PopArgsCount          = %_PopArgsCount%
:: echo:ReturnValueName        = %_PopArgsValue%
:: echo:AllArgs                = %*
:: call echo:%_PopArgsValue% = %%%_PopArgsValue%%%

exit /b 0

::---------------------------------------------
:: P4Cmd <User> <Client> <Cmd> [CmdArgs]
::
:: Execute a specified perforce command.
::
:: Arguments:
::   User:      Perforce user name
::   Client:    Perforce Workspace name
::   Cmd:       Perforce command
::   ...        Cmd arguments
::---------------------------------------------
:P4Cmd
setlocal
set P4="%~dp0\deps\p4\x64\p4.exe"
set P4PORT=perforce01-jf.intel.com:3666
set P4CHARSET=utf8
set P4USER=%1
set P4CLIENT=%2
set P4CMD=%3
if "%P4CMD%" == "" (
    echo:Invalid arguments for :P4Cmd
    echo:Usage: :P4Cmd ^<PerforceUser^> ^<PerforceWorkspace^> ^<PerforceCmd^> [CmdArgs]
    exit /b 1
)
call :PopArgs 3 P4CMDARGS %*

echo:---------------------------------------
echo:Perforce Information
echo:---------------------------------------
%P4% info 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo:P4 command failed
    exit /b
)

echo:
echo:---------------------------------------
echo:Perforce Command:
echo:    p4 %P4CMD% %P4CMDARGS%
echo:---------------------------------------
%P4% %P4CMD% %P4CMDARGS% 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo:P4 command failed
    exit /b
)
exit /b 0

