#pragma once

class accounts
{
	int id;
	int customer_id;
	int pin;
	int amount;
	
public:
	accounts();
	accounts(int id_, int pin_, int c_id, int amount_)
	{
		id = id_;
		customer_id = c_id;
		pin = pin_;
		amount = amount_;
	}
	int get_id() { return id; }
	int get_c_id() { return customer_id; }
	int get_pin() { return pin; }
	int get_amount() { return amount; }
	void operator += (int n);
	int operator -= (int n);
	int transfer(int &r_id,int &amtt);
	~accounts();
};

