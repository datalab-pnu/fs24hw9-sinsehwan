// fixfld.cpp

#include "fixfld.h"
#include <cstring>

//class FixedFieldBuffer

// public members

FixedFieldBuffer :: FixedFieldBuffer (int maxFields, int maxBytes)
 // construct with a maximum of maxFields
: FixedLengthBuffer(maxBytes)
{
	Init (maxFields);
}

// private function to calculate the record size from the field sizes
static int SumFieldSizes (int numFields, int * fieldSize)
{
	int sum = 0;
	for (int i = 0; i < numFields; i++)
		sum += fieldSize[i];
	return sum;
}

// construct with fields of specific size
FixedFieldBuffer :: FixedFieldBuffer (int numFields, int * fieldSize) 
: FixedLengthBuffer(SumFieldSizes(numFields, fieldSize))
{
	Init (numFields, fieldSize);
}


// clear fields from buffer
void FixedFieldBuffer :: Clear ()
{
	FixedLengthBuffer::Clear ();
	NextField = 0;
	Buffer[0]=0;
	Packing = TRUE;
}

 // construct with a maximum of maxFields
int FixedFieldBuffer :: Init (int maxFields)
{
	Clear ();
	if (maxFields < 0) maxFields = 0;
	MaxFields = maxFields;
	FieldSize = new int[MaxFields];
	BufferSize = 0;
	NumFields = 0;
	return 1;
}

// construct with fields of specific size
int FixedFieldBuffer :: Init (int numFields, int * fieldSize) 
{
	// initialize
	Initialized = TRUE;
	Init (numFields);

	// add fields
	for (int j = 0; j < numFields; j++)
		AddField (FieldSize[j]);
	return TRUE;
}



int FixedFieldBuffer::AddField (int fieldSize)
{
	Initialized = TRUE;
	if (NumFields == MaxFields) return FALSE;
	if (BufferSize + fieldSize > MaxBytes) return FALSE;
	FieldSize[NumFields] = fieldSize;
	NumFields ++;
	BufferSize += fieldSize;
	return TRUE;
}

// set the value of the next field of the buffer;
//    if size != -1, it must be the same as the packSize
// return number of bytes packed, -1 if error
int FixedFieldBuffer :: Pack (const void * field, int size)
{
//cout<<"Pack NumFields "<<NumFields<<" field "<<(char *)field<<endl;
	if (NextField == NumFields || !Packing) // buffer is full or not packing mode
		return -1;
	int start = NextByte; // first byte to be packed
	int packSize = FieldSize[NextField]; // number bytes to be packed
	if (size != -1 && packSize != size) return -1; 
	memcpy (&Buffer[start], field, packSize); // move bytes to buffer
	NextByte += packSize;
	NextField ++;
	if (NextField == NumFields) // all fields packed
	{
		Packing = -1;
		NextField = NextByte = 0;
	}
	return packSize;
}

// extract the value of the next field of the buffer
// return the number of bytes extracted, -1 if error
int FixedFieldBuffer :: Unpack (void * field, int maxBytes) 
{
	Packing = FALSE;
	if (NextField == NumFields) // buffer is full 
		return -1;
	int start = NextByte; // first byte to be unpacked
	int packSize = FieldSize[NextField]; // number bytes to be unpacked
	memcpy (field, &Buffer[start], packSize);
	NextByte += packSize;
	NextField ++;
	if (NextField == NumFields) Clear (); // all fields unpacked
	return packSize;
}

void FixedFieldBuffer :: Print (ostream & stream) const
{
	FixedLengthBuffer::Print (stream);
	stream << endl;
	stream << "\t max fields "<<MaxFields<<" and actual "<<NumFields<<endl;
	for (int i = 0; i < NumFields; i++)
		stream <<"\tfield "<<i<<" size "<<FieldSize[i]<<endl;
	Buffer[BufferSize]=0;
	stream <<"NextByte "<<NextByte<<endl;
	stream <<"Buffer '"<<Buffer<<"'"<<endl;
}

