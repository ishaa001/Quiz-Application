#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h> //pipes
#include <sys/wait.h> //wait
#include <ctype.h> //toupper
#include <myheader.h>

#define	READ	0    
#define	WRITE	1     

char correct[30]="Correct!!";
char incorrect[30]="Incorrect!!";

int fd1[2];	//Array for pipe1
int fd2[2];	//Array for pipe2
int pid; //to store child process value
int g_random=0; //for storing random number value
char uname[30];
int status; 
int bytesRead; // number of bytes read from file
char final_ans[100]; //reading the final output in the parent
char read_ans[2]; // to read the ans into the child
char filename[20]; //variable to store the filename
int childpid;

void alarmsignal(int signo)
{
	printf("\nOops! Sorry Times Up\n");
}

void setname(char name[30])
{
	strcpy(uname,name);
}

void quiz_cquestions()
{
	int i=0; //for loops
	int c; //for printing file data
	char ans[2]; //to store the correct options ans
	int oldrandomnumber[10]; //to keep track of randomnumbers so that they are not repeated
	int x; //for loops
	
	while(i<10) // to ensure that the randomnumbers are not repeated
	{
		int randomnumber=rand()%50+1;
        for (x = 0; x < i; x++)
        {
            if(oldrandomnumber[x]==randomnumber)
			{
                break;
            }
        }
        if(x==i)
		{
            oldrandomnumber[i++]=randomnumber;
        }
	}
	i=0;
	score=0;
	while(i<10)
	{
		sleep(1);
		snprintf(filename, 20, "cques%d.txt", oldrandomnumber[i]); //concatenating 
		
		pipe(fd1); //creating pipe1
		pipe(fd2); //creating pipe 2	
		
		system("clear");
		
		//Printing from file onto the console
		char qpath[100]="/home/isha/sem2/Project/Proj/src/Cques/";
		strcat(qpath,filename);
		char c;
		FILE *file;
		file = fopen(qpath, "r");
		if (file) 
		{		
			while ((c = getc(file)) != EOF)
				putchar(c);
			fclose(file);
		}
		
		//Handling alarm and user input
		struct sigaction sa;
		sa.sa_handler = alarmsignal;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGALRM, &sa, NULL);
		alarm(5);
		printf("\n\nChoose the correct ans:");
		if(scanf("%s",ans)==1)
		{
			alarm(0);
		}
			
		int val=oldrandomnumber[i]; 
		g_random=val;
		i++;
		pipe(fd1); //pipe1
		pipe(fd2); //pipe2
		
		pid=fork(); //creating child process
		if(pid==0)
		{
			close(fd2[READ]);
			close(fd1[WRITE]);
			bytesRead = read(fd1[READ],read_ans,strlen(read_ans)+1);
			
			FILE *file1;
			file1 = fopen("./Cques/canswers.txt", "r");
			
			int count=1;
			char line[4];
			
			while (fgets(line, 4, file1))
			{
				if (count == g_random)
				{
					break;
				}
				else
				{
					count++;
				}
			}
			fclose(file1);
			
			char correctans=line[0];
			char useranswer=toupper(read_ans[0]);
			if(correctans==useranswer)
			{
				score+=10;
				write(fd2[WRITE],correct,strlen(correct) + 1);
				close(fd1[READ]);
				close(fd2[WRITE]);
			}
			else
			{
				printf("\n%s The correct ans is %c!",incorrect,correctans);
				fflush(stdout);
				sleep(1);
			}
		}
		else
		{
			close(fd1[READ]);
			close(fd2[WRITE]);
			write(fd1[WRITE],ans,strlen(ans) + 1);
			bytesRead = read(fd2[READ],final_ans,100);
			printf("\n%s\n",final_ans);
			wait(&status);	
			exit(0);
		}
	}
	
	//Handling the quiz scores
	FILE *fptr;
    fptr = fopen("score.txt", "a");
    if(fptr == NULL) //if file does not exist, create it
    {
        freopen("score.txt", "wb", fptr);
    } 
	else
	{
		char subject[30]="C Programming";
		fprintf(fptr, "%s \t%d \t%s\n",uname,score,subject);
		fclose(fptr);
	}
	system("clear");
	printf("\n\n\t\t\t\t\tQuiz is Over!! Your score is %d!!",score);
	int checkout;
	printf("\n\n\t\t\t\t\tPress 0 to continue :");
	scanf("%d",&checkout);
}

void quiz_cnquestions()
{
	int i=0; //for loops
	int c; //for printing file data
	char ans[2]; //to store the correct options ans
	char read_ans[2]; // to read the ans into the child
	char filename[20]; //variable to store the filename
	char final_ans[100]; //reading the final output in the parent
	int bytesRead; // number of bytes read from file
	int oldrandomnumber[10]; //to keep track of randomnumbers so that they are not repeated
	int status; 
	int x; //for loops
	
	while(i<10) // to ensure that the randomnumbers are not repeated
	{
		int randomnumber=rand()%50+1;
        for (x = 0; x < i; x++)
        {
            if(oldrandomnumber[x]==randomnumber)
			{
                break;
            }
        }
        if(x==i)
		{
            oldrandomnumber[i++]=randomnumber;
        }
	}
	i=0;
	score=0;
	while(i<10)
	{
		sleep(1);
		snprintf(filename, 20, "cnques%d.txt", oldrandomnumber[i]); //concatenating 
		
		pipe(fd1); //creating pipe1
		pipe(fd2); //creating pipe 2	
		
		system("clear");
		
		//Printing from file onto the console
		char qpath[100]="/home/isha/sem2/Project/Proj/src/CN/";
		strcat(qpath,filename);
		char c;
		FILE *file;
		file = fopen(qpath, "r");
		if (file) 
		{		
			while ((c = getc(file)) != EOF)
				putchar(c);
			fclose(file);
		}
		
		//Handling alarm and user input
		struct sigaction sa;
		sa.sa_handler = alarmsignal;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGALRM, &sa, NULL);
		alarm(5);
		printf("\n\nChoose the correct ans:");
		if(scanf("%s",ans)==1)
		{
			alarm(0);
		}
			
		int val=oldrandomnumber[i]; 
		g_random=val;
		i++;
		pipe(fd1); //pipe1
		pipe(fd2); //pipe2
		
		pid=fork(); //creating child process
		if(pid==0)
		{
			close(fd2[READ]);
			close(fd1[WRITE]);
			bytesRead = read(fd1[READ],read_ans,strlen(read_ans)+1);
			
			FILE *file1;
			file1 = fopen("./CN/cnanswers.txt", "r");
			
			int count=1;
			char line[4];
			
			while (fgets(line, 4, file1))
			{
				if (count == g_random)
				{
					break;
				}
				else
				{
					count++;
				}
			}
			fclose(file1);
			
			char correctans=line[0];
			char useranswer=toupper(read_ans[0]);
			if(correctans==useranswer)
			{
				score+=10;
				write(fd2[WRITE],correct,strlen(correct) + 1);
				close(fd1[READ]);
				close(fd2[WRITE]);
			}
			else
			{
				printf("\n%s The correct ans is %c!",incorrect,correctans);
				fflush(stdout);
				sleep(1);
			}
		}
		else
		{
			close(fd1[READ]);
			close(fd2[WRITE]);
			write(fd1[WRITE],ans,strlen(ans) + 1);
			bytesRead = read(fd2[READ],final_ans,100);
			printf("\n%s\n",final_ans);
			wait(&status);	
			exit(0);
		}
	}
	
	//Handling the quiz scores
	FILE *fptr;
    fptr = fopen("score.txt", "a");
    if(fptr == NULL) //if file does not exist, create it
    {
        freopen("score.txt", "wb", fptr);
    } 
	else
	{
		char subject[30]="Computer Networks";
		fprintf(fptr, "%s \t%d \t%s\n",uname,score,subject);
		fclose(fptr);
	}
	system("clear");
	printf("\n\n\t\t\t\t\tQuiz is Over!! Your score is %d!!",score);
	int checkout;
	printf("\n\n\t\t\t\t\tPress 0 to continue :");
	scanf("%d",&checkout);
}

void quiz_cppquestions()
{
	int i=0; //for loops
	int c; //for printing file data
	char ans[2]; //to store the correct options ans
	char read_ans[2]; // to read the ans into the child
	char filename[20]; //variable to store the filename
	char final_ans[100]; //reading the final output in the parent
	int bytesRead; // number of bytes read from file
	int oldrandomnumber[10]; //to keep track of randomnumbers so that they are not repeated
	int status; 
	int x; //for loops
	
	while(i<10) // to ensure that the randomnumbers are not repeated
	{
		int randomnumber=rand()%50+1;
        for (x = 0; x < i; x++)
        {
            if(oldrandomnumber[x]==randomnumber)
			{
                break;
            }
        }
        if(x==i)
		{
            oldrandomnumber[i++]=randomnumber;
        }
	}
	i=0;
	score=0;
	while(i<10)
	{
		sleep(1);
		snprintf(filename, 20, "cppques%d.txt", oldrandomnumber[i]); //concatenating 
		
		pipe(fd1); //creating pipe1
		pipe(fd2); //creating pipe 2	
		
		system("clear");
		
		//Printing from file onto the console
		char qpath[100]="/home/isha/sem2/Project/Proj/src/C++/";
		strcat(qpath,filename);
		char c;
		FILE *file;
		file = fopen(qpath, "r");
		if (file) 
		{		
			while ((c = getc(file)) != EOF)
				putchar(c);
			fclose(file);
		}
		
		//Handling alarm and user input
		struct sigaction sa;
		sa.sa_handler = alarmsignal;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGALRM, &sa, NULL);
		alarm(5);
		printf("\n\nChoose the correct ans:");
		if(scanf("%s",ans)==1)
		{
			alarm(0);
		}
			
		int val=oldrandomnumber[i]; 
		g_random=val;
		i++;
		pipe(fd1); //pipe1
		pipe(fd2); //pipe2
		
		pid=fork(); //creating child process
		if(pid==0)
		{
			close(fd2[READ]);
			close(fd1[WRITE]);
			bytesRead = read(fd1[READ],read_ans,strlen(read_ans)+1);
			
			FILE *file1;
			file1 = fopen("./C++/cppanswers.txt", "r");
			
			int count=1;
			char line[4];
			
			while (fgets(line, 4, file1))
			{
				if (count == g_random)
				{
					break;
				}
				else
				{
					count++;
				}
			}
			fclose(file1);
			
			char correctans=line[0];
			char useranswer=toupper(read_ans[0]);
			if(correctans==useranswer)
			{
				score+=10;
				write(fd2[WRITE],correct,strlen(correct) + 1);
				close(fd1[READ]);
				close(fd2[WRITE]);
			}
			else
			{
				printf("\n%s The correct ans is %c!",incorrect,correctans);
				fflush(stdout);
				sleep(1);
			}
		}
		else
		{
			close(fd1[READ]);
			close(fd2[WRITE]);
			write(fd1[WRITE],ans,strlen(ans) + 1);
			bytesRead = read(fd2[READ],final_ans,100);
			printf("\n%s\n",final_ans);
			wait(&status);	
			exit(0);
		}
	}
	
	//Handling the quiz scores
	FILE *fptr;
    fptr = fopen("score.txt", "a");
    if(fptr == NULL) //if file does not exist, create it
    {
        freopen("score.txt", "wb", fptr);
    } 
	else
	{
		char subject[30]="C++ Programming";
		fprintf(fptr, "%s \t%d \t%s\n",uname,score,subject);
		fclose(fptr);
	}
	system("clear");
	printf("\n\n\t\t\t\t\tQuiz is Over!! Your score is %d!!",score);
	int checkout;
	printf("\n\n\t\t\t\t\tPress 0 to continue :");
	scanf("%d",&checkout);
}

void quiz_dsquestions()
{
	int i=0; //for loops
	int c; //for printing file data
	char ans[2]; //to store the correct options ans
	char read_ans[2]; // to read the ans into the child
	char filename[20]; //variable to store the filename
	char final_ans[100]; //reading the final output in the parent
	int bytesRead; // number of bytes read from file
	int oldrandomnumber[10]; //to keep track of randomnumbers so that they are not repeated
	int status; 
	int x; //for loops
	
	while(i<10) // to ensure that the randomnumbers are not repeated
	{
		int randomnumber=rand()%50+1;
        for (x = 0; x < i; x++)
        {
            if(oldrandomnumber[x]==randomnumber)
			{
                break;
            }
        }
        if(x==i)
		{
            oldrandomnumber[i++]=randomnumber;
        }
	}
	i=0;
	score=0;
	while(i<10)
	{
		sleep(1);
		snprintf(filename, 20, "dsques%d.txt", oldrandomnumber[i]); //concatenating 
		
		pipe(fd1); //creating pipe1
		pipe(fd2); //creating pipe 2	
		
		system("clear");
		
		//Printing from file onto the console
		char qpath[100]="/home/isha/sem2/Project/Proj/src/DS/";
		strcat(qpath,filename);
		char c;
		FILE *file;
		file = fopen(qpath, "r");
		if (file) 
		{		
			while ((c = getc(file)) != EOF)
				putchar(c);
			fclose(file);
		}
		
		//Handling alarm and user input
		struct sigaction sa;
		sa.sa_handler = alarmsignal;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGALRM, &sa, NULL);
		alarm(5);
		printf("\n\nChoose the correct ans:");
		if(scanf("%s",ans)==1)
		{
			alarm(0);
		}
			
		int val=oldrandomnumber[i]; 
		g_random=val;
		i++;
		pipe(fd1); //pipe1
		pipe(fd2); //pipe2
		
		pid=fork(); //creating child process
		if(pid==0)
		{
			close(fd2[READ]);
			close(fd1[WRITE]);
			bytesRead = read(fd1[READ],read_ans,strlen(read_ans)+1);
			
			FILE *file1;
			file1 = fopen("./DS/dsanswers.txt", "r");
			
			int count=1;
			char line[4];
			
			while (fgets(line, 4, file1))
			{
				if (count == g_random)
				{
					break;
				}
				else
				{
					count++;
				}
			}
			fclose(file1);
			
			char correctans=line[0];
			char useranswer=toupper(read_ans[0]);
			if(correctans==useranswer)
			{
				score+=10;
				write(fd2[WRITE],correct,strlen(correct) + 1);
				close(fd1[READ]);
				close(fd2[WRITE]);
			}
			else
			{
				printf("\n%s The correct ans is %c!",incorrect,correctans);
				fflush(stdout);
				sleep(1);
			}
		}
		else
		{
			close(fd1[READ]);
			close(fd2[WRITE]);
			write(fd1[WRITE],ans,strlen(ans) + 1);
			bytesRead = read(fd2[READ],final_ans,100);
			printf("\n%s\n",final_ans);
			wait(&status);	
			exit(0);
		}
	}
	
	//Handling the quiz scores
	FILE *fptr;
    fptr = fopen("score.txt", "a");
    if(fptr == NULL) //if file does not exist, create it
    {
        freopen("score.txt", "wb", fptr);
    } 
	else
	{
		char subject[40]="Algorithms and Data Structures";
		fprintf(fptr, "%s \t%d \t%s\n",uname,score,subject);
		fclose(fptr);
	}
	system("clear");
	printf("\n\n\t\t\t\t\tQuiz is Over!! Your score is %d!!",score);
	int checkout;
	printf("\n\n\t\t\t\t\tPress 0 to continue :");
	scanf("%d",&checkout);
}

void quiz_javaquestions()
{
	int i=0; //for loops
	int c; //for printing file data
	char ans[2]; //to store the correct options ans
	char read_ans[2]; // to read the ans into the child
	char filename[20]; //variable to store the filename
	char final_ans[100]; //reading the final output in the parent
	int bytesRead; // number of bytes read from file
	int oldrandomnumber[10]; //to keep track of randomnumbers so that they are not repeated
	int status; 
	int x; //for loops
	
	while(i<10) // to ensure that the randomnumbers are not repeated
	{
		int randomnumber=rand()%50+1;
        for (x = 0; x < i; x++)
        {
            if(oldrandomnumber[x]==randomnumber)
			{
                break;
            }
        }
        if(x==i)
		{
            oldrandomnumber[i++]=randomnumber;
        }
	}
	i=0;
	score=0;
	while(i<10)
	{
		sleep(1);
		snprintf(filename, 20, "javaques%d.txt", oldrandomnumber[i]); //concatenating 
		
		pipe(fd1); //creating pipe1
		pipe(fd2); //creating pipe 2	
		
		system("clear");
		
		//Printing from file onto the console
		char qpath[100]="/home/isha/sem2/Project/Proj/src/Java/";
		strcat(qpath,filename);
		char c;
		FILE *file;
		file = fopen(qpath, "r");
		if (file) 
		{		
			while ((c = getc(file)) != EOF)
				putchar(c);
			fclose(file);
		}
		
		//Handling alarm and user input
		struct sigaction sa;
		sa.sa_handler = alarmsignal;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGALRM, &sa, NULL);
		alarm(5);
		printf("\n\nChoose the correct ans:");
		if(scanf("%s",ans)==1)
		{
			alarm(0);
		}
			
		int val=oldrandomnumber[i]; 
		g_random=val;
		i++;
		pipe(fd1); //pipe1
		pipe(fd2); //pipe2
		
		pid=fork(); //creating child process
		if(pid==0)
		{
			close(fd2[READ]);
			close(fd1[WRITE]);
			bytesRead = read(fd1[READ],read_ans,strlen(read_ans)+1);
			
			FILE *file1;
			file1 = fopen("./Java/javaanswers.txt", "r");
			
			int count=1;
			char line[4];
			
			while (fgets(line, 4, file1))
			{
				if (count == g_random)
				{
					break;
				}
				else
				{
					count++;
				}
			}
			fclose(file1);
			
			char correctans=line[0];
			char useranswer=toupper(read_ans[0]);
			if(correctans==useranswer)
			{
				score+=10;
				write(fd2[WRITE],correct,strlen(correct) + 1);
				close(fd1[READ]);
				close(fd2[WRITE]);
			}
			else
			{
				printf("\n%s The correct ans is %c!",incorrect,correctans);
				fflush(stdout);
				sleep(1);
			}
		}
		else
		{
			close(fd1[READ]);
			close(fd2[WRITE]);
			write(fd1[WRITE],ans,strlen(ans) + 1);
			bytesRead = read(fd2[READ],final_ans,100);
			printf("\n%s\n",final_ans);
			wait(&status);	
			exit(0);
		}
	}
	
	//Handling the quiz scores
	FILE *fptr;
    fptr = fopen("score.txt", "a");
    if(fptr == NULL) //if file does not exist, create it
    {
        freopen("score.txt", "wb", fptr);
    } 
	else
	{
		char subject[30]="Java Programming";
		fprintf(fptr, "%s \t%d \t%s\n",uname,score,subject);
		fclose(fptr);
	}
	system("clear");
	printf("\n\n\t\t\t\t\tQuiz is Over!! Your score is %d!!",score);
	int checkout;
	printf("\n\n\t\t\t\t\tPress 0 to continue :");
	scanf("%d",&checkout);
}

void viewscoreboard()
{
    
	FILE *f;
    f = fopen("scoreboard.txt", "a");
    if(f == NULL) //if file does not exist, create it
    {
        freopen("scoreboard.txt", "wb", f);
    }
	fclose(f);
	
	//sorting the file on the basis of highest score
	FILE* ptr = fopen("score.txt","r");
    if (ptr==NULL)
    {
        printf("no such file.");
    }
    system("sort --key 2 -r --numeric-sort score.txt > scoreboard.txt");
    fclose(ptr);
	
	//reading from the file
	FILE *fptr;
	char line[100];
	if ((fptr = fopen("scoreboard.txt","r")) == NULL)
	{
       printf("Error! opening file");
       exit(1);
	}
	system("clear");
	system("setterm -bold on");
	system("setterm -foreground yellow ");
	printf("\t\t\t\t\tThe scores of the quizes are:\n");
	system("setterm -foreground cyan ");
	printf("\n\t\t\t\t\tName \t Score \t Subject\n");
	while (fgets(line, sizeof(line), fptr)) 
	{
		printf("\t\t\t\t\t%s", line); 
    }
	
	fclose(fptr);
	int e;
	system("setterm -foreground red ");
	printf("\n\n\t\t\t\t\tPress 0 to return to main menu:");
	scanf("%d",&e);
	system("setterm -bold off");
	if(e==0)
		return;
}


void choosesubject()
{
	char qpath[100];
	char apath[100];
	system("clear");
	int choice;
	system("setterm -bold on");
	system("setterm -foreground cyan ");
	printf("\n\t\t\t\t\t1. C Programming.");
	printf("\n\t\t\t\t\t2. C++ Programming.");
	printf("\n\t\t\t\t\t3. Java Programming.");
	printf("\n\t\t\t\t\t4. Algorithms and Data Structures.");
	printf("\n\t\t\t\t\t5. Computer Networks.\n");
	system("setterm -foreground yellow ");
	printf("\n\n\t\t\t\t\tEnter your choice:");
	scanf("%d",&choice);
	system("setterm -bold off");
	if(choice == 1)
	{
		prac_cquestions();
	}
	else if(choice == 2)
	{
		prac_cppquestions();
	}
	else if(choice == 3)
	{
		prac_javaquestions();
	}
	else if(choice == 4)
	{
		prac_dsquestions();
	}
	else if(choice == 5)
	{
		prac_cnquestions();
	}
	else
	{
		printf("\nInvalid Option");
	}
}

void prac_cquestions()
{
	char qpath[100];
	char apath[100];
	strcpy(apath,"/home/isha/sem2/Project/Proj/src/Cques/canswers.txt");
	int i=0;
	int j=1;
	char ans[4];
	while(i<3)
	{
		sleep(1);
		FILE *fptr;
		strcpy(qpath,"/home/isha/sem2/Project/Proj/src/Cques/");
		snprintf(filename, 20, "cques%d.txt", j); //concatenating 
		j++;
		strcat(qpath,filename);
		
		char line[100];
		if ((fptr = fopen(qpath,"r")) == NULL)
		{
		   printf("Error! opening file");
		   exit(1);
		}
		system("clear");
		while (fgets(line, sizeof(line), fptr)) 
		{
			printf("%s", line); 
		}
		fclose(fptr);
		printf("\n\nChoose the correct ans:");
		scanf("%s",ans);
		
		
		i++;
		
		pipe(fd1); //pipe1
		pipe(fd2); //pipe2
		
		pid=fork(); //creating child process
		if(pid==0)
		{
			close(fd2[READ]);
			close(fd1[WRITE]);
			bytesRead = read(fd1[READ],read_ans,strlen(read_ans)+1);
			
			FILE *file1;
			file1 = fopen(apath, "r");
			
			int count=1;
			char line[4];
			
			while (fgets(line, 4, file1))
			{
				if (count == (i+1))
				{
					break;
				}
				else
				{
					count++;
				}
			}
			fclose(file1);
			
			char correctans=line[0];
			char useranswer=toupper(read_ans[0]);
			if(correctans==useranswer)
			{
				score+=10;
				write(fd2[WRITE],correct,strlen(correct) + 1);
				close(fd1[READ]);
				close(fd2[WRITE]);
			}
			else
			{
				printf("\n%s The correct ans is %c!",incorrect,correctans);
				fflush(stdout);
				sleep(1);
			}
		}
		else
		{
			close(fd1[READ]);
			close(fd2[WRITE]);
			write(fd1[WRITE],ans,strlen(ans) + 1);
			bytesRead = read(fd2[READ],final_ans,100);
			printf("\n%s\n",final_ans);
			wait(&status);
			exit(0);			
		}
	}
}

void prac_cppquestions()
{
	char qpath[100];
	char apath[100];
	strcpy(apath,"/home/isha/sem2/Project/Proj/src/C++/cppanswers.txt");
	int i=0;
	int j=1;
	char ans[4];
	while(i<50)
	{
		sleep(1);
		FILE *fptr;
		strcpy(qpath,"/home/isha/sem2/Project/Proj/src/C++/");
		snprintf(filename, 20, "cppques%d.txt", j); //concatenating 
		j++;
		strcat(qpath,filename);
		
		char line[100];
		
		if ((fptr = fopen(qpath,"r")) == NULL)
		{
		   printf("Error! opening file");
		   exit(1);
		}
		system("clear");
		while (fgets(line, sizeof(line), fptr)) 
		{
			printf("%s", line); 
		}
		fclose(fptr);
		printf("\n\nChoose the correct ans:");
		scanf("%s",ans);
		
		
		i++;
		
		pipe(fd1); //pipe1
		pipe(fd2); //pipe2
		
		pid=fork(); //creating child process
		if(pid==0)
		{
			close(fd2[READ]);
			close(fd1[WRITE]);
			bytesRead = read(fd1[READ],read_ans,strlen(read_ans)+1);
			
			FILE *file1;
			file1 = fopen(apath, "r");
			
			int count=1;
			char line[4];
			
			while (fgets(line, 4, file1))
			{
				if (count == (i+1))
				{
					break;
				}
				else
				{
					count++;
				}
			}
			fclose(file1);
			
			char correctans=line[0];
			char useranswer=toupper(read_ans[0]);
			if(correctans==useranswer)
			{
				score+=10;
				write(fd2[WRITE],correct,strlen(correct) + 1);
				close(fd1[READ]);
				close(fd2[WRITE]);
			}
			else
			{
				printf("\n%s The correct ans is %c!",incorrect,correctans);
				fflush(stdout);
				sleep(1);
			}
		}
		else
		{
			close(fd1[READ]);
			close(fd2[WRITE]);
			write(fd1[WRITE],ans,strlen(ans) + 1);
			bytesRead = read(fd2[READ],final_ans,100);
			printf("\n%s\n",final_ans);
			wait(&status);	
			exit(0);
		}
	}
}

void prac_cnquestions()
{
	char qpath[100];
	char apath[100];
	strcpy(apath,"/home/isha/sem2/Project/Proj/src/CN/cnanswers.txt");
	int i=0;
	int j=1;
	char ans[4];
	while(i<50)
	{
		sleep(1);
		FILE *fptr;
		strcpy(qpath,"/home/isha/sem2/Project/Proj/src/CN/");
		snprintf(filename, 20, "cnques%d.txt", j); //concatenating 
		j++;
		strcat(qpath,filename);
		
		char line[100];
		
		if ((fptr = fopen(qpath,"r")) == NULL)
		{
		   printf("Error! opening file");
		   exit(1);
		}
		system("clear");
		while (fgets(line, sizeof(line), fptr)) 
		{
			printf("%s", line); 
		}
		fclose(fptr);
		printf("\n\nChoose the correct ans:");
		scanf("%s",ans);
		
		
		i++;
		
		pipe(fd1); //pipe1
		pipe(fd2); //pipe2
		
		pid=fork(); //creating child process
		if(pid==0)
		{
			close(fd2[READ]);
			close(fd1[WRITE]);
			bytesRead = read(fd1[READ],read_ans,strlen(read_ans)+1);
			
			FILE *file1;
			file1 = fopen(apath, "r");
			
			int count=1;
			char line[4];
			
			while (fgets(line, 4, file1))
			{
				if (count == (i+1))
				{
					break;
				}
				else
				{
					count++;
				}
			}
			fclose(file1);
			
			char correctans=line[0];
			char useranswer=toupper(read_ans[0]);
			if(correctans==useranswer)
			{
				score+=10;
				write(fd2[WRITE],correct,strlen(correct) + 1);
				close(fd1[READ]);
				close(fd2[WRITE]);
			}
			else
			{
				printf("\n%s The correct ans is %c!",incorrect,correctans);
				fflush(stdout);
				sleep(1);
			}
		}
		else
		{
			close(fd1[READ]);
			close(fd2[WRITE]);
			write(fd1[WRITE],ans,strlen(ans) + 1);
			bytesRead = read(fd2[READ],final_ans,100);
			printf("\n%s\n",final_ans);
			wait(&status);	
			exit(0);
		}
	}
}

void prac_dsquestions()
{
	char qpath[100];
	char apath[100];
	strcpy(apath,"/home/isha/sem2/Project/Proj/src/DS/dsanswers.txt");
	int i=0;
	int j=1;
	char ans[4];
	while(i<50)
	{
		sleep(1);
		FILE *fptr;
		strcpy(qpath,"/home/isha/sem2/Project/Proj/src/DS/");
		snprintf(filename, 20, "dsques%d.txt", j); //concatenating 
		j++;
		strcat(qpath,filename);
		
		char line[100];
		
		if ((fptr = fopen(qpath,"r")) == NULL)
		{
		   printf("Error! opening file");
		   exit(1);
		}
		system("clear");
		while (fgets(line, sizeof(line), fptr)) 
		{
			printf("%s", line); 
		}
		fclose(fptr);
		printf("\n\nChoose the correct ans:");
		scanf("%s",ans);
		
		
		i++;
		
		pipe(fd1); //pipe1
		pipe(fd2); //pipe2
		
		pid=fork(); //creating child process
		if(pid==0)
		{
			close(fd2[READ]);
			close(fd1[WRITE]);
			bytesRead = read(fd1[READ],read_ans,strlen(read_ans)+1);
			
			FILE *file1;
			file1 = fopen(apath, "r");
			
			int count=1;
			char line[4];
			
			while (fgets(line, 4, file1))
			{
				if (count == (i+1))
				{
					break;
				}
				else
				{
					count++;
				}
			}
			fclose(file1);
			
			char correctans=line[0];
			char useranswer=toupper(read_ans[0]);
			if(correctans==useranswer)
			{
				score+=10;
				write(fd2[WRITE],correct,strlen(correct) + 1);
				close(fd1[READ]);
				close(fd2[WRITE]);
			}
			else
			{
				printf("\n%s The correct ans is %c!",incorrect,correctans);
				fflush(stdout);
				sleep(1);
			}
		}
		else
		{
			close(fd1[READ]);
			close(fd2[WRITE]);
			write(fd1[WRITE],ans,strlen(ans) + 1);
			bytesRead = read(fd2[READ],final_ans,100);
			printf("\n%s\n",final_ans);
			wait(&status);	
			exit(0);
		}
	}
}

void prac_javaquestions()
{
	char qpath[100];
	char apath[100];
	strcpy(apath,"/home/isha/sem2/Project/Proj/src/Java/javaanswers.txt");
	int i=0;
	int j=1;
	char ans[4];
	while(i<50)
	{
		sleep(1);
		FILE *fptr;
		strcpy(qpath,"/home/isha/sem2/Project/Proj/src/Java/");
		snprintf(filename, 20, "javaques%d.txt", j); //concatenating 
		j++;
		strcat(qpath,filename);
		
		char line[100];
		
		if ((fptr = fopen(qpath,"r")) == NULL)
		{
		   printf("Error! opening file");
		   exit(1);
		}
		system("clear");
		while (fgets(line, sizeof(line), fptr)) 
		{
			printf("%s", line); 
		}
		fclose(fptr);
		printf("\n\nChoose the correct ans:");
		scanf("%s",ans);
		
		
		i++;
		
		pipe(fd1); //pipe1
		pipe(fd2); //pipe2
		
		pid=fork(); //creating child process
		if(pid==0)
		{
			close(fd2[READ]);
			close(fd1[WRITE]);
			bytesRead = read(fd1[READ],read_ans,strlen(read_ans)+1);
			
			FILE *file1;
			file1 = fopen(apath, "r");
			
			int count=1;
			char line[4];
			
			while (fgets(line, 4, file1))
			{
				if (count == (i+1))
				{
					break;
				}
				else
				{
					count++;
				}
			}
			fclose(file1);
			
			char correctans=line[0];
			char useranswer=toupper(read_ans[0]);
			if(correctans==useranswer)
			{
				score+=10;
				write(fd2[WRITE],correct,strlen(correct) + 1);
				close(fd1[READ]);
				close(fd2[WRITE]);
			}
			else
			{
				printf("\n%s The correct ans is %c!",incorrect,correctans);
				fflush(stdout);
				sleep(1);
			}
		}
		else
		{
			close(fd1[READ]);
			close(fd2[WRITE]);
			write(fd1[WRITE],ans,strlen(ans) + 1);
			bytesRead = read(fd2[READ],final_ans,100);
			printf("\n%s\n",final_ans);
			wait(&status);	
			exit(0);
		}
	}
}

void readmaterials()
{
	int choice1;
	int j=1;
	int i;
	char filename[50];
	system("setterm -bold on");
	system("setterm -foreground cyan ");
	printf("\n\t\t\t\t\t1. C Programming.");
	printf("\n\t\t\t\t\t2. C++ Programming.");
	printf("\n\t\t\t\t\t3. Java Programming.");
	printf("\n\t\t\t\t\t4. Algorithms and Data Structures.");
	printf("\n\t\t\t\t\t5. Computer Networks.\n");
	system("setterm -foreground yellow ");
	printf("\n\n\t\t\t\t\tEnter your choice:");
	scanf("%d",&choice1);
	system("setterm -bold off");
	system("clear");
	if(choice1==1)
	{
		for(i=0; i<5; i++)
		{
			int p=fork();
			if ( p == 0 )
			{
				FILE *fptr;
				char line[100];
				snprintf(filename, 50, "./Cques/notec%d.txt", j);
				execl("./child.out","./child.out",filename, NULL ); /* Execute other program */
				fprintf( stderr, "Could not execute\n" );
			}
			else
			{
				childpid=wait(&status);
			}
			j++;
		}
		int e;
		printf("\n\nPress 0 to return to main menu:");
		scanf("%d",&e);
		if(e==0)
			return;
	}
	else if(choice1==2)
	{
		for(i=0; i<5; i++)
		{
			int p=fork();
			if ( p == 0 )
			{
				FILE *fptr;
				char line[100];
				snprintf(filename, 50, "./C++/notecpp%d.txt", j);
				execl("./child.out","./child.out",filename, NULL ); /* Execute other program */
				fprintf( stderr, "Could not execute\n" );
			}
			else
			{
				childpid=wait(&status);
			}
			j++;
		}
		int e;
		printf("\n\nPress 0 to return to main menu:");
		scanf("%d",&e);
		if(e==0)
			return;
	}
	else if(choice1==3)
	{
		for(i=0; i<5; i++)
		{
			int p=fork();
			if ( p == 0 )
			{
				FILE *fptr;
				char line[100];
				snprintf(filename, 50, "./Java/notejava%d.txt", j);
				execl("./child.out","./child.out",filename, NULL ); /* Execute other program */
				fprintf( stderr, "Could not execute\n" );
			}
			else
			{
				childpid=wait(&status);
			}
			j++;
		}
		int e;
		printf("\n\nPress 0 to return to main menu:");
		scanf("%d",&e);
		if(e==0)
			return;
	}
	else if(choice1==4)
	{
		for(i=0; i<5; i++)
		{
			int p=fork();
			if ( p == 0 )
			{
				FILE *fptr;
				char line[100];
				snprintf(filename, 50, "./DS/noteds%d.txt", j);
				execl("./child.out","./child.out",filename, NULL ); /* Execute other program */
				fprintf( stderr, "Could not execute\n" );
			}
			else
			{
				childpid=wait(&status);
			}
			j++;
		}
		int e;
		printf("\n\nPress 0 to return to main menu:");
		scanf("%d",&e);
		if(e==0)
			return;
	}
	else if(choice1==5)
	{
		for(i=0; i<5; i++)
		{
			int p=fork();
			if ( p == 0 )
			{
				FILE *fptr;
				char line[100];
				snprintf(filename, 50, "./CN/notecn%d.txt", j);
				execl("./child.out","./child.out",filename, NULL ); /* Execute other program */
				fprintf( stderr, "Could not execute\n" );
			}
			else
			{
				childpid=wait(&status);
			}
			j++;
		}
		int e;
		printf("\n\nPress 0 to return to main menu:");
		scanf("%d",&e);
		if(e==0)
			return;
	}
	else
	{
		printf("Invalid Choice!");
	}
}