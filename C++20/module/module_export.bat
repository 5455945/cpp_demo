@echo off

rem ����Ҫ����������x86/x64��relase/debugѡ���ӦĿ¼�µ�cl.exe
rem set clcmd=D:\install\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.24.28314\bin\Hostx64\x64\cl.exe
rem ��vs���Լ����ҵ�׼ȷ��cl.exe�汾������Ҫ�ر�ָ��
set clcmd=cl.exe

rem ���module�������˱�׼�⣬��Ҫָ��/module:stdIfcDir
rem /experimental:module /module:stdIfcDir "$(VCToolsInstallDir_160)ifc\$(PlatformTarget)"
rem $(VCToolsInstallDir_160)=D:\install\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.24.28314\
rem $(PlatformTarget)=x64
set target=%1%
if "%target%"=="" set target=x64
@echo %target%
rem �����Լ���ʵ��Ŀ¼����
set stdIfcDir="D:\install\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.24.28314\ifc\%target%"

rem ָ���������ɵ����п�md mdd mt mtd(��̬�� ��̬���Կ� ��̬�� ��̬���Կ�)
rem ��bat�ĵ�һ������ָ���Ƿ���debug�汾�������debug�汾����һ�������� d
set rundll=%2%
if "%rundll%"=="" set rundll=MD

rem ��ʾ����ʱ�����
@echo %rundll%

set CFLAGS=/experimental:module /std:c++latest /EHsc /%rundll% /c /module:stdIfcDir %stdIfcDir% /module:export 

rem cl.exe /experimental:module /std:c++latest /EHsc /MD /c /module:stdIfcDir "D:\install\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.24.28314\ifc\x64" /module:export module01.cpp 
"%clcmd%" %CFLAGS% module01.cpp

rem "%clcmd%" %CFLAGS% ģ���ļ�
"%clcmd%" %CFLAGS% hello.mpp hello.cpp

"%clcmd%" %CFLAGS% module02.cpp

