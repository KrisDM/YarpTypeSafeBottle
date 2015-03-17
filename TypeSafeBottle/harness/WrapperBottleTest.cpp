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
 * @file UtilTest.cpp
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

class WrapperBottleTest : public UnitTest {
public:
    virtual String getName() { return "WrapperBottleTest"; }

	void checkWrapper() {
		report(0,"Checking WrapperBottle functions");
		TestWrapper tw1;
		checkEqual(tw1.subID(),0,"initial subID = 0");
		tw1.is(TestIntStruct());
		checkTrue(tw1.isis(),"TestIntStruct = true");
		checkFalse(tw1.isiv(),"TestIntVector= false");
		checkFalse(tw1.isdv(),"TestDictionaryVector = false");
		tw1.iv(TestIntVector());
		checkFalse(tw1.isis(),"TestIntStruct = false");
		checkTrue(tw1.isiv(),"TestIntVector= true");
		checkFalse(tw1.isdv(),"TestDictionaryVector = false");
		tw1.dv(TestDictionaryVector()); 
		std::cout << tw1.toString() << std::endl;
		tw1.dv().add(AnotherTestDictionary::oneID);
		tw1.dv().add(AnotherTestDictionary::twoID);
		std::cout << tw1.toString() << std::endl;
		checkFalse(tw1.isis(),"TestIntStruct = false");
		checkFalse(tw1.isiv(),"TestIntVector= true");
		checkTrue(tw1.isdv(),"TestDictionaryVector = false");
		bool switchtest = false;
		switch (tw1.subID()) {
		case TestWrapper::isID::value:
		case TestWrapper::ivID::value:
			break;
		case TestWrapper::dvID::value:
			switchtest = true;
		}
		checkTrue(switchtest,"testing WrapperBottle unwrap switch");
		bool iderror = false;
		try {
			TestIntStruct s = tw1.is();
		}
		catch (WrapperBottleIDError& e) {
			printCaughtException(e.what());
			iderror = true;
		}
		checkTrue(iderror,"unallowable unwrap, WrapperBottleIDError expected");
		bool thr1 = false;
		try {
			yarp::os::Bottle b;
			b.addVocab(VOCAB4('d','u','m','m'));
			b.addList();
			TestWrapper tw2 = TypeSafeCast<TestWrapper>(b,true);
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr1 = true;
		}
		checkTrue(thr1,"unallowable TypeSafeCast");
		bool thr2 = false;
		try {
			yarp::os::Bottle b;
			b.addVocab(TestWrapper::dvID::value);
			yarp::os::Bottle& sb = b.addList();
			sb = TestIntStruct();
			TestWrapper tw2 = TypeSafeCast<TestWrapper>(b,true);
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr2 = true;
		}
		checkTrue(thr2,"unallowable TypeSafeCast");
		bool thr3 = false;
		try {
			yarp::os::Bottle b;
			b.addVocab(TestWrapper::isID::value);
			yarp::os::Bottle& sb = b.addList();
			sb = TestIntStruct();
			TestWrapper tw2 = TypeSafeCast<TestWrapper>(b,true);
		}
		catch (TypeCheckError& e) {
			printCaughtException(e.what());
			thr3 = true;
		}
		checkFalse(thr3,"allowable TypeSafeCast");
		tw1.tw(TestWrapper());
		checkTrue(tw1.istw(),"recursion check");
	}

    virtual void runTests() {
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        checkWrapper();
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    }

private:

	void checkConstReference(const TestWrapper& t) {
	     if (t.isdv()) {
			 TestDictionaryVector& d = t.dv();
			 d.add(AnotherTestDictionary::oneID);
		 }
	}

	void printCaughtException(const char* c) {
		std::cout << "==============TypeCheckError Caught=================" << std::endl;
		std::cout << c;
		std::cout << "====================================================" << std::endl;
	}
};

static WrapperBottleTest theWrapperBottleTest;

UnitTest& getWrapperBottleTest() {
    return theWrapperBottleTest;
}

} //end namespace test
} //end namespace msg
} //end namespace darwin