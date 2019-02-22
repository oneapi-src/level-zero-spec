@echo off
setlocal enabledelayedexpansion

if [%_JUSTKILLME%] == [OKAY] (
    set _JUSTKILLME=
) else (
    set _JUSTKILLME=OKAY
    call %0 %* < nul
    goto :eof
)

:: set (or clear) any python related environment variables for the duration of this command
set _ROOTDIR=%~dp0..
set _BUILDTOOLS=%THIRD_PARTY_DIR%
set _PYDIR=%_BUILDTOOLS%\python36_x64
set _PYTHON_EXE=python.exe
set PYTHONOPTIMIZE=2
set PYTHONHOME=%_PYDIR%
set PYTHONPATH=%~dp0;%_PYDIR%\Lib
:: set PYTHONPATH=%PYTHONPATH%;%_BUILDTOOLS%\python-site-packages
:: set PYTHONPATH=%PYTHONPATH%;%_ROOTDIR%\build-tools\rasty\python-packages\Lib\site-packages
set PYTHONSTARTUP=

set EXITCODE=0

:: Parameter validation
if [%1]==[] goto NakedLaunch
:: If the script file doesn't exist, but script.py does, use that.

:: First try %dp0\<script>.py
set _SCRIPT="%~dp0%1.py"
if exist %_SCRIPT% goto Invoke

:: Next, try %dp0\<script>
set _SCRIPT="%~dp0%1"
if exist %_SCRIPT% goto Invoke

:: Next, try <script>.py
set _SCRIPT="%1.py"
if exist %_SCRIPT% goto Invoke

:: Next, try <script>
set _SCRIPT="%1"
if exist %_SCRIPT% goto Invoke

:NakedLaunch
:: Neither %1 nor %1.py exist just pass full args to python and exit
"!_PYDIR!\!_PYTHON_EXE!" %*
exit /b %ERRORLEVEL%


:Invoke
:: Remove script name from the arglist and place the remaining args in PY_ARGS
:: call "%~dp0utils.cmd" :PopArgs 1 _PY_ARGS %*

:: Execute command
set _FULL_CMD="!_PYDIR!\!_PYTHON_EXE!" !_SCRIPT! !_PY_ARGS!
:: echo %_FULL_CMD%
%_FULL_CMD%
exit /b %ERRORLEVEL%

:Usage
echo Usage:
echo   %~n0 script [script_args]

