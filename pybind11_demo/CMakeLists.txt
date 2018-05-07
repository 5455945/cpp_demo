cmake_minimum_required(VERSION 3.0)

set(proname01 "test01") # test01 被 test03.py调用
set(proname02 "test02") # test01 被 test03.py调用

project("pybind11_demo")

# 需要设置python的头文件目录和libs库目录
set(PYTHON_INCLUDE_DIR "" CACHE PATH "Path to compiled dependencies (e.g. C:/Python36/include)")
set(PYTHON_LIB_DIR "" CACHE PATH "Path to compiled dependencies (e.g. C:/Python36/libs)")


if(CMAKE_VERSION VERSION_LESS 3.1)
  return()
endif()

include_directories(${PYTHON_INCLUDE_DIR})
include_directories("3rdparty/pybind11/include")

set(srcs
    src/test01.cpp
)

LINK_DIRECTORIES(${PYTHON_LIB_DIR})

# 生成动态链接库类型文件, .pyd
add_library (${proname01} SHARED ${srcs})
if (WIN32)
  if(MSVC)
    # 增加一些编译属性的方法
    target_compile_options(${proname01} PRIVATE
        #/MP
        #/MX
        /wd4996
        #/wd4503
        )
  endif()
endif()


if (WIN32)
	#target_link_libraries (${proname01} debug "python35_d.lib") # debug版本link _d.lib会出错
	#target_link_libraries (${proname02} debug "python35.lib")   # debug版本link 发布版本正常
	#target_link_libraries (${proname01} optimized "python36.lib")
	target_link_libraries (${proname01} "python36.lib")
	
	# 拷贝文件到生成目录, $(Configuration)是在vs编译时才解析的
    add_custom_command(TARGET ${proname01}
        POST_BUILD
        COMMAND copy /y "\"${CMAKE_SOURCE_DIR}\\src\\test04.py\"" "\"${CMAKE_BINARY_DIR}\\\$(Configuration)\\test04.py\"")
endif()


if (WIN32)
    set_target_properties( ${proname01} PROPERTIES SUFFIX ".pyd")
else()
    set_target_properties( ${proname01} PROPERTIES SUFFIX ".so")
endif()

# proname02
include_directories(${PYTHON_INCLUDE_DIR})
include_directories("3rdparty/pybind11/include")

set(srcs
    src/test02.cpp
)

add_executable (${proname02} ${srcs})
LINK_DIRECTORIES(${PYTHON_LIB_DIR})


if (WIN32)
	#target_link_libraries (${proname01} debug "python35_d.lib") # debug版本link _d.lib会出错
	#target_link_libraries (${proname02} debug "python35.lib")   # debug版本link 发布版本正常
	#target_link_libraries (${proname02} optimized "python35.lib")
	target_link_libraries (${proname02} "python36.lib")
	
	# 拷贝文件到生成目录, $(Configuration)是在vs编译时才解析的
    add_custom_command(TARGET ${proname02}
        POST_BUILD
        COMMAND copy /y "\"${CMAKE_SOURCE_DIR}\\src\\test03.py\"" "\"${CMAKE_BINARY_DIR}\\\$(Configuration)\\test03.py\"")
endif()
