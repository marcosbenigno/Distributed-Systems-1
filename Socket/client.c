#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <sys/socket.h>

#include <sys/types.h>

#include <netinet/in.h>

#include <arpa/inet.h>

#include <cstdlib>

#include <time.h>

#define PORT 4444
int numeroAleatorio(int inicial) {

  int numeroFinal;
  numeroFinal = (rand() % 100 + 1) + inicial;

  return numeroFinal;
}

int main() {
  srand(time(NULL));

  int iter;
  printf("Quantos numeros a serem enviados?");
  scanf("%d", &iter);
	
  int socketCliente;
  int conexao = -1;
  char buffer[1024];
  struct sockaddr_in enderecoServidor;
  
  socketCliente = socket(AF_INET, SOCK_STREAM, 0);
  
  if (socketCliente < 0) {
    printf("Erro na criacao o socket.\n");
    exit(1);
  }

  memset( & enderecoServidor, '\0', sizeof(enderecoServidor));
  enderecoServidor.sin_family = AF_INET;
  enderecoServidor.sin_port = htons(PORT);
  enderecoServidor.sin_addr.s_addr = inet_addr("127.0.0.1");

  while (conexao < 0) {
    conexao = connect(socketCliente, (struct sockaddr * ) & enderecoServidor, sizeof(enderecoServidor));
    printf("Nao conectado.\n");
  }
  
  printf("Conectado\n");
  
  int numero = numeroAleatorio(0);
  int i = 0;
  while (i < iter) {
    printf("Cliente envia: %d\n", numero);
    sprintf(buffer, "%d", numero);
    
    send(socketCliente, buffer, strlen(buffer), 0);
    
    recv(socketCliente, buffer, 1024, 0);

    printf("Resposta do servidor: %s\n", buffer);
    
    numero = numeroAleatorio(numero);
    i = i + 1;
    sleep(1);
  }

  return 0;
}
