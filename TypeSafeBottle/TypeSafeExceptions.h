// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
  * Copyright (C)2014 King's College London
  * Author: Kris De Meyer
  * Permission is granted to copy, distribute, and/or modify this program
  * under the terms of the GNU General Public License, version 2 or any
  * later version published by the Free Software Foundation.
  *
  * A copy of the license can be found at
  * http://www.robotcub.org/icub/license/gpl.txt
  *
  * This program is distributed in the hope that it will be useful, but
  * WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
  * Public License for more details
*/

/**
 * @file TypeSafeExceptions.h
 * @brief File containing exceptions thrown by TypeSafeBottle classes
 */

#pragma once

//std includes
#include <typeinfo>
#include <stdexcept>
#include <string>
#include <sstream>

//yarp includes
#include <yarp/os/Bottle.h>

//local includes


namespace darwin {
	namespace msg {

///An out-of-range error thrown when trying to access a VectorBottle with an index that is too large.
class VectorBottleRangeError : public std::range_error {
public:
	VectorBottleRangeError(const char*,int,int); ///< Message containing typeid of throwing class, index value and size of VectorBottle.
private:
	std::string createstr(const char*,int,int);
};

///An error thrown the user tries to read the wrong type of TypeSafeBottle out of a WrapperBottle
class WrapperBottleIDError : public std::runtime_error {
public:
	WrapperBottleIDError(const yarp::os::Bottle*,const char*,const char*); ///< Typeid of the throwing class, expected and actual subID.
private:
	std::string createstr(const yarp::os::Bottle*,const char*,const char*);
};

///An error thrown from type_check functions, indicating that a TypeSafeCast cannot be performed
class TypeCheckError : public std::runtime_error {
public:
	TypeCheckError(const yarp::os::Bottle*,const char*,const char*,int =-1); ///< Type of throwing class, reason, and additional index information
	TypeCheckError(const char*,const char*,int);
private:
	std::string createstr(const char*,const char*,int);
	std::string createstr(const yarp::os::Bottle*,const char*,const char*,int =-1);
};

/*======================================
* VectorBottleRangeError implementations
========================================*/

inline VectorBottleRangeError::VectorBottleRangeError(const char* type,int index,int size) : std::range_error(createstr(type,index,size)) {

}
		
inline std::string VectorBottleRangeError::createstr(const char* type,int index,int size) {
	std::ostringstream conv;
	conv << "VectorBottleRangeError<" << type << ">: index out of bounds" << std::endl; 
	conv << "Index=" << index << ", Size of VectorBottle=" << size << std::endl;
	return conv.str();
}

/*======================================
* WrapperBottleIDError implementations
========================================*/

inline WrapperBottleIDError::WrapperBottleIDError(const yarp::os::Bottle* bottle,const char* type,const char* expected) : std::runtime_error(createstr(bottle,type,expected)) {

}
		
inline std::string WrapperBottleIDError::createstr(const yarp::os::Bottle* bottle,const char* type,const char* expected) {
	std::ostringstream conv;
	conv << "WrapperBottleIDError<" << type << ">" << std::endl; 
	conv << "Trying to access object with wrong subID, should be=\"" << expected << "\"" << std::endl;
	conv << "In Bottle: " << bottle->toString() << std::endl;
	return conv.str();
}

/*======================================
* TypeSafeCastError implementations
========================================*/
inline TypeCheckError::TypeCheckError(const yarp::os::Bottle* bottle,const char* type,const char* reason,int i) : std::runtime_error(createstr(bottle,type,reason,i)) {

}

inline TypeCheckError::TypeCheckError(const char* type,const char* reason,int vocab) : std::runtime_error(createstr(type,reason,vocab)) {

}
		
inline std::string TypeCheckError::createstr(const yarp::os::Bottle* bottle,const char* type,const char* reason,int i) {
	std::ostringstream conv;
	conv << "TypeCheckError<" << type << ">" << std::endl; 
	conv << "Reason: " << reason;
	if (i >= 0) {
		conv << ": " << i;
	}
	conv << std::endl;
	if (bottle) {
		conv << "In Bottle: " << bottle->toString() << std::endl;
	}
	return conv.str();
}

inline std::string TypeCheckError::createstr(const char* type,const char* reason,int vocab) {
	std::ostringstream conv;
	conv << "TypeCheckError<" << type << ">" << std::endl;
	conv << "Reason: " << reason;
	conv << ": " << yarp::os::Value(vocab,true).toString() << std::endl;
	return conv.str();
}

} //end namespace msg
} //end namespace darwin

//----- end-of-file --- ( next line intentionally left blank ) ------------------


