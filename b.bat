@echo off
if not "%DevEnvDir%" == "" goto start
call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"

:start
"C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.exe" gbe.sln /build

if %errorlevel% GEQ 1 goto end
x64\Debug\gbe.exe C:\Projects\gboy-emulator-c++\roms\dmg_rom.bin C:\Projects\gboy-emulator-c++\roms\zelda.gb

:end