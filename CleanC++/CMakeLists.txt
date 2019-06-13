cmake_minimum_required(VERSION 3.2)
if(CMAKE_VERSION VERSION_LESS 3.2)
  return()
endif()

set(proname "CleanC++")

project("CleanC++")

#add_definitions(/std:c++17)

add_executable(${proname} 
  src/CleanC++01.cpp
  src/CleanC++02.h
  src/CleanC++02.cpp
  src/CleanC++03.cpp
  src/CleanC++04.cpp
  src/CleanC++05.cpp
  src/CleanC++06.cpp
  src/CleanC++07.cpp
  src/CleanC++08.cpp
  src/CleanC++09.cpp
  src/CleanC++.main.cpp)


if (WIN32)
  if(MSVC)
    # 增加一些编译属性的方法
    target_compile_options(${proname} PRIVATE
        #/MP
        #/MX
        #/wd4996
        #/wd4503
		/std:c++17
        )
  endif()
  # g++ 
  # SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors")
endif()