#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <sys/socket.h>

#include <sys/types.h>

#include <netinet/in.h>

#include <arpa/inet.h>

#include <math.h>

#define PORT 4444

bool ePrimo(int n) {
  if (n <= 1)
    return false;
  for (int i = 2; i <= sqrt(n); i++)
    if (n % i == 0)
      return false;
  return true;
}

int main() {

  int socketServidor;
  char buffer[1024];
  int novaConexao = -1;
  struct sockaddr_in enderecoServidor;

  struct sockaddr_in enderecoCliente;
  socklen_t tamanhoDeEndereco;

  socketServidor = socket(AF_INET, SOCK_STREAM, 0);
  if (socketServidor < 0) {
    printf("Erro na criacao o socket.\n");
    exit(1);
  }

  memset( &enderecoServidor, '\0', sizeof(enderecoServidor));
  enderecoServidor.sin_family = AF_INET;
  enderecoServidor.sin_port = htons(PORT);
  enderecoServidor.sin_addr.s_addr = inet_addr("127.0.0.1");

  bind(socketServidor, (struct sockaddr * ) & enderecoServidor, sizeof(enderecoServidor));



  if (listen(socketServidor, 10) == 0) {
    printf("Ouvindo na porta 4444\n");
  } else {
    printf("Erro na criacao do socket\n");
  }
  while (novaConexao == -1) {
    novaConexao = accept(socketServidor, (struct sockaddr * ) & enderecoCliente, & tamanhoDeEndereco);
  }

  printf("Conctado com %s:%d\n", inet_ntoa(enderecoCliente.sin_addr), ntohs(enderecoCliente.sin_port));
  
  while (1) {
    recv(novaConexao, buffer, 1024, 0);
    if (atoi(buffer) == 0) {
      printf("Desconectando...\n");
      break;
    } else {
      printf("Recebido: %s\n", buffer);
      if (ePrimo(atoi(buffer))) {
        strcpy(buffer, "E primo");
        printf("Enviando: E primo\n");
      } else {
        strcpy(buffer, "Nao e primo");
        printf("Enviando: Nao e primo\n");
      }

      send(novaConexao, buffer, strlen(buffer), 0);
      bzero(buffer, sizeof(buffer));

    }

  }

  close(novaConexao);

  return 0;
}
