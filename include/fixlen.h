#ifndef FIXLEN_H
#define FIXLEN_H

#include <cstdlib>
#include <iostream>
#include "iobuffer.h"


// Abstract class designed to support fixed length records
class FixedLengthBuffer: public IOBuffer
{
public:
	FixedLengthBuffer (int recordSize = 1000);
	FixedLengthBuffer (const FixedLengthBuffer & buffer); // copy constructor

	void Clear (); // clear values from buffer
	int Read (istream &);
	int Write (ostream &) const;

	void Print (ostream &) const;
	int SizeOfBuffer () const; // return size of buffer
protected:
 	int Init (int recordSize);
	int ChangeRecordSize (int recordSize);
};


#endif
