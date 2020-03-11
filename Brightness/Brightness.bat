rem /;
rem /; 明るさ100%
rem /;

for /f "tokens=3" %%0 in ('Powercfg /query ^| findstr /i /r /c:"^電源設定の GUID:"')          do set 選択されたプラン=%%0
for /f "tokens=3" %%0 in ('Powercfg /query ^| findstr /i    /c:"(ディスプレイ)"')             do set     ディスプレイ=%%0
for /f "tokens=3" %%0 in ('Powercfg /query ^| findstr /i    /c:"(ディスプレイの明るさ)"')     do set     ディスプレイの明るさ=%%0

rem Powercfg  -SetACValueIndex  %選択されたプラン%  %ディスプレイ%  %ディスプレイの明るさ%    100
rem Powercfg  -SetDCValueIndex  %選択されたプラン%  %ディスプレイ%  %ディスプレイの明るさ%    100
rem powercfg  -setactive %選択されたプラン%
pause