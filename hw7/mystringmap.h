//Marky Santos-Tankia
//Section A

#include "abstractstringmap.h"

template < typename T >
struct Node
{
  public:
    string m_id; //key
    T m_value; //value
  
};

template < typename T >
class MyStringMap
{

  Node<T> ** m_table;
  int m_max;
  int m_size;
  Node<T> m_dead;
  
public:
      
  MyStringMap()
  {
    m_size=0;
    m_table= new Node<T>*[5];
    m_max=5;
    for(int k=0;k<(m_max);k++)
      m_table[k]=NULL;
  }
  ~MyStringMap()
  {
    clear();
    delete [] m_table;
    m_table=NULL;
  }

  virtual void grow()
  {

    //cout<<"FIRST"<<endl;
  
    Node<T> ** tmp= new Node<T>*[m_max*4]; //creates a new table 4times size
    for(int k=0;k<(m_max*4);k++)
      tmp[k]=NULL;

    //cout<<"SECOND"<<endl;
    for(int i=0;i<m_max;i++)
    {
      if(m_table[i]!=NULL && m_table[i]!=&m_dead)
      {
        ///cout<<"NOT NULL: "<<i<<endl;
        ///cout<<"< "<<m_table[i]->m_id<<", "
        ///        <<m_table[i]->m_value<<" >"<<endl<<endl;
        
        Node<T> * copiedNode= new Node<T>;//makes new pointer
        copiedNode->m_id=m_table[i]->m_id;
        copiedNode->m_value=m_table[i]->m_value;

        tmp[i]=copiedNode; //points to new pointer

        /// cout<<"TMP["<<i<<"]< "<<tmp[i]->m_id<<", "
         ///       <<tmp[i]->m_value<<" >"<<endl<<endl;
      }
      else if(m_table[i]==&m_dead)
      {
        ///cout<<"COPYING Tombstone"<<endl;
       tmp[i]=&m_dead;
      }
    }
    //cout<<"THIRD"<<endl;
    
    int keepm_size=m_size;//because clear makes it 0;
    clear();
    m_size=keepm_size;
    //cout<<"FOURTH"<<endl;
    delete [] m_table;
    m_table=tmp;


    m_max=m_max*4;
    ///cout<<"New Max "<<m_max<<endl;
  }

   /*** ---- Accessor Operations ---- */
  
// Purpose: Accessor function for the number of elements in the Map
// Returns: number of elements in the Map 
  virtual int size()
  {
    return m_size;
  }


// Purpose: Checks if a Map is empty
// Returns: 'true' if the Map is empty
//     'false' otherwise  
  virtual bool isEmpty()
  {
    if(m_size==0)
      return true;
    return false;
  }


// Purpose: Returns the value associated with a key.
// Parameters: key of the value to be found 
// Returns: 
//     If The Map contains Key then return the value associated with Key.
//     If The Map does not contains Key then THROW an OOPs object
  virtual const T& valueOf(const string& key) const throw ( Oops )
  {
  	int i= hash(key);
    try
    {
      Oops m=Oops("Key Not Found!!");
      while (m_table[i]!= NULL && m_table[i]->m_id!=key)
        {
          i=(i+1)%m_max;//loops around
        }

        //cout<<"["<<i<<"]"<<endl;
        if(m_table[i]==&m_dead)
        {
          ///cout<<"Is a tombstone"<<endl;
        }
      //cout<<i<< "Place"<<endl;
      if(m_table[i]==NULL || m_table[i]==&m_dead) //not found
        throw (m);

      //key must have been found
      return m_table[i]->m_value;
    }
    catch(Oops e)
    {
      throw(e);
    }
    


  }

    
  /*** ---- Mutator Operations ---- */

// Purpose: Clears the Map
// Postconditions: an empty Map
  virtual void clear()
  {
    static int k=0;
    for(int i=0;i<m_max;i++)
    {

      if(m_table[i]!=NULL && m_table[i]!=&m_dead)
      {

        k++;
        //cout<<"k="<<k<<endl;
        //cout<<"< "<<m_table[i]->m_id<<", "
        //       <<m_table[i]->m_value<<" >"<<endl;
        //cout<<"deleting entry"<<endl;
        delete m_table[i];
        m_table[i]=NULL;
      }      
    }
    //Does not delete table
    m_size=0;

  }


// Purpose: Inserts an element into a Map
// Parameters: Key and  Value to be added to the Map
// Postconditions: The Map now contains the pair < Key, Value >
//     if the Map already contains a value associated with Key,
//     replace it with the parameter Val
  virtual void insert(const string& key, const T& val)
  {
    int i= hash(key);
    while(i>m_max) //grows until hash can be inputted
      grow();

    // stops if find an entry to replace or null pointer or if a tombstone
    while (m_table[i]!= NULL && m_table[i]->m_id!=key && m_table[i]!=&m_dead)
    {
      i=(i+1)%m_max;//loops around
    }
    
    Node<T> * tmp= new Node<T>;
    
    tmp->m_id=key;
    tmp->m_value=val;
    

    //cout<<tmp->m_id<<" "<<tmp->m_value<<endl;


    if(m_table[i]==NULL || m_table[i]==&m_dead)
      m_size++; //* increase only if  new element is added, not replaced. 

    if(m_table[i]!=&m_dead)// delete if not a tombstone.
      delete m_table[i];//removes whatever is on this index

    m_table[i]= tmp;
    ///cout<<"CURRENT INSERT: "<<i<<endl;
    //cout<<"after< "<<m_table[i]->m_id<<", "
    //         <<m_table[i]->m_value<<" >"<<endl;


    while(m_size>m_max*1/4) //m_max has to be 4 times greater than m_size
      grow();
  }  
// Purpose: Removes an element from the Map
// Parameters: K, the Key to remove
// Postconditions: the map does not contains a pair with k as Key
  virtual void remove(const string& k)
  {
    int i=hash(k);
    ///cout<<"CURRENT REMOVE: "<<i<<" ["<<k<<"]"<<endl;
    while(m_table[i]!=NULL && m_table[i]->m_id!=k
      && m_table[i]!=&m_dead)
    {
      i=(i+1)%m_max;
    }
    if(m_table[i]==NULL)
      return; //there is nothing to remove

    delete m_table[i]; //note danger. can lose the rest.
                       //Use a tombstone.
    m_table[i]=&m_dead;
    m_size--;
  }
          
     
  /*** ---- Output Operations ---- */

// Purpose: Prints the Map with pretty formatting
// NOTE: No particular order is required.
  virtual void print()
  {
    //cout<<"< "<<m_table[0]->m_id<<", "
     //           <<m_table[0]->m_value<<" >"<<endl;
    for(int i=0;i<m_max;i++)
    {

      if(m_table[i]!=NULL && m_table[i]!=&m_dead)
      {
        cout<<"< "<<m_table[i]->m_id<<", "
                <<m_table[i]->m_value<<" >"<<endl;
      }
      /*
      if(m_table[i]==&m_dead)
      {
        cout<<i<<" Tombstone: "
        <<"< "<<m_table[i]->m_id<<", "
                <<m_table[i]->m_value<<" >"<<endl;
      }*/
    }
    
  }
          
          
  /*** ---- Utility Functions Operations ---- */

// Purpose: Hashes a string into an integer.
// you shall use this function for your hash-table.
private:
  virtual int hash(const string &s) const
  {
    //cout<<"current string:"<<s<<endl;
    //cout<<s.length()<<endl;
  	int n=0,k=s.length();
  	
    for(int i=0;i<k;i++)
      {
        //cout<<"["<<int(s[i])<<"]";
        n=n+s[i];
      }
      //cout<<endl;
    if(n<0)
      return -(n);
    else
      return n;
  }             
          
};
