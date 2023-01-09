/***********************************************
 * File : TreeType.h
 * Date : 10/10/08
 * Description : Header file of Class TreeType 
 *               A binary search tree
 **********************************************/
#ifndef TREETYPE_H
#define TREETYPE_H

#include <iostream>
#include <fstream>
using namespace std;

#include <queue>

#include "ItemType.h"


class TreeNode{

public:
   ItemType info;
   TreeNode * left;
   TreeNode * right;   
}; 

enum OrderType {PRE_ORDER, IN_ORDER, POST_ORDER};

class TreeType
{
public:
   TreeType();
   ~TreeType();
 
   TreeType(const TreeType & originalTree); //copy constructor
   void operator=(const TreeType & originalTree);

   void MakeEmpty();

   bool IsEmpty() const;
   bool IsFull() const;

   int GetLength() const;  //how many nodes in the tree
   int LeafCount() const;  //how many leaf nodes in the tree
   

   void RetrieveItem( ItemType & item, bool & found) const;
   void InsertItem ( ItemType  item);
   void DeleteItem ( ItemType  item);

   void ResetTree(OrderType order);
   void GetNextItem(ItemType & item, OrderType order, bool & finished);

   // void Print(ofstream & output) const;
   void Print() const;

   void Ancestors(ItemType item) const; // print ancestors of an item in the tree
   void Swap(TreeType & newTree); // original tree unchanged, new tree is a mirror image of original

private:

   TreeNode * root;

   queue<ItemType> * preQue;
   queue<ItemType> * inQue;
   queue<ItemType> * postQue;

   void Destroy(TreeNode *& tree);
   void CopyTree(TreeNode *& copy, const TreeNode * originalTree);

   int Count(TreeNode * tree) const;
   int CountLeaf(TreeNode * tree) const; // used by LeafCount function
   void Retrieve(TreeNode * tree, ItemType & item, bool &found) const;
   void RetrieveAncestors(TreeNode * tree, ItemType item) const; // used in Ancestors function
   void Insert(TreeNode *& tree, ItemType item);
  
   void Delete(TreeNode *& tree, ItemType item);
   void DeleteNode(TreeNode *& tree); // updated to replace node with immediate successor
   void GetPredecessor (TreeNode * tree, ItemType & item);
   void GetSuccessor(TreeNode * tree, ItemType & item); // used for updated DeleteNode function
   void PrintTree(TreeNode * tree) const;

   void SwapChildren(TreeNode* tree); // recursive function that swaps children of a root node

   void PreOrder(TreeNode* tree, queue<ItemType> *& preQue);
   void InOrder (TreeNode* tree, queue<ItemType> *& inQue);
   void PostOrder(TreeNode* tree, queue<ItemType> *& postQue);
};

#endif

