/*
 * Consumidor.h
 *
 *  Created on: Jun 5, 2018
 *      Author: bruno
 */

#ifndef INCLUDE_CONSUMIDOR_H_
#define INCLUDE_CONSUMIDOR_H_

#include <semaphore.h>
#include <thread>
#include "Produtor.h"

class Consumidor {
public:
	static const int BUFFER_SIZE = 1024;

	Consumidor(Produtor& p);
	virtual ~Consumidor();

	int getFront();
	sem_t& getEmpty();
	sem_t& getFull();
	static std::vector<char*> &getBufferLimitado();
	void start();

private:
	int front;
	sem_t full;
	sem_t empty;
	static std::vector<char*> bufferLimitado;

	Produtor& produtor;
	std::thread *th_consumidor;

	void run();
};

#endif /* INCLUDE_CONSUMIDOR_H_ */
