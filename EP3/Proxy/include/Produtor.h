/*
 * Produtor.h
 *
 *  Created on: Jun 5, 2018
 *      Author: bruno
 */

#ifndef INCLUDE_PRODUTOR_H_
#define INCLUDE_PRODUTOR_H_

#include <vector>
#include <semaphore.h>
#include <thread>

class Consumidor;

class Produtor {
public:
	Produtor();
	virtual ~Produtor();

	int getRear();
	void addConsumidor(Consumidor *c);
	void start();

private:
	int rear;

	std::vector<Consumidor*> consumidores;
	std::thread *th_produtor;

	void run();
};

#endif /* INCLUDE_PRODUTOR_H_ */
