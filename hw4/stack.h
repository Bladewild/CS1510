//Marky Santos-Tankia
//Section A


#ifndef STACK_H
#define STACK_H


#include <string>
#include "abstractstack.h"
#include <iostream>

using namespace std;

template <class T>
class Node
{
public:
  T m_data;            // Data to be stored
  Node<T>* m_next;     // Pointer to the next element in the list


  // Purpose: Default constructor
  // Postconditions: next pointer set to NULL
  // ---INLINE---
  Node() : m_next(NULL) {}

  // Purpose: Auxiliaty constructor, construct from parameters
  // Postconditions: data and next pointer set to parameters
  // ---INLINE---
  Node(const T& x, Node<T>* p) 
             : m_data(x), m_next(p) {}

};

template < typename T >
class Stack : public AbstractStack<T>
{
  Node<T> * m_head;

public:
  int m_size;
  string name;
  bool error;

  Stack()
  {
    m_size=0;
    m_head= new Node<T>;
    m_head->m_next=NULL;
    error=false;
  }

  // Purpose: Checks if a Stack is empty
  // Returns: 'true' if the Stack is empty
  //     'false' otherwise
  virtual bool isEmpty() const
  {
    if(m_size==0)
      return true;
    else
      return false;

  }


  // Purpose: looks at the top of the Stack
  // Returns: a const reference to the element currently on top of the Stack
  // Exception: if the Stack is empty, THROW a 'Oops' object with an error message!!!
  virtual const T& top() const throw ( Oops )
  {

    try
    {
      Oops m=Oops("Error");
      if(isEmpty()) 
	    {
        throw (m);
      }
      return m_head->m_data;

    }
    catch(Oops x)
    {
      //cout<<endl<<"----"<<name<<"-----";
      //cout<<"Error in TOP: Stack is empty!";
      //cout<<"INVALID!";
      throw(x);
      //return NULL;
    }
  }

  // Purpose: push an element into the Stack
  // Parameters: x is the value to push into the Stack
  // Postconditions: x is now the element at the top of the Stack,
  virtual void push(const T& x)
  {
    if(isEmpty())
    {
      m_head= new Node<T>();
      m_head->m_data=x;
      m_head->m_next=NULL;
      m_size++;
    }
    else
    {
      Node<T> * p=new Node<T>;
      
      p->m_data=x;
      p->m_next=m_head;
      m_head=p;//p becomes new m_head
      m_size++;
    }

  }
  // Purpose: pop the Stack
  // Postconditions: the element formerly at the top of the Stack has
  // been removed
  // Note: Poping an empty Stack results in an empty Stack.
  virtual void pop()
  {
    if(isEmpty())
    {
      //cout<<"Error in POP: Stack is empty!";
      //cout<<"INVALID!"<<endl;
      Oops m=Oops("Error");
      throw (m);
      error=true;
    }
    else if(m_size>=2) //at least 2 elements
    {
      Node<T> * p=m_head->m_next; //2nd top element is kept.
      delete m_head;
      m_head= p; //new m_head
      m_size--;
    }
    else if (m_size==1) //1 element
    {
      delete m_head;
      m_head= NULL;
      m_size--;
    }
  }


  // Purpose: clears the Stack
  // Postconditions: the Stack is now empty
  virtual void clear()
  {
    if(!isEmpty())
    {
      for(int i=0;i<m_size;i++)
        pop();
      m_size=0;
    }
  }


  // Purpose: DESTRUCTOR
  virtual ~Stack()
  {
    clear();
  }

};

#endif
