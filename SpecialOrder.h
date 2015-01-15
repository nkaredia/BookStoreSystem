#include"Order.h"
#include<iostream>

class SpecialOrder :public Order
{
	char* specialinstructions;
public:
	SpecialOrder();
	SpecialOrder(const ISBN&, const char*);
	SpecialOrder(const SpecialOrder&);
	bool add(istream&);
	void display(ostream&) const;
	SpecialOrder& operator=(const SpecialOrder&);
	~SpecialOrder();
};