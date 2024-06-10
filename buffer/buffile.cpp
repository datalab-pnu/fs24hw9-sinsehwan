// buffile.cpp

#include "buffile.h"

 // create with a buffer
BufferFile::BufferFile (IOBuffer & from) : Buffer(from)
{
}

// Access to IOBuffer
IOBuffer & BufferFile::GetBuffer()
{ return Buffer;}


// create a new file and write a header on it.
// use ios::nocreate to ensure that no file exists
int BufferFile::Create (char * filename, ios_base::openmode mode)
{
	//if (!(mode & ios::out)) return FALSE; // must include ios::out
	// File.open(filename, mode|ios::in|ios::out|ios::noreplace|ios::bin);
	if (!(mode & ios::out)) return FALSE; // must include ios::out
	File.open(filename, mode|ios::in|ios::out|ios::app|ios::binary);
	if (!File.good()) 
	{
		File.close();
		return FALSE;
	}
	HeaderSize = WriteHeader();
	return HeaderSize != 0;
}

// open an existing file and check the header
// a correct header must be on the file
// use ios::nocreate to ensure that a file exists
int BufferFile::Open(char * filename, ios_base::openmode mode)
{
	// these modes are not allowed when opening an existing file
	//if (mode&ios::noreplace||mode&ios::trunc) return FALSE;
	if (mode&ios::app||mode&ios::trunc) return FALSE;

	//File.open (filename, mode|ios::in|ios::nocreate|ios::bin);
	File.open (filename, mode|ios::in|ios::app|ios::binary);
	if (!File.good()) return FALSE;
	File.seekg(0, ios::beg); 
	File.seekp(0, ios::beg);
	HeaderSize = ReadHeader();
	if (!HeaderSize) // no header and file opened for output
		return FALSE;
	File.seekp (HeaderSize, ios::beg);
	File.seekg (HeaderSize, ios::beg);
	return File.good();
}


int BufferFile::Close ()
{
	File.close();
	return TRUE;
}

int BufferFile::Rewind()
{
	File.seekg (HeaderSize, ios::beg);
	File.seekp (HeaderSize, ios::beg);
	return 1;
}

// Input and Output operations

// read a record into the buffer
// return the record address
// return <0 if read failed
// if recaddr == -1, read the next record in the File
// if recaddr != -1, read the record at that address
int BufferFile::Read (int recaddr)
{
	if (recaddr == -1)
		return Buffer.Read (File);
	else
		return Buffer.DRead (File, recaddr);
}

// write the current buffer contents 
int BufferFile::Write (int recaddr)
{
	if (recaddr == -1)
		return Buffer.Write (File);
	else
		return Buffer.DWrite (File, recaddr);
}

// write the current buffer at the end of File
int BufferFile::Append ()
{
	File.seekp (0, ios::end);
	return Buffer.Write (File);
}




// protected methods
int BufferFile::ReadHeader ()
{
	return Buffer.ReadHeader(File);	
}

int BufferFile::WriteHeader ()
{
	return Buffer.WriteHeader(File);
}


