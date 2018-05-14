#pragma once
class id_genA
{
	int id;
	
public:
	id_genA() { id = 18004100; }
	int get_id() { int i = id; id++; return i; }
	~id_genA();
};

