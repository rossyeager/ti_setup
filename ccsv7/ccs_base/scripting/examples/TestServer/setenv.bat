@echo off

REM setpath.bat 

REM Scripting Root - two directories above the current directory
set SCRPITING_ROOT=%~dp0..\..

echo %SCRPITING_ROOT%

REM add locations of dss.bat and loadti to PATH
set PATH=%PATH%;%SCRPITING_ROOT%\bin;%SCRPITING_ROOT%\examples\loadti
set PERL5LIB=%PERL5LIB%;%SCRPITING_ROOT%\examples\TestServer

start "Test Server" cmd
