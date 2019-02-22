@echo off
setlocal enabledelayedexpansion

:: make directory for website
echo mkdir .public
mkdir .public

:: copy over generated content
echo cp -r html/* .public
cp -r html/* .public

:: publish to GitLab "Page" folder
echo mv .public public
mv .public public
