#include "Exibe.h"
#include "Passageiro.h"
#include "Carro.h"
#include "Parque.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <chrono>
#include <atomic>
#include <thread>
#include <cstdlib>

std::atomic_flag Exibe::lockPrint = ATOMIC_FLAG_INIT;

Exibe::Exibe()
{
    //ctor
}

Exibe::~Exibe()
{
    //dtor
}

void Exibe::ExibeMensagem(const char *s){
    while (lockPrint.test_and_set());
    cout<< s <<endl;
    lockPrint.clear();
}

void Exibe::ExibeMensagemNum(const char *s, int num){
    while (lockPrint.test_and_set());
    cout<< s << num <<endl;
    lockPrint.clear();
}

void Exibe::MensagemThread(const char *s, int num){
    while (lockPrint.test_and_set());
    cout<<"A thread " << num << s <<endl;
    lockPrint.clear();
}

void Exibe::Nvoltas(int num, int id){
    while (lockPrint.test_and_set());
    cout<<"O numero de voltas dadas pela Thread "<< id <<" foi "<< num <<endl;
    lockPrint.clear();
}

