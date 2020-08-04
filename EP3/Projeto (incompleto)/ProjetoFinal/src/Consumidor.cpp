#include "Consumidor.h"

std::vector<char*> bufferLimitado(Consumidor::BUFFER_SIZE);

Consumidor::Consumidor(Produtor& p) : produtor(p) {
	front = 1;
	th_consumidor = NULL;
	quantidade++;
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

int Consumidor::getNumeroDeConsumidores(){
    return quantidade;
}

void Consumidor::start() {
	th_consumidor = new std::thread(&Consumidor::run, this);
}

void Consumidor::run() {
	front = produtor.getRear();
	sem_init(&empty, 0, Consumidor::BUFFER_SIZE);
	sem_init(&full, 0, 0);

    //INICIANDO O SOKET PARA LER DA PORTE ONDE O VLC ESTA ESCREVENDO
    slen = sizeof(si_other) ;

    //INICIANDO O WINSOCK (VERSAO PARA WINDOWNS DO SOCKET)
    printf("\Inicializando Winsock...");

    //A FUNCAO WSAStartup INICIA O USO DA DLL WINSOCK POR UM PROCESSO
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        //A FUNCAO WSAGetLastError() RETORNA O STATUS DE ERRO PARA A ULTIMA OPERACAO DO SOCKET QUE FALHOU
        printf("Falha ao inicializar! Error Code : %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    printf("Inicializado.\n");

    //CRIANDO O SOCKET. A FUNCAO socket() CRIA UM SOCKET QUE E VINCULADO A UM PROVEDOR DE SERVIÇOS DE TRANSPORTE ESPECIFICOS
    if((s = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET)
    {
        printf("Não foi possível criar o soket: %d" , WSAGetLastError());
    }
    printf("Socket crido.\n");

    //PREPARANDO A ESTRUTURA DO SOCKET
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( PORT_NET );

    //BIND: ASSOCIA O SOCKET CRIADO A UMA IDENTIFICACAO, CONSTITUIDA POR UM IP DA MAQUINA ONDE RESIDE O SERVIDOR E NUMERO DE PORTA ASSOCIADO A APLICACAO
    if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind falhou. error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    puts("Bind concluido");

	//APARTIR DAQUI INICIA O ENVIO DOS DADOS. A VARIAVEL BUF VAI REDECER OS DADOS ESCRITOS NO BUFFERLIMITADO E VAI ENVIAR PARA O ENDERECO PORT_NET

	while (true) {
		sem_wait(&full);

        /******************************************/

        if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR)
        {
            printf("sendto() falhou. error code : %d" , WSAGetLastError());
            exit(EXIT_FAILURE);
        }

        front = (front+1)% quantidade;

		sem_post(&empty);
	}

	sem_destroy(&empty);
	sem_destroy(&full);


}
