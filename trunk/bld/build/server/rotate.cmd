rem rotate.cmd for OS/2  eCS
rem @echo off

rem Path configuration
rem ==================
set OWROOT=\OWB
set WWWPATH=\www
rem set ARCH7Z=c:\Program Files\7-Zip\7z
rem 7z is standard with eCS 2.1
set ARCH7Z=7z
set RM=%OWROOT%\bld\build\binp\rm

rem Initialization
rem ==============
if exist %OWROOT%\pass1 goto prerequisite_ok
echo Missing %OWROOT%\pass1. Can't continue with rotation.
goto done

:prerequisite_ok

rem Build Archives
rem ==============
if exist %WWWPATH%\snapshots\ss.zip %RM% -f %WWWPATH%\snapshots\ss.zip
if exist %WWWPATH%\snapshots\ss.7z %RM% -f %WWWPATH%\snapshots\ss.7z
"%ARCH7Z%" a -tzip -r %WWWPATH%\snapshots\ss.zip %OWROOT%\pass1\*
"%ARCH7Z%" a -t7z -r %WWWPATH%\snapshots\ss.7z %OWROOT%\pass1\*

rem Move pass1 build
rem =================
if exist %WWWPATH%\snapshot move %WWWPATH%\snapshot %WWWPATH%\snapshot.bak
if exist %WWWPATH%\snapshot goto done
move %OWROOT%\pass1 %WWWPATH%\snapshot

rem Move Archives
rem =============
if exist %WWWPATH%\snapshots\ow-snapshot.zip %RM% -f %WWWPATH%\snapshots\ow-snapshot.zip
if exist %WWWPATH%\snapshots\ow-snapshot.7z %RM% -f %WWWPATH%\snapshots\ow-snapshot.7z
move %WWWPATH%\snapshots\ss.zip %WWWPATH%\snapshots\ow-snapshot.zip
move %WWWPATH%\snapshots\ss.7z %WWWPATH%\snapshots\ow-snapshot.7z

rem Move installers
rem =============
if exist %WWWPATH%\installers\open-watcom-*.* %RM% -f %WWWPATH%\installers\open-watcom-*.*
move %OWROOT%\distrib\ow\open-watcom-*.* %WWWPATH%\installers

rem Final Cleanup
rem =============
%RM% -rf %WWWPATH%\snapshot.bak

:done
