# Copyright (C) 2014 King's College London
# Authors: Kris De Meyer
# CopyPolicy: Released under the terms of the GNU GPL v2.0.
# Test Project for TypeSafeBottle

cmake_minimum_required(VERSION 2.6)
set (PrjctName "TypeSafeBottleTest")
project (${PrjctName})

find_package(YARP REQUIRED)

# Make sure we can call this file by itself or include it from another place
if(NOT DEFINED DARWIN_COMMON)
	set(DARWIN_COMMON "${CMAKE_CURRENT_SOURCE_DIR}/../..")
endif()

# add the ACE, YARP and DARWIN_COMMON folders as include
include_directories($ENV{ACE_ROOT}
					${YARP_INCLUDE_DIRS}
					${DARWIN_COMMON})

# add the required sub directories
add_subdirectory("${DARWIN_COMMON}/TypeSafeBottle" "${CMAKE_CURRENT_BINARY_DIR}/TypeSafeBottle")

set(MsgFileName "TestMessages")
set(FullMsgFileName "${CMAKE_CURRENT_SOURCE_DIR}/${MsgFileName}")

#########################################	
# set up the automatic message generation
#########################################
set(messages_header
    ${MsgFileName}.h)
set(messages_xml
    ${MsgFileName}.xml
	${MsgFileName}.xsd
	${MsgFileName}.xslt)  

#add files to the correct folders in VS
source_group("Header Files" FILES ${messages_header})
source_group("Source Files" FILES ${messages_xml})

#add a target that will not generate a file
add_custom_target(TestMessageGeneration SOURCES ${messages_header} ${messages_xml})

#make this target depend on the TypeSafeBottle target
add_dependencies(TestMessageGeneration TypeSafeBottle)

###############################################################################
#on Windows, add functionality to generate the C++ code from XML using JScript
#this step will run automatically in VS when building the project
if(WIN32)
add_custom_command(OUTPUT ${FullMsgFileName}.h
		           COMMAND cscript generate-code.js ${MsgFileName}.xml ${MsgFileName}.xslt ${MsgFileName}.h
		           DEPENDS ${FullMsgFileName}.xml
		           COMMENT "Generating C++ code from ${MsgFileName}.xml")
endif(WIN32)

###############################################################################
#on Linux, use xsltproc, a command-line XSLT processor
if (UNIX)
add_custom_command(OUTPUT ${FullMsgFileName}.h
                   COMMAND xsltproc -o "${FullMsgFileName}.h" "${FullMsgFileName}.xslt" "${FullMsgFileName}.xml"
                   DEPENDS ${FullMsgFileName}.xml
                   COMMENT "Generating C++ code from ${MsgFileName}.xml")
endif(UNIX)

###############################################################################
#on Windows, we're generating a jscript in the current build directory that will
#automatically generate the header file from the xml file on build using the 
#custom command that was defined above
if(WIN32)
	file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/generate-code.js" "
	var args = WScript.Arguments;
	var xml = args(0);
	var xsl = args(1);
	var out = args(2);
	var xmldoc = new ActiveXObject(\"MSXML2.DOMDocument.6.0\");
	var xsldoc = new ActiveXObject(\"MSXML2.DOMDOCUMENT.6.0\");
	xmldoc.async = false;
	xmldoc.validateOnParse = false;
	xmldoc.load(\"${CMAKE_CURRENT_SOURCE_DIR}/\" + xml);
	if (xmldoc.parseError.errorCode != 0)
		WScript.Echo (\"XML Parse Error : \" + xmldoc.parseError.reason);

	xsldoc.async = false;
	xsldoc.resolveExternals = true;
	xsldoc.load(\"${CMAKE_CURRENT_SOURCE_DIR}/\" + xsl);
	if (xsldoc.parseError.errorCode != 0)
		WScript.Echo (\"XML Parse Error : \" + xsldoc.parseError.reason);

	/* Create a binary IStream */
	var outdoc = new ActiveXObject(\"ADODB.Stream\");
	outdoc.type = 1;
	outdoc.open();
	xmldoc.transformNodeToObject(xsldoc,outdoc);
	outdoc.SaveToFile(\"${CMAKE_CURRENT_SOURCE_DIR}/\" + out,2);
	")
endif(WIN32)

##########################################
# set up the test project itself
##########################################

enable_testing()

set(harness_header 
    TestList.h)
set(harness_source
    harness.cpp
	VocabDictionaryTest.cpp
	StructBottleTest.cpp
	VectorBottleTest.cpp
	WrapperBottleTest.cpp)

#add files to the correct folders in VS
source_group("Header Files" FILES ${harness_header})
source_group("Source Files" FILES ${harness_source})

set(EXE TypeSafeTest)
add_executable(${EXE} ${harness_source} ${harness_header})

target_link_libraries(${EXE} ${YARP_LIBRARIES})

add_dependencies(${EXE} TestMessageGeneration)
   
foreach(test ${harness_source})
	get_filename_component(XN ${test} NAME_WE)
	add_test("${test_family}::${XN}" ${EXE} regression ${XN})
endforeach()
