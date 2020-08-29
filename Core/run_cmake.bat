@echo off
setlocal
cd /d %~dp0

echo Select your desired visual studio:
echo 1) Visual Studio 2019 64-bit (*)

echo.
set /p SELECTED_OPTION=
if "%SELECTED_OPTION%"=="1" (
	goto :SETUP_VS2019_x64
) else (
	echo Restart and Select a valid option.
	pause
	exit /b 1
)

:SETUP_VS2019_x64
	set CMAKE_GENERATOR=-G"Visual Studio 16 2019"
	set BUILD_SUFFIX=_2019_x64
	goto :GENERATE

:GENERATE
set BUILD_FOLDER="build_win32%BUILD_SUFFIX%"
mkdir %BUILD_FOLDER% > NUL 2>&1
pushd %BUILD_FOLDER%

cmake -Wno-dev %CMAKE_GENERATOR% ../eePearGE/Engine
popd
endlocal
pause