#ifndef EXIBE_H
#define EXIBE_H
#include <atomic>

using namespace std;

class Carro;
class Parque;

class Exibe{

public:
    Exibe();
    virtual ~Exibe();
    static void ExibeMensagem(const char *s);
    static void ExibeMensagemNum(const char *s, int num);
    static void MensagemThread(const char *s, int num);
    static void Nvoltas(int num, int id);

private:
    static std::atomic_flag lockPrint;
};

#endif // EXIBE_H
