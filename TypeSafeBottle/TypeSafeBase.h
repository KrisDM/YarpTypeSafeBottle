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
 * @file TypeSafeBase.h
 * @brief Base class for all TypeSafeBottles
 */

#pragma once

//std includes

//yarp includes
#include <yarp/os/ConstString.h>
#include <yarp/os/Bottle.h>
#include <yarp/os/Value.h>
#include <yarp/os/Vocab.h>

//local includes

namespace darwin {
	namespace msg {

/** 
* TypeSafeBase is the parent class of all other TypeSafeBottles and is 
* implemented as a yarp::os::Bottle. It hides the type-unsafe members from
* the user of derived classes. 
*/

class TypeSafeBase : public yarp::os::Bottle {
protected:

	/// Protected default constructor.
	TypeSafeBase(); 

	/// Protected copy constructor.
	TypeSafeBase(const TypeSafeBase&); 

	/// Protected from-string constructor.
	TypeSafeBase(const char*); 

	// Type-unsafe Bottle functions protected to disable user access
	void addInt(int);
	void addVocab(int);
	void addDouble(double);
	void addString(const char*);
	void addString(const yarp::os::ConstString&);
	void add(const yarp::os::Value&);
	void add(yarp::os::Value* value);
	yarp::os::Bottle& addList();
	yarp::os::Property& addDict();
	yarp::os::Value pop();
	yarp::os::Value& get(int) const;
	void fromString(const char*);
	void fromBinary(const char*,int);
	const char* toBinary(size_t*);
	virtual bool check(const char*);
	virtual yarp::os::Value& find(const char*);
	yarp::os::Bottle& findGroup(const char*);
	virtual bool isNull() const;
	void copy(const yarp::os::Bottle&,int,int);
	void append(const yarp::os::Bottle&);
	yarp::os::Bottle tail() const;
	void hasChanged();

private:

	// Type-unsafe Bottle functions made private to prevent access
	void specialize(int);
	int getSpecialization();
	void setNested(bool);
};

/*=====================================
* Class member function implementations
======================================*/

/// Protected default constructor, only allow object creation of derived classes
inline TypeSafeBase::TypeSafeBase() : Bottle() {

}

/// Protected copy constructor, only allow object copy of derived classes
inline TypeSafeBase::TypeSafeBase(const TypeSafeBase& b) : Bottle(b) {

}

/// Proteced from-string constructor.
inline TypeSafeBase::TypeSafeBase(const char* t) : Bottle(t) {

}

inline void TypeSafeBase::addInt(int v) {
	yarp::os::Bottle::addInt(v);
}

inline void TypeSafeBase::addVocab(int v) {
	yarp::os::Bottle::addVocab(v);
}

inline void TypeSafeBase::addDouble(double v) {
	yarp::os::Bottle::addDouble(v);
}

inline void TypeSafeBase::addString(const char* v) {
	yarp::os::Bottle::addString(v);

}

inline void TypeSafeBase::addString(const yarp::os::ConstString& v) {
	yarp::os::Bottle::addString(v);

}

inline void TypeSafeBase::add(const yarp::os::Value& v) {
	yarp::os::Bottle::add(v);
}

inline void TypeSafeBase::add(yarp::os::Value* v) {
	yarp::os::Bottle::add(v);
}

inline yarp::os::Bottle& TypeSafeBase::addList() {
	return yarp::os::Bottle::addList();
}

inline yarp::os::Property& TypeSafeBase::addDict() {
	return yarp::os::Bottle::addDict();
}

inline yarp::os::Value TypeSafeBase::pop() {
	return yarp::os::Bottle::pop();
}

inline yarp::os::Value& TypeSafeBase::get(int i) const {
	return yarp::os::Bottle::get(i);
}

inline void TypeSafeBase::fromString(const char* t) {
	yarp::os::Bottle::fromString(t);
}

inline void TypeSafeBase::fromBinary(const char* t,int i) {
	yarp::os::Bottle::fromBinary(t,i);
}

inline const char* TypeSafeBase::toBinary(size_t* t) {
	return yarp::os::Bottle::toBinary(t);
}

inline bool TypeSafeBase::check(const char* t) {
	return yarp::os::Bottle::check(t);
}

inline yarp::os::Value& TypeSafeBase::find(const char* t) {
	return yarp::os::Bottle::find(t);
}

inline yarp::os::Bottle& TypeSafeBase::findGroup(const char* t) {
	return yarp::os::Bottle::findGroup(t);
}

inline bool TypeSafeBase::isNull() const {
	return yarp::os::Bottle::isNull();
}

inline void TypeSafeBase::copy(const yarp::os::Bottle& b,int i,int l) {
	yarp::os::Bottle::copy(b,i,l);
}

inline void TypeSafeBase::append(const yarp::os::Bottle& b) {
	yarp::os::Bottle::append(b);
}

inline yarp::os::Bottle TypeSafeBase::tail() const {
	return yarp::os::Bottle::tail();
}

inline void TypeSafeBase::hasChanged() {
	yarp::os::Bottle::hasChanged();
}


} //end namespace msg
} //end namespace darwin

//----- end-of-file --- ( next line intentionally left blank ) ------------------



