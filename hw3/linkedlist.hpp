//Name: Marky Santos-Tankia
//CS1510
//Section: A

#include <iostream>
using namespace std;


// Purpose: Default constructor
// Postconditions: this list represents the empty list
template <class T>
LinkedList<T>::LinkedList()
{ 
  m_size=0;
  m_head= new Node<T>;
  m_head->m_next=NULL;
  m_back= new Node<T>;
  m_back->m_next=NULL;
}


// -------------
// --------- Big 3 Member Functions ---
// -------------

// Purpose: Destructor
template <class T>
LinkedList<T>::~LinkedList()
{
  clear();
}

// Purpose: performs a deep copy of the data from rhs into this linked list
// Parameters: rhs is linked list to be copied
// Returns: *this
// Postconditions: this list contains same data values (in the same order)
//     as are in rhs; any memory previously used by this list has been
//     deallocated.
template <class T>
const LinkedList<T>&  LinkedList<T>::operator= (const LinkedList<T>& rhs)
{
  if(this!=&rhs)
  {
    if(!isEmpty())
        clear();
    m_head=rhs.m_head;

    Node<T> *p= new Node<T>; //running pointer
    p=rhs.m_head;
    while(p -> m_next != NULL)
    {
        insert_back(p->m_data);
        p = p->m_next;
    }
    insert_back(p->m_data); //BECAUSE I HAVE NO SENTINEL
    m_size=rhs.m_size;
  }
  return *this;

}

// Purpose: copy constructor
// Parameters: rhs is the LinkedList that is to be copied
// Postconditions: this list contains same data values (in same order) 
//      as in rhs.
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& rhs)
{
  *this=rhs;
}


// -------------
// --------- Basic Accessor Operations ---
// -------------

// Purpose: accessor function to the size the list
// Returns: current size of the list
template <class T>
int LinkedList<T>::size() const
{
  return m_size;
}
  
// Purpose: determines whether the list is empty
// Returns: 'true' if list is empty; 'false' otherwise
template <class T>
bool LinkedList<T>::isEmpty() const
{
  if(m_size==0)
    return true;
  else 
    return false;
}

// Purpose: Get a pointer to the first element node
// Returns: pointer to the first node in the list; 
//     returns NULL if the list is empty
template <class T>
Node<T>* LinkedList<T>::getFirstPtr()
{
  if(!isEmpty())
    return m_head;
  else
  {
    cout<<"List is empty";
    return NULL;
  }
}

// Purpose: Get a pointer to constant to the first element node               
// Returns: pointer to constant to the first node in the list;                
//     returns NULL if the list is empty    
template <class T>
const Node<T>* LinkedList<T>::getFirstPtr() const
{
  if(!isEmpty())
    return m_head;
  else
  {
    cout<<"List is empty";
    return NULL;
  }
}

// Purpose: accessor function for last element node
// Returns: pointer to the last element's node in the list; 
//     returns NULL if list is empty
template <class T>
Node<T>* LinkedList<T>::getLastPtr()
{
  if(!isEmpty())
    return m_back;
  else
  {
    cout<<"List is empty";
    return NULL;
  }
}

// Purpose: accessor function for a node in the list
// Returns: pointer to the node at the i'th position in the list; 
//     returns NULL if no such element exists.
template <class T>
Node<T>* LinkedList<T>::getAtPtr(int i)
{
  if(!isEmpty())
  {
    if(i<0 || i>m_size-1) //stops if out of bounds
      return NULL;
    Node<T> * p= new Node<T>;
    p=m_head;
    for(int j=0;j<i;j++)
      p=p->m_next;
    return p;
  }
  else
  {
    cout<<"List is empty";
    return NULL;
  }
}



// -------------
// --------- Basic Mutator Operations ---
// -------------

// Purpose: effectively "empties" the list, 
//          Turn the list into an empty list.
// Postconditions: ALL dynamically allocated memory for elements is deallocated
template <class T>
void LinkedList<T>::clear()
{
  if(m_size!=0)
  {
    Node<T> * p=new Node<T>;
	p=m_head;
    while(p->m_next!=NULL)
    {
      Node<T> * tmp=p->m_next;
      delete p;
      p=tmp;
    }
    m_size=0;
    m_back=NULL;
    m_head=NULL;
  }
  else
  {
    //cout<<"List Already Empty."<<endl;
  }
}

// Purpose: insert element x in the front of the list 
// Parameters: x is data value to inserted
// Postconditions: x is the first element of the list
template <class T>
void LinkedList<T>::insert_front(const T& x)
{
  Node<T> * tmp=new Node<T>;
  tmp->m_data=x;
  tmp->m_next =m_head;
  m_head=tmp;
  if(m_size==0)//from empty to 1 element
  {
    m_back=tmp;
  }
  else if(m_size==1) //from 1 element to 2 elements
  {
    m_back=m_head->m_next;
  }
  m_size++;
}

// Purpose: insert element x in the back of the list 
// Parameters: x is data value to inserted
// Postconditions: x is the last element of the list
template <class T>
void LinkedList<T>::insert_back(const T& x)
{
  if(isEmpty())
    insert_front(x);//there's going to be only one element.
  else if(m_size==1)
    {
      Node<T> * tmp=new Node<T>;
      tmp->m_data=x;
      m_head->m_next=tmp;
      tmp->m_next=NULL;
      m_back=tmp;
      m_size++;
    }  
  else
  {
    Node<T> * tmp=new Node<T>;
    tmp->m_data=x;
    m_back->m_next=tmp;
    tmp->m_next =NULL;
    m_back=tmp;
    m_size++;
  }
}

// Purpose: puts the data value x at the position pointed by pos
// Parameters: x is data value to inserted
//     pos pointer to the position to insert x at.
// Preconditions: pos is a pointer to a node in this list.
// Postconditions: x is inserted at the position pointed by pos
template <class T>
void LinkedList<T>::insert(const T& x, Node<T>* pos)
{
  Node<T> * tmp= new Node<T>;
  tmp->m_data=pos->m_data;
  tmp->m_next=pos->m_next;
  pos->m_data=x;
  pos->m_next=tmp;
  m_size++;
}


// Purpose: remove the element in the front of the list 
// Postconditions: the first element of the list is removed
template <class T>
void LinkedList<T>::remove_front()
{
  remove(m_head);
}

// Purpose: removes the element at the back of the list 
// Postconditions: the last element of the list is removed
template <class T>
void LinkedList<T>::remove_back()
{
  if(m_head->m_next==NULL)
  {
    delete m_head;
    m_head=NULL;    
    m_size--;
  }
  else
  { 
    Node<T> * p=new Node<T>;
    p=getAtPtr(m_size-2);
    delete m_back;
    p->m_next=NULL;
    m_back=p;
    m_size--;
  }
}

// Purpose: remove the element in the position pointed by pos
// Parameters: pos pointer to the position to remove.
// Preconditions: pos is a pointer to a node in this list.
// Postconditions: element pointed by pos is removed from the list
template <class T>
void LinkedList<T>::remove(Node<T>* pos)
{
  Node<T> * tmp=new Node<T>;
                       /* step 1 */
  tmp = pos->m_next;
                       /* step 2 */
  pos->m_data = tmp->m_data;
  pos->m_next = tmp->m_next;
  delete tmp; 
  m_size--;
}


// --------
// ---- Complex Operations ---
// --------

// Purpose: determines whether this list is identical to rhs list in
// terms of data values and their order in the list
// Parameters: rhs is list to be compared to this list
// Returns: true if lists are identical; otherwise, false
template <class T>
bool LinkedList<T>::operator== (const LinkedList<T>& rhs) const
{
  const Node<T> * lp=new Node<T>;
  lp=this->getFirstPtr();
  const Node<T> * rp=new Node<T>;
  rp=rhs.getFirstPtr();

  do
  {
    if(lp->m_data != rp->m_data)
    {
      return false;
    }

    lp=lp->m_next;
    rp=rp->m_next;
  }while(rp->m_next != NULL && lp->m_next!=NULL);
  return true;
}



// ---------------  Utility Function for Printing
// Purpose: prints a LinkedList
template <class T>                 
std::ostream& operator<< (std::ostream& out, const LinkedList<T>& list)
{
  //first node
  if(!(list.isEmpty()))
  {
    const Node<T> * p= list.getFirstPtr();
    //out<<"[,";
    while(p->m_next!=NULL)
    {
       out<<p->m_data;//<<", ";
       p=p->m_next;
    }
    out<<p->m_data;//<<"]";
  }
  
  return out;
}

