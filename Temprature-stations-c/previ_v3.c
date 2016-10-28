#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main()

{

	int fd1, pid1, pid2, n;
	int p1[2], p2[2];
	int status1, status2;
	pipe(p1);
	pipe(p2);
	char c;

	if (p1 < 0 || p2 < 0){
	printf("Error creant pipe");
	exit(1);
	}
	

	if ( (pid1=fork()) == 0 )
		
	{ 	/* SENSOR 1 */
		if (pid1 < 0){
		printf("S'ha produit un error al crear el proces");
		}
		close(0);
		dup(p1[0]);
		while (n =read(0, &c, 1) > 0){
			if (write (1,&c,1) < 0) {
				printf("Error d'escriptura al pipe 1\n");
			}
		}
		if (n < 0) printf("Error lectura pipe1");

		
		close(p1[0]);
		close(p1[1]);
		exit(0); /*acabo el proces*/
	}

	else

 	{ /*  MASTER */

 		if ( (pid2=fork()) == 0 )

 		{ /* SENSOR 2 */
 			if (pid2 < 0){
				printf("S'ha produit un error al crear el proces2\n");
			}
			close(0); /*impedeix entrada de informació per teclat*/
			dup(p2[0]);
			
			while (n = read(0, &c, 1) > 0){
				if (write (1,&c,1) < 0)
					printf("Error d'escriptura al pipe2\n");
			}
			if (n < 0) printf("Error lectura pipe2");
	 		
			close(p2[0]);
			close(p2[1]);
			exit(0); /*acabo el proces*/
		}

		else

		{ /* MASTER */
			fd1 = open("estacions.txt", O_RDONLY);

			char estacio2[] = "num estacio2, nom estacio2";

			while (read(fd1, &c, 1) > 0){
				if (write(p1[1], &c, 1) < 0) {
					printf("Error d'escriptura del fitxer->pipe");
				}
			}
			if (n < 0) printf("Error lectura fitxer");
			
			close(fd1);
			close(p1[1]);

			write(p2[1], estacio2, (strlen(estacio2)+1));
			close(p2[1]);


			waitpid(pid1, &status1, 0);
			waitpid(pid2, &status2, 0);
			

			printf("Processos sensors acabats , im out\n");
			/* no arriba mai*/
			exit(0);
 		}

	}
}