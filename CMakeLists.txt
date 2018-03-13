cmake_minimum_required(VERSION 2.8)

set ( PROJECT_NAME restapi )

project( ${PROJECT_NAME} )
set ( ${PROJECT_NAME}_HOME ${CMAKE_CURRENT_SOURCE_DIR} )
message("SourceDir: " ${${PROJECT_NAME}_HOME} )

if ( CMAKE_COMPILER_IS_GNUCXX )
   set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive" )
endif ()

# set compiler support for C++11 standard
option(USE_CXX11_STD "Product should be build with C++11 compiler option enabled" ON)

if(USE_CXX11_STD)
    set(CMAKE_CXX_STANDARD 11)
endif()

if(MSVC)
	add_definitions(-D_CONSOLE)
else()
    # GCC or Clang
endif()

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

include_directories( ${ADALINE_EXAMPLE1} PRIVATE ${PROJECT_SOURCE_DIR}/src )

# build target
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/${ADALINE_EXAMPLE1}/${ADALINE_EXAMPLE1}.cpp ${SRC_FILES} ${HDR_FILES})

add_custom_command (
    TARGET ${ADALINE_EXAMPLE1}
    POST_BUILD
    COMMAND ${ADALINE_EXAMPLE1}
    COMMENT "Execute ${ADALINE_EXAMPLE1}"
)