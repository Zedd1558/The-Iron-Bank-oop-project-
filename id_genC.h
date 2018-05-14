#pragma once
class id_genC
{
	int id;
public:
	id_genC() { id = 1600400; };
	id_genC(int id_) { id = id_; }
	int get_id() { int i = id; id++; return i; }
	
};

