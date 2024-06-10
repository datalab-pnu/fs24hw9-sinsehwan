#ifndef FIXFLD_H
#define FIXFLD_H

#include <cstdlib>
#include <iostream>
#include "fixlen.h"


// Abstract class designed to support fixed length records
// Use of this class requires that all fields be defined before
//    reading and writing can take place
class FixedFieldBuffer: public FixedLengthBuffer
{
 public:
	FixedFieldBuffer (int maxFields, int RecordSize = 1000);
	FixedFieldBuffer (int maxFields, int * fieldSize);
	// initialize all fields at once
	void Clear (); // clear values from buffer

 	int Init (int maxFields);
	int Init (int numFields, int * fieldSize);
	int AddField (int fieldSize); // define the next field

	int Pack (const void * field, int size = -1); // set the value of the next field of the buffer;
	int Unpack (void * field, int maxBytes = -1); // extract the value of the next field of the buffer
	void Print (ostream &) const;
	int NumberOfFields () const; // return number of defined fields

 protected:
	int * FieldSize; // array to hold field sizes
	int MaxFields; // maximum number of fields
	int NumFields; // actual number of defined fields
	int NextField; // index of next field to be packed/unpacked

};

#endif
