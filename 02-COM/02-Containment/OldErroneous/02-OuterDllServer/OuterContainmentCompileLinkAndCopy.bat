:: C:\Sugriv\WinDev2022\02-COM\02-Containment\02-OuterDllServer\OuterContainmentCompileLinkAndCopy.bat

dir

copy InnerDllServer.dll C:\Windows\System32

InnerDllServer.reg

cl.exe /c /EHsc OuterDllServer.cpp

dir

link.exe OuterDllServer.obj /DLL /DEF:OuterDllServer.def user32.lib gdi32.lib kernel32.lib ole32.lib oleaut32.lib /SUBSYSTEM:WINDOWS

dir

copy ComboInnerOuter.h ..\03-ClientDeveloperUser
copy ComboInnerOuter.reg ..\03-ClientDeveloperUser
copy InnerDllServer.dll ..\03-ClientDeveloperUser
copy OuterDllServer.dll ..\03-ClientDeveloperUser

