#ifndef CONSUMIDOR_H
#define CONSUMIDOR_H
#include "Produtor.h"
#include <vector>
#include <thread>
#include <stdio.h>
#include <winsock2.h>
#include <semaphore.h>

#define BUFLEN  256  //TAMANHO MAXIMO DO BUFFER
#define PORT_NET 1234   //ENDEREÇO ONDE O SOCKET VAI ENVIAR OS DADOS

class Produtor;

class Consumidor
{
    public:
        static const int BUFFER_SIZE = 1024;
        static std::vector<char*> &getBufferLimitado();
        Consumidor(Produtor& p);
        virtual ~Consumidor();
        int getFront();
        sem_t& getEmpty();
        sem_t& getFull();
        void start();
        int getNumeroDeConsumidores();

    private:
        int quantidade;
        /*SOCKET*/
        SOCKET s;
        struct sockaddr_in server, si_other;
        int slen , recv_len;
        char buf[BUFLEN];
        WSADATA wsa;
        /*SEMAFORO*/
        sem_t full;
        sem_t empty;
        /*BUFFER LIMITADO*/
        int front;
        static std::vector<char*> bufferLimitado;
        Produtor& produtor;
        std::thread *th_consumidor;
        void run();
};

#endif // CONSUMIDOR_H
