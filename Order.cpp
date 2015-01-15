/* Copyright (c) nkaredia */

#include<iostream>
#include<string.h>
#include <iomanip>
#include "Order.h"
using namespace std;

/* Constructor*/
Order::Order()
{
	orderisbn=ISBN();
	orderedCopies=0;
	deliveredCopies=0;
	clientname[0] = '\0';
}

/* One argument constructor that stores Order elements if isbn is registered*/
Order::Order(const ISBN& isbn)
{
	if(isbn.isRegistered())
	{
		orderisbn=isbn;
		orderedCopies=0;
		deliveredCopies=0;
		clientname[0] = '\0';
	}
	else
		*this=Order();
}

/* Two Argument constructor that store clientname if string is no NULL*/
Order::Order(const ISBN& isbn,const char* nm)
{
	if(nm != NULL)
	{
		orderisbn = isbn;	
		orderedCopies = 0;
		deliveredCopies = 0;
		strcpy(clientname,nm);
	}
}

/*Copy Constructor*/
Order::Order(const Order& source)
{
	orderisbn = source.orderisbn;
	orderedCopies=source.orderedCopies;
	deliveredCopies=source.deliveredCopies;
	strcpy(clientname, source.clientname);
	*this = source;
}

/* One Argument constructor that checks two isbn of two objects
 * and returns true if both objects isbn are same otherwise false
 */
bool Order::has(const ISBN& isbn) const
{
	if(orderisbn == isbn)
		return true;
	else
		return false;
}

/* Returns clientname*/
void Order::name(char* str) const
{
	strcpy(str,clientname);
}

/* Returns Number of copies that are ordered*/
int Order::outstanding() const
{
	return orderedCopies;
}

/* Accepts clientname from the user and store it*/
bool Order::client(istream& is)
{
	bool ok=false;
	cout<<"Name (0 to quit) : ";

	is.getline(clientname,101);
	if(strcmp(clientname,"0")!=0)
	{
		ok = true;
	}
	return ok;
}

/* Accepts Quantity for the isbn ordered
 * and update the data for number of isbn ordered
 */
bool Order::add(istream& is)
{
	int quantity;
	bool ok=true;        
		cout<<"Quantity (0 to Quit) : ";
		is >>quantity;
		if(quantity == 0)
		{
			ok = false;
			cout<<"**No delivery recorder!\n";
		}
		while (!(add(quantity)))
		{
			cout << "Enter a positive number.  Try again.\n";
			cout << "Quantity (0 to Quit) : ";
			is >> quantity;
			if (quantity == 0)
			{
				ok = false;
				cout << "**No delivery recorder!\n";
			}
		}
return ok;
}

/* returns true if argument is 
 * greater then zero and
 * update number of isbn ordered
 */
bool Order::add(int n)
{
	if(n > 0 && orderisbn.isRegistered())
	{
		orderedCopies+=n;
		return true;
	}
	else
		return false;
}

/* Accepts the quantity of isbn that is to be delivered*/
bool Order::receive(istream& is)
{
	int quantity=0;
	bool ok=false;
	do
	{
		cout<<"Quantity (0 to quit) : ";
		is>>quantity;
		if(quantity == 0)
			ok = true;
		else if(quantity > orderedCopies)
		{
			cout<<quantity<<" not on order.  Only "<<orderedCopies<<" are on order.  Try again.\n";	
		}
		else
		{
			deliveredCopies+=quantity;
			ok=true;
		}
	}while(!ok);

	return ok;
}

/* Displays formated style of orederedcopies and deliveredcopies*/
void Order::display(ostream& os) const
{
	os << orderisbn <<setw(9)<<orderedCopies<<setw(11)<<deliveredCopies<<" "<<setw(25)<<left<<clientname;
}

/* Destructor*/
Order::~Order()
{
	orderisbn=ISBN();
	orderedCopies=0;
	deliveredCopies=0;
	clientname[0] = '\0';
}

/* Assignment operator that copies data in curret object*/
Order& Order::operator=(const Order& source)
{
	if(this!=&source)
	{
		orderisbn = source.orderisbn;
		orderedCopies = source.orderedCopies;
		deliveredCopies = source.deliveredCopies;
		strcpy(clientname,source.clientname);
	}
	return *this;
}

/* Output operator that display data in formated style*/
ostream& operator<<(ostream& os, const Order& order)
{
	order.display(os);
	return os;
}
