#pragma once
#include<cstring>
#include<iostream>
#include<fstream>
using namespace std;
struct timet {
	int year, month, day, mins, secs, hour, weekDay;
};
class transaction
{
	int id1;
	int id2;
	int amount;
	char type[30];
	struct timet t;
public:
	transaction() {
		id1 = -1; id2 = -1; amount = 0; 
	}
	void set(int id1_, int id2_, int amount_,char* type_,timet t_)
	{
		id1 = id1_;
		id2 = id2_;
		amount = amount_;
		strcpy_s(type, sizeof type,type_);
		t = t_;

		//file storage
		ofstream outfile1;
		outfile1.open("transactions.dat", ios::binary | ios::app | ios::out);
		outfile1.write(reinterpret_cast<char *>(this), sizeof *this);
		outfile1.close();
     }
	int  getid1() { return id1; }
	int  getid2() { return id2; }
	int getamount() { return amount; }
	const char* gettype() { return type; }
	timet gettime() { return t; }
	void show() {
		//cout << id1 << " ";
		//cout << id2 << " ";
		cout << endl ;
		cout << "Transaction details : " << endl;
		cout << "----------------------" << endl;
		cout << "amount : ";
		cout << amount << endl;
		cout<<"transcation type: " <<type << endl;
		if (id2 != -1) { cout << "receiver: " << id2 << endl; }
	    cout<<"date: "<< t.year << " " << t.month << " " << t.day << " | time: " << t.hour << ":" << t.mins << ":" << t.secs << endl;
		cout << endl ;
	}
	~transaction() {};
};

