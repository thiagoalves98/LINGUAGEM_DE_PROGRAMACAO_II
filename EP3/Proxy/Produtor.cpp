/*
 * Produtor.cpp
 *
 *  Created on: Jun 5, 2018
 *      Author: bruno
 */

#include "include/Produtor.h"

Produtor::Produtor() {
	rear = 0;
	th_produtor = NULL;
}

Produtor::~Produtor() {
	// TODO Auto-generated destructor stub
}

int Produtor::getRear() {
	return rear;
}

void Produtor::addConsumidor(Consumidor *c) {
	consumidores.push_back(c);
}

void Produtor::start() {
	th_produtor = new std::thread(&Produtor::run, this);
}

void Produtor::run() {

	while (true) {
		for (int i = 0; i < consumidores.size(); i++)
			sem_wait(&consumidores[i]->getEmpty());

		// (...)

		for (int i = 0; i < consumidores.size(); i++)
			sem_post(&consumidores[i]->getFull());
	}
}

