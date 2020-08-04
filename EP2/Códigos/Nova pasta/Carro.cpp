#include "Carro.h"
#include "Parque.h"
#include "Exibe.h"
#include <chrono>
#include <random>
#include <thread>
#include <iostream>
#include <stdio.h>

const int Carro::CAPACIDADE = 5;

std::atomic <int>  Carro::nPassageiros = ATOMIC_VAR_INIT (0);
std::atomic <bool> Carro::voltaAcabou = ATOMIC_FLAG_INIT;
std::atomic <bool> Carro::carroCheio = ATOMIC_FLAG_INIT;
std::atomic_flag Carro::lockCarro = ATOMIC_FLAG_INIT;

Carro::Carro(){
	this->voltas = 0;
}

Carro::~Carro(){

}

void Carro::esperaEncher(){
	while(!Carro::carroCheio){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void Carro::daUmaVolta(){
    voltaAcabou=false;
	Exibe::ExibeMensagemNum("\nCarro esta dando a volta de numero ", voltas+1);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    while(lockCarro.test_and_set());
        voltaAcabou = true;
    lockCarro.clear();
}

void Carro::esperaEsvaziar(){
	//Exibe::ExibeMensagem("\nEsperando esvaziar");
	while (Carro::carroCheio){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int Carro::getNVoltas(){
	return voltas;
}

void Carro::run(){
	while(Parque::numPessoas > 0){
		esperaEncher();

		daUmaVolta();

		esperaEsvaziar();

        voltas++;

	}
}
