echo off
rem -----------------------------------------------------
rem Set path QTDIR (x64) - QT x64 버전�렉�리륤정��
rem -----------------------------------------------------
rem set path=%path%;"C:\apps\Python34;"

rem -----------------------------------------------------
rem Create Visual Studio Project Directory (x64) - VS �로�트 �렉�리륝성��
rem -----------------------------------------------------
mkdir ..\..\Aquarius-Desktop-MSVC2013-32bit-Debug & pushd ..\..\Aquarius-Desktop-MSVC2013-32bit-Debug

rem -----------------------------------------------------
rem Create Visual Studio Project (x86) - �스로�x86VS �로�트륝성��
rem -----------------------------------------------------
echo on
cmake -G "Visual Studio 12 2013" "..\Aquarius" -DCMAKE_PREFIX_PATH="C:\apps\Qt5.5.1-x86\5.5\msvc2013\lib\cmake"