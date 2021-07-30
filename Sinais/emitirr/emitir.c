#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main() {
	int pid, signal;
	printf("Qual o PID do processo que deseja sinalizar?\n");
	scanf("%d", &pid);
	if (kill(pid, 0) == -1) {
		printf("Processo nao encontrado\n");
		exit(1);
	}
	printf("Entre com o valor correspondente ao sinal que deseja enviar.\n");
	scanf("%d", &signal);
	if (kill(pid, signal) == -1) {
		printf("Erro");
		exit(1);
	}
	printf("Sinal enviado com sucesso\n");
	
	return 0;
}
