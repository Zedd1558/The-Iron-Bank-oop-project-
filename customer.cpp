#pragma once
#include "stdafx.h"
#include "customer.h"
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

customer::customer()
{
}
void customer::create_account(int c_id,int a_id)
{
	cout << endl << endl;
	cout << " New Account's Details \n";
	cout << "____________________________\n";
	id_genA idGenA(a_id);
	int idd = idGenA.get_id();
	//cout << " idgenA value " << idd << endl;
	ofstream outfile;
	outfile.open("idgenA.dat", ios::binary | ios::trunc | ios::out);
	outfile.write(reinterpret_cast<char *>(&idGenA), sizeof idGenA);
	outfile.close();
	cout << " Enter pin : ";
	int pin;
	cin >> pin;
	cout << " Enter intial deposit :";
	int amount;
	cin >> amount;
	//cout << " account " << idd << " " <<pin<<" " <<c_id << " " << amount << endl;
	accounts Account(idd, pin, c_id, amount);
	ofstream outfile1;
	outfile1.open("accounts.dat", ios::binary | ios::app | ios::out);
	outfile1.write(reinterpret_cast<char *>(&Account), sizeof Account);
	outfile1.close();
	cout << "\n New Account Added with ID = " << idd << endl;
	cout << ".........note down your ID...ID is needed to access the account.........\n\n";
	system("pause");
}
void customer::delete_account(int a_id)
{

	accounts Account2;
	fstream file2;
	file2.open("accounts.dat", ios::binary | ios::in );
	if (!file2)
	{
		cout << " account File could not be open !! " << endl;
		return;
	}
	bool found = false;
	while (file2.read(reinterpret_cast<char *>(&Account2), sizeof Account2))
	{
		if (Account2.get_id() == a_id)
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
	if (Account2.get_c_id() != id)
	{
		cout << "\n the account does not belong to you.... " << endl;
		system("pause");
		return;
	}

	string s;
	cout << " Are you sure you want to delete the account? : ";
	cin >> s;
	if( !(s == "yes" | s == "YES" | s == "y" | s == "Y") )
	{
		
		return;
	}
	file2.close();
	int n = a_id;
	accounts ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("accounts.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
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
	remove("accounts.dat");
	rename("Temp.dat", "accounts.dat");
	cout << "\n\tAccount deleted ..\n";
	system("pause");
	return;
}
void customer::access_account()
{
	//code to access and update account 
	cout << "_________________________________" << endl;
	cout << " Enter your Account no : ";
	int a_id;
	cin >> a_id;
	accounts Account;
	fstream file;
	file.open("accounts.dat", ios::binary | ios::in | ios::out);
	if (!file)
	{
		cout << " account File could not be open !! " << endl;
		return;
	}
	bool found = false;
	while (file.read(reinterpret_cast<char *>(&Account), sizeof Account))
	{
		if (Account.get_id() == a_id)
		{
			found = true;
			if (Account.get_c_id() != this->id)
			{
				cout << " the account doesn't belong to you !..." << endl;
				system("pause");
				return;
			}
			else {
				break;
			}
		}
	}
	if (found == false) {
		cout << " the account was not found " << endl;
		system("pause");
		return;
	}
	char password[30], c = ' ';
	cout << " Enter Pin(4-digit) : ";
	int i = 0;
	while (c != 13)
	{
		c = _getch();
		cout << "*";
		password[i] = c;
		i++;
	}
	password[i] = '\0';
	int pin_ = atoi(password);
	fflush(stdin);
	cin.clear();
	cout << endl;
	if (Account.get_pin() != pin_) {
		cout << " wrong pin number...access denied..." << endl;
		system("pause");
		return;
	}
	bool q = false;
	int pos;
	while (1) {
		system("cls");
		cout << "\n\n _______________________________\n";
		cout << " What do you want to do? == >\n";
		cout << " 1. Deposit Cash\n";
		cout << " 2. Withdraw Cash\n";
		cout << " 3. Transfer Money\n";
		cout << " 4. Back\n";
		cout << "\n == Enter a choice: \t";
		//cin>>flush;

		cin.clear();
		fflush(stdin);
		int amt1, amt2;
		int cc;
		cin >> cc;
		switch (cc) {
		case 1:
		{   
			cout << " Enter the amount to be deposited : ";
			cin >> amt1;
			Account.deposit(amt1);
			pos = (-1)*static_cast<int>(sizeof(Account));
			file.seekp(pos, ios::cur);
			file.write(reinterpret_cast<char *> (&Account), sizeof(accounts));
			cout << " Account Updated....." << endl;
			system("pause");
			break;
		}
		case 2:
		{	cout << " Enter the amount to be withdrawn : ";
			cin >> amt2;
			Account.withdraw(amt2);
			pos = (-1)*static_cast<int>(sizeof(Account));
			file.seekp(pos, ios::cur);
			file.write(reinterpret_cast<char *> (&Account), sizeof(accounts));
			cout << " Account Updated....." << endl;
			system("pause");
			break;
		}
		case 3:
		{	
			//cout << "transaction done!" << endl;
			Account.transfer();
			pos = (-1)*static_cast<int>(sizeof(Account));
			file.seekp(pos, ios::cur);
			file.write(reinterpret_cast<char *> (&Account), sizeof(accounts));
			cout << " Accounts Updated....." << endl;
			system("pause");
			break;
		}
		case 4:
			q = true;
			break;

		}
		if (q) {
			break;
		}
		

	}
	file.close();
}
customer::~customer()
{

}
