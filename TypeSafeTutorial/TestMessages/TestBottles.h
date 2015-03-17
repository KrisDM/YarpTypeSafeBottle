//C++ code automatically generated from YarpTypeSafeBottle XML file - do not alter

#pragma once

#include "TypeSafeBottle/TypeSafeBottle.h"

using namespace darwin::msg;

namespace darwin {
	namespace msg {
		namespace test {

//pre-declaration of classes derived from StructBottle
class Pair;
class Trio;
class Composite;
class Everything;

//pre-declaration of classes derived from WrapperBottle
class Anything;

//named VectorBottles - implemented as typedefs
typedef VectorBottle<Pair> PairVector;
typedef VectorBottle<Composite> CompositeVector;
typedef VectorBottle<Everything> EverythingVector;
typedef VocabVector RobotCommand;

//class declarations derived from StructBottle
class Pair : public StructBottle {
public:
	Pair();
	yarp::os::ConstString Name();
	int Value();
	Pair& setName(const yarp::os::ConstString&);
	Pair& setValue(int);
};

class Trio : public StructBottle {
public:
	Trio();
	int anInt();
	double aDouble();
	yarp::os::ConstString aString();
	Trio& setanInt(int);
	Trio& setaDouble(double);
	Trio& setaString(const yarp::os::ConstString&);
};

class Composite : public StructBottle {
public:
	Composite();
	Pair& pair();
	Trio& trio();
	VectorBottle<Pair>& morepairs();
};

class Everything : public StructBottle {
public:
	Everything();
	int aVocab();
	Pair& aPair();
	Trio& aTrio();
	IntVector& anIntVector();
	DoubleVector& aDoubleVector();
	StringVector& aStringVector();
	VocabVector& aVocabVector();
	PairVector& aPairVector();
	EverythingVector& anEverythingVector();
	VectorBottle<Pair>& anotherPairVector();
	VectorBottle<Everything>& anotherEverythingVector();
	Everything& setaVocab(int);
};


//class declarations derived from WrapperBottle
class Anything : public WrapperBottle {
public:
	Anything();
	Pair& pair();
	Trio& trio();
	Everything& all();
	void pair(const Pair&);
	void trio(const Trio&);
	void all(const Everything&);
	bool ispair();
	bool istrio();
	bool isall();
	typedef SubID2Type<Pair,VOCAB4('p','a','i','r')> pairID;
	typedef SubID2Type<Trio,VOCAB4('t','r','i','o')> trioID;
	typedef SubID2Type<Everything,VOCAB3('a','l','l')> allID;
};


//Function definitions
/*========================================
* Pair member function implementations
*=======================================*/

inline Pair::Pair() {
	addstring("Name","");
	addint("Value",0);
}

inline yarp::os::ConstString Pair::Name() {
	return getstring(1);
}

inline int Pair::Value() {
	return getint(3);
}

inline Pair& Pair::setName(const yarp::os::ConstString& v) {
	setstring(1,v);
	return *this;
}

inline Pair& Pair::setValue(int v) {
	setint(3,v);
	return *this;
}

/*========================================
* Trio member function implementations
*=======================================*/

inline Trio::Trio() {
	addint("anInt",0);
	adddouble("aDouble",0.0);
	addstring("aString","");
}

inline int Trio::anInt() {
	return getint(1);
}

inline double Trio::aDouble() {
	return getdouble(3);
}

inline yarp::os::ConstString Trio::aString() {
	return getstring(5);
}

inline Trio& Trio::setanInt(int v) {
	setint(1,v);
	return *this;
}

inline Trio& Trio::setaDouble(double v) {
	setdouble(3,v);
	return *this;
}

inline Trio& Trio::setaString(const yarp::os::ConstString& v) {
	setstring(5,v);
	return *this;
}

/*========================================
* Composite member function implementations
*=======================================*/

inline Composite::Composite() {
	addlist("pair"); pair() = Pair();
	addlist("trio"); trio() = Trio();
	addlist("morepairs"); morepairs() = VectorBottle<Pair>();
}

inline Pair& Composite::pair() {
	return static_cast<Pair&>(getlist(1));
}

inline Trio& Composite::trio() {
	return static_cast<Trio&>(getlist(3));
}

inline VectorBottle<Pair>& Composite::morepairs() {
	return static_cast<VectorBottle<Pair>&>(getlist(5));
}

/*========================================
* Everything member function implementations
*=======================================*/

inline Everything::Everything() {
	addvocab("aVocab",0);
	addlist("aPair"); aPair() = Pair();
	addlist("aTrio"); aTrio() = Trio();
	addlist("anIntVector"); anIntVector() = IntVector();
	addlist("aDoubleVector"); aDoubleVector() = DoubleVector();
	addlist("aStringVector"); aStringVector() = StringVector();
	addlist("aVocabVector"); aVocabVector() = VocabVector();
	addlist("aPairVector"); aPairVector() = PairVector();
	addlist("anEverythingVector"); anEverythingVector() = EverythingVector();
	addlist("anotherPairVector"); anotherPairVector() = VectorBottle<Pair>();
	addlist("anotherEverythingVector"); anotherEverythingVector() = VectorBottle<Everything>();
}

inline int Everything::aVocab() {
	return getvocab(1);
}

inline Pair& Everything::aPair() {
	return static_cast<Pair&>(getlist(3));
}

inline Trio& Everything::aTrio() {
	return static_cast<Trio&>(getlist(5));
}

inline IntVector& Everything::anIntVector() {
	return static_cast<IntVector&>(getlist(7));
}

inline DoubleVector& Everything::aDoubleVector() {
	return static_cast<DoubleVector&>(getlist(9));
}

inline StringVector& Everything::aStringVector() {
	return static_cast<StringVector&>(getlist(11));
}

inline VocabVector& Everything::aVocabVector() {
	return static_cast<VocabVector&>(getlist(13));
}

inline PairVector& Everything::aPairVector() {
	return static_cast<PairVector&>(getlist(15));
}

inline EverythingVector& Everything::anEverythingVector() {
	return static_cast<EverythingVector&>(getlist(17));
}

inline VectorBottle<Pair>& Everything::anotherPairVector() {
	return static_cast<VectorBottle<Pair>&>(getlist(19));
}

inline VectorBottle<Everything>& Everything::anotherEverythingVector() {
	return static_cast<VectorBottle<Everything>&>(getlist(21));
}

inline Everything& Everything::setaVocab(int v) {
	setvocab(1,v);
	return *this;
}

/*========================================
* Anything member function implementations
*=======================================*/

inline Anything::Anything() {

}

inline Pair& Anything::pair() {
	return get(pairID());
}

inline Trio& Anything::trio() {
	return get(trioID());
}

inline Everything& Anything::all() {
	return get(allID());
}

inline void Anything::pair(const Pair& v) {
	set(v,pairID());
}

inline void Anything::trio(const Trio& v) {
	set(v,trioID());
}

inline void Anything::all(const Everything& v) {
	set(v,allID());
}

inline bool Anything::ispair() {
	return (subID() == Anything::pairID::value);
}

inline bool Anything::istrio() {
	return (subID() == Anything::trioID::value);
}

inline bool Anything::isall() {
	return (subID() == Anything::allID::value);
}

} //end namespace test
} //end namespace msg
} //end namespace darwin
