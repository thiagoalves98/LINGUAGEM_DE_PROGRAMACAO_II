#include "Parque.h"
#include "Passageiro.h"

std ::atomic <int> Parque::numPessoas = ATOMIC_VAR_INIT (10);

Parque::Parque(){

}

Parque::~Parque(){

}

void Parque::addPassageiro(Passageiro *p){
	passageiros.push_back(p);
}

vector<Passageiro*>& Parque::getPassageiros(){
	return passageiros;
}
