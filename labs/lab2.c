
//Lydia Kim
//COEN 11L
//Lab 2
//Tues. 5:15

#include <stdio.h>
#include <string.h>

//global variables
#define SIZE 10
int counter = 0;
char names[SIZE][20];
int group[SIZE];

//function declarations
void insert();
void delete();
void list();

	int main ()
	{
		int choice;
		while (1)
		{       
			printf("Welcome to Surf Lesson Waiting List!\n");
			printf("(1) Add your name and group size to waiting list.\n");
			printf("(2) Cancel your appointment.\n");                   
			printf("(3) Show waiting list.\n");                         
			printf("(0) Quit.\n");                                      
			scanf("%d", &choice);
			switch (choice)
			{
				case 1: //add name and group size to end of list
        	                        insert(); 
					break;
	                        case 2: //removes oldest entry w same size as users
					delete();
                	                break;
	                        case 3: //shows list, name and number from old to new
					list();
                	                break;
                        	case 0: //quits program
                                	printf("Program quitting.\n");
	                                return 0;
        	                default:
                	                printf("Invalid option.\n");
                        	        break;
 	               }
        	}

        	return 0;
	}	

	void insert()
	{	
        	char search[20];
		
		if (counter == SIZE)
		{
			printf("The waiting list is full.\n");
			return;
		}
		else 
		{
			printf("Enter your name.\n");
			scanf("%s", search);
			strcpy(names[counter],search);
			printf("How many people are coming?\n");
			scanf("%d",&group[counter]);
			while (group[counter] == 0)
			{
				printf("Enter a number > 0.\n");
				scanf("%d", &group[counter]);
			}
			counter++;
		}
	}
	
	void delete()
	{
		int flag,j,i,sze;
		printf("How many spots are you opening?\n");
		scanf("%d", &sze);

		if (counter == 0)
		{
			printf("There are no appointments.\n");
			return;
		}
		for (i=0;i<counter;i++)
		{
			if (sze>=group[i])
			{
				
				sze-= group[i];
				printf("Appointment with Name:%s and Size:%d is removed.\n",names[i],group[i]);
				for (j=i;j<counter;j++)
				{
					group[j]=group[j+1];//moves size up
					strcpy(names[j],names[j+1]);//moves names up
				
				}
				i--;
			flag = 1;
			counter--;
			}
		}		
		if (flag != 1)
			printf("There is no appointment with that size.\n\n");
	}

	void list()
	{
		int i;
	
		if (counter == 0)
			printf("There are no appointments.\n");	
		else
		{
			for (i=0;i<SIZE;i++) //outputs schedule 
				if (names[i][0]!='\0') 
				{
					printf("Name:%s  ",names[i]);
					printf("Size:%d\n",group[i]);
				}
		}
	}
