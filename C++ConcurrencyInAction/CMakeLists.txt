cmake_minimum_required(VERSION 3.0)

set(Concurrency "C++11ConcurrencyDemo")

project("C++11_Concurrency")

#add_definitions(/std:c++11)
if(CMAKE_VERSION VERSION_LESS 3.1)
  return()
endif()

SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
SET(gConcurrency01 Concurrency01.h Concurrency01.01.cpp)
SET(gConcurrency02 
Concurrency02.h 
Concurrency02.01.cpp
Concurrency02.02.cpp 
Concurrency02.03.cpp
Concurrency02.04.cpp
Concurrency02.05.cpp
Concurrency02.06.cpp
Concurrency02.07.cpp
Concurrency02.08.cpp)
SET(gConcurrency03 
Concurrency03.h
Concurrency03.01.cpp
Concurrency03.02.cpp 
Concurrency03.03.cpp 
Concurrency03.04.cpp 
Concurrency03.05.cpp 
Concurrency03.06.cpp 
Concurrency03.07.cpp 
Concurrency03.08.cpp 
Concurrency03.09.cpp 
Concurrency03.10.cpp 
Concurrency03.11.cpp 
Concurrency03.12.cpp 
Concurrency03.13.cpp 
Concurrency03.14.cpp
Concurrency03.15.cpp)
SET(gConcurrency04 
Concurrency04.h
Concurrency04.01.cpp
Concurrency04.02.cpp
Concurrency04.03.cpp
Concurrency04.04.cpp
Concurrency04.05.cpp
Concurrency04.06.cpp
Concurrency04.07.cpp
Concurrency04.08.cpp
Concurrency04.09.cpp
Concurrency04.10.cpp
Concurrency04.11.cpp
Concurrency04.12.cpp
Concurrency04.13.cpp
Concurrency04.14.cpp
Concurrency04.15.cpp
Concurrency04.16.cpp)
SET(gConcurrency05 
Concurrency05.h
Concurrency05.01.cpp
Concurrency05.02.cpp
Concurrency05.03.cpp
Concurrency05.04.cpp
Concurrency05.05.cpp
Concurrency05.06.cpp
Concurrency05.07.cpp
Concurrency05.08.cpp
Concurrency05.09.cpp
Concurrency05.10.cpp
Concurrency05.11.cpp
Concurrency05.12.cpp
Concurrency05.13.cpp)
SET(gConcurrency06 
Concurrency06.h
Concurrency06.01.cpp
Concurrency06.02.cpp
Concurrency06.03.cpp
Concurrency06.04.cpp
Concurrency06.05.cpp
Concurrency06.06.cpp
Concurrency06.07.cpp
Concurrency06.08.cpp
Concurrency06.09.cpp
Concurrency06.10.cpp
Concurrency06.11.cpp
Concurrency06.12.cpp
Concurrency06.13.cpp)
SET(gConcurrency07 
Concurrency07.h
Concurrency07.01.cpp
Concurrency07.02.cpp
Concurrency07.03.cpp
Concurrency07.04.cpp
Concurrency07.05.cpp
Concurrency07.06.cpp
Concurrency07.07.cpp
Concurrency07.08.cpp
Concurrency07.09.cpp
Concurrency07.10.cpp
Concurrency07.11.cpp
Concurrency07.12.cpp
Concurrency07.13.cpp
Concurrency07.14.cpp
Concurrency07.15.cpp
Concurrency07.16.cpp
Concurrency07.17.cpp
Concurrency07.18.cpp
Concurrency07.19.cpp
Concurrency07.20.cpp
Concurrency07.21.cpp)
SET(gConcurrency08 
Concurrency08.h
Concurrency08.01.cpp
Concurrency08.02.cpp
Concurrency08.03.cpp
Concurrency08.04.cpp
Concurrency08.05.cpp
Concurrency08.06.cpp
Concurrency08.07.cpp
Concurrency08.08.cpp
Concurrency08.09.cpp
Concurrency08.10.cpp
Concurrency08.11.cpp
Concurrency08.12.cpp
Concurrency08.13.cpp)
SET(gConcurrency09 
Concurrency09.h
Concurrency09.01.cpp
Concurrency09.02.cpp
Concurrency09.03.cpp
Concurrency09.04.cpp
Concurrency09.05.cpp
Concurrency09.06.cpp
Concurrency09.07.cpp
Concurrency09.08.cpp
Concurrency09.09.cpp
Concurrency09.10.cpp
Concurrency09.11.cpp
Concurrency09.12.cpp
Concurrency09.13.cpp)
SET(gConcurrency10 Concurrency10.h Concurrency10.01.cpp)
Set(gAppendixA AppendixA.h
AppendixA01.cpp
AppendixA02.cpp
AppendixA03.cpp
AppendixA04.cpp)
Set(gAppendixC AppendixC.h
AppendixC01.cpp
AppendixC02.cpp
AppendixC03.cpp
AppendixC04.cpp
AppendixC05.cpp
AppendixC06.cpp
AppendixC07.cpp
AppendixC08.cpp
AppendixC09.cpp
AppendixC10.cpp)

SOURCE_GROUP(Concurrency01 FILES ${gConcurrency01})
SOURCE_GROUP(Concurrency02 FILES ${gConcurrency02})
SOURCE_GROUP(Concurrency03 FILES ${gConcurrency03})
SOURCE_GROUP(Concurrency04 FILES ${gConcurrency04})
SOURCE_GROUP(Concurrency05 FILES ${gConcurrency05})
SOURCE_GROUP(Concurrency06 FILES ${gConcurrency06})
SOURCE_GROUP(Concurrency07 FILES ${gConcurrency07})
SOURCE_GROUP(Concurrency08 FILES ${gConcurrency08})
SOURCE_GROUP(Concurrency09 FILES ${gConcurrency09})
SOURCE_GROUP(Concurrency10 FILES ${gConcurrency10})
SOURCE_GROUP(AppendixA FILES ${gAppendixA})
SOURCE_GROUP(AppendixC FILES ${gAppendixC})

add_executable(${Concurrency}
${gConcurrency01} 
${gConcurrency02} 
${gConcurrency03} 
${gConcurrency04} 
${gConcurrency05} 
${gConcurrency06} 
${gConcurrency07} 
${gConcurrency08} 
${gConcurrency09} 
${gConcurrency10} 
${gAppendixA} 
${gAppendixC} 
ConcurrencyMain.cpp)
