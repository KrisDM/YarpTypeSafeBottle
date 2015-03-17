# Copyright (C) 2015 King's College London
# Authors: Kris De Meyer
# CopyPolicy: Released under the terms of the GNU GPL v2.0.
cmake_minimum_required(VERSION 2.6)
SET(KEYWORD "TypeSafeTutorial")
PROJECT(${KEYWORD})

find_package(YARP REQUIRED)

set(CMAKE_MODULE_PATH 
  ${CMAKE_MODULE_PATH} 
  ${YARP_MODULE_PATH} 
  ${ICUB_MODULE_PATH}
)

INCLUDE_DIRECTORIES(
    ${YARP_INCLUDE_DIRS} 	
)

add_subdirectory(TestMessages)

# Search for source code.
FILE(GLOB folder_source 
 TypeSafeTutorial.cpp
)

SOURCE_GROUP("Source Files" FILES ${folder_source})
SOURCE_GROUP("Header Files" FILES ${folder_header})

# Set up the main executable.
IF (folder_source)
    ADD_EXECUTABLE(${KEYWORD} 
        ${folder_source} 
        ${folder_header}
    )

    ADD_DEPENDENCIES(${KEYWORD} MessageFormats)
    ADD_DEPENDENCIES(${KEYWORD} TestMessages)

    TARGET_LINK_LIBRARIES(
	${KEYWORD}        
	${YARP_LIBRARIES}
    )	

    INSTALL_TARGETS(/bin ${KEYWORD})
ELSE (folder_source)
    MESSAGE(FATAL_ERROR "No source code files found. Please add something")
ENDIF (folder_source)
