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
 * @file harness.cpp
 * @brief Main file for running unit tests of TypeSafeBottle
 */
 
#include <yarp/conf/system.h>
#include <yarp/os/Network.h>

#pragma warning(push)
#pragma warning(disable: 4996)
#include <yarp/os/impl/UnitTest.h>
#pragma warning(pop)

#include "TestList.h"

using namespace yarp::os::impl;
using namespace darwin::msg::test;

int main(int argc, char *argv[]) {
    yarp::os::Network yarp;

    bool done = false;
    int result = 0;

    if (argc>1) {
        if (String(argv[1])==String("regression")) {
            done = true;
            UnitTest::startTestSystem();
            TestList::collectTests();  // just in case automation doesn't work
            if (argc>2) {
                result = UnitTest::getRoot().run(argc-2,argv+2);
            } else {
                result = UnitTest::getRoot().run();
            }
            UnitTest::stopTestSystem();
        }
    }

    return result;
}