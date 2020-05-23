#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#define MAX_LINE 80
 
int main(void){
	int has_hist=0;
	int hist = 0;
	char arg[10][MAX_LINE / 2 + 1];
	char *args[MAX_LINE / 2 + 1];
	char last_args[10][MAX_LINE / 2 + 1];
	int should_run = 1;
        int num_arg = 0; 
        int n = 0;
	int last_n = 0;
        char c;
	int wait_=1;



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
      //printf("n:%d\n", n);
      if(strcmp(arg[0], "exit") == 0){
	      should_run = 0;
	      continue;
      }

      else if(strcmp(arg[0], "!!") == 0){
           hist = 1;
	   if(!has_hist){
               printf("There is no history command!\n");
	       n = 0;
               hist = 0;
	       continue;
	   }
	   else{
	       printf("last_n:%d\n",last_n);
	       for(int i = 0;i < last_n;++i){
	           strcpy(args[i], last_args[i]);
	           //printf("%s ", args[i]);
		   //printf("\n");
	       }  
	   }
      }   
            
          
         // printf("lastn:%d, n:%d\n", last_n, n);
          
	  if(hist){
	     args[last_n] = NULL;
	  }
	  else{
             args[n] = NULL;
	  }
	  
	  
                     
          if(!hist){
              for(int i = 0;i < n;++i){
                 strcpy(last_args[i], args[i]); //without the last "NULL"
                 //printf("%s ", args[i]);
              }
              last_n = n;
              //printf("%d\n", n);
          }


 
	  hist = 0;	  
	  has_hist = 1;

// exe part:
// check < and > and |

	  pid = fork();

          if(pid < 0){
	      perror("Error:");
	      return -1;
	  }	  
	  else if(pid == 0){
	      execvp(args[0], args);
	      exit(0);
	  }
	  else if(pid > 0){
             if(wait_)
	     wait(NULL);
	     
	  }


 
  n = 0;
 
   
  
}

	return 0;
}

