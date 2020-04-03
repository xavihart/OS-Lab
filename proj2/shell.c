#include<stdio.h>
#include<unistd.h>
#include<string.h>
#define MAX_LINE 80

int main(){
	char arg[MAX_LINE / 2 + 1][20];
	int should_run = 1;
        int num_arg = 0;
	while(should_run){
		printf("osh>");
		fflush(stdout);
		for(int i = 0;i < MAX_LINE / 2 + 1;++i){
		//	arg[i] = NULL;
		}
		int num_arg = 0;
		char tmp[20];
		
                while(scanf("%s", tmp)){
                        char c;
			scanf("%c", &c);
			//printf("%d", num_arg);
			//printf("%c", tmp[0]);
			if(c  == '\n')
				break;
			else{
			    printf("%s\n", tmp);
			    strcpy(arg[num_arg], tmp);
			}
			num_arg += 1;
		}
		
		if(arg[0] == "exit")
			break;
	        execvp(arg[0], arg);
	}

	printf("Bye\n");

	return 0;
}

