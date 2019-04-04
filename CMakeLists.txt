cmake_minimum_required (VERSION 2.6)

project (Homework3)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")

SET(
	LIB_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/PhysicalNumber.cpp
)


SET(
	TESTER_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/PhysicalNumberDemo.cpp 
)

add_library(MeasureLib STATIC ${LIB_SOURCES})

add_executable(tester ${TESTER_SOURCES})

target_link_libraries(tester pthread MeasureLib)
