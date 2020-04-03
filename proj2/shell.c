#include<stdio.h>
#include<unistd.h>

#define MAX_LINE 80

int main(){
	char *arg[MAX_LINE / 2 + 1];
	int should_run = 1;
        int num_arg = 0;
	while(should_run){
		printf("osh>");
		fflush(stdout);
		scanf("%s", arg);
		printf("%s","hello");
		if(strcmp(arg[num_arg], "exit")) 
			should_run = 0;
	        else{	
	 	    execvp(arg[0], arg);
		}
	}

	printf("Bye\n");

	return 0;
}

