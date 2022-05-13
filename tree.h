#ifndef TREE_H
#define TREE_H

#include "treenode.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

// Definition of a Binary Search Tree class
template <typename T>
class Tree{
 public:
  // default constructor, sets the root to NULL
  Tree();
  // copy constructor, deep copies the other tree
  Tree(const Tree& other);
  
  // destructor, recursively destroys all nodes
  ~Tree();
  
  // Returns the height of the tree (the number of nodes along the
  // longest path from root to a leaf). The height of an empty tree is
  // 0, the height of a one-element tree is 1.
  int Height() const;

  // Insert item x into the correct position in the tree
  void Insert(const T& x);

  // delets (a copy of) item x from the tree.  Returns true if it's found,
  // False otherwise
  bool Delete(const T& x);

  // Determines whether item x is in the tree.  Returns true if found, false
  // otherwise
  bool Find(const T& x) const;
  
  // Returns a path of 'L' and 'R' characters to reach item "x" in the tree.
  // If "x" doesn't exist, returns the empty string.
  string Path_To_Item(const T& x) const;
  
  // Returns the item at the end of a path of 'L' or 'R' characters in
  // the reference parameter "x."
  // If there is a node at the end of that path, returns true.
  // If there isn't, returns false.
  bool Follow_Path(const string& path, T& x) const;

  // Outputs the nodes of the tree in order (Left subtree, then the node, then
  // the right subtree)
  void Print_Inorder() const;
  
  // Copies the elements of the tree in search tree order into v
  void Dump_To_Vector(vector<T>& v) const;
  
  // Outputs the nodes of the tree in the order node, left, right
  void Print_Preorder() const;
  
  // Outputs the nodes of the tree in the order left, right, node
  void Print_Postorder() const;
  
  // Prints all nodes at depth d (the root is depth 1) if it is a legal level
  // Nodes are printed left to right
  void Print_Nodes_At_Depth(int d) const;
  
  // Prints all nodes at depth 1, then 2, until tree height depth
  void Print_Nodes_By_Depth() const;

  // sets the tree up with a predefined set of nodes
  void Setup();

 private:
  TreeNode<T>* root;

  // here is where we'll put the private helper functions for all of the 
  // elements of the tree
  
  // Creates a new set of nodes that is a deep copy of the tree rooted at
  // "source".  Returns a pointer to the root of the copy
  TreeNode<T>* Copy_Tree(TreeNode<T>* source);

  // recursively deletes all nodes in the subtree pointed at by "source"
  // This includes the source node itself.
  void Delete_Tree(TreeNode<T>* source);

  // Recursievely finds the height of the sbutree rooted at subTreePtr
  int getHeightHelper(TreeNode<T>* subTreePtr) const;
  
  // Prints the nodes of the tree in LNR order starting wth "source"
  void Print_Inorder_Helper(TreeNode<T>* source) const;
  
  // Recursively performs the LNR inorder copying of values from the tree into a vector
  void copyInorderHelper(TreeNode<T>* source, vector<T>& v) const;
 
  // Prints the nodes of the tree in NLR order starting wth "source"
  void Print_Preorder_Helper(TreeNode<T>* source) const;
  
  // Prints the nodes of the tree in LRN order starting wth "source"
  void Print_Postorder_Helper(TreeNode<T>* source) const;
  
  // Helper for print nodes at depth function
  void printNodeHelper(TreeNode<T>* curNode, int curLvl, int depth) const;
  
  // Recursievely finds x in the subtree rooted at "source".  Returns true if it's there,
  // false otherwise
  bool Find_Helper(TreeNode<T>* source, const T& x) const;
  
  // Recursievely finds x in the subtree rooted at "source".
  // Returns a string of the moves to get there to the public function.
  // Assumes the tree contains x.
  string pathHelper(TreeNode<T>* source, string& s, const T& x) const;
  
  // Recursievely returns the item at the end of a path of 'L' or 'R' characters in
  // the reference parameter "x."
  // If there is a node at the end of that path, returns true.
  // If there isn't, returns false.
  // Assumes path contains only 'L' and 'R' characters.
  bool FollowPathHelper(TreeNode<T>* curNode, const string& path, T& x) const;

  // Deletes node "kill" with parent "parent" from the tree
  void Delete_Node(TreeNode<T>* parent, TreeNode<T>* kill);

  // Returns the parent of the postion we'll delete x.  Returns NULL if no node with x exists
  TreeNode<T>* Find_Delete_Position(TreeNode<T>* cur, const T& x) const;

  // Finds the position x will be inserted into the search tree.  Returns the parent of that position
  TreeNode<T>* Find_Insert_Position(TreeNode<T>* p, const T& x) const;

  TreeNode<T>* Find_Successor_Parent(TreeNode<T>* source) const;
};


// default constructor, sets the root to NULL.
// Note that "root== NULL" will be frequently be used to see if a tree is empty
// So we should make sure our other functions (especially Delete) maintain 
// this propoerty
template <typename T>
Tree<T>::Tree(){
  root = NULL;
}

// copy constructor, calls a deep copy helper function 
template <typename T>
Tree<T>::Tree(const Tree<T>& other){
  if(other.root == NULL) // are they empty?
    root = NULL;
  else{
    root = new TreeNode<T>;
    root->set_item(other.root->get_item());
    root->set_left(Copy_Tree(other.root->get_left()));
    root->set_right(Copy_Tree(other.root->get_right()));
  }
}

// Destructor, recursively destroys nodes in both subtrees
template <typename T>
Tree<T>::~Tree(){
  if(root != NULL){ // don't delete an empty tree
    Delete_Tree(root->get_left());
    root->set_left(NULL);
    Delete_Tree(root->get_right());
    root->set_right(NULL);
    delete root;
    root = NULL;
  }
}

// Returns the height of the tree by calling a helper function
template<typename T>
int Tree<T>::Height() const
{
	return getHeightHelper(root);
}

// Finds the height recursively
template<typename T>
int Tree<T>::getHeightHelper(TreeNode<T>* subTreePtr) const
{
	if(subTreePtr == NULL) // Base case: empty tree has height zero
		return 0;
	else // Recursive case: I am one greater than the height of my tallest subtree
		return 1 + max(getHeightHelper(subTreePtr->get_left()), getHeightHelper(subTreePtr->get_right()));
}

// Insert: Inserts x into the tree at the position requested.  Keeps the nodes
// in a tree with the binary search tree property
template <typename T>
void Tree<T>::Insert(const T& x){
  if(root == NULL){ // create a new root
    root = new TreeNode<T>;
    root->set_item(x);
    root->set_left(NULL);
    root->set_right(NULL);
  }
  else{
    TreeNode<T>* parent = Find_Insert_Position(root, x);
    TreeNode<T>* new_guy = new TreeNode<T>;
	new_guy->set_item(x); // set new_guy's item
	new_guy->set_left(NULL);
	new_guy->set_right(NULL);
	
	// attach new_guy to the tree
	if(x <= parent->get_item()) // belongs on the left
	{
		parent->set_left(new_guy);
	}
	else // belongs on the right
	{
		parent->set_right(new_guy);
	}
  }
}


// Deletes a node from the tree with value x.  Returns true if successful.
// If no item was found, returns false.
template <typename T>
bool Tree<T>::Delete(const T& x){
  // case 1: Deleting from an empty tree
  if(root == NULL)
    return false;
  
  // case 2: Deleting the root
  if(root->get_item() == x){
    // Case 2a: Deleting the root when it's the only node in the tree
    if(root->get_left() == NULL && root->get_right() == NULL){
      delete root;
      root = NULL;
      return true;
    }
    // case 2b: Deleting the root when it has one child
    else{
      if(root->get_left() == NULL || root->get_right() == NULL){
	if(root->get_left() != NULL){
	  TreeNode<T>* kill = root;
	  root=root->get_left();
	  kill->set_left(NULL);
	  delete kill;
	}
	else{
	  TreeNode<T>* kill = root;
	  root = root->get_right();
	  kill->set_right(NULL);
	  delete kill;
	}
      }
      else{
	// case 2c, where the root will have 2 children, can be handled like any other "the node we're deleting has 2 children" case
	
	// task 1: setup a pointer to the parent of the successor node (leftmost
	// node in right subtree
	TreeNode<T>* rkp = Find_Successor_Parent(root);
	TreeNode<T>* real_kill = rkp->get_left();
	
	// Task 1a: Worry about the case where the right subtree has no left node
	if(rkp == root){
	  real_kill = root->get_right();
	  rkp = root;
	}
	// task 2: swap the values in kill and the successor node.
	
	root->set_item(real_kill->get_item());
	
	// task 3: kill the successor node
	Delete_Node(rkp, real_kill);
      } // end case 2c
    } // end "not case 2a" else
  } // end case 2
  
  // just in case..
  if(!Find(x))
     return false;

  // Next, find the node to delete (actually, its parent)
  TreeNode<T>* parent = Find_Delete_Position(root, x);
  // get a pointer to the node we're actually deleting
  TreeNode<T>* kill;

  if(parent->get_item() >= x){
    kill = parent->get_left();

  }
  else{
    kill = parent->get_right();

  }

  Delete_Node(parent, kill);
  return true;
}


// Print-Inorder: Prints the items in the search tree in search tree order
template <typename T>
void Tree<T>::Print_Inorder() const{
  return Print_Inorder_Helper(root);
  cout << endl;
}

// Print_Inorder_Helper: Prints an LNR traversal starting at "source"
template <typename T>
void Tree<T>::Print_Inorder_Helper(TreeNode<T>* source) const{
  if(source != NULL){
    Print_Inorder_Helper(source->get_left());
    cout << source->get_item() << " ";
    Print_Inorder_Helper(source->get_right());
  }
}

// Copies tree elements in sorted order into vector v
template<typename T>
void Tree<T>::Dump_To_Vector(vector<T>& v) const
{
	v.resize(0); // clears it
	copyInorderHelper(root, v);
}

// Recursievely copies tree elements into vector in search tree order
template<typename T>
void Tree<T>::copyInorderHelper(TreeNode<T>* source, vector<T>& v) const
{
	if(source != NULL)
	{
		copyInorderHelper(source->get_left(), v);
		v.push_back(source->get_item());
		copyInorderHelper(source->get_right(), v);
	}
}

// Print-Preorder: Prints the items in the search tree in NLR order
template <typename T>
void Tree<T>::Print_Preorder() const
{
	return Print_Preorder_Helper(root);
	cout << endl;
}


// Print_Preorder_Helper: Prints an NLR traversal starting at "source"
template <typename T>
void Tree<T>::Print_Preorder_Helper(TreeNode<T>* source) const{
  if(source != NULL){
	cout << source->get_item() << " ";
    Print_Preorder_Helper(source->get_left());
    Print_Preorder_Helper(source->get_right());
  }
}

// Print-Postorder: Prints the items in the search tree in LRN order
template <typename T>
void Tree<T>::Print_Postorder() const
{
	return Print_Postorder_Helper(root);
	cout << endl;
}

// Print_Postorder_Helper: Prints an LRN traversal starting at "source"
template <typename T>
void Tree<T>::Print_Postorder_Helper(TreeNode<T>* source) const{
  if(source != NULL){
    Print_Postorder_Helper(source->get_left());
    Print_Postorder_Helper(source->get_right());
	cout << source->get_item() << " ";
  }
}

// Calls helper function to print nodes at given depth (if legal)
template<typename T>
void Tree<T>::Print_Nodes_At_Depth(int d) const
{
	if(0 < d < Height())
		printNodeHelper(root, 1, d);
}

// Recursievely traverses to the correct depth to print by depth
template<typename T>
void Tree<T>::printNodeHelper(TreeNode<T>* curNode, int curLvl, int depth) const
{
	if(curNode != NULL) // avoids dereferencing nullptr
	{
		if(curLvl == depth)
		{
			cout << curNode->get_item() << " "; // base case: we're at the right level
		}
		else // recursive case
		{
			printNodeHelper(curNode->get_left(), curLvl + 1, depth); // go left
			printNodeHelper(curNode->get_right(), curLvl + 1, depth); // then right
		}
	}
}

// Calls helper to print nodes at each depth on their own lines.
template <typename T>
void Tree<T>::Print_Nodes_By_Depth() const
{
	for(int i = 1; i <= Height(); i++)
	{
		printNodeHelper(root, 1, i);
		cout << endl;
	}
}

// Find: finds a node with item x in the tree.  returns true if it exists, 
// returns false otherwise
template <typename T>
bool Tree<T>::Find(const T& x) const{
  return Find_Helper(root, x);
}

// Find_Helper: The pointer version of "find", passing the current node
// as a parameter
template <typename T>
bool Tree<T>::Find_Helper(TreeNode<T>* source, const T& x) const
{
	if(source == NULL) // Case 1: Empty tree, or we've reached the end, and it's not there
	{
		return false;
	}
	else if(source->get_item() == x) // Case 2: Found it
	{
		return true;
	}
	else if(x <= source->get_item()) // Case 3: The item is smaller, check the left subtree
	{
		return Find_Helper(source->get_left(), x);
	}
	else // Case 4: The item is bigger, check the right subtree
	{
		return Find_Helper(source->get_right(), x);
	}
}

// Calls helper to return string of 'L' and 'R' of path to object, if it exists.
template<typename T>
string Tree<T>::Path_To_Item(const T& x) const
{
	string s = "";
	if(Find(x))
		pathHelper(root, s, x);
	return s;
}

// Recursievely finds x in the subtree rooted at "source".
// Returns a string of the moves to get there to the public function.
// Assumes the tree contains x.
template<typename T>
string Tree<T>::pathHelper(TreeNode<T>* source, string& s, const T& x) const
{
	// Find in the main function already checked that x is in the tree. We won't be dereferencing a nullptr
	if(source->get_item() == x) // Base case: we found it, so we're done
		return s;
	else if(x <= source->get_item())
	{
		s += "L"; // it's smaller, so we went left
		return pathHelper(source->get_left(), s, x); // Recursive case: I return my path choice with all the choices after me
	}
	else
	{
		s += "R"; // bigger, so we went right
		return pathHelper(source->get_right(), s, x);
	}
}

// Returns true if there is a node at the end of that path, false otherwise.
// Copies value at node into reference parameter.
template<typename T>
bool Tree<T>::Follow_Path(const string& path, T& x) const
{
	return FollowPathHelper(root, path, x);
}


// Recursively follows path in string. Copies value into x if found and returns true, returns false otherwise.
template<typename T>
bool Tree<T>::FollowPathHelper(TreeNode<T>* curNode, const string& path, T& x) const
{
	if(curNode != NULL)
	{
		if(path.length() == 0) // Base case: I've followed the path to the end, and there is an item there
		{
			x = curNode->get_item();
			return true;
		}
		else if(path[0] == 'L') // Recursive case: Look left and remove first path character
			return FollowPathHelper(curNode->get_left(), path.substr(1), x); 
		else // Recursive case: Look right and remove first path character
			return FollowPathHelper(curNode->get_right(), path.substr(1), x);
	}
	return false; // Base case: No node here and can't continue
}

// deletes the node "kill" with parent "parent".
// I made it its own function to isolate the 3 cases
template <typename T>
void Tree<T>::Delete_Node(TreeNode<T>* parent, TreeNode<T>* kill)
{  
  // is the node we're trying to kill a left or right child?
  bool is_left;
  if(parent->get_left() == kill)
    is_left = true;
  else
    is_left = false;

  // case 1: kill is a leaf.  
  if(kill->get_left() == NULL && kill->get_right() == NULL)
  {
    if(is_left)
      parent->set_left(NULL);
    else
      parent->set_right(NULL);
    delete kill;
  }
  // case 2:  kill has one child.
  else if(kill->get_left() == NULL || kill->get_right() == NULL)
  {
    // lots of cases here.
    if(is_left)
	{
      // kill is a left child
      if(kill->get_left() != NULL)
	  {
		// and has a left child
		parent->set_left(kill->get_left());
      }
      else // kill is a left child but its child is a right child
	  {
		parent->set_left(kill->get_right());
      }
    }
    else // kill is a right child
	{
      if(kill->get_left() != NULL) // kill's one child is a left child
	  {
		parent->set_right(kill->get_left());
      }
      else // kill is a right child that has a right child
	  {
		parent->set_right(kill->get_right());
      }
    }
  }
  // case 3: Kill has two children
  else{
    // task 1: setup a pointer to the parent of the successor node (leftmost
    // node in right subtree)
    TreeNode<T>* rkp = Find_Successor_Parent(kill);
    TreeNode<T>* real_kill = rkp->get_left();
    // task 1a: worry about the case where the right child does not have a left subtree
    if(rkp==kill)
      real_kill = rkp->get_right();

    // task 2: swap the values in kill and the successor node.
    // (or really, just copy the sucessor value into the kill node)
    kill->set_item(real_kill->get_item());
    
    // task 3: kill the successor node
    Delete_Node(rkp, real_kill);
  }
}
      
// Find_Insert_Position: Called by Insert to recursively find 
// the place the item should be inserted. 
//  Returns the _parent_ of the position in the 
// tree x's node should be (because the child on that side will be NULL)
template <typename T>
TreeNode<T>* Tree<T>::Find_Insert_Position(TreeNode<T>* p, const T& x) const{
  if(p == NULL) // shouldn't happen
    return NULL;
  if(p->get_item() >= x){ // look left
    if(p->get_left() == NULL) // then the left child is where the new 
                              // node should be
      return p;
    else 
      return Find_Insert_Position(p->get_left(), x);
  }
  else{ // look right
    if(p->get_right() == NULL) // then the right child is where the new node 
                               // should be
      return p;
    else
      return Find_Insert_Position(p->get_right(), x);
  }
}


    
// Find_Delete_Position- finds the parent of the node we want to delete in
// the tree and returns a pointer to it.  Returns NULL if no node matching
// the item exists
template <typename T>
TreeNode<T>* Tree<T>::Find_Delete_Position(TreeNode<T>* cur, const T& x) const
{
  if(cur != NULL)
  {
	if(x <= cur->get_item()) // look at left child
	{
		if(cur->get_left() == NULL)
		{
			return NULL; // should be left but nothing's there
		}
		else if(cur->get_left()->get_item() == x)
		{
			return cur; // it's the left child, return its parent
		}
		else
		{
			return Find_Delete_Position(cur->get_left(), x); // it's not the left child but is in this subtree
		}
	}
	else // look at right child
	{
		if(cur->get_right() == NULL)
		{
			return NULL;
		}
		else if(cur->get_right()->get_item() == x)
		{
			return cur;
		}
		else
		{
			return Find_Delete_Position(cur->get_right(), x);
		}
	}
  }
}


// Delete_Tree: Recursively deletes all subtrees of "source", then deletes "source"
template <typename T>
void Tree<T>::Delete_Tree(TreeNode<T>* source)
{  
	if(source != NULL)
	{
		Delete_Tree(source->get_left());
		source->set_left(NULL);
		Delete_Tree(source->get_right());
		source->set_right(NULL);
		delete source; // Calls the TreeNode destructor
	}
}


// deep copies a tree rooted at "source".  Returns a pointer to the root of the copy
template <typename T>
TreeNode<T>* Tree<T>::Copy_Tree(TreeNode<T>* source){
  // here's the beginning of Copy_Tree
  if(source == NULL)
    return NULL;
  else{
    // create a new node for the root of the new tree
    TreeNode<T>* new_root = new TreeNode<T>;
    // Set new_root's item to source's item
	new_root->set_item(source->get_item());
    // call Copy_Tree recursively on source->get_left().  it'll return a pointer.
    // set the left child of new_root to be that pointer.  DO NOT SAY NEW AGAIN
	new_root->set_left(Copy_Tree(source->get_left()));
    // call Copy_Tree recursively on source->get_right().  It'll return a pointer.
    // Set the right child of new_root to be that pointer.  DO NOT SAY NEW AGAIN
	new_root->set_right(Copy_Tree(source->get_right()));
    return new_root;
  }
}

// assumes source has a right child
template <typename T>
TreeNode<T>* Tree<T>::Find_Successor_Parent(TreeNode<T>* source) const
{
	TreeNode<T>* cur = source;
	TreeNode<T>* parent = cur;
	cur = cur->get_right();
	if(cur->get_left() == NULL) //then cur is the successor, and source is the parent
		return source;
	else // loop through the left children until you can't any more.  cur is the last left child, parent is its parent.
	{
		while(cur->get_left() != NULL)
		{
			parent = cur;
			cur = cur->get_left();
		}
	}
	return parent;
}


// sets up the tree with a pre-defined structure.
// Only should be used to give you something to work with before Insert is written
// ONLY WORKS ON TREES OF INTS
template <typename T>
void Tree<T>::Setup()
{
  // get rid of anything already there
  Delete_Tree(root);

  // I'm creating these nodes in the order they'll show up in the
  // tree, row by row, starting from the root
  root = new TreeNode<T>;
  root->set_item(10);

  TreeNode<T>* six = new TreeNode<T>;
  six->set_item(6);
  
  TreeNode<T>* fifteen = new TreeNode<T>;
  fifteen->set_item(15);

  TreeNode<T>* four = new TreeNode<T>;
  four->set_item(4);

  TreeNode<T>* eight = new TreeNode<T>;
  eight->set_item(8);

  TreeNode<T>* thirteen = new TreeNode<T>;
  thirteen->set_item(13);

  TreeNode<T>* seventeen = new TreeNode<T>;
  seventeen->set_item(17);

  TreeNode<T>* two = new TreeNode<T>;
  two->set_item(2);

  TreeNode<T>* fourteen = new TreeNode<T>;
  fourteen->set_item(14);

  TreeNode<T>* one = new TreeNode<T>;
  one->set_item(1);

  // now to hook them up
  root->set_left(six);
  root->set_right(fifteen);

  six->set_left(four);
  six->set_right(eight);

  fifteen->set_left(thirteen);
  fifteen->set_right(seventeen);

  four->set_left(two);
  four->set_right(NULL);

  eight->set_left(NULL);
  eight->set_right(NULL);

  thirteen->set_left(NULL);
  thirteen->set_right(fourteen);

  seventeen->set_left(NULL);
  seventeen->set_right(NULL);

  two->set_left(one);
  two->set_right(NULL);

  fourteen->set_left(NULL);
  fourteen->set_right(NULL);

  one->set_left(NULL);
  one->set_right(NULL);
  
  Insert(0);
  Insert(18);
  Insert(7);
  Insert(12);
}


#endif
