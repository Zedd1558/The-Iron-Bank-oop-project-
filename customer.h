#pragma once
#include<cstring>
class customer
{
	int id;
	int pin;
	char name[30];
	char phone[30];
public:
	customer();
	customer(int id_, int pin_, char name_[], char phone_[])
	{
		id = id_;
		pin = pin_;
		strcpy_s(name, sizeof name, name_);
		strcpy_s(phone, sizeof phone, phone_);
	}
	int get_id()
	{
		return id;
	}
	int  get_pin()
	{
		return pin;
	}
	char* get_name()
	{
		return name;
	}
	char* get_phone()
	{
		return phone;
	}
	void create_account(int c_id,int a_id);
	void delete_account(int a_id);
	void access_account();
	~customer();
};

