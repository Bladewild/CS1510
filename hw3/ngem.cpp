//Name: Marky Santos-Tankia
//CS1510
//Section: A

#include "linkedlist.h"

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

void append(LinkedList<char> list [],int id,string sequence);
void trim(LinkedList<char> list [],int id,int pos);
void clip(LinkedList<char> list [],int id,int start,int stop);
void slice(LinkedList<char> list [],int id,int start,int stop);
void copy(LinkedList<char> list [],int id1,int id2);
void swap(LinkedList<char> list [],int id1,int start1,int id2,int start2);
void transcribe(LinkedList<char> list [],int id);

void print(const LinkedList<char> list []);
int main ()
{
  string s;

  LinkedList <char> list [5];

  int count=0;
  while ( cin >> s )
  {
    if(count<5)
    {
      int size=s.size();
      for(int i=0;i<size;i++)
        list[count].insert_back(s[i]);        
      count++;
	  }
	  if(s=="print")
	    print(list);
    else if (s=="append")
    {
      cin>>s;
      int id=atoi(s.c_str());
      cin>>s;
      string newSequence=s;
      append(list,id,newSequence);
    }
    else if (s=="trim")
    {
      cin>>s;
      int id=atoi(s.c_str());
      cin>>s;
      int pos=atoi(s.c_str());
      trim(list,id,pos);
    }
    else if (s=="clip")
    {
      cin>>s;
      int id=atoi(s.c_str());
      cin>>s;
      int start=atoi(s.c_str());
      cin>>s;
      int stop=atoi(s.c_str());
      clip(list,id,start,stop);
    }
    else if (s=="slice")
    {
      cin>>s;
      int id=atoi(s.c_str());
      cin>>s;
      int start=atoi(s.c_str());
      cin>>s;
      int stop=atoi(s.c_str());
      slice(list,id,start,stop);
    }
    else if (s=="copy")
    {
      cin>>s;
      int id1=atoi(s.c_str());
      cin>>s;
      int id2=atoi(s.c_str());
      copy(list,id1,id2);
    }
    else if (s=="swap")
    {
      cin>>s;
      int id1=atoi(s.c_str());
      cin>>s;
      int start1=atoi(s.c_str());
      cin>>s;
      int id2=atoi(s.c_str());
      cin>>s;
      int start2=atoi(s.c_str());
      swap(list,id1,start1,id2,start2);
    }
    else if(s=="transcribe")
    {
      cin>>s;
      int id=atoi(s.c_str());
      transcribe(list,id);
    }

     
  }
  
  
  return 0;

}

//append id sequence
//Insert sequence at the end of the id strand
void append(LinkedList<char> list [],int id,string sequence)
{
  if(id>4 || id<0)
  {
    cout<<"ERROR! append: invalid parameters."<<endl;
    return;
  }
  int size=sequence.size();
  for(int i=0;i<size;i++)
  {
    if(sequence[i]!='P' && sequence[i]!='Y' && sequence[i]!='O'
    && sequence[i]!='T' && sequence[i]!='K' && sequence[i]!='M' 
    && sequence[i]!='B')
    {
      cout<<"ERROR! append: invalid parameters."<<endl;
      return;
    }
  }

  for(int i=0;i<size;i++)
    list[id].insert_back(sequence[i]);
}

//trim id start
//remove from the id strand every element from position start to the end of the strand.
void trim(LinkedList<char> list [],int id,int pos)
{
  if(id>4 || id<0)
  {
    cout<<"ERROR! trim: invalid parameters."<<endl;
    return;
  }
  int size=list[id].size();
  if(pos<0 || pos>size)
  {
    cout<<"ERROR! trim: invalid parameters."<<endl;
    return;
  }
	int difference= list[id].size()-pos;
  for(int i=0;i<difference;i++)
  {
    list[id].remove_back();
  }
}
//clip id start stop
//remove from strand id every element from position start to stop, inclusive.
void clip(LinkedList<char> list [],int id,int start,int stop)
{
  if(id>4 || id<0)
  {
    cout<<"ERROR! clip: invalid parameters."<<endl;
    return;
  }
  if(start>stop) //cannot do backwards
  {
    cout<<"ERROR! clip: invalid parameters."<<endl;
    return;
  }

  int size=list[id].size();
  if(start<0 || start>size || stop<0 || stop>size)
  {
    cout<<"ERROR! clip: invalid parameters."<<endl;
    return;
  }
  for(int i=start;i<=stop;i++)
  {
    list[id].remove(list[id].getAtPtr(start));//used start because removes shifts the places.
  }
}
//slice id start stop
//Replace the id strand with a slice of itself. The slice is the subsequence of id starting at position start and ending at position stop inclusive.
void slice(LinkedList<char> list [],int id,int start,int stop)
{
  if(id>4 || id<0)
  {
    cout<<"ERROR! slice: invalid parameters."<<endl;
    return;
  }
  if(start>stop) //cannot do backwards
  {
    cout<<"ERROR! slice: invalid parameters."<<endl;
    return;
  }
  
  int size=list[id].size();
  if(start<0 || start>size || stop<0 || stop>size)
  {
    cout<<"ERROR! slice: invalid parameters."<<endl;
    return;
  }
  LinkedList <char> newList;
  for(int i=start;i<=stop;i++)
  {
    newList.insert_back(list[id].getAtPtr(i)->m_data);
  }
  list[id]=newList;
}
//copy id1 id2
//make strand id2 an exact copy of strand id1
void copy(LinkedList<char> list [],int id1,int id2)
{
  if(id1>4 || id1<0 || id2>4 || id2<0)
  {
    cout<<"ERROR! copy: invalid parameters."<<endl;
    return;
  }
  if(!(list[id2]==list[id1]))
    list[id2]=list[id1];
}

//swap id1 start1 id2 start2
//Swap the tails of the strands id1 and id2 at positions start1 and start2. The tail of id1 starts at position start1 and the tail of id2 starts at position start2
void swap(LinkedList<char> list [],int id1,int start1,int id2,int start2)
{
  if(id1>4 || id1<0 || id2>4 || id2<0)
  {
    cout<<"ERROR! swap: invalid parameters."<<endl;
    return;
  }
  int size1= list[id1].size();
  int size2= list[id2].size();

  if(start1<0 || start1>size2 || start2<0 || start2>size2)
  {
    cout<<"ERROR! swap: invalid parameters."<<endl;
    return;
  }
   
  for(int i=start1;i<size1;i++)
  {
    char a=list[id1].getAtPtr(i)->m_data;
    list[id2].insert_back(a);//puts tail1 at end of id2. id 2 is stacked
  }
  trim(list,id1,start1);//remove tail1 from id1

  //transfer tail2 to tail 1;Remember, tail 1 is stacked on tail 2.
  for(int i=start2;i<size2;i++)
  {
    char a=list[id2].getAtPtr(i)->m_data;
    list[id1].insert_back(a);//puts tail1 at end of id2. id 2 is stacked
  }
  for(int i=start2;i<size2;i++)
  {
    list[id2].remove(list[id2].getAtPtr(start2));
  }
}
//transcribe id
//Convert every element in strand id to its complement, and reverse the strand.
void transcribe(LinkedList<char> list [],int id)
{ 
  if(id>4 || id<0)
  {
    cout<<"ERROR! transcribe: invalid parameters."<<endl;
    return;
  }
  //Transcribe
  int size=list[id].size();
  for(int i=0;i<size;i++)
  {
    char a=list[id].getAtPtr(i)->m_data;
    switch(a)
    {
      case 'P': a='Y'; break;
      case 'Y': a='P'; break;
      case 'O': a='T'; break;
      case 'T': a='O'; break;
      case 'K': a='M'; break;
      case 'M': a='K'; break;
      //B is same
    }
    list[id].getAtPtr(i)->m_data=a;//complement is switched
  }
  //Reverse
  LinkedList <char> newList;
  size=list[id].size();
  for(int i=0;i<size;i++)
    newList.insert_front(list[id].getAtPtr(i)->m_data);
  list[id]=newList; 

}
//Print out the sequences indicating their id and length. Print in the format shown in the sample output.

void print(const LinkedList<char> list [])
{
  for(int i=0;i<5;i++)
  {
    cout<<"#"<<i<<", "<<list[i].size()<<": "<<list[i]<<endl;
  }
  cout<<endl;
}

