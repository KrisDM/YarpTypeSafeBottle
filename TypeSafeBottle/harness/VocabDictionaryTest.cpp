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
 * @file VocabDictionaryTest.cpp
 * @brief Unit test class to test VocabDictionary classes
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

class VocabDictionaryTest : public UnitTest {
public:
    virtual String getName() { return "VocabDictionaryTest"; }

	void checkIs() {
		report(0,"Checking VocabDictionary \"is\" functions");
		checkFalse(TestDictionary::iso(VOCAB1('a')),"checking false o = a");
		checkFalse(TestDictionary::istw(TestDictionary::oID),"checking false tw = o");
		checkTrue(TestDictionary::iso(VOCAB1('o')),"testing o = o");
		checkTrue(TestDictionary::iso(TestDictionary::oID),"oID self test");
		checkTrue(TestDictionary::istw(TestDictionary::twID),"twID self test");
		checkTrue(TestDictionary::isthr(TestDictionary::thrID),"thrID self test");
		checkTrue(TestDictionary::isfour(TestDictionary::fourID),"fourID self test");
	}

	void checkTypeCheck() {
		report(0,"Checking VocabDictionary \"type_check\" function");
		checkFalse(TestDictionaryTypeCheckErrorThrown(TestDictionary::oID),"type-checking o");
		checkFalse(TestDictionaryTypeCheckErrorThrown(TestDictionary::twID),"type-checking tw");
		checkFalse(TestDictionaryTypeCheckErrorThrown(TestDictionary::thrID),"type-checking thr");
		checkFalse(TestDictionaryTypeCheckErrorThrown(TestDictionary::fourID),"type-checking four");
		checkFalse(TestDictionaryTypeCheckErrorThrown(0),"type-checking 0");
		checkTrue(TestDictionaryTypeCheckErrorThrown(VOCAB1('a')),"type-checking a (exception expected");
	}

	void checkValueStr() {
		report(0,"Checking VocabDictionary \"valueStr\" function");
		checkTrue(TestDictionaryValueStrConversion(TestDictionary::oID),"checking valueStr o");
		checkTrue(TestDictionaryValueStrConversion(TestDictionary::twID),"checking valueStr tw");
		checkTrue(TestDictionaryValueStrConversion(TestDictionary::thrID),"checking valueStr thr");
		checkTrue(TestDictionaryValueStrConversion(TestDictionary::fourID),"checking valueStr four");
		checkFalse(TestDictionaryValueStrConversion(0),"checking valueStr 0");
		checkFalse(TestDictionaryValueStrConversion(VOCAB1('a')),"checking valueStr a");
	}

	void checkTypeSafeCast() {
		report(0,"Checking TypeSafeCast for int values");
		checkFalse(TestDictionaryTypeSafeCast(TestDictionary::oID),"checking typecast o");
		checkTrue(TestDictionaryTypeSafeCast(VOCAB1('a')),"checking typecast a, exception expected");
	}
		

    virtual void runTests() {
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        checkIs();
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		checkTypeCheck();
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		checkValueStr();
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		checkTypeSafeCast();
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    }

private:
	bool TestDictionaryTypeCheckErrorThrown(int testcase) {
		bool check = false;
		try {
			TestDictionary::type_check(testcase);
		}
		catch (TypeCheckError& e) {
			std::cout << "==============TypeCheckError Caught=================" << std::endl;
			std::cout << e.what();
			std::cout << "====================================================" << std::endl;
			check = true;
		}
		return check;
	}
	bool TestDictionaryTypeSafeCast(int testcase) {
		bool check = false;
		try {
			TestDictionary::value v = TypeSafeCast<TestDictionary>(testcase,true);
		}
		catch (TypeCheckError& e) {
			std::cout << "==============TypeCheckError Caught=================" << std::endl;
			std::cout << e.what();
			std::cout << "====================================================" << std::endl;
			check = true;
		}
		return check;
	}
	bool TestDictionaryValueStrConversion(int testcase) {
		yarp::os::ConstString valuestr = TestDictionary::valueStr(testcase);
		yarp::os::Value convertedval(valuestr.c_str(),true);
		return convertedval.asVocab() == testcase;
	}
};

static VocabDictionaryTest theVocabDictionaryTest;

UnitTest& getVocabDictionaryTest() {
    return theVocabDictionaryTest;
}

} //end namespace test
} //end namespace msg
} //end namespace darwin