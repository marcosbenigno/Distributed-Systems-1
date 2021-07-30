#include<stdio.h>

#include<stdlib.h>

#include<unistd.h>

#include<sys/types.h>

#include<string.h>

#include<sys/wait.h>

#include <time.h>

#include <math.h>


int numeroAleatorio(int inicial) {

  int numeroFinal;
  numeroFinal = (rand() % 100 + 1) + inicial;

  return numeroFinal;
}

bool ePrimo(int n) {
  if (n <= 1)
    return false;
  for (int i = 2; i <= sqrt(n); i++)
    if (n % i == 0)
      return false;
  return true;
}

int main() {
  srand(time(NULL));

  int iter = 0;
  printf("Quantos numeros serao enviados?\n");
  scanf("%d", & iter);
  int canal[2];
  pid_t processo;

  if (pipe(canal) == -1) {
    printf("Falha na criacao do pipe.");
    return 1;
  }

  processo = fork();

  if (processo < 0) {
    printf("Erro na criacao do processo.");
    exit(1);
  } else if (processo > 0) {
  //processo pai
    char buffer[1024];

    int numero = 0;
    int i = 0;
    printf("Sou o produtor. PID: %d\n", getpid());
    do {
      close(canal[0]);
      numero = numeroAleatorio(numero);
      sprintf(buffer, "%d", numero);
      write(canal[1], buffer, strlen(buffer) + 1);
      i++;
      sleep(1);
    } while (i < iter);
    sprintf(buffer, "%d", 0);
    write(canal[1], buffer, strlen(buffer) + 1);
    close(canal[1]);

    wait(NULL);
  } else {
  //processo filho
    printf("Sou o consumidor. PID: %d\n", getpid());
    close(canal[1]);

    char buffer[1024];

    while (read(canal[0], buffer, 1024 + 1) > 0) {
      if (atoi(buffer) != 0) {
        if (ePrimo(atoi(buffer))) {
          printf("(%d): %s e primo\n", getpid(), buffer);
        } else {
          printf("(%d): %s NAO e primo\n", getpid(), buffer);
        }

      } else {
        close(canal[0]);
        exit(0);
      }

    }

  }
  return 0;
}
