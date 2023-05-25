//Lydia Kim
//COEN 11L
//Lab 5
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
		int check,size;
        	char search[20];
		NODE *temp,*p,*q;
		p=q=head;//initializes to 1st node 

		if((temp = (struct node*)malloc(sizeof(struct node)))==NULL)
		{ 
			printf("Cannot allocate memory\n");
			return;
		}
		

		printf("Enter your name.\n");
		scanf("%s", search);
		check=checkduplicate(search);
		
		if (check == 0)//if name has not been used  
		{
			strcpy(temp->names,search);//stores name in temp
			printf("How many people are coming?\n");
			scanf("%d", &size);
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
				p= p->next;
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
		if (head==NULL)
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
	}
	void searchsize()
	{
		int flag,search;
		struct node *p=head;

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
