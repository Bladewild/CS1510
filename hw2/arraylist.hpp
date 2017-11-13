//Name: Marky Santos-Tankia
//Section: A
#include <iostream>
using namespace std;


template <typename T>
void ArrayList<T>::grow()
{

  T *tmp=new T[m_max*2];
  for(int i=0;i<m_size;i++)
		tmp[i]=m_data[i];
	m_max=m_max*2;
  delete [] m_data;
  m_data=tmp;
}

template <typename T>
void ArrayList<T>::shrink()
{

  T *tmp=new T[m_max/2];
  for(int i=0;i<m_size;i++)
		tmp[i]=m_data[i];
	m_max=m_max/2;
  delete [] m_data;
  m_data=tmp;
}

//   * ---- Constructors ---

template <typename T>
ArrayList<T>::ArrayList(int s, const T& x) //elements in list could be lower than s
{
  //set varaibles
	m_size=0;
  m_max=s;
  m_data = new T[s];
 for(int i=0; i<m_size; i++)
 {
    m_data[i]=x.m_data[i];
  }
  
}

template <typename T>
ArrayList<T>::~ArrayList()
{
  m_size=0;
  m_max=0;
  delete [] m_data;
  m_data=NULL;  
}

template <typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& rhs)
{
  if(this!=&rhs)
  {
    m_size=rhs.m_size;
    delete [] m_data;
    m_data= new T[rhs.m_max];
    for(int i=0;i<m_size;i++)
    {
      m_data[i]=rhs.m_data[i];
    }

  }
  return *this;
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& cpy)
{
  m_data=NULL;
  *this=cpy;
}

template <typename T>
int ArrayList<T>::size() const
{
  return m_size;
}

//int max() const { return m_max; };

template <typename T>
const T& ArrayList<T>::first() const
{
  if(m_size==0)
  {
    cout<<"!-- ERROR : PANIC in ARRAYLIST!!.first() (List is empty)"<<endl;
    return m_errobj;
  }
  return m_data[0];
}

template <typename T>
T& ArrayList<T>::operator[](int i)
{
  if(i<0 || i>m_size)
  {
    cout<<"!-- ERROR : PANIC in ARRAYLIST!!.[] (index out of bounds)"<<endl;
    return m_errobj;
  }
  return  m_data[i]; 
}

template <typename T>
const T& ArrayList<T>::operator[](int i) const
{
  if(i<0 || i>m_size)
  {
    cout<<"!-- ERROR : PANIC in ARRAYLIST!!.[] (index out of bounds)"<<endl;
    return m_errobj;
  }
  return  m_data[i]; 
}

template <typename T>
int ArrayList<T>::find(const T& x) const
{
  for(int i=0;i<m_size;i++)
  {
    if(m_data[i]==x)
      return i;
  }
  return -1;
}

// * ----- Basic Mutator Operations ----- 

template <typename T>
void ArrayList<T>::clear()
{
  delete [] m_data;
  m_data=NULL;
  m_size=0;
  m_max=0;
}

template <typename T>
void ArrayList<T>::insert_back(const T& x)
{
  if(m_size==m_max)
  {
    if(m_max==0)//stops grow from multiplying 2
      m_max=1;
    else
      grow();
  }
  if(m_data==NULL)
     m_data= new T [m_max];
  m_data[m_size]=x;
  m_size++;
  
}

template <typename T>
void ArrayList<T>::insert(const T& x, int i)
{
  if(i<0 || i>m_size)
  {
    cout<<"!-- ERROR : PANIC in ARRAYLIST!!.insert() (index out of bounds)"<<endl;
    return;
  }
  if(m_size==m_max)
  {
    if(m_max==0)//stops grow from multiplying 2
      m_max=1;
    else
      grow();
  }
  if(m_data==NULL)
     m_data= new T [m_max];
  for(int k=m_size-1;k>=i;k--)
    m_data[k+1]=m_data[k];
   m_data[i]=x;
   m_size++;
}
  
template <typename T>
void ArrayList<T>::remove(int i)
{
  if(i<0 || i>m_size)
  {
    cout<<"!-- ERROR : PANIC in ARRAYLIST!!.remove() (index out of bounds)"<<endl;
    return ;
  }
  if(m_size<(m_max/4))
    shrink();
  for(int k=i;k<m_size-1;k++) //there will always be a space after the last one
    m_data[k]=m_data[k+1]; //so the last element isn't deleted but its not accessed.
  m_size--;

}

// ----- Complex Mutator Operations ----- 
 
// Purpose: swaps two elements of the array
// Parameters: i, k, two positions on the Arraylist
// Postconditions: the elements at positions i and k swap positions

template <typename T>
void ArrayList<T>::swap(int i, int k)
{
  if(i<0 || i>m_size || k<0 || k>m_size)
  {
    cout<<"!-- ERROR : PANIC in ARRAYLIST!!.swap() (index out of bounds)"<<endl;
    return;
  }
  if(i!=k)
  {
    T tmp=m_data[k];
    m_data[k]=m_data[i];
    m_data[i]=tmp;  
  }
  
}
// Purpose: appends two lists
// Parameters: alist, a list to appended to the end of 'this' list
// Postconditions: current size is incremented by size of alist
//     the elements of alist are appended to the elements of 'this' 

template <typename T>
void ArrayList<T>::append(const ArrayList<T>& alist)
{
  for(int i=0; i<alist.m_size;i++)
      insert_back(alist.m_data[i]);
}

// Purpose: Reverses an ArrayLost
// Postconditions: the elements in the list are now reversed.

template <typename T>
void ArrayList<T>::reverse()
{
  T tmp;
  int j=m_size-1;//backwards counter
  for(int i=0;i<m_size/2;i++)
  {
    tmp=m_data[i];
    m_data[i]=m_data[j];
    m_data[j]=tmp;
    j--;
  }
}
