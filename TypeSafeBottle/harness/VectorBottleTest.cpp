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
 * @file VectorBottleTest.cpp
 * @brief Unit test class to test VectorBottle classes
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

class VectorBottleTest : public UnitTest {
public:
    virtual String getName() { return "VectorBottleTest"; }

	void checkIntVector() {
		report(0,"Checking VectorBottle<int> functions");
		TestIntVector t1;
		checkEqual(t1.size(),0,"initial size = 0");
		t1.add(1).add(2);
		checkEqual(t1.size(),2,"size set to 2");
		checkTrue(t1[0] == 1 && t1[1] == 2,"add elements \"1\" and \"2\"");
		t1.set(1,3);
		checkTrue(t1[1] == 3,"set second element to \"3\"");
		bool thr1 = false;
		try {
			t1.set(2,0);
		}
		catch (VectorBottleRangeError& e) {
			printCaughtException(e.what());
			thr1 = true;
		}
		checkTrue(thr1,"checking range error");
		bool thr2 = false;
		try {
			yarp::os::Bottle b; b.addInt(1); b.addString("wrongtype");
			TestIntVector t2 = TypeSafeCast<TestIntVector>(b,true);
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr2 = true;
		}
		checkTrue(thr2,"unallowable TypeSafeCast");
		bool thr3 = false;
		try {
			yarp::os::Bottle b; b.addInt(1); b.addInt(2); b.addInt(3);
			t1 = TypeSafeCast<TestIntVector>(b,true);
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr3 = true;
		}
		checkFalse(thr3,"allowable TypeSafeCast");
		checkEqual(t1.size(),3,"size = 3 (after TypeSafeCast)");
		TestIntVector t3(4,1);
		checkEqual(t3.size(),4,"fill constructor: initial size = 4");
		checkTrue(t3[3] == 1,"fill constructor, all elements are 1");
	}

	void checkDoubleVector() {
		report(0,"Checking VectorBottle<double> functions");
		TestDoubleVector t1;
		checkEqual(t1.size(),0,"initial size = 0");
		t1.add(1.5).add(2.5);
		checkEqual(t1.size(),2,"size set to 2");
		checkEqualish(t1[0],1.5,"add elements \"1.5\"");
		checkEqualish(t1[1],2.5,"add elements \"2.5\"");
		t1.set(1,3);
		checkEqualish(t1[1],3.0,"set second element to \"3.0\"");
		bool thr1 = false;
		try {
			t1.set(2,0);
		}
		catch (VectorBottleRangeError& e) {
			printCaughtException(e.what());
			thr1 = true;
		}
		checkTrue(thr1,"checking range error");
		bool thr2 = false;
		try {
			yarp::os::Bottle b; b.addDouble(1); b.addString("wrongtype");
			TestDoubleVector t2 = TypeSafeCast<TestDoubleVector>(b,true);
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr2 = true;
		}
		checkTrue(thr2,"unallowable TypeSafeCast");
		bool thr3 = false;
		try {
			yarp::os::Bottle b; b.addDouble(1); b.addDouble(2); b.addDouble(3);
			t1 = TypeSafeCast<TestDoubleVector>(b,true);
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr3 = true;
		}
		checkFalse(thr3,"allowable TypeSafeCast");
		checkEqual(t1.size(),3,"size = 3 (after TypeSafeCast)");
		TestDoubleVector t3(4,2.0);
		checkEqual(t3.size(),4,"fill constructor: initial size = 4");
		checkEqualish(t3[3],2.0,"fill constructor, all elements are 2.0");
	}

	void checkStringVector() {
		report(0,"Checking VectorBottle<string> functions");
		TestStringVector t1;
		checkEqual(t1.size(),0,"initial size = 0");
		t1.add("one").add("two");
		checkEqual(t1.size(),2,"size set to 2");
		checkTrue(t1[0] == "one" && t1[1] == "two","add elements \"one\" and \"two\"");
		t1.set(1,"three");
		checkTrue(t1[1] == "three","set second element to \"three\"");
		bool thr1 = false;
		try {
			t1.set(2,"four");
		}
		catch (VectorBottleRangeError& e) {
			printCaughtException(e.what());
			thr1 = true;
		}
		checkTrue(thr1,"checking range error");
		bool thr2 = false;
		try {
			yarp::os::Bottle b; b.addString("one"); b.addList();
			TestStringVector t2 = TypeSafeCast<TestStringVector>(b,true);
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr2 = true;
		}
		checkTrue(thr2,"unallowable TypeSafeCast");
		bool thr3 = false;
		try {
			yarp::os::Bottle b; b.addString("five");
			t1 = TypeSafeCast<TestStringVector>(b,true);
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr3 = true;
		}
		checkFalse(thr3,"allowable TypeSafeCast");
		checkEqual(t1.size(),1,"size = 1 (after TypeSafeCast)");
		TestStringVector t3(4,yarp::os::ConstString("a"));
		checkEqual(t3.size(),4,"fill constructor: initial size = 4");
		checkTrue(t3[3] == "a","fill constructor, all elements are 1");
	}

	void checkVocabVector() {
		report(0,"Checking VectorBottle<vocab> functions");
		TestVocabVector t1;
		checkEqual(t1.size(),0,"initial size = 0");
		t1.add(VOCAB1('o')).add(VOCAB1('t'));
		checkEqual(t1.size(),2,"size set to 2");
		checkTrue(t1[0] == VOCAB1('o') && t1[1] == VOCAB1('t'),"add elements \"[o]\" and \"[t]\"");
		t1.set(1,VOCAB1('x'));
		checkTrue(t1[1] == VOCAB1('x'),"set second element to \"[x]\"");
		bool thr1 = false;
		try {
			t1.set(2,VOCAB1('z'));
		}
		catch (VectorBottleRangeError& e) {
			printCaughtException(e.what());
			thr1 = true;
		}
		checkTrue(thr1,"checking range error");
		bool thr2 = false;
		try {
			yarp::os::Bottle b; b.addInt(1); b.addString("one"); b.addDouble(1.0);
			TestVocabVector t2 = TypeSafeCast<TestVocabVector>(b,true);
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr2 = true;
		}
		checkTrue(thr2,"unallowable TypeSafeCast");
		bool thr3 = false;
		try {
			yarp::os::Bottle b; b.addVocab(1); b.addVocab(2); b.addVocab(3);
			t1 = TypeSafeCast<TestVocabVector>(b,true);
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr3 = true;
		}
		checkFalse(thr3,"allowable TypeSafeCast");
		checkEqual(t1.size(),3,"size = 3 (after TypeSafeCast)");
		TestIntVector t3(4,1);
		checkEqual(t3.size(),4,"fill constructor: initial size = 4");
		checkTrue(t3[3] == 1,"fill constructor, all elements are 1");
	}

	void checkDictionaryVector() {
		report(0,"Checking VectorBottle<dictionary> functions");
		TestDictionaryVector t1;
		checkEqual(t1.size(),0,"initial size = 0");
		t1.add(AnotherTestDictionary::oneID).add(AnotherTestDictionary::twoID);
		checkEqual(t1.size(),2,"size set to 2");
		checkEqual(t1[0],AnotherTestDictionary::oneID,"added element \"[one]\"");
		checkEqual(t1[1],AnotherTestDictionary::twoID,"added element \"[two]\"");
		t1.set(1,AnotherTestDictionary::oneID);
		checkEqual(t1[1],AnotherTestDictionary::oneID,"set second element to \"[one]\"");
		bool thr1 = false;
		try {
			t1.set(2,AnotherTestDictionary::oneID);
		}
		catch (VectorBottleRangeError& e) {
			printCaughtException(e.what());
			thr1 = true;
		}
		checkTrue(thr1,"checking range error");
		bool thr2 = false;
		try {
			yarp::os::Bottle b; b.addVocab(AnotherTestDictionary::oneID); b.addVocab(TestDictionary::fourID);
			TestDictionaryVector t2 = TypeSafeCast<TestDictionaryVector>(b,true);
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr2 = true;
		}
		checkTrue(thr2,"unallowable TypeSafeCast");
		bool thr3 = false;
		try {
			yarp::os::Bottle b; b.addVocab(AnotherTestDictionary::oneID);
			t1 = TypeSafeCast<TestDictionaryVector>(b,true);
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr3 = true;
		}
		checkFalse(thr3,"allowable TypeSafeCast");
		checkEqual(t1.size(),1,"size = 1 (after TypeSafeCast)");
		TestDictionaryVector t3(4,AnotherTestDictionary::twoID);
		checkEqual(t3.size(),4,"fill constructor: initial size = 4");
		checkTrue(t3[3] == VOCAB3('t','w','o'),"fill constructor, all elements are AnotherTestDictionary::twoID");
	}

	void checkStructVector() {
		report(0,"Checking VectorBottle<struct> functions");
		TestStructVector t1;
		checkEqual(t1.size(),0,"initial size = 0");
		t1.add(TestStructStruct()).add(TestStructStruct());
		checkEqual(t1.size(),2,"size set to 2");
		t1[1].aStruct().setanInt(3);
		checkEqual(t1[0].aStruct().anInt(),0,"first element \"0\"");
		checkEqual(t1[1].aStruct().anInt(),3,"second element \"3\"");
		t1[1] = TestStructStruct();
		checkEqual(t1[1].aStruct().anInt(),0,"set second element to \"0\"");
		bool thr1 = false;
		try {
			t1[2] = TestStructStruct();
		}
		catch (VectorBottleRangeError& e) {
			printCaughtException(e.what());
			thr1 = true;
		}
		checkTrue(thr1,"checking range error");
		bool thr2 = false;
		try {
			yarp::os::Bottle b; 
			yarp::os::Bottle& sb = b.addList();
			sb.addString("aStruct");
            yarp::os::Bottle& ssb = sb.addList();
			ssb = TestDoubleStruct();
			TestStructVector t2 = TypeSafeCast<TestStructVector>(b,true);
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr2 = true;
		}
		checkTrue(thr2,"unallowable TypeSafeCast");
		bool thr3 = false;
		try {
			yarp::os::Bottle b;
			yarp::os::Bottle& sb = b.addList();
			sb = TestStructStruct();
			t1 = TypeSafeCast<TestStructVector>(b,true);
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr3 = true;
		}
		checkFalse(thr3,"allowable TypeSafeCast");
		checkEqual(t1.size(),1,"size = 1 (after TypeSafeCast)");
		TestStructStruct ts; 
		ts.aStruct().setanInt(1);
		TestStructVector t3(4,ts);
		checkEqual(t3.size(),4,"fill constructor: initial size = 4");
		checkEqual(t3[3].aStruct().anInt(),1,"fill constructor, all elements should have int value of 1");
	}

    virtual void runTests() {
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        checkIntVector();
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		checkDoubleVector();
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		checkStringVector();
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		checkVocabVector();
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		checkDictionaryVector();
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		checkStructVector();
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    }

private:

	void checkConstReference(const TestStructVector& t) {
	     const TestStructStruct& s = t[0];
		 const TestIntStruct& i = s.aStruct();
	}

	void printCaughtException(const char* c) {
		std::cout << "==============TypeCheckError Caught=================" << std::endl;
		std::cout << c;
		std::cout << "====================================================" << std::endl;
	}
};

static VectorBottleTest theVectorBottleTest;

UnitTest& getVectorBottleTest() {
    return theVectorBottleTest;
}

} //end namespace test
} //end namespace msg
} //end namespace darwin