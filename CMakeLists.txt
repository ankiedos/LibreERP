cmake_minimum_required(VERSION 3.22.1)
project(LibreERP VERSION 0.1.0)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE LIB_FILES lib/src/*.cpp)
add_library(libreerp-utils STATIC ${LIB_FILES})
target_include_directories(libreerp-utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/include /usr/include/mysql)


find_library(SOCI_CORE soci_core REQUIRED)
find_library(SOCI_MYSQL soci_mysql REQUIRED)
find_library(DL dl REQUIRED)
find_library(MYSQL_CLIENT mysqlclient REQUIRED)


file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(libreerp ${SRC_FILES})
target_include_directories(libreerp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include /usr/include/mysql)
target_link_libraries(libreerp
PUBLIC libreerp-utils ${SOCI_CORE} ${SOCI_MYSQL} ${DL} ${MYSQL_CLIENT})