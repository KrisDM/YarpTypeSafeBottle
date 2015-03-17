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
 * @file StructBottle.h
 * @brief A TypeSafeBottle with (field,value) pairs 
 */

#pragma once

//std includes

//yarp includes

//local includes
#include "TypeSafeExceptions.h"
#include "TypeSafeBase.h"

/** 
* StructBottle: a TypeSafeBottle with (field,value) pairs
* Invidual fields can have as values single variables or vectors of elements.
* The type of a variable or vector element can be a builtin type 
* (int, double, string or vocab) or a another TypeSafeBottle
*/

namespace darwin {
	namespace msg {

/// Base class for all TypeSafeBottles that behave like a struct with named fields.
class StructBottle : public TypeSafeBase {
protected:

	/// Protected default constructor.
	StructBottle(); 

	/// Protected copy constructor.
	StructBottle(const StructBottle&); 

	// Utility functions for derived classes
	void addint(const char* n,int v); 
	void adddouble(const char* n,double v); 
	void addstring(const char* n,const char* v); 
	void addvocab(const char* n,int v);
	void addlist(const char* n); 
	int getint(int i) const; 
	double getdouble(int i) const; 
	yarp::os::ConstString getstring(int i) const; 
	int getvocab(int i) const; 
	yarp::os::Bottle& getlist(int i) const; 
	void setint(int i,int v); 
	void setdouble(int i,double v); 
	void setstring(int i,const yarp::os::ConstString& v); 
	void setvocab(int i,int v); 

	/// User has no access to yarp::os::Bottle::size() for StructBottles
	int size() const; 

	/// User has no access to yarp::os::Bottle::clear() for StructBottles
	void clear(); 

	/// Type-check function making common type-checks for StructBottles
	static void base_type_check(const darwin::msg::StructBottle*,const yarp::os::Bottle*); 
};

/*============================
* StructBottle implementations
=============================*/

/// Protected default constructor, only allow object creation via derived classes
inline StructBottle::StructBottle() : TypeSafeBase() {

}

/// Protected copy constructor, only allow object copy via derived classes
inline StructBottle::StructBottle(const StructBottle& s) : TypeSafeBase(s) {

}

/// Add an integer variable with name n and default value v
inline void StructBottle::addint(const char* n,int v) {
	addString(n); 
	addInt(v);
	hasChanged();
}

/// Add a double variable with name n and default value v
inline void StructBottle::adddouble(const char* n,double v) {
	addString(n); 
	addDouble(v);
	hasChanged();
}

/// Add a string variable with name n and default value v
inline void StructBottle::addstring(const char* n,const char* v) {
	addString(n); 
	addString(v);
	hasChanged();
}

/// Add an integer variable with name n and default value v
inline void StructBottle::addvocab(const char* n,int v) {
	addString(n); 
	addVocab(v);
	hasChanged();
}

/// Add an empty vector variable with name n
inline void StructBottle::addlist(const char* n) {
	addString(n); 
	addList();
	hasChanged();
}

/// Get the value of an int variable at position i in the list
inline int StructBottle::getint(int i) const {
	return get(i).asInt();
}

/// Get the value of a double variable at position i in the list
inline double StructBottle::getdouble(int i) const {
	return get(i).asDouble();
}

/// Get the value of a yarp::os::ConstString variable at position i in the list
inline yarp::os::ConstString StructBottle::getstring(int i) const {
	return get(i).asString();
}

/// Get the value of an int variable at position i in the list
inline int StructBottle::getvocab(int i) const {
	return get(i).asVocab();
}

/// Get a reference to a vector variable at position i in the list			
inline yarp::os::Bottle& StructBottle::getlist(int i) const {
	return *get(i).asList();
}

/// Set the int variable at position i to value v
inline void StructBottle::setint(int i,int v) {
	get(i) = yarp::os::Value(v);
	hasChanged();
}

/// Set the double variable at position i to value v
inline void StructBottle::setdouble(int i,double v) {
	get(i) = yarp::os::Value(v);
	hasChanged();
}

/// Copy the content of yarp::os::ConstString v to the variable at position i
inline void StructBottle::setstring(int i,const yarp::os::ConstString& v) {
	get(i) = yarp::os::Value(v);
	hasChanged();
}

/// Set the int variable at position i to value v
inline void StructBottle::setvocab(int i,int v) {
	get(i) = yarp::os::Value(v,true);
	hasChanged();
}

/// Implementation of Bottle::clear function, for in-class use only
inline void StructBottle::clear() {
	yarp::os::Bottle::clear();
}

/// Implementation of Bottle::size function, for in-class use only
inline int StructBottle::size() const {
	return yarp::os::Bottle::size();
}

/// Perform the type-check that all StructBottles have in common
inline void StructBottle::base_type_check(const darwin::msg::StructBottle* t,const yarp::os::Bottle* b) {
	if (t->size() != b->size()) {
		throw TypeCheckError(b,"StructBottle","size mismatch",b->size());
	}
	else {
		for(int i=0;i<t->size();i+=2) {
			yarp::os::Value& v1 = t->get(i+1);
			yarp::os::Value& v2 = b->get(i+1);
			//the fields in Bottle b must be of the same type as in t
			if (v1.isInt() && !v2.isInt()) {
				throw TypeCheckError(b,"StructBottle","field type mismatch in field, should be int",i+2);
			}
			if (v1.isDouble() && !v2.isDouble()) {
				throw TypeCheckError(b,"StructBottle","field type mismatch in field, should be double",i+2);
			}
			if (v1.isVocab() && !(v2.isVocab() || v2.isInt() || v2.isString())) {
				throw TypeCheckError(b,"StructBottle","field type mismatch in field, should be vocab, int or string",i+2);
			}
			if (v1.isString() && !v2.isString()) {
				throw TypeCheckError(b,"StructBottle","field type mismatch in field, should be string",i+2);
			}
			if (v1.isList() && !v2.isList()) {
				throw TypeCheckError(b,"StructBottle","field type mismatch in field, should be list",i+2);
			}
			//the field names in b must be the same as the field names in t
			if (!b->get(i).isString() || t->get(i).asString() != b->get(i).asString()) { 
				throw TypeCheckError(b,"StructBottle","field name mismatch in field",i+1);
			}
		}
	}
}

} //end namespace msg
} //end namespace darwin

//----- end-of-file --- ( next line intentionally left blank ) ------------------


