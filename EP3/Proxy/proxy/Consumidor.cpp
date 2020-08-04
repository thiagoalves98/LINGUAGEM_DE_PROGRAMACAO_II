/*
 * Consumidor.cpp
 *
 *  Created on: Jun 5, 2018
 *      Author: bruno
 */

#include "include/Consumidor.h"

std::vector<char*> bufferLimitado(Consumidor::BUFFER_SIZE);

Consumidor::Consumidor(Produtor& p) : produtor(p) {
	front = 1;
	th_consumidor = NULL;
}

Consumidor::~Consumidor() {
	// TODO Auto-generated destructor stub
}

int Consumidor::getFront() {
	return front;
}

sem_t& Consumidor::getEmpty() {
	return empty;
}

sem_t& Consumidor::getFull() {
	return full;
}

static std::vector<char*>& getBufferLimitado() {
	return bufferLimitado;
}

void Consumidor::start() {
	th_consumidor = new std::thread(&Consumidor::run, this);
}

void Consumidor::run() {
	front = produtor.getRear();
	sem_init(&empty, 0, Consumidor::BUFFER_SIZE);
	sem_init(&full, 0, 0);

	while (true) {
		sem_wait(&full);

		// (...)

		sem_post(&empty);
	}

	sem_destroy(&empty);
	sem_destroy(&full);
}
