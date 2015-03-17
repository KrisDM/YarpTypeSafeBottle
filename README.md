# YarpTypeSafeBottle
Compile-time type-safe extension of the YARP Bottle class, with automatic C++ code generation.

Code and documentation for the TypeSafeBottle infrastructure to automatically generate compile-time type-safe C++ message-format classes for communication between YARP modules. Compatible with the standard but type-unsafe communication infrastructure of YARP, TypeSafeBottle offers the functionality to easily define complex message structures in XML and automatically generate (via XSLT) C++ classes implementing those message structures. 

These automatically-generated classes add ease of use and compile-time type-safety to the messaging infrastructure of YARP, and remove a bottleneck in defining efficient communication protocols between YARP modules (i.e., the need to manually construct messaging code and maintain consistency at the sending and receiving end). 
