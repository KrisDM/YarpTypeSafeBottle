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
 * @file VectorBottle.h
 * @brief A TypeSafeBottle containing 0 or more elements of the same type
 */

#pragma once

//std includes

//yarp includes
#include <yarp/os/Vocab.h>

//local includes
#include "TypeSafeExceptions.h"
#include "TypeSafeBase.h"

/** 
* VectorBottle: a TypeSafeBottle containing 0 or more elements all of the same type.
* VectorBottles are implemented as templates and no further code needs to be generated.
* The content of a VectorBottle can be a builtin type (int, double, string or vocab) or a another TypeSafeBottle
*/

namespace darwin {
	namespace msg {

/// A template class for the generic VectorBottle. Typename T can only be another TypeSafeBottle
template<class T,bool =false>
class VectorBottle : public TypeSafeBase {
public:

	///Default constructor.
	VectorBottle() {

	}

	/// Constructor. Prefill the VectorBottle with n elements
	VectorBottle(int n,const T& t) {
		for(int i=0;i<n;++i) {
			add(t);
		}
	}

	/// Indexing operator. Performs range-check.
	T& operator[](int i) const {
		range_check(i);
	    return static_cast<T&>(*get(i).asList());
	}

	/// Add element v to the end of the vector.
	VectorBottle<T>& add(const T& v) {
		Bottle& b = addList();
		b = v;
		hasChanged();
		return *this;
	}

	/// Set index i to a copy of element v. Performs range-check.
	VectorBottle<T>& set(int i,const T& v) {
		range_check(i);
		*get(i).asList() = v;
		hasChanged();
		return *this;
	}

	/// Type-check function
	static void type_check(const yarp::os::Bottle* b) {
		for(int i=0;i<b->size();++i) {
			if (!b->get(i).isList()) {
				throw TypeCheckError(b,"VectorBottle<T>: ","Not a list",i);
			}
			else {
				T::type_check(b->get(i).asList());
			}
		}
	}

private:
	/// Range-check function.
	void range_check(int i) const {
		if (i >= size()) {
			throw VectorBottleRangeError(typeid(T).name(),i,size());
		}
	}
};

/// Template specialization of VectorBottle for elements of type int
template<>
class VectorBottle<int> : public TypeSafeBase {
public:

	/// Constructor. Prefill the VectorBottle with n values v
	VectorBottle(int n =0,int v =0) {
		for(int i=0;i<n;++i) {
			addInt(v);
		}
	}

	/// Indexing operator. Performs range-check.
	int operator[](int i) const {
		range_check(i);
	    return get(i).asInt();
	}

	/// Add element v to the end of the vector.
	VectorBottle<int>& add(int v) {
		addInt(v);
		hasChanged();
		return *this;
	}

	/// Set index i to v. Performs range-check.
	VectorBottle<int>& set(int i,int v) {
		range_check(i);
		get(i) = yarp::os::Value(v);
		hasChanged();
		return *this;
	}	

	/// Type-check function
	static void type_check(const yarp::os::Bottle* b) {
		for(int i=0;i<b->size();++i) {
			if (!b->get(i).isInt()) {
				throw TypeCheckError(b,"VectorBottle<int>","Not an int",i);
			}
		}
	}
private:
	void range_check(int i) const {
		if (i >= size()) {
			throw VectorBottleRangeError("int",i,size());
		}
	}
};

/// Template specialization of VectorBottle for elements of type vocab
template<>
class VectorBottle<int,true> : public TypeSafeBase {
public:

	/// Constructor. Prefill the VectorBottle with n values v
	VectorBottle(int n =0,int v =0) {
		for(int i=0;i<n;++i) {
			addVocab(v);
		}
	}

	/// Indexing operator. Performs range-check.
	int operator[](int i) const {
		range_check(i);
	    return get(i).asVocab();
	}

	/// Add element v to the end of the vector.
	VectorBottle<int,true>& add(int v) {
		addVocab(v);
		hasChanged();
		return *this;
	}

	/// Set index i to v. Performs range-check.
	VectorBottle<int,true>& set(int i,int v) {
		range_check(i);
		get(i) = yarp::os::Value(v,true);
		hasChanged();
		return *this;
	}	

	/// Type-check function
	static void type_check(const yarp::os::Bottle* b) {
		for(int i=0;i<b->size();++i) {
			if (!(b->get(i).isVocab() || b->get(i).isInt() || b->get(i).isString())) {
				throw TypeCheckError(b,"VectorBottle<vocab>","Not a vocab, int or string",i);
			}
		}
	}
private:
	void range_check(int i) const {
		if (i >= size()) {
			throw VectorBottleRangeError("vocab",i,size());
		}
	}
};

/// Template specialization of VectorBottle for elements of type double.
template<>
class VectorBottle<double> : public TypeSafeBase {
public:

	/// Constructor. Prefill the VectorBottle with n values v
	VectorBottle(int n =0,double v =0.0) {
		for(int i=0;i<n;++i) {
			add(v);
		}
	}

	/// Indexing operator. Performs range-check.
	double operator[](int i) const { 
		range_check(i);
		return get(i).asDouble();
	}

	/// Add element v to the end of the vector.
	VectorBottle<double>& add(double v) {
		addDouble(v);
		hasChanged();
		return *this;
	} 

	/// Set index i to v. Performs range-check.
	VectorBottle<double>& set(int i,double v) {
		range_check(i);
		get(i) = yarp::os::Value(v);
		hasChanged();
		return *this;
	}

	/// Type-check function
	static void type_check(const yarp::os::Bottle* b) {
		for(int i=0;i<b->size();++i) {
			if (!(b->get(i).isDouble() || b->get(i).isInt())) {
				throw TypeCheckError(b,"VectorBottle<double>","Not a double",i);
			}
		}
	}
private:

	/// Range-check function.
	void range_check(int i) const  {
		if (i >= size()) {
			throw VectorBottleRangeError("double",i,size());
		}
	}
};

/// Template specialization of VectorBottle for elements of type yarp::os::ConstString.
template<>
class VectorBottle<yarp::os::ConstString> : public TypeSafeBase {
public:

	/// Constructor. Prefill the VectorBottle with n strings
	VectorBottle() {

	}

	VectorBottle(int n,yarp::os::ConstString& v)  {
		for(int i=0;i<n;++i) {
			addString(v);
		}
	}

	/// Indexing operator. Performs range-check.
	yarp::os::ConstString operator[](int i) const  { 
		range_check(i);
		return get(i).asString();
	}

	/// Add element v to the end of the vector.
	VectorBottle<yarp::os::ConstString>& add(const yarp::os::ConstString& v)  {
		addString(v);
		hasChanged();
		return *this;
	} 

	/// Set index i to v. Performs range-check.
	VectorBottle<yarp::os::ConstString>& set(int i,const yarp::os::ConstString& v)  {
		range_check(i);
		get(i) = yarp::os::Value(v);
		hasChanged();
		return *this;
	}

	/// Type-check function
	static void type_check(const yarp::os::Bottle* b) {
		for(int i=0;i<b->size();++i) {
			if (!b->get(i).isString()) {
				throw TypeCheckError(b,"VectorBottle<yarp::os::ConstString>","Not a string",i);
			}
		}
	}

private:

	/// Range-check function.
	void range_check(int i) const  {
		if (i >= size()) {
			throw VectorBottleRangeError("yarp::os::ConstString",i,size());
		}
	}
};

/// Template specialization of VectorBottle for elements of type vocab belonging to a dictionary
template<typename U>
class DictionaryBottle : public TypeSafeBase {
public:

	DictionaryBottle() {

	}

	/// Constructor. Prefill the VectorBottle with n values v
	DictionaryBottle(int n,typename U::value v) {
		for(int i=0;i<n;++i) {
			add(v);
		}
	}

	/// Indexing operator. Performs range-check.
	typename U::value operator[](int i) const {
		range_check(i);
	    return static_cast<typename U::value>(get(i).asVocab());
	}

	/// Add element v to the end of the vector.
	DictionaryBottle<U>& add(typename U::value v) {
		U::type_check(v);
		addVocab(v);
		hasChanged();
		return *this;
	}

	/// Set index i to v. Performs range-check.
	DictionaryBottle<U>& set(int i,typename U::value v) {
		range_check(i);
		U::type_check(v);
		get(i) = yarp::os::Value(v,true);
		hasChanged();
		return *this;
	}	

	/// Type-check function
	static void type_check(const yarp::os::Bottle* b) {
		for(int i=0;i<b->size();++i) {
			if (!(b->get(i).isVocab() || b->get(i).isInt() || b->get(i).isString())) {
				throw TypeCheckError(b,"DictionaryBottle<U>","Not a vocab, int or string",i);
			}
			else {
				U::type_check(b->get(i).asVocab());
			}
		}
	}
private:
	void range_check(int i) const {
		if (i >= size()) {
			throw VectorBottleRangeError("dictionary",i,size());
		}
	}
};

} //end namespace msg
} //end namespace darwin

//----- end-of-file --- ( next line intentionally left blank ) ------------------





