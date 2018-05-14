#pragma once
class id_genC
{
	int id;
public:
	id_genC() { id = 1600400; };
	int get_id() { int i = id; id++; return i; }
	
};

