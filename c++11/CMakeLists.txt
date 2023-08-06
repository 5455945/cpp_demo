cmake_minimum_required(VERSION 3.0)

set(proname01 "c++11_demo01")
set(proname02 "c++11_demo02")
set(proname03 "c++11_demo03")
set(proname04 "c++11_demo04")
set(proname05 "c++11_demo05")
set(proname06 "c++11_demo06")
set(proname07 "c++11_demo07")
set(proname08 "c++11_demo08")
set(proname09 "c++11_demo09")
set(proname10 "c++11_demo10")
set(proname11 "c++11_demo11")
set(proname12 "c++11_demo12")
set(proname13 "c++11_demo13")
set(proname14 "c++11_demo14")
set(proname15 "c++11_demo15")
set(proname16 "c++11_demo16")
set(proname17 "C++11_2013")
set(proname18 "C++11_timer")

project("C++11_demo")

#add_definitions(/std:c++11)
if(CMAKE_VERSION VERSION_LESS 3.1)
  return()
endif()

set(incs
    pattern/Command.hpp
	pattern/ObjectPool.hpp
	pattern/Observer.hpp
	pattern/Singleton.hpp
	pattern/visitor.hpp
	pattern/NonCopyable.hpp
)

set (src_tests
    pattern_test/Observer-test.cpp
	pattern_test/Singleton-test.cpp
	pattern_test/visitor-test.cpp
	pattern_test/Command-test.cpp
	pattern_test/ObjectPool-test.cpp
)

set (src_mains
    test_main.h
    test_main.cpp
)


include_directories("pattern")

add_executable(${proname01} 01/01-01.h 01/01-01.cpp 
01/01-02.h 01/01-02.cpp
01/01-03.h 01/01-03.cpp
01/01-04.h 01/range.hpp 01/01-04.cpp
01/01-05.h 01/01-05.cpp
01/01-06.h 01/01-06.cpp
01/01-07.h 01/01-07.cpp
01/01-main.cpp)

add_executable(${proname02} 02/02-01.h 02/02-01.cpp 02/02-main.cpp)

add_executable(${proname03} 03/03-01.h 03/03-01.cpp 
03/03-02.h 03/03-02.cpp
03/03-03.h 03/03-03.cpp
03/Optional.hpp
03/Lazy.hpp
03/Lazy17.hpp
03/DllParser.hpp
03/LambdaChain.hpp
03/function_traits.hpp
03/ScopeGuard.hpp
03/03-main.cpp)

add_executable(${proname04} 04/04-01.h 04/04-01.cpp 04/04-main.cpp)

add_executable(${proname05} 05/05-01.h 05/05-01.cpp
  05/05-02.h 05/05-02.cpp
  05/05-03.h 05/05-03.cpp
  05/05-04.h 05/05-04.cpp
  05/05-05.h 05/05-05.cpp
  05/05-06.h 05/05-06.cpp
  05/05-07.h 05/05-07.cpp
  05/05-main.cpp)

add_executable(${proname06} 06/06-01.h 06/06-01.cpp 06/06-main.cpp)

add_executable(${proname07} 07/07-01.h 07/07-01.cpp 07/07-main.cpp)

add_executable (${proname08} ${incs} ${src_tests} ${src_mains} pattern_test/Singleton01.hpp )


add_executable(${proname09} thread_pool/SyncQueue.hpp thread_pool/ThreadPool.hpp thread_pool_test/ThreadPoolTest.cpp)

add_executable(${proname10} aop/aspect.hpp aop/HelloProxy.h aop_test/aop_test.cpp)

add_executable(${proname11} ioc/ioc.hpp ioc_test/ioc_test.cpp)

add_executable(${proname12} message_bus/MessageBus.hpp pattern/function_traits.hpp message_bus_test/message_bus_test.cpp)

include_directories("third_party/sqlite")
include_directories("third_party")
add_executable(${proname13} 
    third_party/rapidjson/document.h
	third_party/rapidjson/rapidjson.h
	third_party/rapidjson/reader.h
	third_party/rapidjson/stringbuffer.h
	third_party/rapidjson/writer.h
	third_party/sqlite/sqlite3.c
	third_party/sqlite/sqlite3.h
	third_party/sqlite/sqlite3ext.h
	SmartDB/Define.h
	SmartDB/JsonCpp.hpp
	SmartDB/SmartDB.hpp
	SmartDB_test/SmartDB_test.cpp
	)

add_executable(${proname15} 
    task_cpp/ParallelAlgrithm.hpp
	task_cpp/Task.hpp
	task_cpp/TaskCpp.h
	task_cpp/TaskGroup.hpp
	task_cpp/When_All_Any.hpp
	task_cpp_test/task_cpp_test.cpp
	)

# result_of error
set(asio_path "D:/install/boost/boost_1_70_0/msvc141/include/boost-1_70")

include_directories(${asio_path})
LINK_DIRECTORIES("D:/install/boost/boost_1_70_0/msvc141/lib")
add_executable(${proname14} linq/LinqCpp.hpp linq_test/linq_test.cpp)

add_executable(${proname16}_client 
    asio_client/asio_client.hpp
	asio_client/asio_client_test.cpp
	asio_server/RWHandler.hpp
	)
	
add_executable(${proname16}_server
    asio_server/asio_server.hpp
	asio_server/asio_server_test.cpp
	asio_server/Message.hpp
	asio_server/RWHandler.hpp
	)
	
add_executable(${proname17} 
  C++11_0/C++11.02.h C++11_0/C++11.02.cpp
  C++11_0/C++11.03.h C++11_0/C++11.03.cpp
  C++11_0/C++11.04.h C++11_0/C++11.04.cpp
  C++11_0/C++11.05.h C++11_0/C++11.05.cpp
  C++11_0/C++11.06.h C++11_0/C++11.06.cpp
  C++11_0/C++11.07.h C++11_0/C++11.07.cpp
  C++11_0/C++11.main.cpp)

add_executable(${proname18} 
  timer/timer.hpp
  timer/test.cc)


if (WIN32)
  if(MSVC)
    # 增加一些编译属性的方法
    target_compile_options(${proname08} PRIVATE
        #/MP
        #/MX
        /wd4996
        #/wd4503
		#/std:c++14
        )
	#target_compile_options(--std=c++11)
	#add_compile_options(--std=c++11)
	target_compile_options(${proname03} PRIVATE
	    /std:c++17
		)
  endif()
  # g++ 
  # SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-elide-constructors")
endif()


	