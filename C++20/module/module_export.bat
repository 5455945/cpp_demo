@echo off

rem 这里要根据你编译的x86/x64；relase/debug选择对应目录下的cl.exe
rem set clcmd=D:\install\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.24.28314\bin\Hostx64\x64\cl.exe
rem 在vs中自己会找到准确的cl.exe版本，不需要特别指定
set clcmd=cl.exe

rem 如果module中引用了标准库，需要指定/module:stdIfcDir
rem /experimental:module /module:stdIfcDir "$(VCToolsInstallDir_160)ifc\$(PlatformTarget)"
rem $(VCToolsInstallDir_160)=D:\install\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.24.28314\
rem $(PlatformTarget)=x64
set target=%1%
if "%target%"=="" set target=x64
@echo %target%
rem 根据自己的实际目录设置
set stdIfcDir="D:\install\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.24.28314\ifc\%target%"

rem 指定代码生成的运行库md mdd mt mtd(动态库 动态调试库 静态库 静态调试库)
rem 本bat的第一个参数指定是否是debug版本，如果是debug版本，第一个参数是 d
set rundll=%2%
if "%rundll%"=="" set rundll=MD

rem 显示运行时库参数
@echo %rundll%

set CFLAGS=/experimental:module /std:c++latest /EHsc /%rundll% /c /module:stdIfcDir %stdIfcDir% /module:export 

rem cl.exe /experimental:module /std:c++latest /EHsc /MD /c /module:stdIfcDir "D:\install\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.24.28314\ifc\x64" /module:export module01.cpp 
"%clcmd%" %CFLAGS% module01.cpp

rem "%clcmd%" %CFLAGS% 模块文件
"%clcmd%" %CFLAGS% hello.mpp hello.cpp

"%clcmd%" %CFLAGS% module02.cpp

