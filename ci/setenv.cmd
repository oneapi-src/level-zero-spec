:: set relative path vars
set RUN_PY=%~dp0bt
set SCRIPTS_DIR=%~dp0..\scripts

:: set absolute path vars (for CI runner env)
set THIRD_PARTY_DIR=C:\ci\third_party

:: update path for script dependencies
set PATH=%THIRD_PARTY_DIR%\doxygen-1.8.15.windows.x64.bin;%PATH%
