:: script to build file
:: TODO: This does not work and does some weird shit with xcopy
@echo off
 
set buildDir=%~dp0..\build

if not exist %buildDir% mkdir %buildDir%
set binDir=%~dp0..\bin

pushd %buildDir%
 
:: compiler input
set objDir=.
set outputExe=%binDir%\raytrace.exe
set libs=SDL2.lib SDL2main.lib SDL2test.lib Shell32.lib
set files=..\src\*.cpp
 
:: compiler flags:
:: /Zi enable debugging information
:: /FC use full path in diagnostics
:: /Fo<path> the path to write object files
:: /Fe<path> the path to write the executable file
:: /W3 Most Warning
:: /EHsc exception format, autogenerated
set compileFlags=/Zi /FC /W3 /EHsc /Fo:%objDir% /Fe:%outputExe%  

:: linker flags:
:: /SUBSYSTEM specifies exe env - defines entry point symbol
:: This is needed by SDL2 since it defines SDL_Main=main() and calls WinMain() itself
set linkFlags=/link /SUBSYSTEM:CONSOLE

if not exist %objDir% mkdir %objDir%
 
cl %compileFlags% %files% %libs% %linkFlags%
 
:: Copy dependencies ????
:: xcopy /y ..\external\SDL\lib\x64\SDL2.dll . 

popd