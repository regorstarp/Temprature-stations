#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main()

{

	int pid1, pid2;
	int p1[2], p2[2];
	int status1, status2;
	pipe(p1);
	pipe(p2);
	char buffer_lectura[30];
	if (p1 < 0 || p2 < 0){
	printf("Error creant pipe");
	exit(1);
	}

	if ( (pid1=fork()) == 0 )
		
	{ 	/* SENSOR 1 */
		if (pid1 < 0){
		printf("S'ha produit un error al crear el proces");
		}
		close(p1[1]);
		read(p1[0], buffer_lectura, sizeof(buffer_lectura));
		printf("%s\n", buffer_lectura);
		exit(0); /*acabo el proces*/

	}

	else

 	{ /*  MASTER */

 		if ( (pid2=fork()) == 0 )

 		{ /* SENSOR 2 */
 			if (pid2 < 0){
				printf("S'ha produit un error al crear el proces");
			}
			close(p1[1]);
			read(p2[0], buffer_lectura, sizeof(buffer_lectura));
			printf("%s\n", buffer_lectura);
			exit(0); /*acabo el proces*/
		}

		else

		{ /* MASTER */
			char estacio1[] = "num estacio1, nom estacio1";
			char estacio2[] = "num estacio2, nom estacio2";

			close(p1[0]);
			close(p2[0]);
			write(p1[1], estacio1, (strlen(estacio1)+1)); /* falta fer que llegeixi del teclat*/
			write(p2[1], estacio2, (strlen(estacio2)+1)); 
			

		/* Esperem el primer sensor */

			waitpid(pid1, &status1, 0);

		/* Esperem el segon sensor */

			waitpid(pid2, &status2, 0);
			/* tancar tot el que s'ha de tancar*/
			printf("Processos sensors acabats , im out\n");

 		}

	}
}