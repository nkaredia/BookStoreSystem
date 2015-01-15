/* Copyright (c) nkaredia */

#include<iostream>
using namespace std;
class ISBNPrefix;

class ISBN
{
	char isbn[11];
	char area[6];
	char publisher[8];
	char title[7];
	bool registeredisbn;
	bool isRegistered(const ISBNPrefix&);
public:
	ISBN();
	ISBN(const char*, const ISBNPrefix&);
	void display(ostream& os) const;
	void toStr(char*) const;
	void gettempisbn(char*) const;   //  gets temporary isbn if needed
	void toStrWithStyle(char*) const;
	bool empty() const;
	bool isRegistered() const;
	bool read(istream&, const ISBNPrefix&);	

};
ostream& operator<<(ostream& os, const ISBN& isbn);
bool operator==(const ISBN& left, const ISBN& right);
int isValid(const char str[]);