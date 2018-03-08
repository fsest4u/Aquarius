cmake_minimum_required(VERSION 3.0)

project(3rdparty)

# Note: All files in the cmake dir will be included as if they were in this file.
#       The paths in each .cmake file are relative to this directory not the
#       cmake directory.

IF(MSVC)
    add_definitions( /D_CRT_SECURE_NO_WARNINGS /DUNICODE /D_UNICODE /Zc:wchar_t-  )
ENDIF()

if( NOT USE_SYSTEM_LIBS OR NOT ZLIB_FOUND )
    MESSAGE(STATUS "Using Bundled ZLIB")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/zlib.cmake)
else ()
    MESSAGE(STATUS "Using System ZLIB")
endif()

if( NOT USE_SYSTEM_LIBS OR NOT MINIZIP_FOUND )
    MESSAGE(STATUS "Using Bundled MiniZip")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/minizip.cmake)
else ()
    MESSAGE(STATUS "Using System MiniZip")
endif()

if( NOT USE_SYSTEM_LIBS OR NOT VIRGO_FOUND )
    MESSAGE(STATUS "Using Bundled Virgo")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/virgo.cmake)
else ()
    MESSAGE(STATUS "Using System Virgo")
endif()

if( NOT USE_SYSTEM_LIBS OR NOT HTTPSERVER_FOUND )
    MESSAGE(STATUS "Using Bundled HttpServer")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/httpserver.cmake)
else ()
    MESSAGE(STATUS "Using System HttpServer")
endif()

if( NOT USE_SYSTEM_LIBS OR NOT PISCES_FOUND )
    MESSAGE(STATUS "Using Bundled Pisces")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/pisces.cmake)
else ()
    MESSAGE(STATUS "Using System Pisces")
endif()

if (SYSTEM_LIBS_REQUIRED)
    if (NOT ZLIB_FOUND OR NOT MINIZIP_FOUND OR NOT VIRGO_FOUND OR NOT HTTPSERVER_FOUND OR NOT PISCES_FOUND )
        MESSAGE(FATAL_ERROR "Could not find all required system libraries...")
    endif()
endif()
