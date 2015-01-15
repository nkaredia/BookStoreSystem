// copyright (c) nkaredia
#include<iostream>
#include<cstdlib>
using namespace std;
#include "ISBNPrefix.h"
#include <cstdio>
#include <cstring>

/* A one argument constructor that receives filename and
 * opens the file if not NULL
 */
ISBNPrefix::ISBNPrefix(const char filename[])
{
	if (filename == NULL)
	    fp = NULL;
	else
		fp = fopen(filename,"r");
}

/* A one argument constructor that receives an object and copy it.*/
ISBNPrefix::ISBNPrefix(const ISBNPrefix& source)
{
	fp = source.fp;
}

/* A member fuction that receives area and return true if area is
 * found in the file else false
 */
bool ISBNPrefix::isRegistered(int area) const
{     
	bool returnvalue=false;
	if(fp != NULL)
	{
		rewind(fp); 
		int ar,pub1,pub2;		
		if(area >= 0)
		{
			while(fscanf(fp,"%d%d%d",&ar,&pub1,&pub2) != EOF && returnvalue == false)
			{     //this function returns true if area is found in while loop
				if(ar == area)
					returnvalue = true;  
			}
		}
	}
return returnvalue;
}

/*A member function that receives area and finds the minminum number of digits
 * and returns it
 */
int ISBNPrefix::minNoDigits(int area) const
{
	int minimumnoofdigits = 0;
	if(fp!=NULL)
	{
		rewind(fp);
		
		char ar[7],pub1[10],pub2[10];
		while(fscanf(fp,"%s%s%s",ar,pub1,pub2) != EOF && minimumnoofdigits == 0)
		{
			if(area == atoi(ar))
			{
				minimumnoofdigits=strlen(pub1);
			}
		}
		
	}
	return minimumnoofdigits;
}

/* A member fuction that receives two argument and returns true if
 * publisher prefix is found in the file otherwise false
 */
bool ISBNPrefix::isRegistered(int area, const char* publisher) const
{
	bool returnvalue = false;  
	if(fp!=NULL)
	{
		rewind(fp);
		int publish = atoi(publisher); //converting the whole string to integer  
	 
		char ar[6],pub1[8],pub2[8];
		while(fscanf(fp,"%s%s%s", ar,pub1,pub2) != EOF && returnvalue == false)
		{   	 
			if (strlen(pub1) == strlen(publisher) && atoi(ar) == area && publish>=atoi(pub1) && publish<=atoi(pub2))
		 	{   
				returnvalue = true;			  
		    }		
	    }
	}
		return returnvalue;	
}

/*Assinment operator*/
ISBNPrefix& ISBNPrefix::operator=(const ISBNPrefix& source)
{
	if(this != &source)
	{
		if(fp != NULL)
			this->fp = source.fp;
	}
	return *this;
}

/* No argument destructor that close the file */
ISBNPrefix::~ISBNPrefix()
{
	fclose(fp);
}
