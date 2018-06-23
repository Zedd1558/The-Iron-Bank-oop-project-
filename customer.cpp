#pragma once
//_CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "customer.h"
#include "accounts.h"
#include"customer.h"
#include "transaction.h"
#include "admin.h"
#include<ctime>
#include "id_genC.h"
#include "id_genE.h"
#include "id_genA.h"
#include <cstdlib>
#include<conio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<Windows.h>
using namespace std;
void getTm(timet &timenow)
{
	time_t tt;
	time(&tt);
	tm TM;
	localtime_s(&TM,&tt);
	timenow.year = TM.tm_year + 1900;
	timenow.month = TM.tm_mon;
	timenow.day = TM.tm_mday;
	timenow.hour = TM.tm_hour;
	timenow.mins = TM.tm_min;
	timenow.secs = TM.tm_sec;
	timenow.weekDay = TM.tm_wday;
}
void loading1() {
	system("cls");
	cout << "\n\n...loading...\n________________\n\n\n\n";
	for (int i = 0; i<25; i++)
	{

		//cout << "\n" << "\n";

		cout << ">>";
		Sleep(50);
	}
	system("cls");
}
bool checkNumber11(string s)
{
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] < 48 || s[i]>57) return false;
	}
	return true;
}
int stooi11(string s)
{
	int id = 0;
	int h = 1;
	for (int i = (int)(s.size()) - 1; i >= 0; i--)
	{
		id += (s[i] * h);
		h *= 10;
	}
	return id;
}


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
	cout << " Enter pin(4-digit) : ";
	int pin; string spin;
	while (1) {
		cin >> spin;
		if (checkNumber11(spin)) break;
		else { cout << "\ninvalid input... Enter again... "; }
	}
	pin = stoi(spin);

	cout << " Enter intial deposit :";
	int amount; string samount;
	while (1) {
		cin >> samount;
		if (checkNumber11(samount)) break;
		else { cout << "\ninvalid input... Enter again... "; }
	}
	amount = stooi11(samount);
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
bool checkNumber(string s)
{
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] < 48 || s[i]>57) return false;
	}
	return true;
}
int stooi(string s)
{
	int id = 0;
	int h = 1;
	for (int i = (int)s.size() - 1; i >= 0; i--)
	{
		id += (s[i] * h);
		h *= 10;
	}
	return id;
}
void customer::access_account()
{
	//code to access and update account 
	cout << "_________________________________" << endl;
	cout << " Enter your Account no : ";
	int a_id;
	//cin >> a_id;
	int id_;
	string sid_;
	char password[30], c = ' ';
	//cout << " _____________________________\n";
	while (1)
	{
		//cout << " Enter ID : ";
		cin >> sid_;
		if (checkNumber(sid_))break;
		else { cout << "\ninvalid input... Enter again... : "; }
	}
	id_ = stoi(sid_);
	a_id = id_;
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
		cout << " the account was not found ..." << endl;
		system("pause");
		return;
	}
//	char password[30], c = ' ';
	cout << " Enter Pin(4-digit) : ";
	int i = 0;
	while (c != 13)
	{
		c = _getch();
		cout << "*";
		password[i] = c;
		i++;
		if (i > 3)break;
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
	loading1();
	bool q = false;
	int pos;
	while (1) {
		system("cls");
		cout << "\n\n _______________________________\n";
		cout << " What do you want to do? == >\n";
		cout << " 1. Deposit Cash\n";
		cout << " 2. Withdraw Cash\n";
		cout << " 3. Transfer Money\n";
		cout << " 4. Transaction Report\n";
		cout << " 5. Back\n";
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
			
			int iid_;
			string sid_;
			
			while (1)
			{
				
				cin >> sid_;
				if (checkNumber(sid_))break;
				else { cout << "\ninvalid input... Enter again... :"; }
			}
			iid_ = stoi(sid_);
			amt1 = iid_;
			Account+=(amt1);
			//depositing
			transaction t;
			timet timenow;
			getTm(timenow);
			char a[] = "deposit";
			t.set(a_id, -1, amt1, a, timenow);
			t.show();
			pos = (-1)*static_cast<int>(sizeof(Account));
			file.seekp(pos, ios::cur);
			file.write(reinterpret_cast<char *> (&Account), sizeof(accounts));
			cout << " Account Updated....." << endl;
			system("pause");
			break;
		}
		case 2:
		{	cout << " Enter the amount to be withdrawn : ";

			string samt2;
			
			while (1)
			{
				cin >> samt2;
				if (checkNumber(samt2))break;
				else { cout << "\ninvalid input... Enter again... :"; }
			}
			amt2 = stoi(samt2);
			bool kflag = Account-=(amt2);
			transaction ttt;
			timet timenow2;
			getTm(timenow2);
			char aaa[] = "withdraw";
			ttt.set(a_id, -1, amt2, aaa, timenow2);
			//cout << "ok";
			ttt.show();
			pos = (-1)*static_cast<int>(sizeof(Account));
			file.seekp(pos, ios::cur);
			file.write(reinterpret_cast<char *> (&Account), sizeof(accounts));
			if( !kflag)cout << " Account Updated....." << endl;
			system("pause");
			break;
		}
		case 3:
		{	
			//cout << "transaction done!" << endl;
			int r_id, amtt;
			int gflag = Account.transfer(r_id,amtt);
			if (!gflag)
			{
				transaction tttt;
				timet timenow22;
				getTm(timenow22);
				char aaaa[] = "transfer";
				tttt.set(a_id, r_id, amtt, aaaa, timenow22);
				tttt.show();
				
			}
			pos = (-1)*static_cast<int>(sizeof(Account));
			file.seekp(pos, ios::cur);
			file.write(reinterpret_cast<char *> (&Account), sizeof(accounts));
			if(!gflag) cout << " Accounts Updated....." << endl;
			system("pause");
			break;
		}
		case 4:
		{
			cout << "\nTransactions for this Account\n";
			cout << "=============================";
			fstream infile0;
			infile0.open("transactions.dat", ios::binary | ios::in | ios::app);
			transaction Trans;
			while (infile0.read(reinterpret_cast<char *>(&Trans), sizeof Trans))
			{

				if (Trans.getid1() == a_id || Trans.getid2() == a_id)Trans.show();

			}
			infile0.close();
			cout << endl << endl;
			system("pause");
		}
			break;
		case 5:
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
