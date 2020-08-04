#ifndef PRODUTOR_H
#define PRODUTOR_H
#include "Consumidor.h"
#include <vector>
#include <thread>
#include <stdio.h>
#include <winsock2.h>
#include <semaphore.h>

#define BUFLEN  1380  //TAMANHO MAXIMO DO BUFFER
#define PORT_VLC 8888   //ENDEREÇO QUE O SOCKET VAI RECEBER OS DADOS DO VLC

class Consumidor;

class Produtor {
public:
	Produtor();
	virtual ~Produtor();
	int getRear();
	void addConsumidor(Consumidor *c);
	void start();

private:
	SOCKET s;
    struct sockaddr_in server, si_other;
    int slen , recv_len;
    char buf[BUFLEN];
    WSADATA wsa;
    char aux;

	int rear;

	std::vector<Consumidor*> consumidores;
	std::thread *th_produtor;

	void run();
};

#endif // PRODUTOR_H
