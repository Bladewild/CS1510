//Marky Santos-Tankia
//Section A

#include <iostream>
#include "stack.h"
#include <cstdlib>
#include <sstream>

using namespace std; 

bool checkOperator(string s);
bool checkBracket(string s);
bool isOpeningBracket(string s);
bool isSameBracket(string top,string s);
int operate(int a,string op,int b);

int main()
{
  string ins;
  string input;
  bool ERROR=false;
  int count=0;
  Stack<int> total;
  total.name= "NUMBERS";
  Stack<string> operations;  
  operations.name= "OPERATIONS";
  Stack<string> brackets;  
  brackets.name= "BRACKETS";

  do
  {
  	count++;
  	getline(cin, ins); 
  	istringstream inputstr(ins);
  	if(ins!=".")
  	{
  		
  	  cout<<"#"<<count<<": ";
  	  try
  	  {
  	  while(inputstr>>input) 
  	  {
  	  	//if(input==".")
  	    //  break;
  	  	//asdcout<<"CURRENT: "<<input<<endl;
  	  	
        
  	    if(checkBracket(input))
  	  	{
  	  	  
  	  	  
  	  		//asdcout<<"DERP"<<endl;
  	  		if(isOpeningBracket(input))//add to stack
  	  		{
  	  		  
  	  			//asdcout<<"DERP OPENING"<<endl;

  	  			brackets.push(input); //ONLY PUSH----
  	  			//asdcout<<"\'"<<input<<"\' have been pushed"<<endl;
  	  			//asdcout<<"BRACKET SIZE: "<<brackets.m_size<<endl;
  	  		}
  	  		else
  	  		{
  	  		  if(total.m_size==0)//closing initial bracket.
					  {
					    ERROR=true;
					    Oops m=Oops("Error");
  	  			  throw (m);
					    break;
					  }
  	  			//asdcout<<"DERP CLOSING"<<endl;
  	  			//asdcout<<"BRACKET SIZE: "<<brackets.m_size<<endl;
  	  			string top=brackets.top();
  	  			//asdcout<<"DERP AFTER"<<endl;
  	  			//check whether same type of bracket
  	  			if(isSameBracket(top,input))//same, pop	
  	  			{
  	  				//cout<<total.m_size<<endl;
  	  		
          		
				  if(total.m_size==0)//empty brackets initially.
					{
					  ERROR=true;
					  Oops m=Oops("Error");
  	  			throw (m);
					  break;
					}
					
					
  	  				int result,a,b;

  	  				//asdcout<<brackets.top()<<" REMOVED"<<endl;
  	  				brackets.pop(); // BRACKETS REMOVED ONLY POP----
  	  				//asdcout<<"BRACKET SIZE: "<<brackets.m_size<<endl;

  	  				//complete the operations
  	  				b=total.top();//get top number
  	  				total.pop();
  	  				a=total.top();//get next top number
  	  				total.pop();
  	  				//both numbers have been popped

  	  				//asdcout<<"\n\nUsing "<<operations.top()<<" operator"<<endl;
  	  				result= operate(a,operations.top(),b);// a operator b
  	  				operations.pop();//get rid
  	  				total.push(result);

  	  			}
  	  			else //INVALID INPUT!!!
  	  			{
  	  			  Oops m=Oops("Error");
  	  				throw (m);
  	  			}
  	  		}
  	  	}//-------------------------------------------
  	  	else if(checkOperator(input))
  	  	{
  	  		
  	  		if(total.m_size==0)//empty brackets.
  	  		{
  	  		  ERROR=true;
  	  		  Oops m=Oops("Error");
  	  			throw (m);
			}
			
  	  		operations.push(input);
  	  	}
  	  	else //a number
  	  	{
  	  		//the top two will be evaluated.

			if(brackets.m_size==0)//no brackets.
  	  		{
  	  		  ERROR=true;
  	  		  Oops m=Oops("Error");
  	  			throw (m);
			}
			
  	  		int number=atoi(input.c_str());
  	  		total.push(number);
  	  	}
  	  }
  	}
  	catch(Oops x)
  	{
  	  ERROR=true;
    }
    
  	  

  	  //out of the loop
  	  bool a,b,c;
  	  a=operations.error;
  	  b=brackets.error;
  	  c=operations.error;
      if(a || b || c)
        ERROR=true;
        
  	  if(brackets.m_size!=0) //the brackets did not close
  	  	ERROR=true;
  	  if(operations.m_size!=0) //the oepertions did not close
  	    ERROR=true;
  	    
  		//check if there is still something in the stacks
  		if(ERROR)
  		{
				//cout<<"#"<<count<<": "<<"INVALID!"<<endl;
				cout<<"INVALID!";
				ERROR=false;
  		}
  		else
  		{
  			//cout<<"#"<<count<<": ";
  		  cout<<total.top();
  		  total.pop();
  		  //cout<<endl;
   		  //cout<<brackets.m_size;
   		  //cout<<endl;
   		  //cout<<operations.m_size;

  		}
  		
  		cout<<endl;

  		//clear out stacks
  		total.clear();
  		brackets.clear();
  		operations.clear();
  	}
  }while(ins!=".");

  
}
bool checkOperator(string s)
{
  if(s=="+")
  	return true;
  else if(s=="-")
  	return true;
  else if(s=="*")
  	return true;
  else if(s=="/")
  	return true;
  else if(s=="%")
  	return true;
  return false;
}
bool checkBracket(string s)
{
  if(s=="("||s==")")
  	return true;
  else if(s=="["||s=="]")
  	return true;
  else if(s=="{"||s=="}")
  	return true;
  return false;
}

bool isOpeningBracket(string s)
{
  if(s=="(")
  	return true;
  else if(s=="[")
  	return true;
  else if(s=="{")
  	return true;
  return false;
}

bool isSameBracket(string top,string s)
{
	if(top=="(" && s==")")
  	return true;
  else if(top=="[" && s=="]")
  	return true;
  else if(top=="{" && s=="}")
  	return true;
  return false;
}

int operate(int a,string op,int b)
{
	int result=0;
	//asdcout<<a<<" "<<op<<" "<<b<<endl;
	if(op=="+")
  	result=a+b;
  else if(op=="-")
  	result=a-b;
  else if(op=="*")
  	result=a*b;
  else if(op=="/")
  	result=a/b;
  else if(op=="%")
  	result=a%b;
  //asdcout<<endl<<"RESULT: "<<result<<endl;
  return result;

}


/*
int main()
{
	Stack<string> brackets; 
	string top;
  brackets.name= "BRACKETS";

  brackets.push("(");
  cout<<brackets.top();
  brackets.push("[");
  cout<<brackets.top();
  brackets.push("{");
  cout<<brackets.top();
  brackets.push("-");
  cout<<brackets.top();

  cout<<endl<<endl<<"SIZE: "<<brackets.m_size;
  cout<<endl;
  cout<<brackets.top()<<" REMOVED"<<endl;
  brackets.pop();
  cout<<"SIZE: "<<brackets.m_size<<endl<<endl;

  cout<<brackets.top()<<" REMOVED"<<endl;
  brackets.pop();
  cout<<"SIZE: "<<brackets.m_size<<endl<<endl;
   
  cout<<brackets.top()<<" REMOVED"<<endl;
  brackets.pop();
  cout<<"SIZE: "<<brackets.m_size<<endl<<endl;
  
  cout<<brackets.top()<<" REMOVED"<<endl;
  brackets.pop();
  cout<<"SIZE: "<<brackets.m_size<<endl<<endl;
  

	return 0;
}
*/
/*
int main()
{
	Stack<int> s;
	
	s.push(3);
	cout<<s.top();
	s.push(5);
	cout<<s.top()<<" "<<s.m_size<<endl;
	s.pop();
	cout<<s.top()<<" "<<s.m_size<<endl;
	s.pop();
	cout<<" "<<s.m_size<<endl;
	s.pop();
	cout<<" "<<s.m_size<<endl;
	s.pop();
	cout<<" "<<s.m_size<<endl;
	
	s.push(3);
	cout<<s.top();
	s.push(5);
	cout<<s.top();
	cout<<endl<<"Clearing."<<endl;
	s.clear();
	cout<<endl<<s.top()<<" Size:"<<s.m_size<<endl;
	s.push(3);
	cout<<s.top();
	s.push(5);
	cout<<s.top();
	cout<<endl<<" Size:"<<s.m_size;
	s.pop();
	cout<<endl<<s.top()<<" Size:"<<s.m_size<<endl;
	s.pop();
	cout<<endl<<s.top()<<" Size:"<<s.m_size<<endl;
	s.pop();
	return 0;
}
*/
