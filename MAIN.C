#include"ELECTION.H"
int main()
{
	char n;
	//clrscr();
	while(1)
	{
		//clrscr();
		printf("\n\n\t\t\tWelcome to Voting System\n");

		printf("\n\t\t\t   1.Student panel \n\t\t\t   2.Admin panel \n\t\t\t   3.Exit \n\t\t\t   Option:");
		scanf(" %c",&n);


		if(n==49)
				stu();
		else
		{	if(n==50)
				admin();
			else
			{
				if(n==51)
				{
					free(ptr);
					free(a);
					return 0;
				}
				else
				{
					printf("\nInvalid option");
					continue;
				}
			}
		}
	}
	return 0;
}
