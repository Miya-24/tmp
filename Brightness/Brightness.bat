rem /;
rem /; ���邳100%
rem /;

for /f "tokens=3" %%0 in ('Powercfg /query ^| findstr /i /r /c:"^�d���ݒ�� GUID:"')          do set �I�����ꂽ�v����=%%0
for /f "tokens=3" %%0 in ('Powercfg /query ^| findstr /i    /c:"(�f�B�X�v���C)"')             do set     �f�B�X�v���C=%%0
for /f "tokens=3" %%0 in ('Powercfg /query ^| findstr /i    /c:"(�f�B�X�v���C�̖��邳)"')     do set     �f�B�X�v���C�̖��邳=%%0

rem Powercfg  -SetACValueIndex  %�I�����ꂽ�v����%  %�f�B�X�v���C%  %�f�B�X�v���C�̖��邳%    100
rem Powercfg  -SetDCValueIndex  %�I�����ꂽ�v����%  %�f�B�X�v���C%  %�f�B�X�v���C�̖��邳%    100
rem powercfg  -setactive %�I�����ꂽ�v����%
pause