#include "tree.h"
#include <vector>

using namespace std;

int main(){
  Tree<int> my_tree;
  
  cout << "Testing insert and inorder traversal..." << endl;
  cout << "Enter 10 numbers: ";
    for(int i = 0; i < 10; i++){
      int x;
      cin >> x;
      my_tree.Insert(x);
    }
  cout << "inorder traversal: ";
  my_tree.Print_Inorder();
  cout << endl;
  
  cout << endl << "Creating default tree using setup to test remaining member functions..." << endl;
  my_tree.Setup();
  
  cout << "Testing traversals..." << endl;
  cout << "inorder traversal: ";
  my_tree.Print_Inorder();
  cout << endl;
  cout << "preorder traversal: ";
  my_tree.Print_Preorder();
  cout << endl;
  cout << "postorder traversal: ";
  my_tree.Print_Postorder();
  cout<< endl;
  
  cout << endl << "Testing height..." << endl;
  cout << "Height (should be 6) = " << my_tree.Height() << endl;
  Tree<int> empTree;
  cout << "Height of an empty tree (0) = " << empTree.Height() << endl;
  empTree.Insert(5);
  cout << "Height of a one-element tree (1) = " << empTree.Height() << endl;
  
  cout << endl << "Testing copy constructor..." << endl;
  Tree<int> copy(my_tree);
  copy.Insert(-1);
  cout << "Copy test- original tree: ";
  my_tree.Print_Inorder();
  cout << endl;
  cout << "Copy test- copy tree (should have -1): ";
  copy.Print_Inorder();
  cout << endl;
  
  cout << endl << "Testing find..." << endl;
  cout << "Enter an item to find: ";
  int x;
  cin >> x;
  if(my_tree.Find(x))
    cout << "It's there " << endl;
   else
     cout << "It's not there " << endl;

  cout << endl << "Testing delete..." << endl;
  for(int i = 0; i < 10; i++){
   cout << "Enter an item to delete: ";
   int del_item;
   cin >> del_item;
   my_tree.Delete(del_item);
   cout << "Current tree: ";
    my_tree.Print_Inorder();
   }
   cout << endl;
   
  cout << endl << "Resetting tree..." << endl;
  my_tree.Setup();
  cout << endl << "Testing toVector..." << endl;
  vector<int> values;
  my_tree.Dump_To_Vector(values);
  for(int i = 0; i < values.size(); i++)
  {
	  cout << values[i] << " ";
  }
  cout << endl << "Testing on pre-filled vector (output should be the same)..." << endl;
  values.resize(5);
  values[0] = 1;
  my_tree.Dump_To_Vector(values);
    for(int i = 0; i < values.size(); i++)
  {
	  cout << values[i] << " ";
  }
  cout << endl;
  
  cout << endl << "Testing print nodes at depth..." << endl;
  cout << "Nodes at depth 0: ";
  my_tree.Print_Nodes_At_Depth(0);
  cout << endl << "Nodes at depth 1: ";
  my_tree.Print_Nodes_At_Depth(1);
  cout << endl << "Nodes at depth 2: ";
  my_tree.Print_Nodes_At_Depth(2);
  cout << endl << "Nodes at depth 3: ";
  my_tree.Print_Nodes_At_Depth(3);
  cout << endl << "Nodes at depth 4: ";
  my_tree.Print_Nodes_At_Depth(4);
  cout << endl << "Nodes at depth 5: ";
  my_tree.Print_Nodes_At_Depth(5);
  cout << endl << "Nodes at depth 6: ";
  my_tree.Print_Nodes_At_Depth(6);
  cout << endl << "Nodes at depth 7: ";
  my_tree.Print_Nodes_At_Depth(7);
  
  cout << endl << "Testing print by depth..." << endl;
  my_tree.Print_Nodes_By_Depth();
  
  cout << endl << "Path to 10 (""): " << my_tree.Path_To_Item(10) << endl;
  cout << "Path to 6 (L): " << my_tree.Path_To_Item(6) << endl;
  cout << "Path to 0 (LLLLL): " << my_tree.Path_To_Item(0) << endl;
  cout << "Path to 7 (LRL): " << my_tree.Path_To_Item(7) << endl;
  cout << "Path to 12 (RLL): " << my_tree.Path_To_Item(12) << endl;
  cout << "Path to 18 (RRR): " << my_tree.Path_To_Item(18) << endl;
  cout << "Path to 19 (""): " << my_tree.Path_To_Item(19) << endl;
  
  cout << endl << "Testing follow path..." << endl;
  int temp = 0;
  string path = "";
  cout << "Item at empty path (10): ";
  my_tree.Follow_Path(path, temp);
  cout << temp << endl;
  path = "L";
  cout << "Item at L (6): ";
  my_tree.Follow_Path(path, temp);
  cout << temp << endl;
  path = "LLLLL";
  cout << "Item at LLLLL (0): ";
  my_tree.Follow_Path(path, temp);
  cout << temp << endl;
  path = "LRL";
  cout << "Item at LRL (7): ";
  my_tree.Follow_Path(path, temp);
  cout << temp << endl;
  path = "RLL";
  cout << "Item at RLL (12): ";
  my_tree.Follow_Path(path, temp);
  cout << temp << endl;
  path = "RRR";
  cout << "Item at RRR (18): ";
  my_tree.Follow_Path(path, temp);
  cout << temp << endl;
  path = "LRLR";
  cout << "Item at LRLR (none): ";
  if(my_tree.Follow_Path(path, temp))
	cout << temp << endl;
  else
	cout << "none" << endl;

  return 0;
}
