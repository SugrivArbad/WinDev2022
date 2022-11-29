
:: C:\Sugriv\WinDev2022\02-COM\02-Containment\03-ClientDeveloperUser\ClientContainmentDeleteFilesAndRegistryEntries.bat

dir

del ComboInnerOuter.h ComboInnerOuter.reg ContainmentInnerServer.dll ContainmentOuterServer.dll ClientOfContainment.exe ClientOfContainment.obj ClientOfContainment.res

dir

:: CLSID_MultiplicationDivision
reg delete "HKEY_CLASSES_ROOT\CLSID\{FEF4B50F-49C0-42E0-9C7D-14402E6ED242}\InProcServer" /f 
reg delete "HKEY_CLASSES_ROOT\CLSID\{FEF4B50F-49C0-42E0-9C7D-14402E6ED242}" /f 

:: CLSID_SumSubtract
reg delete "HKEY_CLASSES_ROOT\CLSID\{705893BA-2601-429F-81B9-660977075646}\InProcServer" /f
reg delete "HKEY_CLASSES_ROOT\CLSID\{705893BA-2601-429F-81B9-660977075646}" /f

del C:\Windows\System32\ContainmentInnerServer.dll C:\Windows\System32\ContainmentOuterServer.dll





:: C:\Sugriv\WinDev2022\02-COM\02-Containment\02-ContainmentOuterServer\OuterContainmentDeleteFilesAndRegistryEntries.bat
:: If you changed ContainmentInnerServer's .reg/.h file(s) or you have made changes in ContainmentOuterServer's .reg/.h file(s) then also make appropriate changes in ComboInnerOuter's .reg/.h file

cd ..\02-ContainmentOuterServer\

dir

del ContainmentInnerServer.dll ContainmentInnerServer.h ContainmentInnerServer.reg ContainmentOuterServer.dll ContainmentOuterServer.exp ContainmentOuterServer.lib ContainmentOuterServer.obj

dir

:: CLSID_MultiplicationDivision
reg delete "HKEY_CLASSES_ROOT\CLSID\{BBB02707-82BA-4ADD-84F7-BE9FBF855EB4}\InProcServer" /f
reg delete "HKEY_CLASSES_ROOT\CLSID\{BBB02707-82BA-4ADD-84F7-BE9FBF855EB4}" /f

del C:\Windows\System32\ContainmentInnerServer.dll






:: C:\Sugriv\WinDev2022\02-COM\02-Containment\01-ContainmentInnerServer\InnerContainmentDeleteFilesAndRegistryEntries.bat

cd ..\01-ContainmentInnerServer\

dir

del ContainmentInnerServer.dll ContainmentInnerServer.exp ContainmentInnerServer.lib ContainmentInnerServer.obj

dir





:: C:\Sugriv\WinDev2022\02-COM\02-Containment\01-ContainmentInnerServer\InnerContainmentCompileLinkAndCopy.bat

dir

cl.exe /c /EHsc ContainmentInnerServer.cpp

dir

link.exe ContainmentInnerServer.obj /DLL /DEF:ContainmentInnerServer.def user32.lib gdi32.lib kernel32.lib /SUBSYSTEM:WINDOWS

dir

copy ContainmentInnerServer.dll ..\02-ContainmentOuterServer
copy ContainmentInnerServer.h ..\02-ContainmentOuterServer
copy ContainmentInnerServer.reg ..\02-ContainmentOuterServer







:: C:\Sugriv\WinDev2022\02-COM\02-Containment\02-ContainmentOuterServer\OuterContainmentCompileLinkAndCopy.bat

cd ..\02-ContainmentOuterServer\

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








:: C:\Sugriv\WinDev2022\02-COM\02-Containment\03-ClientOfContainment\ClientContainmentCompileLinkAndCopy.bat

cd ..\03-ClientOfContainment\

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

