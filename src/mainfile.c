#include<stdio.h>
#include<stdlib.h>
#include<myheader.h>
#include<unistd.h>

int main()
{
	int choice1=0; // variable for selecting the categories
	int choice2=0; // variable for selecting the subjects
	char name[30]=""; // input for user name
	while(1)
	{
		system("clear");
		system("setterm -background black ");
		system("setterm -foreground yellow ");
		system("setterm -bold on");
		printf("\n\t\t\t\t\t\tGeek O Pedias\n");
		system("setterm -bold off");
		system("setterm -foreground cyan ");
		system("setterm -bold on");
		printf("\n\t\t\t\t\t1. Are you ready? Let's QuiZ!\n");
		printf("\n\t\t\t\t\t2. View Scoreboard!\n");
		printf("\n\t\t\t\t\t3. Are you afraid? Let's practice!\n");
		printf("\n\t\t\t\t\t4. Exit!\n");
		system("setterm -foreground green ");
		printf("\n\n\t\t\t\t\tEnter your choice:");
		scanf("%d",&choice1);
		system("setterm -bold off");
		
		//switch case for first choices
		switch(choice1)
		{
			case 1:
				system("clear");
				system("setterm -foreground cyan ");
				system("setterm -bold on");
				printf("\n\t\t\t\t\t1. C Programming.\n");
				printf("\n\t\t\t\t\t2. C++ Programming.\n");
				printf("\n\t\t\t\t\t3. Java Programming.\n");
				printf("\n\t\t\t\t\t4. Algorithms and Data Structures.\n");
				printf("\n\t\t\t\t\t5. Computer Networks.\n");
				system("setterm -foreground green ");
				printf("\n\n\t\t\t\t\tEnter your choice:");
				scanf("%d",&choice2);
				system("setterm -bold off");
				switch(choice2)
				{
					case 1:
						system("setterm -bold on");
						system("setterm -foreground green ");
						printf("\n\t\t\t\t\tEnter your name:");
						scanf("%s",name);
						system("setterm -bold off");
						setname(name);
						quiz_cquestions();
						break;
					
					case 2:
						system("setterm -bold on");
						system("setterm -foreground green ");
						printf("\n\t\t\t\t\tEnter your name:");
						scanf("%s",name);
						system("setterm -bold off");
						setname(name);
						quiz_cppquestions();
						break;
					
					case 3:
						system("setterm -bold on");
						system("setterm -foreground green ");
						printf("\n\t\t\t\t\tEnter your name:");
						scanf("%s",name);
						system("setterm -bold off");
						setname(name);
						quiz_javaquestions();
						break;
					
					case 4:
						system("setterm -bold on");
						system("setterm -foreground green ");
						printf("\n\t\t\t\t\tEnter your name:");
						scanf("%s",name);
						system("setterm -bold off");
						setname(name);
						quiz_dsquestions();
						break;
					
					case 5:
						system("setterm -bold on");
						system("setterm -foreground green ");
						printf("\n\t\t\t\t\tEnter your name:");
						scanf("%s",name);
						system("setterm -bold off");
						setname(name);
						quiz_cnquestions();
						break;
						
					default:
						printf("Invalid Option!!\n");
						exit(0);
						break;
				}
				break;
			
			case 2:
				viewscoreboard();
				break;
			
			case 3:
				system("clear");
				system("setterm -foreground cyan ");
				system("setterm -bold on");
				printf("\n\t\t\t\t\t1. Take Quiz.");
				printf("\n\t\t\t\t\t2. Read and Learn.\n");
				system("setterm -foreground green ");
				printf("\n\n\t\t\t\t\tEnter your choice:");
				scanf("%d",&choice2);
				if(choice2==1)
				{
					choosesubject();
				}
				else
				{
					readmaterials();
				}
				system("setterm -bold off");
				break;
				
			case 4:
				exit(1);	
				break;
			
			default:
				printf("Invalid Option!!");
				exit(0);
				break;
		}
	}
}






