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

if (WIN32)
  if(MSVC)
    # 增加一些编译属性的方法
	# add_compiler_options(/std:c++latest)
	target_compile_options(${proname01} PRIVATE
	    # 增加对c++最新标准的支持
	    /std:c++latest
		/std:c17
		# 使用实验属性 module
	    /experimental:module
		# 消除两个警告
		/wd4819
		/wd4828
		# fmt库文件需要utf-8格式
		/utf-8
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
		/permissive-
		#/exportHeader
		# 消除两个警告
		/wd4819
		/wd4828
		# fmt库文件需要utf-8格式
		/utf-8
	)
  endif()
  # g++ 
  # SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors")
endif()
