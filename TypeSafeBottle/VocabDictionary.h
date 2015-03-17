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
 * @file VocabDictionary.h
 * @brief A base class to define a set of vocab literals
 */

#pragma once

//std includes

//yarp includes

//local includes
#include "TypeSafeExceptions.h"

/** 
* VocabDictionary: a base class to define a set of vocab literals, similarly to WrapperBottle subIDs
*/

namespace darwin {
	namespace msg {

/// A base class for TypeSafeBottles that wrap around other TypeSafeBottles 
/// for strongly-typed transmission over a yarp::os::Port or yarp::os::BufferedPort
class VocabDictionary {
protected:

	/// Protected default constructor.
	VocabDictionary();

	/// Protected copy constructor.
	VocabDictionary(const VocabDictionary&);

	/// Type-check function making common type-checks for VocabDictionary
	static yarp::os::ConstString base_valueStr(int);
};

/*===============================
* VocabDictionary implementations
================================*/

/// Protected default constructor, only allow object creation via derived classes
inline VocabDictionary::VocabDictionary() {
	
}

/// Protected copy constructor, only allow object copy via derived classes
inline VocabDictionary::VocabDictionary(const VocabDictionary& s) {
	
}

/// Get the string representation of the Vocab subID
inline yarp::os::ConstString VocabDictionary::base_valueStr(int i) {
	return yarp::os::Value(i,true).toString();
}

} //end namespace msg
} //end namespace darwin

//----- end-of-file --- ( next line intentionally left blank ) ------------------





