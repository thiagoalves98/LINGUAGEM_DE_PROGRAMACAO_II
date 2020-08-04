#ifndef CARRO_H
#define CARRO_H
#include <atomic>


using namespace std;

class Parque;
class Exibe;

class Carro{

public:

	static const int CAPACIDADE;
	static std::atomic<int> nPassageiros;
    static std::atomic<bool>voltaAcabou;
	static std::atomic<bool>carroCheio;

	Carro();
	virtual ~Carro();
	void esperaEncher();
	void daUmaVolta();
	void esperaEsvaziar();
	int getNVoltas();
	void run();

private:
	int voltas;
	static std::atomic_flag lockCarro;
};

#endif // CARRO_H
