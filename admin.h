#pragma once
#include "employee.h"
#include<cstring>
class admin :
	public employee
{
public:
	admin();
	admin(int id_, int pin_, char name_[], char phone_[])
	{
		id = id_;
		pin = pin_;
		strcpy_s(name, sizeof name,name_);
		strcpy_s(phone, sizeof phone,phone_);
	}
	void create_employee(int e_id);
	void delete_employee(int e_id);
	void create_admin(int e_id);
	//from base class employee
	//create customer
	//del customer
	//show transaction
	~admin();
};

