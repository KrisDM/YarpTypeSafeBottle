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
 * @file TypeSafeBottle.h
 * @brief The main entry point to include TypeSafeBottle base classes into your project
 */

#pragma once

//std includes
#include <iostream>

//yarp includes

//local includes
#include "VocabDictionary.h"
#include "VectorBottle.h"
#include "StructBottle.h"
#include "WrapperBottle.h"

/** 
* Main file to include for TypeSafeBottles in another project 
* There are 3 types of TypeSafeBottle: VectorBottle, StructBottle and WrapperBottle.
* VectorBottles contain 0 or more elements of the same type, builtin types (int, double, string and vocab) or other TypeSafeBottles
* StructBottles contain named (field,value) pairs. A value can be a builtin type, another TypeSafeBottle, or a vector of TypeSafeBottles
* WrapperBottles wrap around other TypeSafeBottles to allow strongly-typed transmission over a yarp::os::BufferedPort
*/

namespace darwin {
	namespace msg {

/// Pre-declarations of the different types of TypeSafeBottles
template<typename T,bool> class VectorBottle;
template<typename U> class DictionaryBottle;
class StructBottle;
class WrapperBottle;

/// Pre-declarations of exceptions thrown by TypeSafeBottles
class VectorBottleRangeError; ///< Out-of-range exception for VectorBottles
class WrapperBottleIDError; ///< When trying to read the wrong wrapped TypeSafeBottle from a WrapperBottle
class TypeCheckError; ///< Thrown when an untyped yarp::os::Bottle does not fulfil the definition of a TypeSafeBottle

/// Useful typedefs for VectorBottles of the builtin types.
typedef VectorBottle<int> IntVector;
typedef VectorBottle<int,true> VocabVector;
typedef VectorBottle<double> DoubleVector;
typedef VectorBottle<yarp::os::ConstString> StringVector;

/*======================================
* TypeSafeCast implementations
========================================*/

/// Do a type-safe cast of pointer to Bottle b to a reference to TypeSafeBottle T
/// Throws TypeCheckErrors if types are not the same
template<typename T>
T& TypeSafeCast(yarp::os::Bottle* b,bool quiet =false) {
	try {
		T::type_check(b);
	}
	catch (TypeCheckError& e) {
		if (!quiet) {
			std::cout << e.what() << std::endl;
		}
		throw; //rethrow
	}
	return *static_cast<T*>(b);
}

/// Do a type-safe cast of reference to Bottle b to a reference to TypeSafeBottle T
/// Throws TypeCheckErrors if types are not the same
template<typename T>
T& TypeSafeCast(yarp::os::Bottle& b,bool quiet =false) {
	try {
		T::type_check(&b);
	}
	catch (TypeCheckError& e) {
		if (!quiet) {
			std::cout << e.what() << std::endl;
		}
		throw; //rethrow
	}
	return *static_cast<T*>(&b);
}

template<typename T>
typename T::value TypeSafeCast(int v,bool quiet =false) {
	try {
		T::type_check(v);
	}
	catch (TypeCheckError& e) {
		if (!quiet) {
			std::cout << e.what() << std::endl;
		}
		throw; //rethrow
	}
	return static_cast<typename T::value>(v);
}

} //end namespace msg
} //end namespace darwin

//----- end-of-file --- ( next line intentionally left blank ) ------------------




