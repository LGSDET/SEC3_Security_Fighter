@echo off
set PROJECT_PATH=ADS-B-Group.groupproj
set RAD_STUDIO_VARS="C:\Program Files (x86)\Embarcadero\Studio\23.0\bin\rsvars.bat"

:: Set default values
set CONFIG=Release
set PLATFORM_TYPE=Win64

:: Handle parameters
if not "%1"=="" set CONFIG=%1
if not "%2"=="" set PLATFORM_TYPE=%2

:: Validate CONFIG
if /i not "%CONFIG%"=="Debug" if /i not "%CONFIG%"=="Release" (
    echo Error: CONFIG must be either Debug or Release
    echo Current value: %CONFIG%
    exit /b 1
)

:: Validate PLATFORM_TYPE
if /i not "%PLATFORM_TYPE%"=="Win32" if /i not "%PLATFORM_TYPE%"=="Win64" (
    echo Error: PLATFORM_TYPE must be either Win32 or Win64
    echo Current value: %PLATFORM_TYPE%
    exit /b 1
)

echo set environment
call %RAD_STUDIO_VARS%

echo Building ADS-B-Group project...
echo "MSBuild %PROJECT_PATH% /p:Config=%CONFIG% /p:Platform=%PLATFORM_TYPE%"
MSBuild %PROJECT_PATH% /p:Config=%CONFIG% /p:Platform=%PLATFORM_TYPE%
if %ERRORLEVEL% neq 0 (
    echo Build failed.
    exit /b %ERRORLEVEL%
)

echo ADS-B-Display.exe path: %PLATFORM_TYPE%\%CONFIG%\ADS-B-Display.exe
