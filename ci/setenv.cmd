:: set path vars
set ROOT_DIR=%~dp0..
set SCRIPTS_DIR=%~dp0..\scripts
set CI_DIR=%~dp0

:: set environment vars
if [%COMPUTERNAME%] == [VPGADVDEV001] (
    set THIRD_PARTY_DIR=C:\ci\third_party
) else (
    set THIRD_PARTY_DIR=%~dp0..\third_party
)

:: update path for script dependencies
set PATH=%THIRD_PARTY_DIR%\doxygen-1.8.15.windows.x64.bin;%PATH%

:: set python
set RUN_PY=%~dp0bt

