:: This is a single line comment
:: C:\Sugriv\WinDev2022\02-COM\02-Containment\03-ClientDeveloperUser\ClientContainmentDeleteFilesAndRegistryEntries.bat

dir

del ComboInnerOuter.h ComboInnerOuter.reg InnerDllServer.dll OuterDllServer.dll Window.exe Window.obj Window.res

dir

:: CLSID_MultiplicationDivision
reg delete "HKEY_CLASSES_ROOT\CLSID\{BBB02707-82BA-4ADD-84F7-BE9FBF855EB4}" /f 

:: CLSID_SumSubtract
reg delete "HKEY_CLASSES_ROOT\CLSID\{FFCDBBFA-95CB-4674-9E19-05DCBF7E160C}" /f

del C:\Windows\System32\InnerDllServer.dll C:\Windows\System32\OuterDllServer.dll

