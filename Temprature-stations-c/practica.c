#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define NUM_FILLS 10
#define MAX 255

int main() {
	FILE*  estacions;
	FILE* mesures;
	int pid, i, j, a, analisi[2], p[NUM_FILLS][2];
	char b[MAX], c[MAX], d[MAX];
	char min[MAX];
	int comparar, minima = 52;

	estacions = fopen("estacions.txt", "r");
	mesures = fopen("mesures.txt", "w+");
	pipe(analisi);

	for (i = 0; i < NUM_FILLS; i++){
		pipe(p[i]);

		if (p[i] < 0) {
			printf("Error creant pipe: %d", i); 
			exit(1);
		}
		pid = fork();
		if (pid == 0) 
		{
			/*fill*/
			int n,numero;
			char envia[MAX];
			close(p[i][1]);
			read(p[i][0], b, MAX);
			close(p[i][0]);
			sscanf(b, "%d %s %d", &numero, envia, &n); /*llegir numes lultim numero*/
			
			int y, suma = 0;
			int aux;
			srand(time(NULL) + getpid());

			for (y = 0; y < n; y++) {
				aux = rand() % 51; /* num aleatori de 0 a 50 */
				suma = suma + aux;
			}
			suma = suma / n;
			sleep(10);
			close(analisi[0]);
			sprintf(b,"%d %s %d", numero, envia, suma); /* ajunta en un string*/
			write(analisi[1], b, MAX);
			close(analisi[1]);
			exit(EXIT_SUCCESS);
		}
		else if (pid < 0){
			printf("S'ha produit un error al crear el proces\n");
			exit(1);
		}
		else if (pid > 0) {
			/*Master*/
			close(p[i][0]);
			fgets(c,MAX,estacions); /*llegeix una linia del fitxer*/
			write(p[i][1], c, MAX);
			close(p[i][1]);
		}
	}
	/* fora del for */
	pid = fork();
	if (pid == 0){
		/*analisi*/
		close(analisi[1]);
		for (a = 0; a < NUM_FILLS; a++){
			read(analisi[0], d, MAX);
			sscanf(d, "%*d %*s %d", &comparar);
			fprintf(mesures, "%d", comparar);
			fprintf(mesures, "\n");
			if (comparar < minima){
				strcpy(min, d);
				minima = comparar;
			}
		}
		close(analisi[0]);
		fprintf(mesures, "Temperatura minima: ");
		fprintf(mesures, "%s", min);
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0){
		/* error fork*/
		printf("S'ha produit un error al crear el proces\n");
		exit(1);
	}
	else if (pid > 0) {
    /* master*/
	for (j = 0; j < NUM_FILLS + 1; ++j)
	{
		wait(NULL);	 
	}
	exit(EXIT_SUCCESS);
	}
}