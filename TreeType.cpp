/********************************************************
 * File : TreeType.cpp
 * Date : 10/10/08
 * Description : Impelementation file of TreeType class
 ********************************************************/

#include "TreeType.h"
#include <new>

TreeType::TreeType()
{
   root = NULL;
   
   preQue = NULL;
   postQue = NULL;
   inQue = NULL;
}

TreeType::TreeType(const TreeType& originalTree)
{
   CopyTree(root, originalTree.root);
}

void TreeType::operator=(const TreeType& originalTree)
{
    if (&originalTree == this)
       return;

    Destroy(root);
    CopyTree(root, originalTree.root);
}


void TreeType::CopyTree(TreeNode *&copy, const TreeNode* originalTree)
{

    if (originalTree == NULL)
        copy = NULL;
    else
    {
      copy = new TreeNode;
      copy->info = originalTree->info;
      CopyTree(copy->left, originalTree->left);
      CopyTree(copy->right, originalTree->right);
    }
}


TreeType::~TreeType()
{
   MakeEmpty();  

   if (preQue !=NULL)  delete preQue;
   if (postQue != NULL) delete postQue;
   if (inQue != NULL) delete inQue;
}

void TreeType::Destroy(TreeNode *& tree)
{
   if (tree!= NULL)
   {
     Destroy(tree->left);
     Destroy(tree->right);
     delete tree;
   } 
}

void TreeType::MakeEmpty()
{
   Destroy(root);
   root = NULL;
}



bool TreeType::IsFull() const
{

  TreeNode * location;
  try{
     location = new TreeNode;
     delete location;
     return false;
  }catch( std::bad_alloc e){
    return true;
  }
}


bool TreeType::IsEmpty() const
{
   return root == NULL;

}

int TreeType::GetLength() const
{
    return Count(root);    
}

int TreeType::Count(TreeNode * tree) const
{
   if (tree == NULL)
       return 0;
   else
       return Count(tree->left) + Count(tree->right) +1;
}



void TreeType::RetrieveItem(ItemType & item, bool & found) const
{
    Retrieve(root, item, found);
}


void TreeType::Retrieve(TreeNode* tree, 
              ItemType& item, bool& found) const
{
  if (tree == NULL)   found = false;                     

  else if (item.ComparedTo(tree->info) == LESS)      
    Retrieve(tree->left, item, found);
  else if (item.ComparedTo(tree->info) == GREATER)
    Retrieve(tree->right, item, found);
  else
  {
    item = tree->info;
    found = true;
  }
}   


void TreeType::InsertItem(ItemType item)
{
   Insert(root, item);
}

void TreeType::Insert(TreeNode* & tree, ItemType item)
{
  if (tree == NULL)
  { // Insertion place found.
    tree = new TreeNode;
    tree->right = NULL;
    tree->left = NULL;
    tree->info = item;
  }
  else if (item.ComparedTo(tree->info) == LESS)
    Insert(tree->left, item);    
  else 
    Insert(tree->right, item);   
} 


void TreeType::DeleteItem(ItemType item)
{
    Delete(root, item);
}


// first, find which node should be deleted.
void TreeType::Delete(TreeNode*& tree, ItemType item)
{
  if (item.ComparedTo(tree->info) == LESS)
     Delete(tree->left, item);   
  else if (item.ComparedTo(tree->info) == GREATER)
     Delete(tree->right, item);  
  else
     DeleteNode(tree);  // Node found
} 

// updated
void TreeType::DeleteNode(TreeNode*&  tree) {
/*
       ItemType data;
       TreeNode* tempPtr;

        tempPtr = tree;

        if ( tree->left == NULL) {
              tree = tree->right;
              delete tempPtr; 
       } else if (tree->right == NULL){
              tree = tree->left;
              delete tempPtr;
       }else{
              GetPredecessor(tree->left, data);
               tree->info = data;
               Delete(tree->left, data);
        }
*/
   ItemType data; TreeNode* tempPtr;
   tempPtr = tree;
   if (tree->left == NULL) {
	   tree = tree->right;
	   delete tempPtr;
   }
   else if (tree->right == NULL) {
	   tree = tree->left;
	   delete tempPtr;
   }
   else {
	   GetSuccessor(tree, data); // call GetSuccessor function to replace deleted item with immediate successor
	   tree->info = data;
	   Delete(tree->right, data);
   }
} 

void TreeType::GetSuccessor(TreeNode * tree, ItemType & item)
{ 
   tree = tree->right;
   item = tree->info;
}

void TreeType::GetPredecessor( TreeNode* tree,
                               ItemType& data)
{
  while (tree->right != NULL)
    tree = tree->right;
  data = tree->info;
}
/*
void TreeType::Print() const
{
   PrintTree(root);
}
*/
void TreeType::Print() const
{
   std::cout<<"Binary Search Tree: (in-order)"<<endl;
   PrintTree(root);
   std::cout<<endl;
}

void TreeType::PrintTree(TreeNode* tree) const
{
  
  if (tree != NULL)
  {
    PrintTree(tree->left);   
    tree->info.Print(); std::cout << "  ";
    PrintTree(tree->right);  
  }
}


void TreeType::PreOrder(TreeNode * tree, queue<ItemType>* & preQue)
{

   if (tree != NULL)
   {
      preQue->push(tree->info);
      PreOrder(tree->left, preQue);
      PreOrder(tree->right, preQue);
   } 
}



void TreeType::InOrder(TreeNode * tree, queue<ItemType>*& inQue)
{

   if (tree != NULL)
   {
      InOrder(tree->left, inQue);
      inQue->push(tree->info);      
      InOrder(tree->right, inQue);
   } 
}



void TreeType::PostOrder(TreeNode * tree, queue<ItemType>* & postQue)
{

   if (tree != NULL)
   {
      PostOrder(tree->left, postQue);     
      PostOrder(tree->right, postQue);
      postQue->push(tree->info);       
   } 
}

void TreeType::ResetTree(OrderType order)
// Calls function to create a queue of the tree 
// elements in the desired order.
//the queue should be deleted after using it.
{
  switch (order)
  {
    case PRE_ORDER : preQue = new queue<ItemType>;
                     PreOrder(root, preQue);
                     break;
    case IN_ORDER  : inQue = new queue<ItemType>;
                     InOrder(root, inQue);
                     break;
    case POST_ORDER: postQue = new queue<ItemType>;
                     PostOrder(root, postQue);
                     break;
  }
} 


void TreeType::GetNextItem(ItemType & item, OrderType order, bool& finished)
{
   finished = false;
   switch(order)
   {
     case PRE_ORDER  : item = preQue->front();
                       preQue->pop( );
                      if (preQue->empty())
                       {
                         finished = true;
                         delete preQue;
                         preQue = NULL;
                       }
                      break;
    case IN_ORDER   : item = inQue->front();
                      inQue->pop();
                      if (inQue->empty())
                      {
                        finished = true;
                        delete inQue;
                        inQue = NULL;
                      }
                      break;
    case  POST_ORDER: item = postQue->front();
                      postQue->pop(); 
                      if (postQue->empty())
                      {
                        finished = true;
                         delete postQue;
                        postQue = NULL;
                      }
                      break;

   }
}

int TreeType::LeafCount() const
{
   return CountLeaf(this->root); // call CountLeaf function
}

int TreeType::CountLeaf(TreeNode * tree) const // recursive function to count all leaf nodes
{
   if (tree->right == NULL && tree->left == NULL) return 1;
   else if (tree->right == NULL) return CountLeaf(tree->left);
   else if (tree->left == NULL) return CountLeaf(tree->right);
   else return CountLeaf(tree->right) + CountLeaf(tree->left);
}

void TreeType::Ancestors(ItemType item) const
{ 
   RetrieveAncestors(this->root, item); // call RetrieveAncestors function
}

void TreeType::RetrieveAncestors(TreeNode * tree, ItemType item) const //recursive function that prints out ancestors on its way to find target item
{
   if (item.ComparedTo(tree->info) == LESS)
   {
	tree->info.Print();  
	RetrieveAncestors(tree->left, item);
   }
   else if (item.ComparedTo(tree->info) == GREATER) 
   {
	tree->info.Print();
	RetrieveAncestors(tree->right, item);
   }
}

void TreeType::Swap(TreeType & newTree)
{
   SwapChildren(newTree.root); // call SwapChildren
}

void TreeType::SwapChildren(TreeNode* tree)
{
   TreeNode* tempPointer; // temp pointer in order to perform actual swap of nodes
   if (tree->left != NULL) SwapChildren(tree->left); // only call function recursively if the child is not NULL
   if (tree->right != NULL) SwapChildren(tree->right);
   if (tree->right != NULL || tree->left != NULL) // swap children of a node if at least is not NULL
   {
	tempPointer = tree->right; 
	tree->right = tree->left;
	tree->left = tempPointer;
   }
}


