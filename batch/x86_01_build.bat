echo off
rem -----------------------------------------------------
rem Set path QTDIR (x64) - QT x64 踰꾩쟾붾젆좊━瑜ㅼ젙댁
rem -----------------------------------------------------
rem set path=%path%;"C:\apps\Python34;"

rem -----------------------------------------------------
rem Create Visual Studio Project Directory (x64) - VS 꾨줈앺듃 붾젆좊━瑜앹꽦댁
rem -----------------------------------------------------
mkdir ..\..\Aquarius-Desktop-MSVC2013-32bit-Release & pushd ..\..\Aquarius-Desktop-MSVC2013-32bit-Release

rem -----------------------------------------------------
rem Create Visual Studio Project (x86) - 뚯뒪濡쒕x86VS 꾨줈앺듃瑜앹꽦댁
rem -----------------------------------------------------
echo on
cmake -G "Visual Studio 12 2013" "..\Aquarius" -DCMAKE_PREFIX_PATH="C:\apps\Qt5.5.1-x86\5.5\msvc2013\lib\cmake"