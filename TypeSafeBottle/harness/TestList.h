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
 * @file TestList.h
 * @brief Class listing all unit tests of darwin::common
 */

#pragma once

//yarp includes
#pragma warning(push)
#pragma warning(disable: 4996)
#include <yarp/os/impl/UnitTest.h>
#pragma warning(pop)

namespace darwin {
    namespace msg {
		namespace test {
            class TestList;
		}
    }
}

namespace darwin {
	namespace msg {
		namespace test {

// list one function for each new test, and add to collectTests() method.
extern yarp::os::impl::UnitTest& getVocabDictionaryTest();
extern yarp::os::impl::UnitTest& getStructBottleTest();
extern yarp::os::impl::UnitTest& getVectorBottleTest();
extern yarp::os::impl::UnitTest& getWrapperBottleTest();

class TestList {
public:
    static void collectTests() {
        yarp::os::impl::UnitTest& root = yarp::os::impl::UnitTest::getRoot();
        root.add(getVocabDictionaryTest());
		root.add(getStructBottleTest());
		root.add(getVectorBottleTest());
		root.add(getWrapperBottleTest());
    }
};

} //end namespace test
} //end namespace msg
} //end namespace darwin

//----- end-of-file --- ( next line intentionally left blank ) ------------------

