#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
int p1[2], p2[2], pid, i, fill1_fi = 0, fill2_fi = 0, fills_acabats = 0;
pipe(p1);
pipe(p2);
char nom[30];
int status1, status2;
if (p1 < 0 || p2 < 0){
	printf("Error creant pipe");
	exit(1);
}
for (i = 0; i < 2; i++){
	pid = fork();

	if (pid < 0){
		printf("S'ha produit un error al crear el proces");
	}

	if((pid == 0) && (i == 0)){
		/* FILL 1 */
		dup(p1[0]);
		read(p1[0],&nom,11);
		printf("%s\n", nom);
		close(p1[0]);
		close(p1[1]);
		fill1_fi = 1;
		exit(0); /*acabo el proces*/
	}
	
	if((pid == 0) && (i == 1)){
		/* FILL 2 */
		dup(p2[0]);
		read(p2[0],&nom,10);
		printf("%s\n", nom);
		close(p2[0]);
		close(p2[1]);
		fill2_fi = 1;
		exit(0); /*acabo el proces*/
	}

	if(fill1_fi == 1 && fill2_fi == 1){
		fills_acabats = 1;
	}

	if(pid > 0){
		/* PARE */
		write(p1[1], "primer fill", 11); /* falta fer que llegeixi del teclat*/
		write(p2[1],"segon fill", 10);
		/*esperar a que els fills acabin*/
		
		waitpid(pid, &status1, 0);
		printf("final");
	}
}
}