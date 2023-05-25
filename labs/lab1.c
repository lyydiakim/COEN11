//LAB1 DIVISION TEST
//Lydia Kim	
//COEN 11L, TUES. 5:15

#include<stdio.h> 

int division(int,int);
int main()
{
	int quotient,divisor,result,i;
	int count=0;					

	srand ((int) time (NULL));				//makes random numbers not repeat
	
   	for (i=0; i<10; i++)					
	{
		quotient = rand () % 13;			//random # from 0-12
		divisor = rand() % 12+1;			//dividend is not divisble by 0, so +1 makes range b/w 1-12
		result = division(quotient,divisor);
		
		if (result == 1)
		{
			printf("\nCorrect.\n");
			count++;				
		}
		else
		{
			printf("\nIncorrect.\n");
			printf("%i is answer\n", quotient);	//displays correct answer
		}
	}	

	printf("Score: %i / 10. \n", count);			//shows total score out of 10
	return 0;
}

int division(q,dr)
{
	int dividend,guess;
	dividend = q*dr;			

	printf("The divisor is %i\n", dr);	//divisor=denominator
        printf("The dividend is %i\n", dividend);   
	printf("Quotient? ");				
	scanf("%i",&guess);				//need '&' bc integer
	
	if (guess == q)
		return 1;
	else
		return 0;
}
