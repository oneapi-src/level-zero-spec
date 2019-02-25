@echo off
setlocal enabledelayedexpansion

:: setup environment
call %~dp0setenv.cmd

:: run cmd
echo %RUN_PY% ci.py --publish-html
%RUN_PY% ci.py --publish-html