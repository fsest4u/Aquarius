echo off
rem -----------------------------------------------------
rem Set path QTDIR (x64) - QT x64 è¸°ê¾©¾ë¶¾ì¢ç¼ì rem -----------------------------------------------------
rem set path=%path%;"C:\apps\Python34;"

rem -----------------------------------------------------
rem Create Visual Studio Project Directory (x64) - VS ê¾¨ì¤ºë ë¶¾ì ì¢âì¹ê½
rem -----------------------------------------------------
mkdir ..\..\Aquarius-Desktop-MSVC2013-32bit-Release & pushd ..\..\Aquarius-Desktop-MSVC2013-32bit-Release

rem -----------------------------------------------------
rem Create Visual Studio Project (x86) - ªæ¿¡ìx86VS ê¾¨ì¤ºëì¹ê½
rem -----------------------------------------------------
echo on
cmake -G "Visual Studio 12 2013" "..\Aquarius" -DCMAKE_PREFIX_PATH="C:\apps\Qt5.5.1-x86\5.5\msvc2013\lib\cmake"