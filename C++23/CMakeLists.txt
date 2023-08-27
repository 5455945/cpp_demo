cmake_minimum_required(VERSION 3.0)

#cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug 
#cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
#cmake --build build
#:: cd build && cmake --build .

set(proname01 "c++23_demo01")
set(proname02 "c++23_demo02")


project("C++23_demo")

#add_definitions(/std:c++11)
if(CMAKE_VERSION VERSION_LESS 3.1)
  return()
endif()

# 以相对路径为所有项目 添加fmt的头文件目录
#include_directories("./fmt/include")

# 添加一个项目
add_executable(${proname01}
01/01-01.h 01/01-01.cpp
01/01-02.h 01/01-02.cpp
01/01-03.h 01/01-03.cpp
01/01-04.h 01/01-04.cpp
01/01-05.h 01/01-05.cpp
01/01-06.h 01/01-06.cpp
01/01-main.cpp)
# 为${proname01}增加相对路径的私有头文件目录
target_include_directories(${proname01} PRIVATE "./fmt/include")

add_executable(${proname02}
02/02-01.h 02/02-01.cpp
02/02-02.h 02/02-02.cpp
02/02-03.h 02/02-03.cpp
02/02-04.h 02/02-04.cpp
02/02-05.h 02/02-05.cpp
02/02-06.h 02/02-06.cpp
02/02-07.h 02/02-07.cpp
02/02-08.h 02/02-08.cpp
02/02-09.h 02/02-09.cpp
02/02-10.h 02/02-10.cpp
02/02-11.h 02/02-11.cpp
02/02-12.h 02/02-12.cpp
02/02-13.h 02/02-13.cpp
02/02-14.h 02/02-14.cpp
02/02-15.h 02/02-15.cpp
02/02-16.h 02/02-16.cpp
02/02-17.h 02/02-17.cpp
02/02-18.h 02/02-18.cpp
02/02-19.h 02/02-19.cpp
02/02-20.h 02/02-20.cpp
02/02-21.h 02/02-21.cpp
02/02-22.h 02/02-22.cpp
02/02-23.h 02/02-23.cpp
02/02-24.h 02/02-24.cpp
02/02-25.h 02/02-25.cpp
02/02-26.h 02/02-26.cpp
02/02-main.cpp
)

#target_sources(${proname02}
#  PRIVATE
#  FILE_SET CXX_MODULES FILES
#  ${PROJECT_BINARY_DIR}/stdxx/std.ixx
#  PRIVATE
#  demo.cpp
#)
   #file(COPY
   ## you don't want to hardcode the path here in a real-world project,
   ## but you get the idea
   ##"C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.36.32532/modules/std.ixx"
   #"%VCToolsInstallDir\modules\std.ixx"
   #DESTINATION
   #${PROJECT_BINARY_DIR}/stdxx
   #)
#message(status, "%VCToolsInstallDir%\modules\std.ixx")
#MESSAGE(STATUS "VCToolsInstallDir dir: $ENV{VSINSTALLDIR}")
#MESSAGE(STATUS "VCToolsInstallDir dir: $ENV{LOCALAPPDATA}")
#// <BuildStlModules>true</BuildStlModules>
# enablemodules "yes"
# buildstlmodules "yes"
# enablemodules "no"
# buildstlmodules "no"
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (WIN32)
  if(MSVC)
    get_filename_component(vs_bin_path "${CMAKE_LINKER}" DIRECTORY)
	message(status, "vs_bin_path:  ${vs_bin_path}")
    # 增加一些编译属性的方法
	# add_compiler_options(/std:c++latest)
	### add_compiler_options(COMPILE_FEATURES, buildstlmodules "yes")
	###set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)
	target_compile_options(${proname01} PRIVATE
	    # 增加对c++最新标准的支持
	    /std:c++latest
		/std:c17
		# 使用实验属性 module
	    /experimental:module
		/permissive-
		# 消除两个警告
		/wd4819
		/wd4828
		# fmt库文件需要utf-8格式
		/utf-8
	)
    add_custom_command(TARGET ${proname01}
	  PRE_BUILD
	  COMMAND echo cl /std:c++latest /EHsc /nologo /W4 /MTd /c "${vs_bin_path}\\..\\..\\..\\modules\\std.ixx" "${vs_bin_path}\\..\\..\\..\\modules\\std.compat.ixx"
	  COMMAND cl /std:c++latest /EHsc /nologo /W4 /MTd /c "${vs_bin_path}\\..\\..\\..\\modules\\std.ixx" "${vs_bin_path}\\..\\..\\..\\modules\\std.compat.ixx"
	  #WORKING_DIRECTORY .
      COMMENT "cl /std:c++latest /EHsc /nologo /W4 /MTd /c \"%VCToolsInstallDir%\\modules\\std.ixx\" \"%VCToolsInstallDir%\\modules\\std.compat.ixx\""
    )

	#set(CMAKE_CXX_STANDARD 23)
	# Set the startup project .
	if (NOT ${CMAKE_VERSION} VERSION_LESS "3.6.0")
	  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${proname02})
	endif ()
	target_compile_options(${proname02} PRIVATE
	    # 增加对c++最新标准的支持
	    /std:c++latest
		/std:c17
		# 使用实验属性 module
	    /experimental:module
		#/c
		/permissive-
		#/exportHeader
		# 消除两个警告
		/wd4819
		/wd4828
		# fmt库文件需要utf-8格式
		/utf-8
		#buildstlmodules:"yes"
	)
    add_custom_command(TARGET ${proname02}
	  PRE_BUILD
	  COMMAND echo cl /std:c++latest /EHsc /nologo /W4 /MTd /c "${vs_bin_path}\\..\\..\\..\\modules\\std.ixx" "${vs_bin_path}\\..\\..\\..\\modules\\std.compat.ixx"
	  COMMAND cl /std:c++latest /EHsc /nologo /W4 /MTd /c "${vs_bin_path}\\..\\..\\..\\modules\\std.ixx" "${vs_bin_path}\\..\\..\\..\\modules\\std.compat.ixx"
	  #WORKING_DIRECTORY .
      COMMENT "cl /std:c++latest /EHsc /nologo /W4 /MTd /c \"%VCToolsInstallDir%\\modules\\std.ixx\" \"%VCToolsInstallDir%\\modules\\std.compat.ixx\""
    )
  endif()
  # g++ 
  # SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors")
endif()
