echo off
del /q RunConvert.bat
for /r %%a in (*.map) do echo ConvertMaps.exe %%a 128 >> RunConvert.bat