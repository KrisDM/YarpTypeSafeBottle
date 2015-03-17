/* TypeSafeTutorial.cpp
 * Copyright (C) 2013, King's College London
 * Authors: Kris De Meyer
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later
 */

#include <yarp/os/BufferedPort.h>
#include "TestMessages/TestBottles.h"
#include <iostream>

using namespace std;
using namespace darwin::msg::test;

void write(const char* pre,const yarp::os::ConstString& str) {
	cout << pre << str << endl;
}

int main( int argc, const char* argv[] )
{
	//Create a Name/Value pair and set its fields
	Pair p1;
	//Values are default values
	write("Empty Pair p1: ",p1.toString());
	//You can chain the "set" commands
	p1.setName("A").setValue(10); 

	//Create a Name/Value pair, assign, and change its "Value" field
	Pair p2 = p1;
	p2.setValue(100);
	write("Pair p1: ",p1.toString());
	write("Pair p2: ",p2.toString());


	//Copy-construct a Name/Value pair, then change the "Name" field
	Pair p3(p2);
	p3.setName("B");
	write("Pair p1: ",p1.toString());
	write("Pair p2: ",p2.toString());
	write("Pair p3: ",p3.toString());

	cout << endl << endl;

	PairVector pv1;
	pv1.add(p1).add(p2);
	write("PairVector pv1: ",pv1.toString());
	PairVector pv2 = pv1;
	write("PairVector pv2 after copy constructor: ",pv2.toString());
	PairVector pv3;
	pv3.add(Pair());
	pv2 = pv3;
	write("PairVector pv2 after first assignment operation: ",pv2.toString());
	pv3.add(Pair()).add(Pair()).add(p3);
	write("PairVector pv2 before second assignment operation: ",pv2.toString());
	pv2 = pv3;
	write("PairVector pv2 after second assignment operation: ",pv2.toString());

	cout << endl << endl;

	//Create a trio of int/double/string data
	Trio t1;
	//You can chain the "set" commands
	t1.setanInt(3).setaDouble(3.14).setaString("Hello"); 
	write("Trio t1: ",t1.toString());
	//Access all the individual elements
	cout << "Individual elements: " << t1.anInt() << ' ' << t1.aDouble() << ' ' << t1.aString() << endl;

	cout << endl << endl;

	//Create composites
	Composite comp1,comp2;
	comp1.pair() = p1;
	comp1.trio() = t1;
	comp1.morepairs().add(p3).add(p2).add(p1);
	comp2.morepairs().add(p1).add(p2);

	CompositeVector compvec1,compvec2;
	write("CompositeVector compvec1 after creation (should be empty): ",compvec1.toString());
	write("CompositeVector compvec2 after creation (should be empty): ",compvec2.toString());
	compvec1.add(comp1).add(comp2);
	compvec2 = compvec1;
	write("CompositeVector compvec1 (after fill): ",compvec1.toString());
	write("CompositeVector compvec2 (after copy): ",compvec2.toString());


	//Create a vector of ints
	IntVector ib1;
	//This vector is still empty
	write("Empty IntVector ib1: ",ib1.toString());
	//Add some elements
	for(int i=0;i<4;++i) {
		ib1.add(i);
	}
	write("IntVector ib1: ",ib1.toString());
	//Return the value at index 2
	cout << "Index 2 of ib1: " << ib1[2] << endl;  
	//Set the value at index 2 to 10
	ib1.set(2,10);
	write("IntVector ib1: ",ib1.toString());
	
	//Create a new vector, then assign all values from previous
	IntVector ib2 = ib1;
	write("IntVector ib2: ",ib2.toString());
	//Clear the first vector
	ib1.clear();
	write("Cleared IntVector ib1: ",ib1.toString());
	//Now copy the first vector to second (will empty it)
	ib2 = ib1;
	write("Empty IntVector ib2: ",ib2.toString());
	cout << endl << endl;

	VocabVector vb1;
	vb1.add(VOCAB3('s','t','a'));
	vb1.add(VOCAB3('s','t','o'));
	write("VocabBottle vb1: ",vb1.toString());
	cout << "Individual element access returns int value: " << vb1[0] << ' ' << vb1[1] << endl;
	vb1.set(1,VOCAB4('s','t','o','p'));
	write("VocabBottle vb1: ",vb1.toString());
	cout << endl << endl;

	//Creates an object that contains a bit of everything
	Everything ev1;
	//All default values or empty lists
	write("Empty Everything ev1: ",ev1.toString());
	//Add a vocab element
	ev1.setaVocab(VOCAB3('p','a','u'));
	//Copy a Name/Value pair
	ev1.aPair() = p1;
	//Copy a trio
	ev1.aTrio() = t1;
	//Copy a vector of ints (but it's still empty - see above)
    ev1.anIntVector() = ib1;
	//Add a value to the vector
	ev1.anIntVector().add(20);

	ev1.aVocabVector() = vb1;
	//Add 3 pairs to the object
	ev1.aPairVector().add(p1).add(p2).add(p3);
	//Now copy the values of p2 to the third element in the vector
	ev1.aPairVector().operator[](2) = p2;
	write("Everything ev1: ",ev1.toString());

	//Create another Everything object
	Everything ev2;
	//Copy the values of p1 across
	ev2.aPair() = p1;
	//Change the Value field (of local "aPair", but not of p1)
	ev2.aPair().setValue(1000);
	//Add a few strings to the aStringVector field
	ev2.aStringVector().add("Hello, ").add("World").add("\n");
	write("Everything ev2: ",ev2.toString());
	write("Contents of aStringVector: ",ev2.aStringVector().toString());
	cout << "Individual elements (last one is newline): " << ev2.aStringVector()[0] << ev2.aStringVector()[1] << ev2.aStringVector()[2] << endl;
	//Add this Everything object to the vector of the first Everything (we now have recursive containment)
	ev1.anEverythingVector().add(ev2);
	write("Everything ev1: ",ev1.toString());

	//now try to access a vector with an out-of-range index, you'll get an exception
	cout << endl << "Expecting an out-of-range exception:" << endl;
	try {
		int i = ib1[10];
	}
	catch (const VectorBottleRangeError& e) {
		cout << e.what() << endl;
	}

	//try to set a vector value with an out-of-range index, you'll get another exception
	cout << "Expecting an out-of-range exception:" << endl;
	try {
		ib1.set(20,10);
	}
	catch (const VectorBottleRangeError& e) {
		cout << e.what() << endl;
	}
	
	//now create a wrapper to send different message formats over the same port or buffered port
	//the wrapper contains as first field a subID that allows the type of message to be reconstructed 
	//by the receiver
	Anything any1;

	//wrapping a Pair object, the compiler will warn if you try to wrap a Trio object using the function "pair"
	any1.pair(p3);
	write("Anything any1 with Pair: ",any1.toString());
	//wrap a Trio object using the "trio" function, again typesafe.
	any1.trio(t1);
	write("Anything any1 with Trio: ",any1.toString());
	//now wrap an Everything object, which is indicated by the "all" subID
	any1.all(ev1);
	write("Anything any1 with Everything: ",any1.toString());
	//we know there's an "all" subID message, so we can index it to get to the inner "aPair" field
	cout << endl << endl;
	write("Everything.aPair extracted from wrapper: ",any1.all().aPair().toString());
	//now we'll get an exception, as we're trying to extract a "pair" subID object whereas the wrapper contains an "all" subID object
	cout << endl << "Expecting an exception because we're trying to extract something from the wrapper that isn't wrapped:" << endl;
	try {
		any1.pair().toString();
	}
	catch (const WrapperBottleIDError& e) {
		cout << e.what() << endl << endl;
	}
	//now give the wrapper a Pair to wrap:
	any1.pair(p3);

	//this is the safe way to handle wrapped messages
	//Anything::xxxxID::value is an enum value, therefore a constant expression which can be used as case labels
	//This is safer to use than "case VOCAB4('p','a','i','r'):" as the compiler can't check if you spell "pair" correctly
	switch (any1.subID()) {
	case Anything::pairID::value: {
		cout << "Now it's safe to use the pair() member function to extract the wrapped message" << endl;
		Pair pwrap = any1.pair();
		write("Pair extracted from wrapper: ",pwrap.toString());
		break;
	}
	case Anything::trioID::value: {
		cout << "Now it's safe to use the trio() member function to extract the wrapped message" << endl;
		Trio twrap = any1.trio();
		write("Trio extracted from wrapper: ",twrap.toString());
		break;
	}
	case Anything::allID::value: {
		cout << "Now it's safe to use the all() member function to extract the wrapped message" << endl;
		Everything awrap = any1.all();
		write("Everything extracted from wrapper: ",awrap.toString());
		break;
	}
	default:
		cout << "Impossible to end up here. How did that happen?" << endl;
	}
	cout << endl << endl;
	cout << "SubID of WrapperBottle with Pair: " << any1.subID() << " SubID as String: " << any1.subIDStr() << endl;

	Anything any2;
	cout << "Printout of empty WrapperBottle: " << any2.toString() << endl;
	cout << "SubID of empty WrapperBottle: " << any2.subID() << " SubID as String: " << any2.subIDStr() << endl;
	

	yarp::os::BufferedPort<Pair> buffer;
	Pair& p = buffer.prepare();
	p = p1;
	write("Pair to be written over BufferedPort: ",p.toString());
	buffer.write();

	yarp::os::Port port;
	write("Anything with Pair to be written to Port: ",any1.toString());
	port.write(any1);

	cout << endl << endl << "Press enter to finish..." << endl;
	cin.ignore();
}

