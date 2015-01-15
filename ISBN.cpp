// Copyright (c) nkaredia 
#include<iostream>
#include<cstdlib>
using namespace std;
#include "ISBN.h"
#include "ISBNPrefix.h"
#include <cstring>
#include <cstdio>

/* Constructor*/
ISBN::ISBN()
{
	registeredisbn = false;
	area[0]='\0';
	isbn[0] = '\0';
	publisher[0]='\0';
	title[0]='\0';
}

/* A two argument constructor that stores data*/
ISBN::ISBN(const char* str, const ISBNPrefix& list)
{
	
	if(isValid(str) == 1 && str != NULL)
	{	
		strcpy(isbn, str);
		registeredisbn=isRegistered(list);
	}
	else
	{
		*this = ISBN();
	}
}

/* one argument member fuction that decodes each isbn element is isbn is valid and registered*/
bool  ISBN::isRegistered(const ISBNPrefix& list)
{
	int i=0,j=0,k=0;
	bool returnvalue=false,validarea=false,validpublisher=false;
	int ar,arealength = 0,lenareapub=0; //int area,length of the area, length of area and publisher;
	while(i < 5 && validarea == false)
	{
	   area[i]=isbn[i];  //while 1st loop,setting 1st element of str[0] to area[0]
	   area[i+1]='\0';  //setting null character
	   ar = atoi(area);
	   if (list.isRegistered(ar) != 0)  //if func return true area then
	   {                              //the valid variables will be set true
		   validarea=true;            //if not it will agian loop and 2nd element of str[1]
		   returnvalue = true;        //will be set in area[1]...and loop will continue 
	   }							  //till func returns true and while conditions.....
	   i++;
	}

	if(validarea != false)		//if area is not valid no need to find publisher and title
	{
		arealength=strlen(area);
		while(j<7 && validpublisher == false)  //this while loop works same as above
		{
			publisher[j]=isbn[j+arealength];    // setting 1st element of publisher from str
			publisher[j+1]='\0';			   // the 1st str element of publisher is achieved from 
			if(list.isRegistered(ar,publisher) != 0)//length of area ie.arealength
			{
				validpublisher = true;
				returnvalue = true;
			}
			else 
				returnvalue = false;
			j++;
		}
	}
	if(validpublisher != false)		//getting title if area and publisher are true 
	{
		lenareapub=strlen(area)+strlen(publisher);//getting length of both area publisher to get title
		while(k < 9-lenareapub)		//totallength of ISBN without check digit - length of area and pub	
		{                           //will be the title...
			title[k]=isbn[k+lenareapub];  
			k++;
		}
		title[k]='\0';
	}
	if(validarea == false || validpublisher == false)
		registeredisbn = false;
	return returnvalue;
}

/* Member function which returns true if isbn is registered*/
bool ISBN::isRegistered() const
{
	if(registeredisbn)
		return true;
	else
		return false;
}

/* One argument member function that copies isbn string into it*/
void  ISBN::toStr(char* str) const
{
		strcpy(str,isbn);//return concatenated version of isbn;
}


/* One argument member function which stores formated isbn string if registered*/
void  ISBN::toStrWithStyle(char* str) const
{
	if(registeredisbn == true)
	{
		sprintf(str,"%s-%s-%s-%c",area,publisher,title,isbn[9]);
	}		// using sprintf() styling isbn with dash
	else
		toStr(str);
}


/* Member function that returns empty state of object*/
bool ISBN::empty() const
{

	if (isbn[0] == '\0' && area[0]=='\0' && publisher[0]=='\0' && title[0]=='\0') 
		return true;
	else
		return false;
}

/* Member function that format style to be displayed*/
void  ISBN::display(ostream& os) const
{
	char str[14];
	toStrWithStyle(str);
	os.width(13);
 	os.setf(ios::right);
	os << str;
}
/* Member function that read data from the user*/
bool ISBN::read(istream& is, const ISBNPrefix& list)
{
	char isb[11];
	bool loop = false;
	while(loop == false)
	{
		cout << "ISBN (0 to quit) :";
		is.getline(isb, 11);
		if(strcmp(isb,"0")==0)
			loop = true;
		else if(strlen(isb) < 10) 
		{
			cerr << " Too few characters. Try again" << endl;
			is.ignore(2000, '\n');
		}
		else if(isValid(isb) == 1)
		{
			strcpy(isbn,isb);
			registeredisbn = isRegistered(list);
			loop = true;
		}
		else if(isValid(isb) == 0) 
		{
			cerr << " Invalid check digit. Try again." << endl;
			is.ignore(2000, '\n');
		}
	} 
	if((strcmp(isb,"0") == 0))
		return false;
	else
		return loop;
}

/* A friend operator which receives two objects and
 * compare the string of isbn of two objects
 * and returns true if both are same otherwise false
 */
bool operator==(const ISBN& left, const ISBN& right)
{
	bool returnvalue = false;
	char isbn1[11],isbn2[11];
	left.toStr(isbn1);
	right.toStr(isbn2);
	if(strcmp(isbn1 ,isbn2) == 0)
		returnvalue = true;
	return returnvalue;
}


ostream& operator<<(ostream& os, const ISBN& isbn)
{
	isbn.display(os);
	return os;
}

/* a Global function that receives a whole string 
 * and checks if the isbn is valid and return 1
 * otherwise 0(zero)
 */
int isValid(const char str[])
{
		int convertIsbn[10],i,mul[10],sum=0,mod;
    	for(i=0;i<9;i++)
    	{
        	convertIsbn[i] = str[i] -'0';  //converting value from char to int
        	mul[i] = (i+1) * convertIsbn[i];//multiplying values accordingly ie.1*element[0],2*element[1].....
        	sum+=mul[i];
    	}
		mod = sum%11;
		if(str[9] == 'X')
			convertIsbn[9] = 10;
		else
			convertIsbn[9] = str[9] - '0';
		if(mod == convertIsbn[9])
			return 1;
		else
			return 0;
}
