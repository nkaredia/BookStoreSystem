#include<iostream>
#include"SpecialOrder.h"
#include<string>
#include<cstdlib>
#include<iomanip>
#include<cstring>
#include<cstdio>

using namespace std;

/*constructor*/
SpecialOrder::SpecialOrder()
{
	specialinstructions = NULL;
}

/*two argument constructor with calling base class constructor to store isbn string*/
SpecialOrder::SpecialOrder(const ISBN& isbn, const char* instr) :Order(isbn)
{
	if (instr != NULL)
	{
		specialinstructions = new char[strlen(instr) + 1];
		strcpy(specialinstructions, instr);
	}
}

/*copy constructor*/
SpecialOrder::SpecialOrder(const SpecialOrder& obj) :Order(obj)
{

	if (obj.specialinstructions != NULL)
	{
		specialinstructions = new char[strlen(obj.specialinstructions) + 1];
		strcpy(specialinstructions, obj.specialinstructions);
	}
}

/*Recieves instruction from user*/
bool SpecialOrder::add(istream& is)
{
	string s;
	bool returnvalue = false;
	if (Order::add(is)==true)
	{
		cout << "Instruction  : ";
		is.ignore();
		getline(is, s);
		if (specialinstructions != NULL) delete []specialinstructions;
		specialinstructions = new char[s.length() + 1];
		strcpy(specialinstructions, s.c_str());
		returnvalue = true;
	}
	return returnvalue;
}

/*displays order in formatted style*/
void SpecialOrder::display(ostream& os) const
{
	Order::display(os);
	os <<setw(25)<< specialinstructions;
}

/*Assignment operator*/
SpecialOrder& SpecialOrder::operator=(const SpecialOrder& obj)
{
	if (this != &obj)
	{
		Order::operator=(obj);
		specialinstructions = new char[strlen(obj.specialinstructions) + 1];
		strcpy(specialinstructions, obj.specialinstructions);
	}
	return *this;
}

/*destructor*/
SpecialOrder::~SpecialOrder()
{
	if (specialinstructions!=NULL)
		delete []specialinstructions;
}