//tstbtree.cc
#include "btnode.h"
#include "./btindex/btnode.cpp" // for template method body
#include "btree.h"
#include "./btindex/btree.cpp"   // for template method body
#include <iostream>

using namespace std;

const char * keys="CSDTAMPIBWNGURKEHOLJYQZFXV";

// for template separate compile

//template class SimpleIndex<char>;
//template class BTree<char>;
//template class BTreeNode<char>;
//template class RecordFile<BTreeNode<char> >;


const int BTreeSize = 4;
int main (int argc, char ** argv)
{
	int result, i;
	BTree <char> bt (BTreeSize);
	result = bt.Create ("testbt.dat",ios::in|ios::out);
	if (!result){cout<<"Please delete testbt.dat"<<endl;return 0;}
	for (i = 0; i<26; i++)
	{
		cout<<"Inserting "<<keys[i]<<endl;
		result = bt.Insert(keys[i],i);
		bt.Print(cout);
	}
	result = bt.Insert(keys[20], 224);//
	cout << bt.Search('A',1);
	return 1;
}