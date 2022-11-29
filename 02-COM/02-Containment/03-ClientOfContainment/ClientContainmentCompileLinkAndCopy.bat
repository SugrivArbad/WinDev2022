:: C:\Sugriv\WinDev2022\02-COM\02-Containment\03-ClientOfContainment\ClientContainmentCompileLinkAndCopy.bat

dir

copy ContainmentInnerServer.dll C:\Windows\System32
copy ContainmentOuterServer.dll C:\Windows\System32

ComboInnerOuter.reg

cl.exe /c /EHsc /D UNICODE ClientOfContainment.cpp

dir

rc.exe ClientOfContainment.rc

dir

link.exe ClientOfContainment.obj ClientOfContainment.res user32.lib gdi32.lib kernel32.lib ole32.lib oleaut32.lib /SUBSYSTEM:WINDOWS

dir

ClientOfContainment.exe

dir

