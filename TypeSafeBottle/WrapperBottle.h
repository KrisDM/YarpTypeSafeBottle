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
 * @file WrapperBottle.h
 * @brief A TypeSafeBottle to wrap other TypeSafeBottles for typed transmission over BufferedPorts
 */

#pragma once

//std includes

//yarp includes

//local includes
#include "TypeSafeExceptions.h"
#include "TypeSafeBase.h"

/** 
* WrapperBottle: a TypeSafeBottle that can wraps around other TypeSafeBottles of different types.
* Predominant use case is to allow different message types to be sent over an explicitly-typed BufferedPort.
* A WrapperBottle contains 1 and 1 only wrapped TypeSafeBottle of 1 of its allowed subtypes.
* WrapperBottles add a vocab subtype identifier before the start of the wrapped TypeSafeBottle
* The wrapped subtypes can be unrelated, the WrapperBottle then behaves like a C union
* If wrapped subtypes are related, the WrapperBottle can be thought to deliver a primitive form of polymorphism
* WrapperBottles are non-template but have templated get and set functions for the different subtypes
* Overloading on the return type of the get function is achieved by template meta-programming
* Strictly speaking, no additional code needs to be generated for WrapperBottles, but derived classes
* that hide the function templates are generated for ease of use.
*/

namespace darwin {
	namespace msg {

/// A helper class used to specialize get and set functions in WrapperBottles
///(template meta-programming - see Modern C++ Design by Alexandrescu)
template<typename T,int v>
struct SubID2Type {
	enum { value = v };
	typedef T OriginalType;
};

/// A base class for TypeSafeBottles that wrap around other TypeSafeBottles 
/// for strongly-typed transmission over a yarp::os::Port or yarp::os::BufferedPort
class WrapperBottle : public TypeSafeBase {
public:

	int subID() const;
	yarp::os::ConstString subIDStr() const;

protected:

	/// Protected default constructor.
	WrapperBottle();

	/// Protected copy constructor.
	WrapperBottle(const WrapperBottle&);

	/// Set the contained TypeSafeBottle
    template<typename U,int v> void set(const U&,const SubID2Type<U,v>&); 

	/// Get the contained TypeSafeBottle
    template<typename U,int v> U& get(const SubID2Type<U,v>&) const;

	/// User has no access to yarp::os::Bottle::size() for WrapperBottles
	int size() const;

	/// User has no access to yarp::os::Bottle::clear() for WrapperBottles
	void clear();

	/// Type-check function making common type-checks for WrapperBottles
	static void base_type_check(const yarp::os::Bottle*);
};

/*=============================
* WrapperBottle implementations
==============================*/

/// Protected default constructor, only allow object creation via derived classes
inline WrapperBottle::WrapperBottle() : TypeSafeBase() {
	yarp::os::Bottle::addVocab(0);
	yarp::os::Bottle::addList();
}

/// Protected copy constructor, only allow object copy via derived classes
inline WrapperBottle::WrapperBottle(const WrapperBottle& s) : TypeSafeBase(s) {

}

/// Get the int value of the Vocab subID specifier of 
inline int WrapperBottle::subID() const {
	return yarp::os::Bottle::get(0).asVocab();
}

/// Get the string representation of the Vocab subID
inline yarp::os::ConstString WrapperBottle::subIDStr() const {
	return yarp::os::Bottle::get(0).toString();
}

/// Implementation of Bottle::clear function, for in-class use only
inline void WrapperBottle::clear() {
	yarp::os::Bottle::clear();
}

/// Implementation of Bottle::size function, for in-class use only
inline int WrapperBottle::size() const {
	return yarp::os::Bottle::size();
}

/// Template function to wrap a TypeSafeBottle using its SUBID
/** For each subID, SUBID defines a type, meaning that 
*any use of these template functions with a specific SUBID
*type specifier gives rise to an overloaded function,
*which forces the compiler to generate code for that type. */
template<typename U,int v> void WrapperBottle::set(const U& u,const SubID2Type<U,v>& subid) {
	clear();
	addVocab(subid.value);
	addList() = u;
	hasChanged();
}

/// Template function to get a reference to a wrapped TypeSafeBottle using its SUBID
/** For each subID, SUBID defines a type, meaning that 
*any use of these template functions with a specific SUBID
*type specifier gives rise to an overloaded function,
*which forces the compiler to generate code for that type.
*This function will throw an WrapperBottleIDError exception
*if you try to read a Bottle format with a different subID
*than the one that is currently wrapped. */
template<typename U,int v> U& WrapperBottle::get(const SubID2Type<U,v>& subid) const {
	if (subID() != subid.value) {
		throw WrapperBottleIDError(this,typeid(U).name(),subIDStr().c_str());
	}
	return static_cast<U&>(*(yarp::os::Bottle::get(1).asList()));
}

/// Perform the type-check that all WrapperBottles have in common
inline void WrapperBottle::base_type_check(const yarp::os::Bottle* b) {
	if (b->size() != 2) {
		throw TypeCheckError(b,"WrapperBottle","size should be 2 but is ",b->size());
	}
	else {
		//the first element should be a vocab, the second element should be a list
		if (!b->get(0).isVocab()) {
			throw TypeCheckError(b,"WrapperBottle","first element should be a vocab");
		}
		if (!b->get(1).isList()) {
			throw TypeCheckError(b,"WrapperBottle","second element should be a list");
		}
		//if the first element is 0, then the second element should be empty
		if (b->get(0).asVocab() == 0 && b->get(1).asList()->size()) {
			throw TypeCheckError(b,"WrapperBottle","subID is 0 but list is not empty");
		}
	}
}

} //end namespace msg
} //end namespace darwin

//----- end-of-file --- ( next line intentionally left blank ) ------------------





