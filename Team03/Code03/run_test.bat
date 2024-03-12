@echo off

if "%1" == "" (
    echo Usage: script ^<testname^>
    exit /b 1
)

set TEST_NAME=%1
set AUTOTESTER_EXE=out\build\x64-Debug\src\autotester\autotester.exe
set TEST_SOURCE_FILE=tests\%TEST_NAME%_source.txt
set TEST_QUERIES_FILE=tests\%TEST_NAME%_queries.txt
set OUTPUT_FILE=tests\out.xml

if not exist %AUTOTESTER_EXE% (
    echo Error: autotester.exe not found. Make sure it is built.
    exit /b 1
)

echo Running autotester...
%AUTOTESTER_EXE% %TEST_SOURCE_FILE% %TEST_QUERIES_FILE% %OUTPUT_FILE%

echo Starting Python HTTP server...
start python -m http.server 8000

echo Script completed successfully.