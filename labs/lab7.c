//Lydia Kim
//COEN 11L
//Lab 7
//Tues. 5:15

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//global variables
#define NODE struct node 
struct node
{
	char names[20];
	int group;
	NODE *next;
};
NODE *head = (NODE*)NULL;
NODE *tail = (NODE*)NULL;


//function declarations
void insert(char *,int);
void delete();
void list();
void searchsize();
int checkduplicate(char names[20]);
void read_file(char *argv);
void save_file(char *argv);
void quit(char *argv);

int main (int argc, char *argv[])
{
	char search[10];
	int checkname,choice,size;
	
	if (argc == 1) //only 1 argument which is the executable
	{
		printf("Filename missing.\n");
		return;
	}
	read_file(argv[1]);

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
				printf("Enter your name.\n");
				scanf("%s", search);
				checkname=checkduplicate(search);
			
				if (checkname == 0)//if name has not been used  
				{
					printf("How many people are coming?\n");
					scanf("%d", &size);
					insert(search,size); 
				}
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
				quit(argv[1]);
	                        return;
        	        default:
                                printf("Invalid option.\n");
                       	        break;
 	        }
       	}

        	return 0;
}	

void insert(char *search, int size)
{
	NODE *temp;
	if((temp = (struct node*)malloc(sizeof(struct node)))==NULL)
	{ 
		printf("Cannot allocate memory\n");
		return;
	}

	strcpy(temp->names,search);//stores name in temp
	temp->group = size;//stores size in temp
	temp->next = NULL;// bc inserting in end, last memory alloc. must=NULL
	
	if (head == NULL)//if list is empty
	{
		head=tail=temp;
	}
	else//not empty 
	{
		tail->next=temp;///adds temp to the end 
		tail=temp;
	}
}

int checkduplicate(char *name)
{
	NODE *p=head;
	while (p!=NULL)
	{
		if(strcmp(name,p->names)==0)
		{
			printf("That name has already been used.\n");
			return 1;
		}
		p=p->next;
	}
	return 0;
}	

void delete()
{
	int flag,size;
	NODE *p, *q;
	p=q=head;

	printf("How many spots are you opening?\n");
	scanf("%d", &size);

	if (head==NULL)//same as counter == 0
	{
		printf("There are no reservations made.\n");
		return;
	}
	while (p!= NULL && size>0) 
	{
		if (p->group <= size)
		{
			size-=p->group;
			printf("Appointment under Name:%s and Size:%d cancelled.\n\n", p->names, p->group);
			flag = 1;
		
			if (head==tail)//if theres only one node 
			{
				head=tail=NULL;
				free(p);
				break;
			}
			else if (p == head)//delete 1st node
			{
				head = head->next;
				free(p);
				p=q=head;
			}
			
			else if (p == tail)//delete last node 
			{
				q->next=NULL;
				free(p);
				tail=q;
				break;
			}
		
			else //in the middle
			{
				q-> next = p->next;
				free(p);
				p=q->next;

			}
		}

		else 
		{
			q=p;
			p=p->next;
		}
	}

	if (flag!=1) 
	{
		printf("No appointment sizes less than %d\n\n", size);
		return;
	}
}

void list()
{
	NODE *p=head;
	if (head == NULL) 
		printf("There are no appointments.\n");	
	else 
	{
		while(p!=NULL)//outputs schedule 
		{
			printf("Name:%s  ",p->names);
			printf("Size:%d\n",p->group);
			p=p->next;
		}

	}
	return;
}
void searchsize()
{
	int flag,search;
	NODE *p=head;

	printf("What is your group size?\n");
	scanf("%d", &search);

	while (p!=NULL)
	{
		if(p->group <= search)
		{
			printf("Name:%s  ", p->names);
			printf("Size:%d\n", p->group);
			flag = 1;
		}
		p=p->next; 
	}
		
	if (flag != 1)
		printf("There are no appointment that are <= the group size: %d\n\n",search);
}

void read_file (char *argv)
{
	int i,size;
	char name[20];
	FILE *fp;
	NODE *p;
	fp = fopen(argv, "r");
	if (fp == NULL)
	{
		printf("File does not exist.\n");
		return;
	}
	
	else
	{
		fseek(fp,13,SEEK_SET);  
		while (fscanf(fp,"%s  %d",name,&size)==2)
		{
			insert(name,size);
		}
	}
	fclose(fp);
	return;
}

void save_file (char *argv)
{
	FILE *fp;
	NODE *p;
	
	fp = fopen(argv,"w");
	if (fp == NULL)
	{
		printf("File does not exist.\n");
		return;
	}

	p = head;
	fputs("Name   Size \n",fp);
	while (p != NULL)
	{
		fprintf(fp,"%s  %d\n",p->names,p->group);
		p=p->next;
	}

	fclose(fp);
	return;
}

void quit(char *argv)
{
	NODE *p,*q;
	p=head;
	printf("Program quitting.\n");
	save_file(argv);
	
	while (p!=NULL)
	{
		q=p->next;	
		free(p);
		p=q;
	}	
	head=tail=NULL;	
	return;
}
