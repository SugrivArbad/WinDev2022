:: C:\Sugriv\WinDev2022\02-COM\02-Containment\02-OuterDllServer\ClientContainmentCompileLinkAndCopy.bat

dir

copy InnerDllServer.dll C:\Windows\System32
copy OuterDllServer.dll C:\Windows\System32

ComboInnerOuter.reg

cl.exe /c /EHsc Window.cpp

dir

rc.exe Window.rc

dir

link.exe Window.obj Window.res user32.lib gdi32.lib ole32.lib oleaut32.lib /SUBSYSTEM:WINDOWS

dir

Window.exe

dir

