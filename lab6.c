//Lydia Kim
//COEN 11L
//Lab 6
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
struct list 
{
	NODE *head; 
	NODE *tail;
};

struct list reserve[4] = {{NULL,NULL}, {NULL,NULL} , {NULL,NULL} , {NULL,NULL}};

//function declarations
void insert(void);
void delete(void);
void list(void);
void searchsize(void);
int checkduplicate(char names[20]);
void freenodes(void);
int category (int);

	int main (void)
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
				case 3: //shows lists 1-4
					list();
					break;
				case 4: //Shows entries in the list that are < or = to input
					searchsize();
					break;
				case 0: //quits program
					freenodes();
					printf("Program quitting.\n");
					return 0;
				default:
					printf("Invalid option.\n");
					break;
 	               }
		}

      	  	return 0;
	}	

	void insert(void)
	{
		int check,size,sze;
     	  	char search[20];
		NODE *temp;

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
			strcpy(temp->names,search);//store name

			printf("How many people are coming?\n");//store size
			scanf("%d", &size);
			if (size<=0)
			{	printf("Must be greater than 0.\n");
				return;
			}
			sze = category(size);
			temp->group = size;

			temp->next = NULL;// bc inserting in end, last memory alloc. must=NULL
				
	 		if (reserve[sze].head == NULL)//if list is empty
			{
				reserve[sze].head = reserve[sze].tail=temp;
			}
			else//not empty 
			{
				reserve[sze].tail->next=temp;///adds temp to the end 
				reserve[sze].tail=temp;
			}
			
		
		}
	}

	
	int checkduplicate(char *search)
	{
		int i;
		NODE *p;
		for (i=0;i<4;i++)
		{
			p=reserve[i].head;
			while (p!=NULL)
			{
				if(strcmp(search,p->names)==0)
				{
					printf("That name has already been used.\n");
					return 1;
				}
				p=p->next;
			}
		}
		return 0;
	}	
	void delete(void)
	{
		int i,size,sze,counter=0,flag=0;
		NODE *p, *q;

		for(i=0;i<4;i++)
		{
			if (reserve[i].head==NULL)//if list is empty
				counter++;
		}
		if (counter == 4)
		{
			printf("There are no reservations made.\n");
			return;
		}

		else 
		{ 
			printf("How many spots are you opening?\n");
			scanf("%d", &size);
		
			sze = category(size);

			for (i=0;i<=sze;i++)
			{
				p=q=reserve[i].head;
				while (p != NULL && size > 0)
				{
					if (p->group <= size)
					{
						size -= p->group;
						printf("Appointment under Name:%s and Size:%d cancelled.\n\n", p->names, p->group);
						flag = 1;
			
						if (reserve[i].head == reserve[i].tail)//if theres only one node 
						{
							reserve[i].head = reserve[i].tail = NULL;
							free(p);
							break;
						}
						else if (p == reserve[i].head)//delete 1st node
						{
							reserve[i].head = p->next;
							free(p);
							p = q = reserve[i].head;
						}
			
						else if (p == reserve[i].tail)//delete last node 
						{
							reserve[i].tail = q;
							q->next = NULL;
							free(p);
							break;
						}
				
						else //in the middle
						{
							q->next = p->next;
							free(p);
							p = q->next;

						}
					}
					else 
					{
						q = p;
						p = p->next;
					}
				}
			}
		}

		if (flag != 1) 
		{
			printf("No appointment sizes less than %d\n\n", size);
			return;
		}
	}

	void list(void) 
	{
		int i,counter;
		NODE *p,*q;

		for(i=0;i<4;i++)
		{	
			q=reserve[i].head;
			if (q==NULL)
				counter++;
		}
		if (counter==4)	
			printf("There are no appointments.\n");	
		else
		{
			for (i=0;i<4;i++)
			{
				p=reserve[i].head;
				if (reserve[i].head == NULL)
				{
					printf("\nLIST %d is empty.\n", i+1);	
					continue;
				}
				printf("\nLIST %d:\n",i+1);
				while(p!=NULL)//outputs schedule 
				{
					printf("Name:%s  ",p->names);
					printf("Size:%d\n",p->group);
					p=p->next;
				}
			}	
		}
	}
	void searchsize(void)
	{
		int i,flag,search,sze;
		NODE *p; 

		printf("What is your group size?\n");
		scanf("%d", &search);
		sze = category(search);
		for (i=0;i<=sze;i++)
		{
			p=reserve[i].head;
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
		}	
		if (flag != 1)
			printf("There are no appointment that are <= the group size: %d\n\n",search);
	}

	void freenodes(void)
	{
		int i;
		NODE *p,*q;

		for (i=0;i<4;i++)
		{
			p=reserve[i].head;
			while (p!=NULL)
			{
				q=p->next;
				free(p);
				p=q;
			}
		}
	}

	int category (int size)
	{
		int sze;
		if (size >=1 && size <=2 )
			sze = 0; 
		if ( size >=3 &&  size <=4 )
			sze = 1;
		if ( size >=5 && size <=6 )
			sze = 2;
		if ( size > 6)
			sze = 3; 
		return sze;
	}
