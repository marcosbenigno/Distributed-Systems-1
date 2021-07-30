#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>


void primeiroHandler(int sig)
{
	
    printf("Recebido sinal SIGUSR1 (%d)\n", sig);

}


void segundoHandler(int sig)
{
    printf("Recebido sinal SIGUSR2 (%d)\n", sig);
}

void terceiroHandler(int sig)
{
    printf("Recebido sinal SIGCHLD (%d), finalizando.......\n", sig);
    exit(0);
   
}

int main() {
	int tipoDeEspera;
	printf("Digite 1 para busy-waiting\nDigite 2 para blocking wait\n");
	scanf("%d", &tipoDeEspera);

	printf("Esperando sinais SIGUSR1, SIGUSR2 ou SIGCHLD (sair).\n");
	signal(SIGUSR1, primeiroHandler);
	signal(SIGUSR2, segundoHandler);
	signal(SIGCHLD, terceiroHandler);
	
	if (tipoDeEspera == 1) {
		//busy
		while (1) {
			sleep(1);
		}
	} else if (tipoDeEspera == 2) {
		//blocking
		while (1) {
			pause();
		}
	
	}
	
	return 0;
}
