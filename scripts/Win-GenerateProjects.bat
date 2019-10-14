
@echo off
pushd ..\
CALL vendor\premake\premake5.exe vs2017
popd
PAUSE
