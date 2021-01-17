:: Setup.bat
:: This setups up the environment before you can call any of the other functions
@echo off

set scriptsDir=%~dp0..\build
cd /d %scriptsDir%..

:: Call msvc setup environment
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvars64.bat"

:: setup path to scripts, add it for calling scripts
set path=%scriptsDir%;%path%

::Add depdencies
set INCLUDE=%scriptsDir%..\include;%INCLUDE%
set LIB=%scriptsDir%..\lib;%LIB%
