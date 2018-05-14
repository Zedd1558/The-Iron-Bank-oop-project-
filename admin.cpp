#pragma once
#include "stdafx.h"
#include "employee.h"
#include "accounts.h"
#include"customer.h"
#include "admin.h"
#include "id_genC.h"
#include "id_genE.h"
#include "id_genA.h"
#include <cstdlib>
#include<conio.h>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void admin::create_admin(int a_id)
{
	char name[30];
	cout << endl << endl;
	cout << " New Admin's Details \n";
	cout << "____________________________\n";
	cout << " Enter name : ";
	cin >> name;
	int idd = a_id;
	id_genE idGenE(idd);
	idd = idGenE.get_id();
	ofstream outfile;
	outfile.open("idgenE.dat", ios::binary | ios::trunc | ios::out);
	outfile.write(reinterpret_cast<char *>(&idGenE), sizeof idGenE);
	outfile.close();
	cout << " Enter pin : ";
	int pin;
	cin >> pin;
	cout << " Enter phone number : ";
	char phone[30];
	cin >> phone;
	admin Admin(idd, pin, name, phone);
	ofstream outfile1;
	outfile1.open("admin.dat", ios::binary | ios::app | ios::out);
	outfile1.write(reinterpret_cast<char *>(&Admin), sizeof Admin);
	outfile1.close();
	cout << "\n New Admin Added with ID = " << idd << endl;
	cout << ".........note down the ID...ID is needed to access the account.........\n\n";
	system("pause");
}

void admin::create_employee(int e_id)
{
	char name[30];
	cout << endl << endl;
	cout << " New Employee's Details \n";
	cout << "____________________________\n";
	cout << " Enter name : ";
	cin >> name;
	int idd = e_id;
	id_genE idGenE(idd);
	idd = idGenE.get_id();
	ofstream outfile;
	outfile.open("idgenE.dat", ios::binary | ios::trunc | ios::out);
	outfile.write(reinterpret_cast<char *>(&idGenE), sizeof idGenE);
	outfile.close();
	cout << " Enter pin : ";
	int pin;
	cin >> pin;
	cout << " Enter phone number : ";
	char phone[30];
	cin >> phone;
	employee Employee(idd, pin, name, phone);
	ofstream outfile1;
	outfile1.open("employee.dat", ios::binary | ios::app | ios::out);
	outfile1.write(reinterpret_cast<char *>(&Employee), sizeof Employee);
	outfile1.close();
	cout << "\n New Employee Added with ID = " << idd << endl;
	cout << ".........note down the ID...ID is needed to access the account.........\n\n";
	system("pause");
}
void admin::delete_employee(int e_id)
{
	employee Employee;
	fstream file2;
	file2.open("employee.dat", ios::binary | ios::in);
	if (!file2)
	{
		cout << " Employee File could not be open !! " << endl;
		return;
	}
	bool found = false;
	while (file2.read(reinterpret_cast<char *>(&Employee), sizeof Employee))
	{
		if (Employee.get_id() == e_id)
		{
			{
				found = true;
				break;
			}
		}
	}
	if (found == false) {
		cout << "\n the account does not exist ...." << endl;
		system("pause");
		return;
	}
	string s;
	cout << " Are you sure you want to delete the Employee? : ";
	cin >> s;
	if (!(s == "yes" | s == "YES" | s == "y" | s == "Y"))
	{

		return;
	}
	file2.close();
	int n = e_id;
	employee ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("employee.dat", ios::binary);
	if (!inFile)
	{
		cout << "Employee file could not be open !! ....";
		return;
	}
	outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(accounts)))
	{
		if (ac.get_id() != n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(accounts));
		}
	}
	inFile.close();
	outFile.close();
	remove("employee.dat");
	rename("Temp.dat", "employee.dat");
	cout << "\n\tEmployee deleted ..\n";
	system("pause");
	return;
}
admin::admin()
{
}
admin::~admin()
{
}
