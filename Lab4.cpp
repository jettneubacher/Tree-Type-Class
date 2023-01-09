/*
 * Author: Jett Neubacher
 * Date Last Modified: 11/18/2022
 * Lab4.cpp
*/

#include<iostream>
#include"ItemType.h"
#include"TreeType.h"
using namespace std;

int main()
{
   char user = 'x'; // variable for user command input
   TreeType tree; // declare tree
   while (user != 'Q') // while loop that allows user to run various commands on the tree until the wish to quit (input Q to quit)
   {
	   cout << "I(insert), D(delete), P(print), C(count), L(leaf count), A(ancestors), S(swap), E(empty), Q(quit)" << endl;
	   cout << "Enter command: "; cin >> user;
	   if (user == 'I') // insert a node into the tree
	   {
		   char input; cout << "Enter input: "; cin >> input;
		   ItemType insert; insert.Initialize(input);
		   tree.InsertItem(insert);
	   }
	   else if (user == 'D') // delete a node from the tree
	   {
		   char input; cout << "Enter item to delete: "; cin >> input;
		   ItemType deletion; deletion.Initialize(input);
		   tree.DeleteItem(deletion);
	   }
	   else if (user == 'P') // print out the tree in 3 different ways
	   {
		   OrderType order;
		   ItemType item;
		   bool finished = false;
		   cout << "In-Order: " << endl << "  ";
		   order = IN_ORDER;
		   tree.ResetTree(order);
		   if (tree.GetLength() == 0) finished = true;
		   while (!finished)
		   {
			tree.GetNextItem(item, order, finished); item.Print(); cout << "  ";
		   }
		   cout << endl;
		   finished = false;
		   cout << "Pre-Order: " << endl << "  "; order = PRE_ORDER;  tree.ResetTree(PRE_ORDER);
		   if (tree.GetLength() == 0) finished = true;
		   while(!finished)
		   {
			   tree.GetNextItem(item, order, finished); item.Print(); cout << "  ";
		   }
		   cout << endl;
		   finished = false;
		   cout << "Post-Order: " << endl << "  "; order = POST_ORDER;
		   tree.ResetTree(POST_ORDER);
		   if (tree.GetLength() == 0) finished = true;
		   while(!finished)
		   {
			   tree.GetNextItem(item, order, finished); item.Print(); cout << "  ";
		   }
		   cout << endl;
	   }
	   else if (user == 'C') // print out the number of nodes
	   {
		   int length = tree.GetLength(); cout << "Tree has " << length << " nodes" << endl;
	   }
	   else if (user == 'L') // print out the number of leaf nodes
	   {
		   int length = tree.LeafCount(); cout << "Tree has " << length << " leaf nodes" << endl;
	   }
	   else if (user == 'A') // print out the ancestory of a node
	   {
		   char input; cout << "Enter item to find ancestory of: "; cin >> input;
		   ItemType ancestor; ancestor.Initialize(input);
		   tree.Ancestors(ancestor);
	   }
	   else if (user == 'S') // swap tree and print out the new swapped tree in order
	   {
		   TreeType newTree(tree);
		   tree.Swap(newTree);
		   newTree.Print();
	   }
	   else if (user == 'E') // empty the tree
	   {
		   tree.MakeEmpty();
	   }
   }
   return 0;
}
