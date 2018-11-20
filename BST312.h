
/*  BST312.h
  CS 312 Fall 2018

  a simple implementation of a binary search tree


*/

#ifndef BST_312_H
#define BST_312_H

#include <cstdlib>  // Provides size_t
#include <iostream>
#include <vector>

using namespace std;

template<class ItemType>
class BST_312 {
public:

    BST_312();

    //Copy constructor
    BST_312(const BST_312 & src);

    ~BST_312();

/****************************
makeEmpty

Function: Removes all the items from the BST.
Preconditions: BST has been initialized
Postconditions: All the items have been removed
*****************************/
    void makeEmpty();

/****************************
isEmpty

Function: Checks to see if there are any items in the BST.
Preconditions: BST has been initialized
Postconditions: Returns true if there are no items in the BST, else false.
*****************************/
    bool isEmpty() const;

/****************************
isFull

Function: Determines if you have any more room to add items to the BST
Preconditions: BST has been initialized
Postconditions: Returns true if there is no more room to add items, else false
*****************************/
    bool isFull() const;

/****************************
insertItem

Function: Adds newItem to the BST.
Preconditions: BST has been initialized and is not full.
Postconditions: newItem is in the proper position for a BST.
*****************************/
    void insertItem(const ItemType &);

/****************************
deleteItem

Function: Removes target from BST.
Preconditions: BST has been initialized.
Postconditions: If found, element has been removed from BST.
*****************************/
    void deleteItem(const ItemType& newItem);

/****************************
countNodes

Function: Counts the number of nodes in the BST
Preconditions: BST has been initialized.
Postconditions: returns the number of nodes in the BST
*****************************/
    int countNodes();

/****************************
preOrderTraversal

Function: Returns the preOder (Node, Left, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> preOrderTraversal();

/****************************
inOrderTraversal

Function: Returns the inOder (Left, Node, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> inOrderTraversal();

/****************************
postOrderTraversal

Function: returns the postOder (Left, Right, Node) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> postOrderTraversal();

/********************
 isItemInTree

Function: Determines if a given Item is in tree.
Preconditions: BST has been initialized.
Postconditions: none
*****************************/

    bool isItemInTree(const ItemType& item);


private:
    struct TreeNode {
        ItemType data;
        TreeNode *left;
        TreeNode *right;
    };

    TreeNode * root;


    void insertItem(TreeNode*& t, const ItemType& newItem);
    void inOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    int countNodes(TreeNode* t) const;
    void deleteNode(TreeNode*& node);
    void makeEmpty(TreeNode*& t);
    void deleteItem(TreeNode*& t, const ItemType& newItem);
    void getPredecessor(TreeNode* t, ItemType& data);
    void preOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void postOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void copyTree(TreeNode*& copy, const TreeNode *originalTree);

};

/*******************************
//Function implementations
********************************/

template<class ItemType>
BST_312<ItemType>::BST_312 ()
{
    root = NULL;
}

template<class ItemType>
BST_312<ItemType>::BST_312(const BST_312 & src)
{
    copyTree(root, src.root);
}

template<class ItemType>
BST_312<ItemType>::~BST_312()
{
    makeEmpty();

}


template<class ItemType>
void BST_312<ItemType>::copyTree(TreeNode*& copy, const TreeNode* originalTree)
{
    if (originalTree == NULL)
        copy = NULL;
    else
    {
        copy = new TreeNode;
        copy->data = originalTree->data;

        copyTree(copy->left, originalTree->left);
        copyTree(copy->right, originalTree->right);
    }
}


template<class ItemType>
void BST_312 <ItemType>::deleteNode(TreeNode*& t)
{
    ItemType info;
    TreeNode *tempPtr;

    tempPtr = t;

    if (t->left == NULL)
    {
        t = t->right;
        delete tempPtr;
    }
    else if (t->right == NULL)
    {
        t = t->left;
        delete tempPtr;
    }
    else
    {
        getPredecessor(t->left, info);
        t->data = info;
        deleteItem(t->left, info);
    }
}



//find largest in left subtree
template<class ItemType>
void BST_312 <ItemType>::getPredecessor(TreeNode* t, ItemType& data)
{

    while (t->right != NULL)
        t = t->right;

    data = t->data;

}


template<class ItemType>
void BST_312 <ItemType>::deleteItem(TreeNode*& t, const ItemType& newItem)
{
    if (t == NULL)
        return;
    else if (newItem < t->data)
        deleteItem(t->left, newItem);
    else if (newItem > t->data)
        deleteItem(t->right, newItem);
    else
        deleteNode(t);
}


template<class ItemType>
void BST_312 <ItemType>::deleteItem(const ItemType& newItem)
{
    deleteItem(root, newItem);

}

template<class ItemType>
void BST_312 <ItemType>::makeEmpty(TreeNode*& t)
{
    if (t != NULL) {
        makeEmpty(t->left); // if it is not null recursively delete all nodes that are not null
        makeEmpty(t->right);

        deleteNode(t);

    }

}

template<class ItemType>
void BST_312 <ItemType>::makeEmpty()
{
    makeEmpty(root); //have it start at the root and then make the root null
    root = NULL;
}

template<class ItemType>
bool BST_312 <ItemType>::isEmpty() const
{
    return root == NULL; // if nothing at root - BST is empty
}



template<class ItemType>
bool BST_312 <ItemType>::isFull() const
{
    try
    {
        TreeNode *temp = new TreeNode;
        delete temp;
        return false;
    }
    catch (std::bad_alloc)
    {
        return true;
    }

}


template<class ItemType>
void BST_312 <ItemType>::insertItem(TreeNode*& t, const ItemType& newItem) {

    if (t == NULL) { //if there are no nodes at all
        t = new TreeNode; //create a node
        t->data = newItem; // put the data in
        t->left = NULL; // no left or right branches
        t->right = NULL; // as the first node
    } else if (newItem < t->data) { // if the data is less than the first branch
        insertItem(t->left, newItem); //according to rules of bst you put this on left branch
        if (t->left == NULL) { //if left is null - reached end of branch
            TreeNode *tempPtr; //create a node
            tempPtr->data = newItem; //put data in node
            t->left = tempPtr; //assign it to the left branch
            delete tempPtr; //free temporary pointer
        }
    } else{
        insertItem(t->right, newItem); //similar to left branch but for right branch
        if (t->right == NULL) {
            TreeNode *tempPtr;
            tempPtr->data = newItem;
            t->right = tempPtr;
            delete tempPtr;
        }
    }
}

template<class ItemType>
void BST_312 <ItemType>::insertItem(const ItemType& newItem)
{
    insertItem(root, newItem); //for insert item we are just placing these at the root
}



template<class ItemType>
int BST_312 <ItemType>::countNodes(TreeNode* t) const
{
    int Nodes = 1; //first give a node for the starting node - if there were no nodes this would not be called in the first place
    if(t->left != NULL){
        Nodes += countNodes(t->left); //if left has a branch then count nodes on left branch

    }
    if(t->right != NULL){ //if right has a branch then count nodes on right branch
        Nodes += countNodes(t->right);
    }

    return(Nodes); //return integer

}


template<class ItemType>
int BST_312 <ItemType>::countNodes()
{
    if (root == NULL){ //if root is null there are no nodes in the tree
        return 0;
    }

    else{
        return countNodes(root); //count nodes from the root of the BST
    }

}

template<class ItemType>
void BST_312 <ItemType>::preOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    if(t == NULL){
        return;
    }
    result.push_back(t->data); //in preorder traversal
    preOrderTraversal(t->left, result); // the first thing is the node at the top
    preOrderTraversal(t->right, result); // then left and right

}


template<class ItemType>
vector<ItemType> BST_312 <ItemType>::preOrderTraversal()
{

    vector<ItemType> result; //in pre order reversal
    preOrderTraversal(root, result); //create a vector and use root as main node
    return(result); //return vector

}

template<class ItemType>
void BST_312 <ItemType>::inOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    if(t == NULL){
        return;
    }
    inOrderTraversal(t->left, result); //in order traversal has the order of left branch,
    result.push_back(t->data);// the original node
    inOrderTraversal(t->right, result); //and finally the right branch

}

template<class ItemType>
vector<ItemType> BST_312 <ItemType>::inOrderTraversal()
{
    vector<ItemType> result; //create a vector
    inOrderTraversal(root, result); //make root the main treenode to go from
    return(result);
}

template<class ItemType>
void BST_312 <ItemType>::postOrderTraversal(TreeNode* t,vector<ItemType>& result) const {

    if (t == NULL) {
        return;
    }
    postOrderTraversal(t->left, result); //post order traversal is left, right, then the original node
    postOrderTraversal(t->right, result);
    result.push_back(t->data);
}


template<class ItemType>
vector<ItemType> BST_312 <ItemType>::postOrderTraversal()
{
    vector<ItemType> result; //create a vector
    postOrderTraversal(root, result); //root is the main tree node we are using
    return(result);
}

template<class ItemType>
bool BST_312 <ItemType>::isItemInTree(const ItemType& item) {
    vector<ItemType> List = postOrderTraversal(); // create a list of items to compare the result with
    typename std::vector<ItemType>::iterator it; //create an iterator that will be able to search through the list
    for (it = List.begin(); it != List.end(); ++it) { //precisely to find the data element we are looking for
        if (item == *it) {
            return true;
        }
    }
    ~List;// otherwise we free the list vector we made and return false
    return false;
}
#endif
