#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#define MAX_LINE 80
 
int main(void){
	char arg[10][MAX_LINE / 2 + 1];
	char *args[MAX_LINE / 2 + 1];
	int should_run = 1;
        int num_arg = 0; 
        int n = 0;
	int len = 0;
        char c;
      while(should_run){
        printf("osh>"); 	      
        pid_t pid;
	for(int i = 0;i < 10;++i) args[n] = NULL;
	while(scanf("%s", arg[n])){
		
                args[n] = arg[n];
	        n ++;
		c = getchar();
		if(c == '\n'){
		   break;
		}
			
        }
      
      if(strcmp(arg[0], "exit") == 0) should_run = 0;
      else{
	  pid = fork();
          if(pid < 0){
	      perror("Error:");
	      return -1;
	  }	  
	  else if(pid == 0){
	      args[n] = NULL;    
              execvp(args[0], args);
	      n = 0;
	      exit(0);
	  }
	  else if(pid > 0){
             n = 0;
	     wait(NULL);
	     
	  }
      }
       

   }

	return 0;
}

