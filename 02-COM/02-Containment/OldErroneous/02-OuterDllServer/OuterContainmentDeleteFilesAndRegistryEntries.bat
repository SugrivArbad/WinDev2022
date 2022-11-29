:: C:\Sugriv\WinDev2022\02-COM\02-Containment\02-OuterDllServer\OuterContainmentDeleteFilesAndRegistryEntries.bat
:: If you changed InnerDllServer's .reg/.h file(s) or you have made changes in OuterDllServer .reg/.h file(s) then also make appropriate changes in ComboInnerOuter's .reg/.h file

dir

del InnerDllServer.dll InnerDllServer.h InnerDllServer.reg OuterDllServer.dll OuterDllServer.exp OuterDllServer.lib OuterDllServer.obj

dir

:: CLSID_MultiplicationDivision
reg delete "HKEY_CLASSES_ROOT\CLSID\{BBB02707-82BA-4ADD-84F7-BE9FBF855EB4}" /f

del C:\Windows\System32\InnerDllServer.dll

