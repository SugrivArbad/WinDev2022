:: C:\Sugriv\WinDev2022\02-COM\02-Containment\01-ContainmentInnerServer\InnerContainmentCompileLinkAndCopy.bat

dir

cl.exe /c /EHsc ContainmentInnerServer.cpp

dir

link.exe ContainmentInnerServer.obj /DLL /DEF:ContainmentInnerServer.def user32.lib gdi32.lib kernel32.lib /SUBSYSTEM:WINDOWS

dir

copy ContainmentInnerServer.dll ..\02-ContainmentOuterServer
copy ContainmentInnerServer.h ..\02-ContainmentOuterServer
copy ContainmentInnerServer.reg ..\02-ContainmentOuterServer

