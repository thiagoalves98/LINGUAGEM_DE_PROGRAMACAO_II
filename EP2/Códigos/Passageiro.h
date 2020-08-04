#ifndef PASSAGEIRO_H
#define PASSAGEIRO_H
#include <atomic>


using namespace std;

class Carro;
class Parque;
class Exibe;

class Passageiro{

public:

	Passageiro(int id, Carro *c);
	virtual ~Passageiro();
	void entraNoCarro();
	void esperaVoltaAcabar();
	void saiDoCarro();
	void passeiaPeloParque();
	bool parqueFechado();
	void run();
	void ApresentaRelatorio();

private:

    static std::atomic_flag lockControle;
    static std::atomic<int> Contador;
	int id;
	Carro *carro;
	int voltasPorThread[11] = {0};
	int cont = 0;

};

#endif // PASSAGEIRO_H
