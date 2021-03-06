cmake_minimum_required(VERSION 2.8)

set ( PROJECT_NAME restapi )
set ( TEST_APPLICATION test_application )

project( ${PROJECT_NAME} )
set ( ${PROJECT_NAME}_HOME ${CMAKE_CURRENT_SOURCE_DIR} )
message("SourceDir: " ${${PROJECT_NAME}_HOME} )

if ( CMAKE_COMPILER_IS_GNUCXX )
   set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive" )
endif ()

# set where to find additional cmake modules if any
# comment it out if not required
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
message ( "CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}" )

# set compiler support for C++11 standard
option(USE_CXX11_STD "Product should be build with C++11 compiler option enabled" ON)

if(USE_CXX11_STD)
    set(CMAKE_CXX_STANDARD 11)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

if(MSVC)
	add_definitions(-D_CONSOLE)
else()
    # GCC or Clang
endif()

set ( THREADS_USE_PTHREADS_WIN32 TRUE )
find_package(Threads REQUIRED)

message ( "THREADS_PTHREADS_INCLUDE_DIR = ${THREADS_PTHREADS_INCLUDE_DIR}" )
message ( "THREADS_PTHREADS_WIN32_LIBRARY = ${THREADS_PTHREADS_WIN32_LIBRARY}" )
message ( "CMAKE_THREAD_LIBS_INIT = ${CMAKE_THREAD_LIBS_INIT}" )

find_package ( CPR REQUIRED )
if ( CPR_FOUND )
message ( STATUS "CPR_INCLUDE_DIRS = ${CPR_INCLUDE_DIRS}" )
message ( STATUS "CPR_LIBRARIES = ${CPR_LIBRARIES}" )
include_directories ( ${CPR_INCLUDE_DIRS} )
endif ( CPR_FOUND )

find_package(JSONCPP REQUIRED)
if ( JSONCPP_FOUND )
message ( STATUS "JSONCPP_INCLUDE_DIRS = ${JSONCPP_INCLUDE_DIRS}" )
message ( STATUS "JSONCPP_LIBRARIES = ${JSONCPP_LIBRARIES}" )
include_directories ( ${CPR_INCLUDE_DIRS} )
endif ( JSONCPP_FOUND )

# use standard file endings - rename to cxx if needed
set(CXX_SRC_EXT_PATTERN ".cpp")
set(C_SRC_EXT_PATTERN ".c")
set(HDR_EXT_PATTERN ".h")
set(HXX_EXT_PATTERN ".hpp")

# get all *.cpp files from src to build target
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*${CXX_SRC_EXT_PATTERN} ${PROJECT_SOURCE_DIR}/src/*${C_SRC_EXT_PATTERN})
file(GLOB HDR_FILES ${PROJECT_SOURCE_DIR}/src/*${HDR_EXT_PATTERN} ${PROJECT_SOURCE_DIR}/src/*${HXX_EXT_PATTERN})
# makes source and header files group
source_group("Source Files" FILES ${SRC_FILES})
source_group("Header Files" FILES ${HDR_FILES})

add_library(${PROJECT_NAME} ${SRC_FILES} ${HDR_FILES})

target_include_directories( ${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src )
#target_link_libraries(${PROJECT_NAME} PRIVATE ${JSONCPP_LIBRARIES})

# get all *.cpp files from src to build target
file(GLOB TEST_APPLICATION_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*${C_SRC_EXT_PATTERN} ${PROJECT_SOURCE_DIR}/test/*${CXX_SRC_EXT_PATTERN})
file(GLOB TEST_APPLICATION_HDR_FILES ${PROJECT_SOURCE_DIR}/test/*${HDR_EXT_PATTERN} ${PROJECT_SOURCE_DIR}/test/*${HXX_EXT_PATTERN})
# makes source and header files group
source_group("Source Files" FILES ${TEST_APPLICATION_SRC_FILES})
source_group("Header Files" FILES ${TEST_APPLICATION_HDR_FILES})

add_executable(${TEST_APPLICATION} ${TEST_APPLICATION_SRC_FILES} ${TEST_APPLICATION_HDR_FILES})
target_include_directories( ${TEST_APPLICATION} PRIVATE ${PROJECT_SOURCE_DIR}/src )
target_link_libraries(${TEST_APPLICATION} ${PROJECT_NAME} ${CPR_LIBRARIES} ${JSONCPP_LIBRARIES} ${THREADS_PTHREADS_WIN32_LIBRARY})

#install(TARGETS ${PROJECT_NAME}
#    RUNTIME DESTINATION bin
#    LIBRARY DESTINATION lib
#    ARCHIVE DESTINATION lib
#)

# build target
#add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/${ADALINE_EXAMPLE1}/${ADALINE_EXAMPLE1}.cpp ${SRC_FILES} ${HDR_FILES})

#add_custom_command (
#    TARGET ${ADALINE_EXAMPLE1}
#    POST_BUILD
#    COMMAND ${ADALINE_EXAMPLE1}
#    COMMENT "Execute ${ADALINE_EXAMPLE1}"
#)