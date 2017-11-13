//NAME: Marky Santos-Tankia
//SECTION: A

#ifndef MYBSTREE_H
#define MYBSTREE_H

#include "abstractbstree.h"

using namespace std;


template < typename T >
struct TreeNode
{
	TreeNode<T> * m_right;
	TreeNode<T> * m_left;
	T m_data;
};

template < typename T >
class MyBSTree
{
	private:

		TreeNode<T> * m_root;

	public:
	  	
	  
	  MyBSTree<T>()
	  {
	  	m_root = NULL;
	  }

		MyBSTree<T>(const MyBSTree& rhs)
		{
			m_root = NULL;
			clone(rhs.m_root);
		}
		
		//Deconstructor
		~MyBSTree<T>()
		{
		  clear();
    }
		
		//clears tree w/ recursion
		void clear(TreeNode<T> *p);
		
		//Clones the tree i.e. '=' operator
		void clone(const TreeNode<T>* t);

		//gets size of tree recursively
		int calcSize(TreeNode<T>* node);

		//gets height tree recursively
		int calcHeight(TreeNode<T>* node);

		//prints preorder through recursive means
		void preOrder(TreeNode<T>* printer);

		//prints postorder through recursive means
	  void postOrder(TreeNode<T>* printer);

	  //recursively prints
	  void prettyPrint(const TreeNode<T>* t, int pad);

	  //equals operator for copy constructor
	  const MyBSTree<T>& operator=(const MyBSTree<T>& rhs);

	  

		

		//---- Accessor Operations ----
  
		// Purpose: Accessor function for the number of elements in the tree
		// Returns: number of elements in the tree 
		int size();

		// Purpose: Checks if a tree is empty
		// Returns: 'true' if the tree is empty
		//     'false' otherwise  
		bool isEmpty() const;

		// Purpose: Returns the height of the tree
		// Returns: height the tree 
		int height();


		// Purpose: finds the maximum element in the Tree
		// Returns: a const reference to the maximum element
		// Exception: if the tree is empty, THROW a 'Oops' object with an error message!!!
		const T& getMax() const throw (Oops);

		// Purpose: finds the minimum element in the Tree
		// Returns: a const reference to the minimum element
		// Exception: if the tree is empty, THROW a 'Oops' object with an error message!!!
		const T& getMin() const throw (Oops);

		// Purpose: finds an element in the Tree
		// Parameters: x is value to be found 
		// Returns: 
		//     If the tree contains x then  
		//         return N, the level of the node containing x
		//         (the root is considered level 1)
		//     If The tree does not contains x then  
		//         return -N, where N is the level of the tree reached in the search
		//     REPEAT: The root of the tree is considered level 1. 
		int find(const T& x);


    
		  //---- Mutator Operations ----

		// Purpose: Clears the Tree
		// Postconditions: an empty Tree
		void clear();

		// Purpose: Inserts an element into a tree
		// Parameters: x is value to be added to the tree
		// Postconditions: The tree now contains x
		//     if the tree already contains x, ignore insertion
		void insert(const T& x);

		// Purpose: Removes an element from the tree
		// Parameters: x, the element to remove
		// Postconditions: the tree does not contains x
		void remove(const T& x);
          
     
		  // ---- Output Operations ----

		// Purpose: Prints the Tree in Pre-Order    
		void printPreOrder();

		// Purpose: Prints the Tree in Pre-Order    
		void printPostOrder();

		// Purpose: Prints the Tree In-Order with formatting
		//     each level indented 4 spaces, one element per line    
		void print();

};

#include "mybstree.hpp"
#endif 
