/* Copyright (c) nkaredia */

#include<iostream>
class ISBNPrefix
{
	FILE* fp;
	ISBNPrefix(const ISBNPrefix& source);
	ISBNPrefix& operator=(const ISBNPrefix& source);
public:
	ISBNPrefix(const char*);  
	bool isRegistered(int) const; 
	int minNoDigits(int) const; 
	bool isRegistered(int,const char*) const;
	~ISBNPrefix();
};
