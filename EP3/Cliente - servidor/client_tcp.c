#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;

    // A estrutura sockaddr_in contem um endereco de internet
    struct sockaddr_in serv_addr;

    char buffer[BUFFER_SIZE];

    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    portno = atoi(argv[2]);

    // Cria um socket TCP e retorna um descritor
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
        error("ERROR opening socket");

    /*
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    */

    // Zera a estrutura "server"
    bzero((char *) &serv_addr, sizeof(serv_addr));
    // Define a familia do endereco como do tipo Internet
    serv_addr.sin_family = AF_INET;
    // Seta o endereco para argv[1]
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    // A funcao htons() converte o numero da porta para o padrao Little Endian.
    serv_addr.sin_port = htons(portno);

    // Solicita uma conexao ao servidor
    if (connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    printf("Please enter the message: ");

    bzero(buffer,BUFFER_SIZE);
    fgets(buffer,255,stdin);

    // Envia uma mensagem para o servidor atraves do socket
    n = write(sockfd, buffer, strlen(buffer));

    if (n < 0)
        error("ERROR writing to socket");

    bzero(buffer,BUFFER_SIZE);

    // Le os dados recebidos atraves do socket e os armazena em buffer.
    // A funcao read() e' bloqueante.
    n = read(sockfd, buffer, 255);

    if (n < 0)
         error("ERROR reading from socket");

    printf("%s\n",buffer);


    return 0;
}
