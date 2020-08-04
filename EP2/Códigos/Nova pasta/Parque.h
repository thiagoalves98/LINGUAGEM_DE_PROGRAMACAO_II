#ifndef PARQUE_H
#define PARQUE_H
#include <vector>
#include <atomic>

using namespace std;

class Passageiro;

class Parque{

public:

	static std::atomic<int> numPessoas;
	Parque();
	virtual ~Parque();
	void addPassageiro(Passageiro *p);
	std::vector<Passageiro*>& getPassageiros();

private:
	std::vector<Passageiro*> passageiros;
};


#endif // PARQUE_H
