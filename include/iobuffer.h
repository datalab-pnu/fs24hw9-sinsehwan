#ifndef IOBUFFER_H
#define IOBUFFER_H

#include <cstdlib>
#include <iostream>

#ifndef FALSE
#define FALSE (0)
#define TRUE (1)
#endif

using namespace std;

class IOBuffer
{
public:
    IOBuffer(int maxBytes =1000);
    virtual void Clear(); // clear fields from buffer
    int Init(int MaxBytes);

    virtual int Read(istream &) =0; //read a buffer
    virtual int Write(ostream &) const =0; //write a buffer

    virtual int Pack(const void* field, int size=-1) =0;
    virtual int Unpack(void* field, int maxbytes = -1) =0;

	// these are the direct access read and write operations
	virtual int DRead(istream &, int recref); // read specified record
	virtual int DWrite(ostream &, int recref) const; // write specified record

	// these header operations return the number of bytes in the header
	virtual int ReadHeader(istream &); // write a buffer to the stream
	virtual int WriteHeader(ostream &) const; // write a buffer to the stream    

    virtual void Print(ostream &) const;
    
protected:
    int Initialized; // TRUE if buffer is initialized
    char *Buffer; //character array to hold field values
    int BufferSize; // sum of the sizes of packed fields
    int MaxBytes; //max # of char in the buffer
    int NextByte; // index of next byte to be packed/unpacked
    int Packing;  // TRUE if in packing mode, FALSE, if unpacking
};

#endif

