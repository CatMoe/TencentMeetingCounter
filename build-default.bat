@ECHO OFF
chcp 65001
cls
@SETLOCAL

mkdir win-BIN-x64
pushd win-BIN-x64
cmake -T "v142,host=x64" -A "x64" ^
  -DCMAKE_INSTALL_PREFIX=install ^
  -DCMAKE_BUILD_TYPE=Release -DOCR_OUTPUT="BIN" ..
cmake --build . --config Release -j %NUMBER_OF_PROCESSORS%
cmake --build . --config Release --target install
popd

mkdir win-BIN-Win32
pushd win-BIN-Win32
cmake -T "v142,host=x64" -A "Win32" ^
  -DCMAKE_INSTALL_PREFIX=install ^
  -DCMAKE_BUILD_TYPE=Release -DOCR_OUTPUT="BIN" ..
cmake --build . --config Release -j %NUMBER_OF_PROCESSORS%
cmake --build . --config Release --target install
popd

@REM mkdir win-JNI-x64
@REM pushd win-JNI-x64
@REM cmake -T "v142,host=x64" -A "x64" ^
@REM   -DCMAKE_INSTALL_PREFIX=install ^
@REM   -DCMAKE_BUILD_TYPE=Release -DOCR_OUTPUT="JNI" ..
@REM cmake --build . --config Release -j %NUMBER_OF_PROCESSORS%
@REM cmake --build . --config Release --target install
@REM popd

@REM mkdir win-JNI-Win32
@REM pushd win-JNI-Win32
@REM cmake -T "v142,host=x64" -A "Win32" ^
@REM   -DCMAKE_INSTALL_PREFIX=install ^
@REM   -DCMAKE_BUILD_TYPE=Release -DOCR_OUTPUT="JNI" ..
@REM cmake --build . --config Release -j %NUMBER_OF_PROCESSORS%
@REM cmake --build . --config Release --target install
@REM popd

@REM mkdir win-CLIB-x64
@REM pushd win-CLIB-x64
@REM cmake -T "v142,host=x64" -A "x64" ^
@REM   -DCMAKE_INSTALL_PREFIX=install ^
@REM   -DCMAKE_BUILD_TYPE=Release -DOCR_OUTPUT="CLIB" ..
@REM cmake --build . --config Release -j %NUMBER_OF_PROCESSORS%
@REM cmake --build . --config Release --target install
@REM popd

@REM mkdir win-CLIB-Win32
@REM pushd win-CLIB-Win32
@REM cmake -T "v142,host=x64" -A "Win32" ^
@REM   -DCMAKE_INSTALL_PREFIX=install ^
@REM   -DCMAKE_BUILD_TYPE=Release -DOCR_OUTPUT="CLIB" ..
@REM cmake --build . --config Release -j %NUMBER_OF_PROCESSORS%
@REM cmake --build . --config Release --target install
@REM popd

@ENDLOCAL
