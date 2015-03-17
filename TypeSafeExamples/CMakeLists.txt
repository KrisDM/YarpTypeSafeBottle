# Copyright (C) 2015 King's College London
# Authors: Kris De Meyer
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

cmake_minimum_required(VERSION 2.6)

# package dependencies
find_package(YARP REQUIRED)

# the project
set (PrjctName "TypeSafeExamples")
project (${PrjctName})

# the location for the TypeSafeBottle code (change to fit your repository layout)
set (TYPESAFE_DIR "../TypeSafeBottle")

# include dependencies
include_directories(${YARP_INCLUDE_DIRS}
					${TYPESAFE_DIR})

# the XML file and its full file name
set(MsgFileName "TypeSafeExamples")
set(FullMsgFileName "${CMAKE_CURRENT_SOURCE_DIR}/${MsgFileName}")

##########################################	
# set up the project for the example files
##########################################
set(messages_header
    ${MsgFileName}.h)
set(messages_xml
    ${MsgFileName}.xml
	${MsgFileName}.xsd
	${MsgFileName}.xslt)  

#add files to the correct folders in Visual Studio
source_group("Header Files" FILES ${messages_header})
source_group("Source Files" FILES ${messages_xml})

#add a target that will not generate an executable
add_custom_target(${PrjctName} SOURCES ${messages_header} ${messages_xml})

#make this target depend on the TypeSafeBottle target
add_dependencies(${PrjctName} TypeSafeBottle)

#########################################################################################################
#Add a custom command that will automatically generate the C++ when building the project
#On unsupported platforms, you should find a way to make the automatic build work or disable what follows
#########################################################################################################

#if you work on an unsupported platform, the below line will probably generate a build error
set(generate_command "UNKNOWN_OS")

#To generate C++ from XML on Windows, we use a javascript that is included in the TypeSafeBottle directory
if(WIN32)
set(generate_command "cscript ${TYPESAFE_DIR}/win-generate-code-from-xml.js ${MsgFileName}.h ${MsgFileName}.xslt ${MsgFileName}.xml")
endif(WIN32)

#On many UNIX distributions, we can use console program xsltproc
if (UNIX)
set(generate_command "xsltproc -o \"${FullMsgFileName}.h\" \"${FullMsgFileName}.xslt\" \"${FullMsgFileName}.xml\")
endif(UNIX)

add_custom_command(OUTPUT ${FullMsgFileName}.h
		           COMMAND ${generate_command}
		           DEPENDS ${FullMsgFileName}.xml
		           COMMENT "Generating C++ code from ${MsgFileName}.xml")