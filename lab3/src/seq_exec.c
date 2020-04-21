#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
int main(int argc, char **argv) 
{ 
        char *argvn[4]={"Command-line",argv[1],argv[2],NULL}; 
        execvp("./Seq",argvn);
    return 0; 
} 
