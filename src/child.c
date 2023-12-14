#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include<string.h>
#include <myheader.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	int j=1;
	int i=0;
	
	FILE *fptr;
	char line[100];
	if ((fptr = fopen(argv[1],"r")) == NULL)
	{
		printf("Error! opening file");
		exit(1);
	}
	while (fgets(line, sizeof(line), fptr)) 
	{
		printf("%s", line); 
	}
	fclose(fptr);
}