:: This is a single line comment
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

