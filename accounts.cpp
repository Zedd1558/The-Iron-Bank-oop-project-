#pragma once 
#include "stdafx.h"
#include "accounts.h"
#include "id_genC.h"
#include "transaction.h"
#include<ctime>
#include<iostream>
#include<string>
#include<fstream>
using namespace std;
bool checkNumber22(string s)
{
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] < 48 || s[i]>57) return false;
	}
	return true;
}
int stooi22(string s)
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
accounts::accounts()
{
	//cout << " account generated...\n";
}

accounts::~accounts()
{
}

void accounts:: operator += (int n)
{
	amount += n;
	cout << "\n " << n << " Tk credited to a/c " << id << " .... " << endl;
	
}
int accounts:: operator -= (int n)
{
	if (amount < n) {
		cout << "\n not enough balance...\n";
		return 1;
	}
	amount -= n;
	cout << "\n " << n << " Tk debited from a/c " << id << " .... " << endl;
	return 0;
}
int accounts::transfer(int &r_id,int &amtt)
{
	int amt, out_id; 
	cout << "Enter the amount to be transferred : ";
	string samt;
	while (1) {
		cin>>samt;
		if (checkNumber22(samt)) break;
		else { cout << "\ninvalid input... Enter again... "; }
	}
	amt = stoi(samt);
	amtt = amt;
	if (amount<amt)
	{
		cout << "\n not enough balance... transfer failed...\n";
		return 1;
	}
	cout << "Enter the Reciever account no : ";
	//cin >> out_id; 
	string soutid;
	while (1) {
		cin >> soutid;
		if (checkNumber22(soutid)) break;
		else { cout << "\ninvalid input... Enter again... "; }
	}
	out_id = stoi(soutid);
	r_id = out_id;
	accounts Account2;
	fstream file2;
	file2.open("accounts.dat", ios::binary | ios::in | ios::out);
	if (!file2)
	{
		cout << " account File could not be open !! " << endl;
		return 1 ;
	}
	bool found = false;
	while (file2.read(reinterpret_cast<char *>(&Account2), sizeof Account2))
	{
		if (Account2.get_id() == out_id)
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
		return 1 ;
	}
	amount -= amt;
	Account2+=(amt);
	int pos = (-1)*static_cast<int>(sizeof(Account2));
	file2.seekp(pos, ios::cur);
	file2.write(reinterpret_cast<char *> (&Account2), sizeof(accounts));
	file2.close();
	return 0;
	
}