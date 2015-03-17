# Copyright (C) 2013 King's College London
# Authors: Kris De Meyer
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

cmake_minimum_required(VERSION 2.6)

#list the files in the folder
SET(folder_header
   TypeSafeBottle.h 
   TypeSafeBase.h 
   VectorBottle.h 
   StructBottle.h 
   WrapperBottle.h
   VocabDictionary.h
   TypeSafeExceptions.h)

SET(folder_source
    YarpTypeSafeBottle.xsd
	YarpTypeSafeBottle.xslt)

#add files to the correct folders in VS
source_group("Header Files" FILES ${folder_header})
source_group("Source Files" FILES ${folder_source})

# add a target that will not generate a file
add_custom_target(TypeSafeBottle SOURCES ${folder_header} ${folder_source})