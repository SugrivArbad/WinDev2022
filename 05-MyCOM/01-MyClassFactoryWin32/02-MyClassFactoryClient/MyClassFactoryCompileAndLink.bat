:: current directory --> 05-MyCOM\01-MyClassFactoryWin32\02-MyClassFactoryClient

dir

:: this delete is effective onwards second compile and link
del MyClassFactoryClient.exe MyClassFactoryClient.obj MyClassFactoryClient.res MyClassFactoryReg.txt MyClassFactoryServer.h

:: this delete is effective onwards second compile and link
:: this requires command prompt with administrative access (Run as administrator)
del C:\Windows\System32\MyClassFactoryServer.dll

dir

cd ..\01-MyClassFactoryServer

dir

:: this delete is effective onwards second compile and link
del MyClassFactoryServer.dll MyClassFactoryServer.exp MyClassFactoryServer.lib MyClassFactoryServer.obj

dir

cl.exe MyClassFactoryServer.cpp /c /EHsc

dir

link.exe MyClassFactoryServer.obj /DLL /DEF:MyClassFactoryServer.def user32.lib gdi32.lib kernel32.lib /SUBSYSTEM:WINDOWS

dir

copy MyClassFactoryReg.txt ..\02-MyClassFactoryClient
copy MyClassFactoryServer.dll ..\02-MyClassFactoryClient
copy MyClassFactoryServer.h ..\02-MyClassFactoryClient

cd ..\02-MyClassFactoryClient

dir

:: Client puts MyClassFactoryClient.dll to global accessable path (C:\Windows\System32\)
move MyClassFactoryServer.dll C:\Windows\System32\

dir C:\Windows\System32\MyC*

dir

cl.exe MyClassFactoryClient.cpp /c /EHsc

dir

rc MyClassFactoryClient.rc

dir

link.exe MyClassFactoryClient.obj MyClassFactoryClient.res user32.lib gdi32.lib /SUBSYSTEM:WINDOWS

dir

MyClassFactoryClient.exe

