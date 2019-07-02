cmake_minimum_required(VERSION 3.2)
if(CMAKE_VERSION VERSION_LESS 3.2)
  return()
endif()

set(proname "OpenMP")

project("OpenMP")

#add_definitions(/std:c++17)

add_executable(${proname} 
  src/OpenMP01.01.h
  src/OpenMP01.01.cpp
  src/OpenMP01.02.h
  src/OpenMP01.02.cpp
  src/OpenMP01.03.h
  src/OpenMP01.03.cpp
  src/OpenMP01.04.h
  src/OpenMP01.04.cpp
  src/OpenMP01.05.h
  src/OpenMP01.05.cpp
  src/OpenMP.main.cpp)


if (WIN32)
  if(MSVC)
    # 增加一些编译属性的方法
    target_compile_options(${proname} PRIVATE
	    /openmp
        #/MP
        #/MX
        #/wd4996
        #/wd4503
		#/std:c++17
        )
  endif()
  # g++ 
  # SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors")
endif()