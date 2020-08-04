#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 256

void error(char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    int sockfd, newsockfd, portno;
    char buffer[BUFFER_SIZE];
    int n;
    unsigned int clilen;

    // A estrutura sockaddr_in contem um endereco de internet
    struct sockaddr_in serv_addr, cli_addr;

    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }

    // Cria um socket TCP e retorna um descritor
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
        error("ERROR opening socket");bb
    // Zera a estrutura "server"
    bzero( (char *) &serv_addr, sizeof(serv_addr) );
    // Numero da porta
    portno = atoi(argv[1]);
    // Define a familia do endereco como do tipo Internet
    serv_addr.sin_family = AF_INET;
    // Seta o endereco para localhost (127.0.0.1)
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    // A funcao htons() converte o numero da porta para o padrao Little Endian.
    serv_addr.sin_port = htons(portno);

    // Associa um socket a um endereco
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    // Aloca recursos para armazenar as solicitaçoes de conexao. No maximo 5
    // solicitacoes podem ser tratadas.
    listen(sockfd, 5);

    clilen = sizeof(cli_addr);

    // Bloqueia a execucao ate que seja estabelecida uma conexao com algum cliente
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

    if (newsockfd < 0)
        error("ERROR on accept");

    // Zera o buffer
    bzero(buffer, BUFFER_SIZE);

    // Le os dados recebidos atraves do socket e os armazena em buffer.
    // A funcao read() e' bloqueante.
    n = read(newsockfd, buffer, 255);

    if (n < 0)
        error("ERROR reading from socket");

    printf("Your message: %s\n",buffer);

    // Envia uma mensagem para o cliente atraves do socket
    n = write(newsockfd,"I got your message", 18);

    if (n < 0)
        error("ERROR writing to socket");

    return 0;
}
