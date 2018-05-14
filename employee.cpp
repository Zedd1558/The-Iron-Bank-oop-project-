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

employee::employee()
{

}
employee::~employee()
{
}
void employee::create_customer(int c_id)
{
	char name[30];
	cout << endl << endl;
	cout << " New Customer's Details \n";
	cout << "____________________________\n";
	cout << " Enter name : ";
	cin >> name;
	int idd = c_id;
	id_genC idGenC(idd);
	idd = idGenC.get_id();
	ofstream outfile;
	outfile.open("idgenC.dat", ios::binary | ios::trunc | ios::out);
	outfile.write(reinterpret_cast<char *>(&idGenC), sizeof idGenC);
	outfile.close();
	cout << " Enter pin : ";
	int pin;
	cin >> pin;
	cout << " Enter phone number : ";
	char phone[30];
	cin >> phone;
	customer Customer(idd, pin, name, phone);
	ofstream outfile1;
	outfile1.open("customer.dat", ios::binary | ios::app | ios::out);
	outfile1.write(reinterpret_cast<char *>(&Customer), sizeof Customer);
	outfile1.close();
	cout << "\n New Customer Added with ID = " << idd << endl;
	cout << ".........note down your ID...ID is needed to access the account.........\n\n";
	system("pause");
}
void employee::delete_customer(int c_id) 
{
	//delete customer and all the accounts he has
	customer Customer;
	fstream file2;
	file2.open("customer.dat", ios::binary | ios::in);
	if (!file2)
	{
		cout << " customer File could not be open !! " << endl;
		return;
	}
	bool found = false;
	while (file2.read(reinterpret_cast<char *>(&Customer), sizeof( customer)))
	{
		if (Customer.get_id() == c_id)
		{
			{
				found = true;
				break;
			}
		}
	}
	if (found == false) {
		cout << "\n the customer does not exist ...." << endl;
		system("pause");
		return;
	}
	string s;
	cout << " Are you sure you want to delete the account? : ";
	cin >> s;
	if (!(s == "yes" | s == "YES" | s == "y" | s == "Y"))
	{

		return;
	}
	file2.close();
	int n = c_id;
	customer ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("customer.dat", ios::binary);
	if (!inFile)
	{
		cout << " File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(customer)))
	{
		if (ac.get_id() != n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(customer));
		}
	}
	inFile.close();
	outFile.close();
	remove("customer.dat");
	rename("Temp.dat", "customer.dat");

	accounts acc;
	ifstream inFile2;
	ofstream outFile2;
	inFile2.open("accounts.dat", ios::binary);
	if (!inFile2)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	outFile2.open("Temp.dat", ios::binary);
	inFile2.seekg(0, ios::beg);
	while (inFile2.read(reinterpret_cast<char *> (&acc), sizeof(accounts)))
	{
		if (acc.get_c_id() != n)
		{
			outFile2.write(reinterpret_cast<char *> (&acc), sizeof(accounts));
		}
	}
	inFile2.close();
	outFile2.close();
	remove("accounts.dat");
	rename("Temp.dat", "accounts.dat");

	cout << "\n\tCustomer and his Accounts deleted ..\n";
	system("pause");
	return;
}
void employee::show_transaction()
{
	//make a transaction record file 
}