del MyClassFactoryClient.exe MyClassFactoryClient.obj MyClassFactoryServer.dll MyClassFactoryServer.obj

cl.exe /c /EHsc MyClassFactoryServer.cpp

link.exe MyClassFactoryServer.obj /DLL /DEF:MyClassFactoryServer.def user32.lib /SUBSYSTEM:WINDOWS

cl.exe /c /EHsc MyClassFactoryClient.cpp

link.exe MyClassFactoryClient.obj user32.lib gdi32.lib /SUBSYSTEM:WINDOWS

MyClassFactoryClient.exe

