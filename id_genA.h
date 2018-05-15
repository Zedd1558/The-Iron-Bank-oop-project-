#pragma once
class id_genA
{
	int id;
	
public:
	id_genA() { id = 1804100; }
	id_genA(int id_) { id = id_; }
	int get_id() { int i = id; id++; return i; }
	~id_genA();
};

