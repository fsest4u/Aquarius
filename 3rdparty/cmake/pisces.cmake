########################################################
#  
#  This is a CMake configuration file.
#  To use it you need CMake which can be 
#  downloaded from here: 
#    http://www.cmake.org/cmake/resources/software.html
#
#########################################################

cmake_minimum_required( VERSION 3.0.0 ) 

project( Pisces )

set( PISCES_LIBRARIES ${PROJECT_NAME} CACHE INTERNAL "" )
set( PISCES_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/src CACHE INTERNAL "" )

#########################################################

# Qt5 packages minimum version 5.4
find_package(Qt5 5.4 COMPONENTS Core Network Svg WebKit WebKitWidgets Widgets Xml XmlPatterns Concurrent PrintSupport LinguistTools)
set(CMAKE_AUTOMOC ON)

set( MAIN_FILES
	${PROJECT_NAME}/src/main.cpp
    ${PROJECT_NAME}/src/PiscesConstants.h
	${PROJECT_NAME}/src/PiscesFeatures.h
)

set( MAINUI_FILES 
	${PROJECT_NAME}/src/mainUI/MainWindow.h
	${PROJECT_NAME}/src/mainUI/MainWindow.cpp
	${PROJECT_NAME}/src/mainUI/FileManager.h
	${PROJECT_NAME}/src/mainUI/FileManager.cpp
)

set( MISC_FILES 
    ${PROJECT_NAME}/src/misc/SettingData.h
    ${PROJECT_NAME}/src/misc/SettingData.cpp
    ${PROJECT_NAME}/src/misc/RequestMapper.h
    ${PROJECT_NAME}/src/misc/RequestMapper.cpp
	${PROJECT_NAME}/src/misc/Utility.h
	${PROJECT_NAME}/src/misc/Utility.cpp
)

set( UI_FILES
	${PROJECT_NAME}/src/formFiles/MainWindow.ui
)

set( QRC_FILES
	${PROJECT_NAME}/src/resFiles/resources.qrc
)

set( RAW_SOURCES ${MAIN_FILES} ${MAINUI_FILES} ${MISC_FILES})

#########################################################

# Runs UIC on specified files
qt5_wrap_ui( UI_FILES_H ${UI_FILES} )
# Runs RCC on specified files
qt5_add_resources( QRC_FILES_CPP ${QRC_FILES} )
# Runs lrelease on the specified files
qt5_add_translation( QM_FILES ${TS_FILES} )

# Define the Pisces version string for use in source files
# set_source_files_properties( Misc/Utility.cpp PROPERTIES COMPILE_DEFINITIONS PISCES_FULL_VERSION="${PISCES_FULL_VERSION}" )
# set_source_files_properties( Dialogs/About.cpp PROPERTIES COMPILE_DEFINITIONS PISCES_FULL_VERSION="${PISCES_FULL_VERSION}" )
# set_property( SOURCE Dialogs/About.cpp APPEND PROPERTY COMPILE_DEFINITIONS PISCES_FULL_VERSION="${PISCES_FULL_VERSION}" PISCES_CODE_NAME="${PISCES_CODE_NAME}" )

#########################################################

# Adds folders for Visual Studio solution explorer (and for Xcode explorer)
source_group( "Form Files"        FILES ${UI_FILES} )
source_group( "Resource Files"    FILES ${QRC_FILES} )
source_group( "Misc"              FILES ${MISC_FILES} )
source_group( "Main UI"           FILES ${MAINUI_FILES} )
source_group( "Main Files"        FILES ${MAIN_FILES} )

#########################################################

set( ALL_SOURCES ${RAW_SOURCES} ${UI_FILES_H} ${QRC_FILES_CPP} ${QM_FILES} )

#########################################################

# We need to pick up the ui*.h files,
# and the headers for the linked-to libraries.
# The directories are in reverse order because we're using before to
# put our include dirs before any system ones.
include_directories( BEFORE
                     ${CMAKE_CURRENT_SOURCE_DIR}
                     ${CMAKE_CURRENT_BINARY_DIR} )

#########################################################

add_library( ${PROJECT_NAME} ${ALL_SOURCES} )

if (MSVC)
    set(QT_MAIN Qt5::WinMain)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/src
    ${HSERVER_INCLUDE_DIRS}
)

target_link_libraries( ${PROJECT_NAME} ${QT_MAIN} ${HSERVER_LIBRARIES})
qt5_use_modules(${PROJECT_NAME} Widgets Xml XmlPatterns PrintSupport Svg WebKit WebKitWidgets Network Concurrent Multimedia)

#########################################################

# Speed up stirng building
add_definitions( -DQT_USE_FAST_CONCATENATION )
add_definitions( -DQT_USE_FAST_OPERATOR_PLUS )

#########################################################

# "Link time code generation" flags for MSVC
if( MSVC )
    add_definitions( /DUNICODE /D_UNICODE /DHAVE_ROUND )
    # The /Zc:wchar_t- flag can't go into add_definitions
    # because the RC compiler picks it up too and it provokes a name clash
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:wchar_t- /MP")
    set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Oi /GL" ) 
    set( CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG" )

# "Print all warnings" flag for GCC
elseif( CMAKE_COMPILER_IS_GNUCXX )
    add_definitions( -Wall )
endif()

#########################################################
