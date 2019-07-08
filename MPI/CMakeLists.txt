cmake_minimum_required(VERSION 3.2)
if(CMAKE_VERSION VERSION_LESS 3.2)
  return()
endif()

set(proname01 "mpi_hello")
set(proname02 "mpi_send_recv")
set(proname03 "mpi_ping_pong")
set(proname04 "mpi_ring")
set(proname05 "mpi_compare_bcast")
set(proname06 "mpi_my_bcast")
set(proname07 "mpi_avg")
set(proname08 "mpi_all_avg")
set(proname09 "MPIBlockingCommunication")
set(proname10 "MPINonBlockingCommunication")
set(proname11 "MPICommunicatorRemoveFirstProcess")
set(proname12 "MPICommunicatorSplitProcess")
set(proname13 "MPISynchronizeTime")
set(proname14 "MPIHelloWorld")
set(proname15 "MPIOpenMPExample")
set(proname16 "MPIRingBroadcast")
set(proname17 "MPIMatrixVectorMultiplication")
set(proname18 "MPIFactorialReduce")
set(proname19 "MPIMinimumReduce")
set(proname20 "MPIMonteCarloPi")
set(proname21 "SequentialVolumeUnionSpheres")
set(proname22 "MPIVolumeUnionSpheres")
set(proname23 "MPIPiApproximationHole")
set(proname24 "GrayString")
set(proname25 "MPIBroadcastRing")
set(proname26 "MPIScatteringRing")
set(proname27 "MPIBroadcastHypercube")
set(proname28 "SequentialQuickSort")

project("mpi")

add_executable(${proname01} src/mpi_hello.cpp)
add_executable(${proname02} src/mpi_send_recv.cpp)
add_executable(${proname03} src/mpi_ping_pong.cpp)
add_executable(${proname04} src/mpi_ring.cpp)
add_executable(${proname05} src/mpi_compare_bcast.cpp)
add_executable(${proname06} src/mpi_my_bcast.cpp)
add_executable(${proname07} src/mpi_avg.cpp)
add_executable(${proname08} src/mpi_all_avg.cpp)
add_executable(${proname09} src/MPIBlockingCommunication.cpp)
add_executable(${proname10} src/MPINonBlockingCommunication.cpp)
add_executable(${proname11} src/MPICommunicatorRemoveFirstProcess.cpp)
add_executable(${proname12} src/MPICommunicatorSplitProcess.cpp)
add_executable(${proname13} src/MPISynchronizeTime.cpp)
add_executable(${proname14} src/MPIHelloWorld.cpp)
add_executable(${proname15} src/MPIOpenMPExample.cpp)
add_executable(${proname16} src/MPIRingBroadcast.cpp)
add_executable(${proname17} src/MPIMatrixVectorMultiplication.cpp)
add_executable(${proname18} src/MPIFactorialReduce.cpp)
add_executable(${proname19} src/MPIMinimumReduce.cpp)
add_executable(${proname20} src/MPIMonteCarloPi.cpp)
add_executable(${proname21} src/SequentialVolumeUnionSpheres.cpp)
add_executable(${proname22} src/MPIVolumeUnionSpheres.cpp)
add_executable(${proname23} src/MPIPiApproximationHole.cpp)
add_executable(${proname24} src/GrayString.cpp)
add_executable(${proname25} src/MPIBroadcastRing.cpp)
add_executable(${proname26} src/MPIScatteringRing.cpp)
add_executable(${proname27} src/MPIBroadcastHypercube.cpp)
add_executable(${proname28} src/SequentialQuickSort.cpp)

if (WIN32)
  if(MSVC)
  	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	  set(_lib_suffix x64)
	else()
	  set(_lib_suffix x86)
	endif()
	
    # 增加一些编译属性的方法
    target_compile_options(${proname01} PRIVATE
	  #/openmp
      #/wd4996
      #/wd4503
	  #/std:c++17
    )
	
	# MPI SDK安装路径
	set(mpi_path "C:/Program Files (x86)/Microsoft SDKs/MPI" CACHE STRING "mpi include path" FORCE)
	include_directories("${mpi_path}/include")
	# 设置一些链接属性
	set_target_properties(${proname01}
        PROPERTIES
        LINK_FLAGS /LIBPATH:"${mpi_path}/Lib/${_lib_suffix}"
    )
	# MPI的静态库引入
	target_link_libraries(${proname01} msmpi)
	
	set_target_properties(${proname02}
        PROPERTIES
        LINK_FLAGS /LIBPATH:"${mpi_path}/Lib/${_lib_suffix}"
    )
	target_link_libraries(${proname02} msmpi)

	set_target_properties(${proname03}
        PROPERTIES
        LINK_FLAGS /LIBPATH:"${mpi_path}/Lib/${_lib_suffix}"
    )
	target_link_libraries(${proname03} msmpi)

	set_target_properties(${proname04}
        PROPERTIES
        LINK_FLAGS /LIBPATH:"${mpi_path}/Lib/${_lib_suffix}"
    )
	target_link_libraries(${proname04} msmpi)
	
	set_target_properties(${proname05}
        PROPERTIES
        LINK_FLAGS /LIBPATH:"${mpi_path}/Lib/${_lib_suffix}"
    )
	target_link_libraries(${proname05} msmpi)
	
	set_target_properties(${proname06}
        PROPERTIES
        LINK_FLAGS /LIBPATH:"${mpi_path}/Lib/${_lib_suffix}"
    )
	target_link_libraries(${proname06} msmpi)
		
	set_target_properties(${proname07}
        PROPERTIES
        LINK_FLAGS /LIBPATH:"${mpi_path}/Lib/${_lib_suffix}"
    )
	target_link_libraries(${proname07} msmpi)
		
	set_target_properties(${proname08}
        PROPERTIES
        LINK_FLAGS /LIBPATH:"${mpi_path}/Lib/${_lib_suffix}"
    )
	target_link_libraries(${proname08} msmpi)
	
	set_target_properties(${proname09}
        PROPERTIES
        LINK_FLAGS /LIBPATH:"${mpi_path}/Lib/${_lib_suffix}"
    )
	target_link_libraries(${proname09} msmpi)
	
	set_target_properties(${proname10}
        PROPERTIES
        LINK_FLAGS /LIBPATH:"${mpi_path}/Lib/${_lib_suffix}"
    )
	target_link_libraries(${proname10} msmpi)
	
	set_target_properties(${proname11}
        PROPERTIES
        LINK_FLAGS /LIBPATH:"${mpi_path}/Lib/${_lib_suffix}"
    )
	target_link_libraries(${proname11} msmpi)
	
	set_target_properties(${proname12}
        PROPERTIES
        LINK_FLAGS /LIBPATH:"${mpi_path}/Lib/${_lib_suffix}"
    )
	target_link_libraries(${proname12} msmpi)

	set_target_properties(${proname13}
        PROPERTIES
        LINK_FLAGS /LIBPATH:"${mpi_path}/Lib/${_lib_suffix}"
    )
	target_link_libraries(${proname13} msmpi)
	
	set_target_properties(${proname14}
        PROPERTIES
        LINK_FLAGS /LIBPATH:"${mpi_path}/Lib/${_lib_suffix}"
    )
	target_link_libraries(${proname14} msmpi)
	
	set_target_properties(${proname15}
        PROPERTIES
        LINK_FLAGS /LIBPATH:"${mpi_path}/Lib/${_lib_suffix}"
    )
	target_link_libraries(${proname15} msmpi)
	
	set_target_properties(${proname16}
        PROPERTIES
        LINK_FLAGS /LIBPATH:"${mpi_path}/Lib/${_lib_suffix}"
    )
	target_link_libraries(${proname16} msmpi)

	set_target_properties(${proname17}
        PROPERTIES
        LINK_FLAGS /LIBPATH:"${mpi_path}/Lib/${_lib_suffix}"
    )
	target_link_libraries(${proname17} msmpi)
	
	set_target_properties(${proname18}
        PROPERTIES
        LINK_FLAGS /LIBPATH:"${mpi_path}/Lib/${_lib_suffix}"
    )
	target_link_libraries(${proname18} msmpi)
	
	set_target_properties(${proname19}
        PROPERTIES
        LINK_FLAGS /LIBPATH:"${mpi_path}/Lib/${_lib_suffix}"
    )
	target_link_libraries(${proname19} msmpi)
	
	set_target_properties(${proname20}
        PROPERTIES
        LINK_FLAGS /LIBPATH:"${mpi_path}/Lib/${_lib_suffix}"
    )
	target_link_libraries(${proname20} msmpi)
	
	set_target_properties(${proname22}
        PROPERTIES
        LINK_FLAGS /LIBPATH:"${mpi_path}/Lib/${_lib_suffix}"
    )
	target_link_libraries(${proname22} msmpi)
	
	set_target_properties(${proname23}
        PROPERTIES
        LINK_FLAGS /LIBPATH:"${mpi_path}/Lib/${_lib_suffix}"
    )
	target_link_libraries(${proname23} msmpi)
	
	set_target_properties(${proname25}
        PROPERTIES
        LINK_FLAGS /LIBPATH:"${mpi_path}/Lib/${_lib_suffix}"
    )
	target_link_libraries(${proname25} msmpi)
	
	set_target_properties(${proname26}
        PROPERTIES
        LINK_FLAGS /LIBPATH:"${mpi_path}/Lib/${_lib_suffix}"
    )
	target_link_libraries(${proname26} msmpi)
	
	set_target_properties(${proname27}
        PROPERTIES
        LINK_FLAGS /LIBPATH:"${mpi_path}/Lib/${_lib_suffix}"
    )
	target_link_libraries(${proname27} msmpi)
  endif()
endif()
