#include "Passageiro.h"
#include "Carro.h"
#include "Parque.h"
#include "Exibe.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <chrono>
#include <atomic>
#include <thread>
#include <cstdlib>
#define MAX_NUM_VOLTAS 4

std::atomic_flag Passageiro::lockControle = ATOMIC_FLAG_INIT;
std :: atomic <int>  Passageiro::Contador = ATOMIC_VAR_INIT (1);

int estagio[11] = {0};
int ultimo[11] = {0};

Passageiro::Passageiro(int id, Carro *c){
	this->id = id;
	this->carro = c;
}

Passageiro::~Passageiro(){

}

void Passageiro::entraNoCarro(){

    for(int j = 1; j <= 10; j++){
        estagio[id] = j;
        ultimo[j] = id;

        for(int k = 1; k <= 10; k++){
                if(k == id){ continue; }
                while( (estagio[k] >= estagio[id]) && (ultimo[j] == id) ){ }
                while(Carro::carroCheio) { }
        }
    }
    /*Seção Critica*/
    Exibe::MensagemThread(" entrou no carro", id);
    voltasPorThread[id]++;
    Carro::nPassageiros.fetch_add(1, std::memory_order_seq_cst);
    if(Carro::nPassageiros == 5){
        //Exibe::ExibeMensagemNum("\nO Carro esta cheio! O numero de passageiros eh ", Carro::nPassageiros);
        Carro::carroCheio = true;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));  //Delay de entrada
    estagio[id] = 0;
}

void Passageiro::esperaVoltaAcabar(){
    while (!Carro::voltaAcabou)
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void Passageiro::saiDoCarro(){
    Exibe::MensagemThread(" saiu do carro", id);
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); //Delay de saida
    Contador.fetch_add(1, std::memory_order_seq_cst);
    if(Contador == 6){
        Carro::nPassageiros.fetch_sub(5, std::memory_order_seq_cst);
        Exibe::ExibeMensagem("Carro vazio\n");
        if(Carro::nPassageiros == 0){
            Carro::carroCheio = false;
            Carro::voltaAcabou = false;
            Contador.fetch_sub(5, std::memory_order_seq_cst);
        }
    }
}

void Passageiro::passeiaPeloParque(){
    while(Carro::carroCheio) { }
    int x = (rand()%4)+1;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000*5));
	Exibe::MensagemThread(" esta passeando", id);
}

bool Passageiro::parqueFechado(){
	if(carro->getNVoltas() < MAX_NUM_VOLTAS-1){
            return false;
    }else
        return true;
}

void Passageiro::ApresentaRelatorio(){
    Exibe::Nvoltas(voltasPorThread[id], id);
    while (lockControle.test_and_set());
    Parque::numPessoas.fetch_sub(2, std::memory_order_seq_cst);
    lockControle.clear();
}

void Passageiro::run(){
	while (!parqueFechado()){

		entraNoCarro(); // protocolo de entrada

		esperaVoltaAcabar();

		saiDoCarro(); // protocolo de saida

		passeiaPeloParque(); // secao nao critica
	}

    ApresentaRelatorio();
}
