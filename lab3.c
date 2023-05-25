//Lydia Kim
//COEN 11L
//Lab 3
//Tues. 5:15

#include <stdio.h>
#include <string.h>

//global variables
#define SIZE 10
int counter = 0;
struct info 
{
	char names[20];
	int group;
};
struct info x[10];

//function declarations
void insert();
void delete();
void list();
void searchsize();
int checkduplicate(char names[20]);

	int main ()
	{
		int choice;
		while (1)
		{       
			printf("Welcome to Surf Lesson Waiting List!\n");
			printf("(1) Add your name and group size to waiting list.\n");
			printf("(2) Remove appointment.\n");                   
			printf("(3) Show waiting list.\n");                         
			printf("(4) Show entries that are < or = your group size.\n");
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
				case 4: //Shows entries in the list that are < or = to input
					searchsize();
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
		int check;
		struct info *p = &x[0];//sets pointer=1st x array	
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
			check=checkduplicate(search);//sets check=function
			if (check == 0)//if return = 0 
			{
				strcpy(x[counter].names,search);
				printf("How many people are coming?\n");
				scanf("%d",&x[counter].group);

				while (x[counter].group == 0)
				{
					printf("Enter a number > 0.\n");
					scanf("%d", &x[counter].group);
				}
				counter++;
			}

			else
			{	
				printf("The name %s has already been used.\n",search);
				return; 
			}
		}
	}

	int checkduplicate(char *name)
	{
		int i;
		struct info *p = &x[0];
		for (i=0;i<counter;i++,p++)
		{
			if(strcmp(name,p->names)==0)
				return 1;
		}
		return 0;
	}	
	void delete()
	{
		int flag,j,i,sze;
		struct info *p= &x[0];
		struct info *value;
		struct info *q= &x[0];
		printf("How many spots are you opening?\n");
		scanf("%d", &sze);

		if (counter == 0)
		{
			printf("There are no appointments.\n");
			return;
		}
		for (i=0;i<counter;i++,p++)
		{
			if (sze>= p->group)
			{
				sze-= p->group;
				printf("Appointment with Name:%s and Size:%d is removed.\n",p->names,p->group);
				for (j=i;j<counter-1;j++)
				{
					x[j]=x[j+1];
				}
				p--;
				i--;
				flag = 1;
				counter--;
			}
		}		
		if (flag != 1)
		{
			printf("There is no appointment with that size.\n\n");
			return;

		}
	}

	void list()
	{
		int i;
		struct info *p = &x[0];
		if (counter == 0)
			printf("There are no appointments.\n");	
		else
		{
			for (i=0;i<counter;i++,p++) //outputs schedule 
			{
					printf("Name:%s  ",p->names);
					printf("Size:%d\n",p->group);
			}

		}
	}
	void searchsize()
	{
		int flag,search,i;
		struct info *p=&x[0];
		struct info *q=&x[0];
		printf("What is your group size?\n");
		scanf("%d", &search);

		for (i=0; i<counter; i++,p++,q++)
		{
			if(p->group <= search)
			{
				printf("Name:%s  ", q->names);
				printf("Size:%d\n", p->group);
				flag = 1;
			}
		}
		
		if (flag != 1)
			printf("There are no appointment that are <= the group size: %d\n\n",search);
	}
