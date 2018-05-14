#pragma once 
#include "stdafx.h"
#include "accounts.h"
#include "id_genC.h"
#include<iostream>
#include<fstream>
using namespace std;

accounts::accounts()
{
	//cout << " account generated...\n";
}

accounts::~accounts()
{
}

void accounts::deposit(int n)
{
	amount += n;
	cout << "\n " << n << " Tk credited to a/c " << id << " .... " << endl;
}
int accounts::withdraw(int n)
{
	if (amount < n) {
		cout << "\n not enough balance...\n";
		return 1;
	}
	amount -= n;
	cout << "\n " << n << " Tk debited from a/c " << id << " .... " << endl;
	return 0;
}
void accounts::transfer()
{
	int amt, out_id;
	cout << "Enter the amount to be transferred : ";
	cin >> amt;
	if (amount<amt)
	{
		cout << "\n not enough balance... transfer failed...\n";
		return;
	}
	cout << "Enter the Reciever account no : ";
	cin >> out_id;
	accounts Account2;
	fstream file2;
	file2.open("accounts.dat", ios::binary | ios::in | ios::out);
	if (!file2)
	{
		cout << " account File could not be open !! " << endl;
		return;
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
		return;
	}
	amount -= amt;
	Account2.deposit(amt);
	int pos = (-1)*static_cast<int>(sizeof(Account2));
	file2.seekp(pos, ios::cur);
	file2.write(reinterpret_cast<char *> (&Account2), sizeof(accounts));
	file2.close();
	return;
	
}