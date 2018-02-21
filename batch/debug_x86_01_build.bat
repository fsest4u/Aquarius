echo off
rem -----------------------------------------------------
rem Set path QTDIR (x64) - QT x64 Î≤ÑÏ†ÑîÎ†â†Î¶¨Î•§Ï†ï¥Ï
rem -----------------------------------------------------
rem set path=%path%;"C:\apps\Python34;"

rem -----------------------------------------------------
rem Create Visual Studio Project Directory (x64) - VS ÑÎ°úùÌä∏ îÎ†â†Î¶¨Î•ùÏÑ±¥Ï
rem -----------------------------------------------------
mkdir ..\..\Aquarius-Desktop-MSVC2013-32bit-Debug & pushd ..\..\Aquarius-Desktop-MSVC2013-32bit-Debug

rem -----------------------------------------------------
rem Create Visual Studio Project (x86) - åÏä§Î°úÎx86VS ÑÎ°úùÌä∏Î•ùÏÑ±¥Ï
rem -----------------------------------------------------
echo on
cmake -G "Visual Studio 12 2013" "..\Aquarius" -DCMAKE_PREFIX_PATH="C:\apps\Qt5.5.1-x86\5.5\msvc2013\lib\cmake"