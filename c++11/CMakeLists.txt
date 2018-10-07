cmake_minimum_required(VERSION 3.0)

set(proname08 "c++11_demo08")
set(proname09 "c++11_demo09")
set(proname10 "c++11_demo10")
set(proname11 "c++11_demo11")
set(proname12 "c++11_demo12")
set(proname13 "c++11_demo13")
set(proname14 "c++11_demo14")
set(proname15 "c++11_demo15")
set(proname16 "c++11_demo16")

project(${proname08})

add_definitions(/std:c++11)
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

add_executable (${proname08} ${incs} ${src_tests} ${src_mains})


add_executable(${proname09} thread_pool/SyncQueue.hpp thread_pool/ThreadPool.hpp thread_pool_test/ThreadPoolTest.cpp)

#add_executable(${proname10} aop/aspect.hpp aop_test/aop_test.cpp)

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
	
# result_of error
#add_executable(${proname14} linq/LinqCpp.hpp linq_test/linq_test.cpp)

add_executable(${proname15} 
    task_cpp/ParallelAlgrithm.hpp
	task_cpp/Task.hpp
	task_cpp/TaskCpp.h
	task_cpp/TaskGroup.hpp
	task_cpp/When_All_Any.hpp
	task_cpp_test/task_cpp_test.cpp
	)
	
set(asio_path "D:/install/lib/boost_1_68_0/msvc141/include/boost-1_68")

include_directories(${asio_path})
LINK_DIRECTORIES("D:/install/lib/boost_1_68_0/msvc141/lib")

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
  endif()
endif()


	