cmake_minimum_required (VERSION 2.6)
project (awaituv)

if (MSVC)

##find_package(curl REQUIRED)

find_path(LIBUV_INCLUDE_DIR uv.h HINTS D:\\DEV\\GitHub\\vcpkg\\packages\\libuv_x86-windows-static\\include)
include_directories(${LIBUV_INCLUDE_DIR})
find_library(LIBUVLIBRARY libuv.lib HINTS D:\\DEV\\GitHub\\vcpkg\\packages\\libuv_x86-windows-static\\lib)
link_libraries(${LIBUVLIBRARY})
link_directories( D:\\DEV\\GitHub\\vcpkg\\packages\\libuv_x86-windows-static\\lib )


find_path(CURL_INCLUDE_DIR curl/curl.h D:\\DEV\\GitHub\\vcpkg\\packages\\curl_x86-windows-static\\include)
include_directories(${CURL_INCLUDE_DIR})
find_library(CURLLIBRARY libcurl.lib HINTS D:\\DEV\\GitHub\\vcpkg\\packages\\curl_x86-windows-static\\lib)
link_libraries(${CURLLIBRARY})
link_directories( D:\\DEV\\GitHub\\vcpkg\\packages\\curl_x86-windows-static\\lib )
#find_package(CURL REQUIRED)
#target_link_libraries(main PRIVATE ${CURL_LIBRARIES})
#target_include_directories(main PRIVATE ${CURL_INCLUDE_DIRS})


find_library(SSH2LIBRARY libssh2.lib HINTS D:\\DEV\\GitHub\\vcpkg\\packages\\libssh2_x86-windows-static\\lib)
link_libraries(${SSH2LIBRARY})
link_directories( D:\\DEV\\GitHub\\vcpkg\\packages\\libssh2_x86-windows-static\\lib )

find_library(ZLIBLIBRARY zlib.lib HINTS D:\\DEV\\GitHub\\vcpkg\\packages\\zlib_x86-windows-static\\lib)
link_libraries(${ZLIBLIBRARY})
link_directories( D:\\DEV\\GitHub\\vcpkg\\packages\\zlib_x86-windows-static\\lib )

find_library(OPENSSLLIBRARY NAMES ssleay32.lib    HINTS D:\\DEV\\GitHub\\vcpkg\\packages\\openssl_x86-windows-static\\lib)
link_libraries(${OPENSSLLIBRARY})
find_library(OPENSSLLIBRARY2 NAMES libeay32.lib    HINTS D:\\DEV\\GitHub\\vcpkg\\packages\\openssl_x86-windows-static\\lib)
link_libraries(${OPENSSLLIBRARY2})
link_directories( D:\\DEV\\GitHub\\vcpkg\\packages\\openssl_x86-windows-static\\lib )


link_libraries(ws2_32.lib Iphlpapi.lib Psapi.lib Userenv.lib Wldap32.lib Crypt32.lib)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -await")
link_libraries (libuv libcurl)
endif()

if(UNIX)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread -fcoroutines-ts")
find_package(CURL REQUIRED)
link_libraries(${CURL_LIBRARIES})
link_libraries (libuv.a)
endif()

set (CMAKE_CXX_STANDARD 14)

include_directories(inc)
add_subdirectory(samples)
