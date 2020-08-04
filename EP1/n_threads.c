#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#define MAX_ELEMENTOS 200
#define NUM_THREADS 200

int MatrizA[MAX_ELEMENTOS][MAX_ELEMENTOS],
    MatrizB[MAX_ELEMENTOS][MAX_ELEMENTOS],
    MatrizC[MAX_ELEMENTOS][MAX_ELEMENTOS];

void GeraMatriz(int Matriz[][MAX_ELEMENTOS]){
    int aux1,
        aux2,
        nAleatorio = 0;

    srand(time(NULL));
    for(aux1 = 0; aux1 < MAX_ELEMENTOS; aux1++){
        for(aux2 = 0; aux2 < MAX_ELEMENTOS; aux2++){
            nAleatorio = rand() % 10;
            if (nAleatorio > 0 && nAleatorio < 10){
                Matriz[aux1][aux2] = nAleatorio;
            }
           else if(nAleatorio == 0){
               Matriz[aux1][aux2] = nAleatorio + 1;
            }
            else{
               Matriz[aux1][aux2] = 1;
            }
        }
    }
}

void *ProdutoDuasThread(void *arg){
    int *i = (int *) arg;
    int aux1,
        aux2,
        aux3,
        calcula,
        x = *i;

    if(x = 0){
        aux1 = 0;
        calcula = (MAX_ELEMENTOS/2)-1;
    }
    if(x = 1){
        aux1 = MAX_ELEMENTOS/2;
        calcula = MAX_ELEMENTOS;
    }

    for(aux1; aux1 < calcula ; aux1++){
        for(aux2 = 0; aux2 < MAX_ELEMENTOS; aux2++){
            MatrizC[aux1][aux2] = 0;
            for(aux3 = 0; aux3 < MAX_ELEMENTOS; aux3++){
                MatrizC[aux1][aux2] =  MatrizC[aux1][aux2] + (MatrizA[aux1][aux3] * MatrizB[aux3][aux2]);
            }
      }
    }
}

void *ProdutoQuatroThread(void *arg){
    int *i = (int *) arg;
    int aux1,
        aux2,
        aux3,
        calcula,
        x = *i;
    switch(x){
        case 0:
        {
            aux1 = 0;
            calcula = (MAX_ELEMENTOS/4)-1;
        }
        case 1:
        {
            aux1 = (MAX_ELEMENTOS/4);
            calcula = (MAX_ELEMENTOS/2)-1;
        }
        case 2:
        {
            aux1 = (MAX_ELEMENTOS/2);
            calcula =(3*MAX_ELEMENTOS/4)-1;
        }
        case 3:
        {
            aux1 = (3*MAX_ELEMENTOS/4);
            calcula = MAX_ELEMENTOS;
        }
    }
     for(aux1; aux1 < calcula ; aux1++){
        for(aux2 = 0; aux2 < MAX_ELEMENTOS; aux2++){
            MatrizC[aux1][aux2] = 0;
            for(aux3 = 0; aux3 < MAX_ELEMENTOS; aux3++){
                MatrizC[aux1][aux2] =  MatrizC[aux1][aux2] + (MatrizA[aux1][aux3] * MatrizB[aux3][aux2]);
            }
      }
    }
}

void *ProdutoNThread(void *arg){
    int *i = (int *) arg;
    int aux1,
        aux2,
        aux3,
        x = *i;

        for(aux2 = 0; aux2 < MAX_ELEMENTOS; aux2++){
            MatrizC[x][aux2] = 0;
            for(aux3 = 0; aux3 < MAX_ELEMENTOS; aux3++){
                MatrizC[x][aux2] =  MatrizC[x][aux2] + (MatrizA[x][aux3] * MatrizB[aux3][aux2]);
            }
        }
}

int main(){

    void GeraMatriz(int Matriz[][MAX_ELEMENTOS]);
    void * ProdutoDuasThread(void *arg);
    void * ProdutoQuatroThread(void *arg);
    void * ProdutoNThread(void *arg);

    int i;
    pthread_t threadID[NUM_THREADS]; //Cria o array de threads

    GeraMatriz(MatrizA);
    GeraMatriz(MatrizB);

    //Para utilização correta do código, deve ser selecionado o laço for responsavel pela estratégia desejada.
    //No caso do ProdutoNThread, o valor de NUM_THREADS deve ser exatamente o valor de MAX_ELEMNTOS

    for(i = 0; i < 2; i++) //Calcula com Duas Thread
    {
        pthread_create(&threadID[i], NULL, ProdutoDuasThread, &i);
    }
    for(i = 0; i < 2; i++)
    {
        pthread_join(threadID[i], NULL);
    }
    pthread_exit(NULL);

    /*for (i = 0; i < 4; i++) //Calcula com Quatro Thread
    {
        pthread_create(&threadID[i], NULL, ProdutoQuatroThread, &i);
    }
    for (i = 0; i < 4; i++)
    {
        pthread_join(threadID[i], NULL);
    }

    pthread_exit(NULL);*/

    /*for (i = 0; i <MAX_ELEMENTOS; i++) //Calcula com N Thread
    {
        pthread_create(&threadID[i], NULL, ProdutoNThread, &i);
    }
    for (i = 0; i <MAX_ELEMENTOS; i++)
    {
        pthread_join(threadID[i], NULL);
    }

    pthread_exit(NULL);*/

    return 0;
}