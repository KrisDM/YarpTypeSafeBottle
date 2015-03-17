//
// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
  * Copyright (C)2014  King's College London
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
 * @file StructBottleTest.cpp
 * @brief Unit test class to test StructBottle classes
 */

#pragma once

//yarp includes
#pragma warning(push)
#pragma warning(disable: 4996)
#include <yarp/os/impl/UnitTest.h>
#pragma warning(pop)

//local includes
#include "TestMessages.h"

using namespace yarp::os;
using namespace yarp::os::impl;

namespace darwin {
namespace msg {
namespace test {

class StructBottleTest : public UnitTest {
public:
    virtual String getName() { return "StructBottleTest"; }

	void checkIntStructBottle() {
		report(0,"Checking StructBottle with an integer field");
		TestIntStruct testStruct;
		checkEqual(testStruct.anInt(),0,"initial value 0");
		testStruct.setanInt(1);
		checkEqual(testStruct.anInt(),1,"value set to 1");
		bool thr1 = false;
		try {
			yarp::os::Bottle b; b.addString("wrongfieldname"); b.addInt(1);
			TestIntStruct t = TypeSafeCast<TestIntStruct>(b,true);
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr1 = true;
		}
		checkTrue(thr1,"unallowable TypeSafeCast");
		bool thr2 = false;
		try {
			yarp::os::Bottle b; b.addString("anInt"); b.addInt(0);
			TestIntStruct t = TypeSafeCast<TestIntStruct>(b,true);
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr2 = true;
		}
		checkFalse(thr2,"allowable TypeSafeCast");
	}

	void checkDoubleStructBottle() {
		report(0,"Checking StructBottle with a double field");
		TestDoubleStruct testStruct;
		checkEqualish(testStruct.aDouble(),0.0,"initial value 0.0");
		testStruct.setaDouble(1.0);
		checkEqualish(testStruct.aDouble(),1.0,"value set to 1.0");
		bool thr1 = false;
		try {
			yarp::os::Bottle b; b.addString("aDouble"); b.addString("wrongvalue");
			TestDoubleStruct t = TypeSafeCast<TestDoubleStruct>(b,true);
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr1 = true;
		}
		checkTrue(thr1,"unallowable TypeSafeCast");
		bool thr2 = false;
		try {
			yarp::os::Bottle b; b.addString("aDouble"); b.addDouble(0);
			TestDoubleStruct t = TypeSafeCast<TestDoubleStruct>(b,true);
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr2 = true;
		}
		checkFalse(thr2,"allowable TypeSafeCast");
	}

	void checkStringStructBottle() {
		report(0,"Checking StructBottle with a string field");
		TestStringStruct testStruct;
		checkTrue((testStruct.aString() == ""),"initial empty string");
		testStruct.setaString("some string");
		checkTrue((testStruct.aString() == "some string"),"string set to \"some string\"");
		bool thr1 = false;
		try {
			TestDoubleStruct b;
			TestStringStruct t = TypeSafeCast<TestStringStruct>(b,true);
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr1 = true;
		}
		checkTrue(thr1,"unallowable TypeSafeCast");
		bool thr2 = false;
		try {
			yarp::os::Bottle b; b.addString("aString"); b.addString("");
			TestStringStruct t = TypeSafeCast<TestStringStruct>(b,true);
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr2 = true;
		}
		checkFalse(thr2,"allowable TypeSafeCast");
	}

	void checkVocabStructBottle() {
		report(0,"Checking StructBottle with a vocab field");
		TestVocabStruct testStruct;
		checkEqual(testStruct.aVocab(),0,"initial value 0");
		testStruct.setaVocab(VOCAB4('t','e','s','t'));
		checkEqual(testStruct.aVocab(),VOCAB4('t','e','s','t'),"value set to \"test\"");
		bool thr1 = false;
		try {
			yarp::os::Bottle b; b.addString("wrongfieldname"); b.addInt(1);
			TestVocabStruct t = TypeSafeCast<TestVocabStruct>(b,true);
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr1 = true;
		}
		checkTrue(thr1,"unallowable TypeSafeCast");
		bool thr2 = false;
		try {
			yarp::os::Bottle b; b.addString("aVocab"); b.addInt(0);
			TestVocabStruct t = TypeSafeCast<TestVocabStruct>(b,true);
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr2 = true;
		}
		checkFalse(thr2,"allowable TypeSafeCast");
	}

	void checkDictionaryStructBottle() {
		report(0,"Checking StructBottle with a dictionary vocab field");
		TestDictionaryStruct testStruct;
		checkEqual(testStruct.anEntry(),0,"initial value 0");
		testStruct.setanEntry(TestDictionary::oID);
		checkEqual(testStruct.anEntry(),TestDictionary::oID,"value set to TestDictionary::oID");
		bool thr1 = false;
		try {
			testStruct.setanEntry(static_cast<TestDictionary::value>(1));
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr1 = true;
		}
		checkTrue(thr1,"value set not allowed TestDictionary");
		bool thr2 = false;
		try {
			yarp::os::Bottle b; b.addString("anEntry"); b.addInt(1);
			TestDictionaryStruct t = TypeSafeCast<TestDictionaryStruct>(b,true);
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr2 = true;
		}
		checkTrue(thr2,"unallowable TypeSafeCast");
		bool thr3 = false;
		try {
			yarp::os::Bottle b; b.addString("anEntry"); b.addInt(TestDictionary::oID);
			TestDictionaryStruct t = TypeSafeCast<TestDictionaryStruct>(b,true);
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr3 = true;
		}
		checkFalse(thr3,"allowable TypeSafeCast");
	}

	void checkStructStructBottle() {
		report(0,"Checking StructBottle with a TestIntStruct field");
		TestStructStruct testStruct;
		TestIntStruct intStruct;
		checkTrue(testStruct.aStruct() == intStruct,"initial value");
		intStruct.setanInt(1);
		testStruct.aStruct() = intStruct;
		checkEqual(testStruct.aStruct().anInt(),1,"value set to 1");
		bool thr1 = false;
		try {
			yarp::os::Bottle b; 
			b.addString("aStruct"); 
			b.addList();
			TestStructStruct t = TypeSafeCast<TestStructStruct>(b,true);
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr1 = true;
		}
		checkTrue(thr1,"unallowable TypeSafeCast");
		bool thr2 = false;
		try {
			yarp::os::Bottle b; 
			b.addString("aStruct"); 
			yarp::os::Bottle& b2 = b.addList();
			b2 = intStruct;
			TestStructStruct t = TypeSafeCast<TestStructStruct>(b,true);
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr2 = true;
		}
		checkFalse(thr2,"allowable TypeSafeCast");
	}

	void checkVectorStructBottle() {
		report(0,"Checking StructBottle with vector fields");
		TestVectorStruct testStruct;
		checkEqual(testStruct.anIntVector().size(),0,"initial size = 0");
		checkEqual(testStruct.aDoubleVector().size(),0,"initial size = 0");
		checkEqual(testStruct.aStringVector().size(),0,"initial size = 0");
		checkEqual(testStruct.aVocabVector().size(),0,"initial size = 0");
		checkEqual(testStruct.aDictionaryVector().size(),0,"initial size = 0");
		checkEqual(testStruct.aDictionaryStructVector().size(),0,"initial size = 0");
		testStruct.aDictionaryVector().add(TestDictionary::oID);
		bool thr1 = false;
		try {
			testStruct.aDictionaryVector().add(static_cast<TestDictionary::value>(AnotherTestDictionary::twoID));
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr1 = true;
		}
		checkTrue(thr1,"adding unallowed value to aDictionaryVector field");
	}

	void checkRecursiveStructBottle() {
		report(0,"Checking StructBottle with recursive fields");
		TestRecursiveVectorStruct ts1;
		ts1.recursive().add(ts1);
		ts1.recursive().add(ts1);
		std::cout << ts1.toString() << std::endl;
	}

	void checkClassNameInDictionaryName() {
		report(0,"Regression test for error caused by className of Struct appearing inside Dictionary className");
		AnotherTest t;
		checkEqual(t.aValue(),AnotherTestDictionary::unknownID,"aValue field Initial value should be zero");
		checkEqual(t.aDoub().anInt(),0,"aDoub field Initial value should be zero");
	}

    virtual void runTests() {
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        checkIntStructBottle();
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		checkDoubleStructBottle();
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		checkStringStructBottle();
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		checkVocabStructBottle();
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		checkDictionaryStructBottle();
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		checkStructStructBottle();
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		checkVectorStructBottle();
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		checkRecursiveStructBottle();
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		checkClassNameInDictionaryName();
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    }

private:

	void checkConstReference(const TestIntStruct& t) {
	     int i = t.anInt();
	}

	void printCaughtException(const char* c) {
		std::cout << "==============TypeCheckError Caught=================" << std::endl;
		std::cout << c;
		std::cout << "====================================================" << std::endl;
	}
};

static StructBottleTest theStructBottleTest;

UnitTest& getStructBottleTest() {
    return theStructBottleTest;
}

} //end namespace test
} //end namespace msg
} //end namespace darwin