//pare amb 2 fills
#include <stdio.h>
#include <unistd.h>
main(void)
{
 pid_t pid;
 int x;

 /***** falta posar wait *****/
 for(x = 0; x < 2; x++)
 {
  
  pid=fork(); 
  if(pid)
  {
   printf("Soc el proces %d\n", getpid());
   sleep(2);
  }
  else if(pid == -1)
  {
  	printf("Error en crear el proces");
  }
  else
  {
   printf("Soc el fill %d, el meu pare es %d\n", getpid(), getppid());
   sleep(2);
   break;
  }
  
 }
 return 0;
}

