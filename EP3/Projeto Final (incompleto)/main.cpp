#include "Consumidor.h"
#include "Produtor.h"
#include <vector>
#include <thread>
#include <stdio.h>
#include <iostream>

using namespace std;

int main()
{
    Produtor produtor;
    Consumidor *consumidor[5];

    thread tProdutor(&Produtor::start, &produtor);

    /*
    for (int i = 1; i <= 5; i++)
    {
    	consumidor[i] = new Consumidor(produtor);
    	//CHAMA O CONSTRUTOR DO CONSUMIDOR E CRIA 5 CONSUMIDORES
    }

    thread tProdutor(&Produtor::start, &produtor);
    //INICIA O PRODUTOR

    vector<thread> tConsumidor;
    for (auto &p : consumidor) tConsumidor.push_back(thread(&Consumidor::start, p));
    //INICIA OS CONSUMIDORES

    tProdutor.join();

    for(auto &th:tConsumidor) th.join();

    for(int i=1; i <=5; i++)
    {
        delete consumidor[i];
    }
    */
    return 0;
}
