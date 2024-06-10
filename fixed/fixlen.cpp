// fixlen.cpp

#include "fixlen.h"
#include <cstring>

//class FixedLengthBuffer

// public members

 // construct with a maximum of maxFields
FixedLengthBuffer::FixedLengthBuffer (int recordSize)
: IOBuffer (recordSize)
{
	Init (recordSize);
}

// clear fields from buffer
void FixedLengthBuffer::Clear ()
{
	IOBuffer::Clear ();
	Buffer[0]=0;
	Packing = TRUE;
}

// write the number of bytes in the buffer field definitions
int FixedLengthBuffer::Read(istream & stream)
{
	int recaddr = stream.tellg (); stream.clear();
	Clear ();
	Packing = FALSE;
	stream.read(Buffer, BufferSize);
	if ( !stream.good() ) {stream.clear(); return recaddr;}
	return recaddr;
}


// read the number of bytes in the buffer field definitions
// return the location of the record in the file
int FixedLengthBuffer::Write(ostream & stream) const
{
	int recaddr = stream.tellp ();
	stream.write (Buffer, BufferSize);
	if (! stream.good()) return -1;
	return recaddr;
}

void FixedLengthBuffer::Print(ostream & stream) const
{
	IOBuffer::Print (stream);
	stream <<  "Fixed ";
}

// construct with a maximum of maxFields
int FixedLengthBuffer::Init(int recordSize)
{
	Clear ();
	BufferSize = recordSize;
	return 1;
}

// construct with a maximum of maxFields
int FixedLengthBuffer::ChangeRecordSize (int recordSize)
{
	BufferSize = recordSize;
	return 1;
}
