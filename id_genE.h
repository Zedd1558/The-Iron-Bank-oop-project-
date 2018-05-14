#pragma once
class id_genE
{
	int id;
public:
	id_genE() { id = 1700410; }
	int get_id() { int i = id; id++; return i; }
	~id_genE();
};

