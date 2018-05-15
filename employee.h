#pragma once
#include<iostream>
#include<string>
#include<cstring>
using namespace std;
class employee
{
protected:
	int id;
	int pin;
	char name[30];
	char phone[30];
public:
	employee();
	employee(int id_, int pin_ , char name_[], char phone_[])
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
	void create_customer(int c_id);
	void delete_customer(int c_id);
	void show_transaction();
	~employee();
};

