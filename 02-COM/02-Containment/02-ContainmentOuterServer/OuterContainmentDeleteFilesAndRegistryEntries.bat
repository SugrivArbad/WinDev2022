:: C:\Sugriv\WinDev2022\02-COM\02-Containment\02-ContainmentOuterServer\OuterContainmentDeleteFilesAndRegistryEntries.bat
:: If you changed ContainmentInnerServer's .reg/.h file(s) or you have made changes in ContainmentOuterServer's .reg/.h file(s) then also make appropriate changes in ComboInnerOuter's .reg/.h file

dir

del ContainmentInnerServer.dll ContainmentInnerServer.h ContainmentInnerServer.reg ContainmentOuterServer.dll ContainmentOuterServer.exp ContainmentOuterServer.lib ContainmentOuterServer.obj

dir

:: CLSID_MultiplicationDivision
reg delete "HKEY_CLASSES_ROOT\CLSID\{BBB02707-82BA-4ADD-84F7-BE9FBF855EB4}\InProcServer" /f
reg delete "HKEY_CLASSES_ROOT\CLSID\{BBB02707-82BA-4ADD-84F7-BE9FBF855EB4}" /f

del C:\Windows\System32\ContainmentInnerServer.dll

