:: C:\Sugriv\WinDev2022\02-COM\02-Containment\01-InnerDllServer\InnerContainmentCompileLinkAndCopy.bat

dir

cl.exe /c /EHsc InnerDllServer.cpp

dir

link.exe InnerDllServer.obj /DLL /DEF:InnerDllServer.def user32.lib gdi32.lib kernel32.lib /SUBSYSTEM:WINDOWS

dir

copy InnerDllServer.dll ..\02-OuterDllServer
copy InnerDllServer.h ..\02-OuterDllServer
copy InnerDllServer.reg ..\02-OuterDllServer

