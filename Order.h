/* Copyright (c) nkaredia   */


#include "ISBN.h"
class Order
{
	char clientname[101];
	ISBN orderisbn;
	int orderedCopies, deliveredCopies;
	
public:
	Order();//
	Order(const ISBN&);//
	Order(const ISBN&,const char*);
	Order(const Order&);
	bool has(const ISBN&) const;//
	void name(char* str) const;
	bool client(istream&);
	int outstanding() const;
	virtual bool add(istream&);
	bool add(int);
	bool receive(istream& is);
	virtual void display(ostream&) const;
	Order& operator=(const Order&);
	~Order();
};

ostream& operator<<(ostream& os, const Order& order); 