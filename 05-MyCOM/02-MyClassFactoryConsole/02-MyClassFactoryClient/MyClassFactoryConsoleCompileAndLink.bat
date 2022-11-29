:: Current direcotry -> 05-MyCOM/02-MyClassFactoryConsole/02-MyClassFactoryClient 

dir

:: This delete is effective onwards second compile and link
del MyClassFactoryClient.exe MyClassFactoryClient.obj MyClassFactoryReg.txt MyClassFactoryServer.dll MyClassFactoryServer.h

dir

cd ..\01-MyClassFactoryServer

dir

:: This delete is effective onwards second compile and link
del MyClassFactoryServer.dll MyClassFactoryServer.exp MyClassFactoryServer.lib MyClassFactoryServer.obj

dir

cl.exe MyClassFactoryServer.cpp /c /EHsc

dir

link.exe MyClassFactoryServer.obj /DLL /DEF:MyClassFactoryServer.def

dir

copy MyClassFactoryReg.txt ..\02-MyClassFactoryClient
copy MyClassFactoryServer.dll ..\02-MyClassFactoryClient
copy MyClassFactoryServer.h ..\02-MyClassFactoryClient

cd ..\02-MyClassFactoryClient

dir

cl.exe MyClassFactoryClient.cpp /c /EHsc 

dir

link.exe MyClassFactoryClient.obj

dir

MyClassFactoryClient.exe

