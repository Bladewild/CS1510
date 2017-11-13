//NAME: Marky Santos-Tankia
//SECTION: A

#include <iostream>
using namespace std;


// Purpose: Accessor function for the number of elements in the tree
// Returns: number of elements in the tree
template < typename T >
int MyBSTree<T>::size()
{
  int number = 0;
  number = calcSize(m_root);
  return number;
}

template < typename T >
int MyBSTree<T>::calcSize(TreeNode<T>* node)
{
  int size = 0;
  if(node != NULL)
  {
    if(node->m_left)
      size += calcSize(node->m_left);
    if(node->m_right)
      size += calcSize(node->m_right);
    return size + 1;
  }
  else
    return 0;
}


// Purpose: Checks if a tree is empty
// Returns: 'true' if the tree is empty
//     'false' otherwise  
template < typename T >
bool MyBSTree<T>::isEmpty() const
{
  if(m_root == NULL)
    return true;
  else
    return false;
}


// Purpose: Returns the height of the tree
// Returns: height the tree 
template < typename T >
int MyBSTree<T>::height()
{
  int height = 0;
  height = calcHeight(m_root);
  return height;
}


//recursive height function
template < typename T >
int  MyBSTree<T>::calcHeight(TreeNode<T>* node)
{
  if(node == NULL)
    return 0;
    
  int left = calcHeight(node->m_left);
  int right = calcHeight(node->m_right);
    
  if(left > right)
    return 1+left;
  else
    return 1+right;
}


// Purpose: finds the maximum element in the Tree
// Returns: a const reference to the maximum element
// Exception: if the tree is empty, THROW a 'Oops' object with an error message!!!
template < typename T >
const T& MyBSTree<T>::getMax() const throw (Oops)
{
  if(isEmpty())
    throw Oops("OOPS! : Tree is Empty!!");
  
  TreeNode<T>* tmp;
  tmp = m_root;

  while(tmp->m_right != NULL)
    tmp = tmp->m_right;
  return tmp->m_data;
    
}


// Purpose: finds the minimum element in the Tree
// Returns: a const reference to the minimum element
// Exception: if the tree is empty, THROW a 'Oops' object with an error message!!!
template < typename T >
const T& MyBSTree<T>::getMin() const throw (Oops)
{
  if(isEmpty())
    throw Oops("OOPS! : Tree is Empty!!");
  
  TreeNode<T>* tmp;
  tmp = m_root;  
  
  while(tmp->m_left != NULL)
    tmp = tmp->m_left;
  return tmp->m_data;
  
    
}


// Purpose: finds an element in the Tree
// Parameters: x is value to be found 
// Returns: 
//     If the tree contains x then  
//         return N, the level of the node containing x
//         (the root is considered level 1)
//     If The tree does not contains x then  
//         return -N, where N is the level of the tree reached in the search
//     REPEAT: The root of the tree is considered level 1. 
template < typename T >
int MyBSTree<T>::find(const T& x)
{
  int level = 1;    
  TreeNode<T>* tmp = m_root;

  if(isEmpty())
    return 0;
    
  while(tmp != NULL)
  {
    if(x < (tmp->m_data))
    {
      tmp = tmp->m_left;
    }
    else if(x > (tmp->m_data))
    {
      tmp = tmp->m_right;
    }
    else //x is found
    {
      return level;
    }
    level++;
  }
    
  return ((-1)*level);
}


// Purpose: Clears the Tree
// Postconditions: an empty Tree
template < typename T >
void MyBSTree<T>::clear()
{
  if(m_root != NULL)
    clear(m_root);   
}
  
//recursive clear function
template < typename T >
void MyBSTree<T>::clear(TreeNode<T> *q)
{
  if(q->m_left != NULL)
    clear(q->m_left);  
  if(q->m_right != NULL)
    clear(q->m_right);  
  delete q;
}


//creates a copy of the tree
template < typename T >
const MyBSTree<T>& MyBSTree<T>::operator=(const MyBSTree<T>& rhs)
{
  if(this != &rhs)
  {
    clear();
    m_root = NULL;
    clone(rhs.m_root);
  }
  return *this;
}


//clones trees; helps operator '='  
template < typename T >
void MyBSTree<T>::clone(const TreeNode<T>* t)
{
  if(t)
  {
    insert(t->m_data);
    clone(t->m_left);
    clone(t->m_right);
  }
}


// Purpose: Inserts an element into a tree
// Parameters: x is value to be added to the tree
// Postconditions: The tree now contains x
//     if the tree already contains x, ignore insertion
template < typename T >
void MyBSTree<T>::insert(const T& x)
{
  if(find(x) > 0)
    return;
   
  TreeNode<T>* tmp;
  TreeNode<T>* parent;
  
  tmp = new TreeNode<T>;
  tmp->m_data = x;
  tmp->m_left = NULL;
  tmp->m_right = NULL;
    
  parent = NULL;
  
  if(isEmpty())
    m_root = tmp;      
  else
  {
    TreeNode<T>* current;
    current = m_root;
    
    while(current)
    {
      parent = current;
      if(tmp->m_data > current->m_data)
        current = current->m_right;
      else
        current = current->m_left;
    }
      
    if(tmp->m_data < parent->m_data)
      parent->m_left = tmp;
    else
      parent->m_right = tmp;
  }
}


// Purpose: Removes an element from thetree
// Parameters: x, the element to remove
// Postconditions: the tree does not contains x
template < typename T >
void MyBSTree<T>::remove(const T& x)
{
  bool found = false;
  if(isEmpty())
  {
    cout << "Tree is empty!" << endl;
    return;
  }
  TreeNode<T>* curr;
  TreeNode<T>* parent;
  curr = m_root;
  parent = NULL;
   
  while(curr != NULL)
  {
    if(curr->m_data == x) //curr is the node that has x
    {
      found = true;
      break;
    }
    else
    {
      parent = curr;
      if(x > curr->m_data) curr = curr->m_right;
      else curr = curr->m_left;
    }
  }
  if(!found)
  {
    cout << "Element not present in tree!" << endl;
    return;
  }


  // cases
  // 1) remove node with no child
  // 2) remove node with 1 child
  // 3) remove child with 2 children

  //node with no child
  if( curr->m_left == NULL && curr->m_right == NULL)
  {
    if(m_root == curr && parent==NULL)
    {
      delete m_root;
    }
    else if(parent->m_left == curr) //the curr is m_left
    {
      parent->m_left = NULL;
    }
    else //curr is m_right
    {
      parent->m_right = NULL;
    }
    delete curr;
    return;
  }
  //node with one child
  if((curr->m_left == NULL && curr->m_right != NULL) || (curr->m_left != NULL && curr->m_right == NULL))
  {
    if(curr->m_left == NULL && curr->m_right != NULL)  //right child present
    {
      if(m_root == curr && parent==NULL) //element is the root
      {
        m_root = m_root->m_right;
        delete curr;
      }
      else if(parent->m_left == curr) //parent node, curr is on left, curr child on right
      {
        parent->m_left = curr->m_right;
        delete curr;
      }
      else //parent node, curr is on right
      {
        parent->m_right = curr->m_right;
        delete curr;
      }
    }
    else //left child present, no right child
    {
      if(curr == m_root)
      {
        m_root = m_root->m_left;
        delete curr;
      }
      else if(parent->m_left == curr) //parent node, curr is on left, curr child on left
      {
        parent->m_left = curr->m_left;
        delete curr;
      }
      else
      {
        parent->m_right = curr->m_left;
        delete curr;
      }
    }
    return;
  }
  
  
  
  //node with 2 children
  //replace node with greatest value in left subtree
  if (curr->m_left != NULL && curr->m_right != NULL)
  {
    TreeNode<T>* chkr;
    chkr = curr->m_left;
    if((chkr->m_left == NULL) && (chkr->m_right == NULL)) //left no children
    {
      curr->m_data = chkr->m_data;
      delete chkr;
      curr->m_left = NULL;
    }
    else//left child has children
    {
      // checks if left child of curr node has a right child, 
      //if yes, then move down to locate greatest element
      if((curr->m_left)->m_right != NULL) //left right child exists 
      {
        TreeNode<T>* leftrightcurr;
        TreeNode<T>* leftcurr;
        leftcurr = curr->m_left; //left child of curr
        leftrightcurr = (curr->m_left)->m_right; //right child of the one above
        while(leftrightcurr->m_right != NULL)
        {
          leftcurr = leftrightcurr;
          leftrightcurr = leftrightcurr->m_right;
        } //ends up with leftrightcurr being greatest left side of tree
        curr->m_data = leftrightcurr->m_data;
        leftcurr->m_right = NULL; //parent node of greatest element of left subtree        
        leftcurr->m_right=leftrightcurr->m_left; //replaces node from left if exists
        delete leftrightcurr; //deletes greatest element on left subtree
        
      }
      else //left right child does not exists
      {
        TreeNode<T>* tmp;
        tmp = curr->m_left;
        curr->m_data = tmp->m_data;
        curr->m_left = tmp->m_left;  //moves up the child of the node moved.
        delete tmp; 
      }
    }
  }
}

// Purpose: Prints the Tree in Pre-Order    
template < typename T >
void MyBSTree<T>::printPreOrder() //const
{
  preOrder(m_root);
  cout << endl;
}


//recursive printpreorder function
template < typename T >
void  MyBSTree<T>::preOrder(TreeNode<T>* printer)
{
  if(printer != NULL)
  {
    cout <<printer->m_data << " ";
    if(printer->m_left)
      preOrder(printer->m_left);
    if(printer->m_right)
      preOrder(printer->m_right);
  }
}


// Purpose: Prints the Tree in Pre-Order    
template < typename T >
void MyBSTree<T>::printPostOrder()// const
{
  postOrder(m_root);
  cout << endl;
}


//recursive printpostorder function
template < typename T >
void  MyBSTree<T>::postOrder(TreeNode<T>* printer)
{
  if(printer != NULL)
  {
    if(printer->m_left)
      postOrder(printer->m_left);
    if(printer->m_right)
      postOrder(printer->m_right);
    cout << printer->m_data << " ";
  }
}


// Purpose: Prints the Tree In-Order with formatting
//     each level indented 4 spaces, one element per line  
template < typename T >
void MyBSTree<T>::print()
{
  prettyPrint(m_root, 0);
}


//recursive print function
template < typename T >
void  MyBSTree<T>::prettyPrint(const TreeNode<T>* t, int pad)
{
  string s(pad, ' ');
  
  if (t == NULL)
    cout << endl;
  else
  {
    prettyPrint(t->m_right, pad+4);
    cout << s << t->m_data << endl;
    prettyPrint(t->m_left, pad+4);
  }
}
