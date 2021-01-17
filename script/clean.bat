:: Script to clean up build environment
:: TODO: Fix this to work with 
@echo off

set buildDir=%~dp0..\build
:: set objDir=.\obj\
 
if exist %buildDir% (  
  pushd %buildDir%
  del /q /s *.exe *.pdb *.ilk *.dll
  :: rd /s /q %objDir%
  :: rd /s /q .vs
  popd
)