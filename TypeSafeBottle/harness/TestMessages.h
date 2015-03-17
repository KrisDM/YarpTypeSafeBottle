//C++ code automatically generated from YarpTypeSafeBottle XML file - do not alter

#pragma once

#include "TypeSafeBottle/TypeSafeBottle.h"

using namespace darwin::msg;

namespace darwin {
	namespace msg {
		namespace test {

//pre-declaration of classes derived from VocabDictionary
class TestDictionary;
class AnotherTestDictionary;

//pre-declaration of classes derived from StructBottle
class TestIntStruct;
class TestDoubleStruct;
class TestStringStruct;
class TestVocabStruct;
class TestDictionaryStruct;
class TestStructStruct;
class TestRecursiveVectorStruct;
class doub;
class AnotherTest;
class TestVectorStruct;

//pre-declaration of classes derived from WrapperBottle
class TestWrapper;

//named VectorBottles - implemented as typedefs
typedef IntVector TestIntVector;
typedef DoubleVector TestDoubleVector;
typedef StringVector TestStringVector;
typedef VocabVector TestVocabVector;
typedef DictionaryBottle<AnotherTestDictionary> TestDictionaryVector;
typedef VectorBottle<TestStructStruct> TestStructVector;

//class declarations derived from VocabDictionary
class TestDictionary : public VocabDictionary {
public:
	static bool iso(int);
	static bool istw(int);
	static bool isthr(int);
	static bool isfour(int);
	static void type_check(int);
	static yarp::os::ConstString valueStr(int);
	enum value {
		oID = VOCAB1('o'),
		twID = VOCAB2('t','w'),
		thrID = VOCAB3('t','h','r'),
		fourID = VOCAB4('f','o','u','r'),
		unknownID = 0
	};
protected:
	TestDictionary() {};
	TestDictionary(const TestDictionary&) {};
};

class AnotherTestDictionary : public VocabDictionary {
public:
	static bool isone(int);
	static bool istwo(int);
	static void type_check(int);
	static yarp::os::ConstString valueStr(int);
	enum value {
		oneID = VOCAB3('o','n','e'),
		twoID = VOCAB3('t','w','o'),
		unknownID = 0
	};
protected:
	AnotherTestDictionary() {};
	AnotherTestDictionary(const AnotherTestDictionary&) {};
};


//class declarations derived from StructBottle
class TestIntStruct : public StructBottle {
public:
	TestIntStruct();
	int anInt() const;
	TestIntStruct& setanInt(int);
	static void type_check(const yarp::os::Bottle*);
};

class TestDoubleStruct : public StructBottle {
public:
	TestDoubleStruct();
	double aDouble() const;
	TestDoubleStruct& setaDouble(double);
	static void type_check(const yarp::os::Bottle*);
};

class TestStringStruct : public StructBottle {
public:
	TestStringStruct();
	yarp::os::ConstString aString() const;
	TestStringStruct& setaString(const yarp::os::ConstString&);
	static void type_check(const yarp::os::Bottle*);
};

class TestVocabStruct : public StructBottle {
public:
	TestVocabStruct();
	int aVocab() const;
	TestVocabStruct& setaVocab(int);
	static void type_check(const yarp::os::Bottle*);
};

class TestDictionaryStruct : public StructBottle {
public:
	TestDictionaryStruct();
	TestDictionary::value anEntry() const;
	TestDictionaryStruct& setanEntry(TestDictionary::value);
	static void type_check(const yarp::os::Bottle*);
};

class TestStructStruct : public StructBottle {
public:
	TestStructStruct();
	TestIntStruct& aStruct() const;
	static void type_check(const yarp::os::Bottle*);
};

class TestRecursiveVectorStruct : public StructBottle {
public:
	TestRecursiveVectorStruct();
	VectorBottle<TestRecursiveVectorStruct>& recursive() const;
	static void type_check(const yarp::os::Bottle*);
};

class doub : public StructBottle {
public:
	doub();
	int anInt() const;
	doub& setanInt(int);
	static void type_check(const yarp::os::Bottle*);
};

class AnotherTest : public StructBottle {
public:
	AnotherTest();
	AnotherTestDictionary::value aValue() const;
	doub& aDoub() const;
	AnotherTest& setaValue(AnotherTestDictionary::value);
	static void type_check(const yarp::os::Bottle*);
};

class TestVectorStruct : public StructBottle {
public:
	TestVectorStruct();
	IntVector& anIntVector() const;
	DoubleVector& aDoubleVector() const;
	StringVector& aStringVector() const;
	VocabVector& aVocabVector() const;
	DictionaryBottle<TestDictionary>& aDictionaryVector() const;
	VectorBottle<TestDictionaryStruct>& aDictionaryStructVector() const;
	static void type_check(const yarp::os::Bottle*);
};


//class declarations derived from WrapperBottle
class TestWrapper : public WrapperBottle {
public:
	TestWrapper();
	TestIntStruct& is() const;
	TestIntVector& iv() const;
	TestDictionaryVector& dv() const;
	TestWrapper& tw() const;
	void is(const TestIntStruct&);
	void iv(const TestIntVector&);
	void dv(const TestDictionaryVector&);
	void tw(const TestWrapper&);
	bool isis() const;
	bool isiv() const;
	bool isdv() const;
	bool istw() const;
	static void type_check(const yarp::os::Bottle*);
	typedef SubID2Type<TestIntStruct,VOCAB2('i','s')> isID;
	typedef SubID2Type<TestIntVector,VOCAB2('i','v')> ivID;
	typedef SubID2Type<TestDictionaryVector,VOCAB2('d','v')> dvID;
	typedef SubID2Type<TestWrapper,VOCAB2('t','w')> twID;
};


//Function definitions
/*========================================
* TestDictionary member function implementations
*=======================================*/

inline bool TestDictionary::iso(int v) {
	return (v == TestDictionary::oID);
}

inline bool TestDictionary::istw(int v) {
	return (v == TestDictionary::twID);
}

inline bool TestDictionary::isthr(int v) {
	return (v == TestDictionary::thrID);
}

inline bool TestDictionary::isfour(int v) {
	return (v == TestDictionary::fourID);
}

inline void TestDictionary::type_check(int v) {
	switch (v) {
	case oID:
	case twID:
	case thrID:
	case fourID:
	case unknownID:
		break;
	default:
		throw TypeCheckError("TestDictionary","incorrect value",v);
	}
}

inline yarp::os::ConstString TestDictionary::valueStr(int v) {
	yarp::os::ConstString returnval = "";
	try {
		TestDictionary::type_check(v);
		returnval = VocabDictionary::base_valueStr(v);
	}
	catch (TypeCheckError&) {
		;
	}
	return returnval;
}

/*========================================
* AnotherTestDictionary member function implementations
*=======================================*/

inline bool AnotherTestDictionary::isone(int v) {
	return (v == AnotherTestDictionary::oneID);
}

inline bool AnotherTestDictionary::istwo(int v) {
	return (v == AnotherTestDictionary::twoID);
}

inline void AnotherTestDictionary::type_check(int v) {
	switch (v) {
	case oneID:
	case twoID:
	case unknownID:
		break;
	default:
		throw TypeCheckError("AnotherTestDictionary","incorrect value",v);
	}
}

inline yarp::os::ConstString AnotherTestDictionary::valueStr(int v) {
	yarp::os::ConstString returnval = "";
	try {
		AnotherTestDictionary::type_check(v);
		returnval = VocabDictionary::base_valueStr(v);
	}
	catch (TypeCheckError&) {
		;
	}
	return returnval;
}

/*========================================
* TestIntStruct member function implementations
*=======================================*/

inline TestIntStruct::TestIntStruct() {
	addint("anInt",0);
}

inline int TestIntStruct::anInt() const {
	return getint(1);
}

inline TestIntStruct& TestIntStruct::setanInt(int v) {
	setint(1,v);
	return *this;
}

inline void TestIntStruct::type_check(const yarp::os::Bottle* b) {
	TestIntStruct t;
	StructBottle::base_type_check(&t,b);
}

/*========================================
* TestDoubleStruct member function implementations
*=======================================*/

inline TestDoubleStruct::TestDoubleStruct() {
	adddouble("aDouble",0.0);
}

inline double TestDoubleStruct::aDouble() const {
	return getdouble(1);
}

inline TestDoubleStruct& TestDoubleStruct::setaDouble(double v) {
	setdouble(1,v);
	return *this;
}

inline void TestDoubleStruct::type_check(const yarp::os::Bottle* b) {
	TestDoubleStruct t;
	StructBottle::base_type_check(&t,b);
}

/*========================================
* TestStringStruct member function implementations
*=======================================*/

inline TestStringStruct::TestStringStruct() {
	addstring("aString","");
}

inline yarp::os::ConstString TestStringStruct::aString() const {
	return getstring(1);
}

inline TestStringStruct& TestStringStruct::setaString(const yarp::os::ConstString& v) {
	setstring(1,v);
	return *this;
}

inline void TestStringStruct::type_check(const yarp::os::Bottle* b) {
	TestStringStruct t;
	StructBottle::base_type_check(&t,b);
}

/*========================================
* TestVocabStruct member function implementations
*=======================================*/

inline TestVocabStruct::TestVocabStruct() {
	addvocab("aVocab",0);
}

inline int TestVocabStruct::aVocab() const {
	return getvocab(1);
}

inline TestVocabStruct& TestVocabStruct::setaVocab(int v) {
	setvocab(1,v);
	return *this;
}

inline void TestVocabStruct::type_check(const yarp::os::Bottle* b) {
	TestVocabStruct t;
	StructBottle::base_type_check(&t,b);
}

/*========================================
* TestDictionaryStruct member function implementations
*=======================================*/

inline TestDictionaryStruct::TestDictionaryStruct() {
	addvocab("anEntry",TestDictionary::unknownID);
}

inline TestDictionary::value TestDictionaryStruct::anEntry() const {
	return static_cast<TestDictionary::value>(getvocab(1));
}

inline TestDictionaryStruct& TestDictionaryStruct::setanEntry(TestDictionary::value v) {
	TestDictionary::type_check(v);
	setvocab(1,v);
	return *this;
}

inline void TestDictionaryStruct::type_check(const yarp::os::Bottle* b) {
	TestDictionaryStruct t;
	StructBottle::base_type_check(&t,b);
	TestDictionary::type_check(b->get(1).asVocab());
}

/*========================================
* TestStructStruct member function implementations
*=======================================*/

inline TestStructStruct::TestStructStruct() {
	addlist("aStruct"); aStruct() = TestIntStruct();
}

inline TestIntStruct& TestStructStruct::aStruct() const {
	return static_cast<TestIntStruct&>(getlist(1));
}

inline void TestStructStruct::type_check(const yarp::os::Bottle* b) {
	TestStructStruct t;
	StructBottle::base_type_check(&t,b);
	TestIntStruct::type_check(b->get(1).asList());
}

/*========================================
* TestRecursiveVectorStruct member function implementations
*=======================================*/

inline TestRecursiveVectorStruct::TestRecursiveVectorStruct() {
	addlist("recursive"); recursive() = VectorBottle<TestRecursiveVectorStruct>();
}

inline VectorBottle<TestRecursiveVectorStruct>& TestRecursiveVectorStruct::recursive() const {
	return static_cast<VectorBottle<TestRecursiveVectorStruct>&>(getlist(1));
}

inline void TestRecursiveVectorStruct::type_check(const yarp::os::Bottle* b) {
	TestRecursiveVectorStruct t;
	StructBottle::base_type_check(&t,b);
	VectorBottle<TestRecursiveVectorStruct>::type_check(b->get(1).asList());
}

/*========================================
* doub member function implementations
*=======================================*/

inline doub::doub() {
	addint("anInt",0);
}

inline int doub::anInt() const {
	return getint(1);
}

inline doub& doub::setanInt(int v) {
	setint(1,v);
	return *this;
}

inline void doub::type_check(const yarp::os::Bottle* b) {
	doub t;
	StructBottle::base_type_check(&t,b);
}

/*========================================
* AnotherTest member function implementations
*=======================================*/

inline AnotherTest::AnotherTest() {
	addvocab("aValue",AnotherTestDictionary::unknownID);
	addlist("aDoub"); aDoub() = doub();
}

inline AnotherTestDictionary::value AnotherTest::aValue() const {
	return static_cast<AnotherTestDictionary::value>(getvocab(1));
}

inline doub& AnotherTest::aDoub() const {
	return static_cast<doub&>(getlist(3));
}

inline AnotherTest& AnotherTest::setaValue(AnotherTestDictionary::value v) {
	AnotherTestDictionary::type_check(v);
	setvocab(1,v);
	return *this;
}

inline void AnotherTest::type_check(const yarp::os::Bottle* b) {
	AnotherTest t;
	StructBottle::base_type_check(&t,b);
	AnotherTestDictionary::type_check(b->get(1).asVocab());
	doub::type_check(b->get(3).asList());
}

/*========================================
* TestVectorStruct member function implementations
*=======================================*/

inline TestVectorStruct::TestVectorStruct() {
	addlist("anIntVector"); anIntVector() = IntVector();
	addlist("aDoubleVector"); aDoubleVector() = DoubleVector();
	addlist("aStringVector"); aStringVector() = StringVector();
	addlist("aVocabVector"); aVocabVector() = VocabVector();
	addlist("aDictionaryVector"); aDictionaryVector() = DictionaryBottle<TestDictionary>();
	addlist("aDictionaryStructVector"); aDictionaryStructVector() = VectorBottle<TestDictionaryStruct>();
}

inline IntVector& TestVectorStruct::anIntVector() const {
	return static_cast<IntVector&>(getlist(1));
}

inline DoubleVector& TestVectorStruct::aDoubleVector() const {
	return static_cast<DoubleVector&>(getlist(3));
}

inline StringVector& TestVectorStruct::aStringVector() const {
	return static_cast<StringVector&>(getlist(5));
}

inline VocabVector& TestVectorStruct::aVocabVector() const {
	return static_cast<VocabVector&>(getlist(7));
}

inline DictionaryBottle<TestDictionary>& TestVectorStruct::aDictionaryVector() const {
	return static_cast<DictionaryBottle<TestDictionary>&>(getlist(9));
}

inline VectorBottle<TestDictionaryStruct>& TestVectorStruct::aDictionaryStructVector() const {
	return static_cast<VectorBottle<TestDictionaryStruct>&>(getlist(11));
}

inline void TestVectorStruct::type_check(const yarp::os::Bottle* b) {
	TestVectorStruct t;
	StructBottle::base_type_check(&t,b);
	IntVector::type_check(b->get(1).asList());
	DoubleVector::type_check(b->get(3).asList());
	StringVector::type_check(b->get(5).asList());
	VocabVector::type_check(b->get(7).asList());
	DictionaryBottle<TestDictionary>::type_check(b->get(9).asList());
	VectorBottle<TestDictionaryStruct>::type_check(b->get(11).asList());
}

/*========================================
* TestWrapper member function implementations
*=======================================*/

inline TestWrapper::TestWrapper() {

}

inline TestIntStruct& TestWrapper::is() const {
	return get(isID());
}

inline TestIntVector& TestWrapper::iv() const {
	return get(ivID());
}

inline TestDictionaryVector& TestWrapper::dv() const {
	return get(dvID());
}

inline TestWrapper& TestWrapper::tw() const {
	return get(twID());
}

inline void TestWrapper::is(const TestIntStruct& v) {
	set(v,isID());
}

inline void TestWrapper::iv(const TestIntVector& v) {
	set(v,ivID());
}

inline void TestWrapper::dv(const TestDictionaryVector& v) {
	set(v,dvID());
}

inline void TestWrapper::tw(const TestWrapper& v) {
	set(v,twID());
}

inline bool TestWrapper::isis() const {
	return (subID() == TestWrapper::isID::value);
}

inline bool TestWrapper::isiv() const {
	return (subID() == TestWrapper::ivID::value);
}

inline bool TestWrapper::isdv() const {
	return (subID() == TestWrapper::dvID::value);
}

inline bool TestWrapper::istw() const {
	return (subID() == TestWrapper::twID::value);
}

inline void TestWrapper::type_check(const yarp::os::Bottle* b) {
	WrapperBottle::base_type_check(b);
	switch (b->get(0).asVocab()) {
	case isID::value:
		TestIntStruct::type_check(b->get(1).asList());
		break;
	case ivID::value:
		TestIntVector::type_check(b->get(1).asList());
		break;
	case dvID::value:
		TestDictionaryVector::type_check(b->get(1).asList());
		break;
	case twID::value:
		TestWrapper::type_check(b->get(1).asList());
		break;
	case 0:
		break;
	default:
		throw TypeCheckError(b,"TestWrapper","incorrect subID",b->get(0).asVocab());
	}
}

} //end namespace test
} //end namespace msg
} //end namespace darwin
