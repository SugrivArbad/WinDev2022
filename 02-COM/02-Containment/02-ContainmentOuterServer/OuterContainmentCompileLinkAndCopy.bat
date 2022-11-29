:: C:\Sugriv\WinDev2022\02-COM\02-Containment\02-ContainmentOuterServer\OuterContainmentCompileLinkAndCopy.bat

dir

copy ContainmentInnerServer.dll C:\Windows\System32

ContainmentInnerServer.reg

cl.exe /c /EHsc ContainmentOuterServer.cpp

dir

link.exe ContainmentOuterServer.obj /DLL /DEF:ContainmentOuterServer.def user32.lib gdi32.lib kernel32.lib ole32.lib oleaut32.lib /SUBSYSTEM:WINDOWS

dir

copy ComboInnerOuter.h ..\03-ClientOfContainment
copy ComboInnerOuter.reg ..\03-ClientOfContainment
copy ContainmentInnerServer.dll ..\03-ClientOfContainment
copy ContainmentOuterServer.dll ..\03-ClientOfContainment

