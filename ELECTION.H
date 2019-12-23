#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
//Global Declaration of Variables
int flag=0,fptr,*ptr,rno,year,maxrollno,cnt=0,false1=0;
int num1;
char branch[6],br1[6];

//Structure that holds candidate name and count of vote
typedef struct cand
{
	 char nm[20];
	 int count;
}CAND;
CAND *a;
//fn to store names of candidates standing for election

void candname(CAND *a)
{
	FILE*f1;
	printf("Enter Candidate name:");
	scanf("\n");
	gets(a->nm);
	a->count=0;

	//Names are stored in text file
	f1=fopen("PreviousElection.txt","r+");
	fseek(f1,0,SEEK_END);
	fprintf(f1,"\n%s",a->nm);
	fptr=ftell(f1);
	fclose(f1);

}
//fn that creates number of files equal to number of candidates

void flcreate(int no)
{
	FILE *fp;
	int i;
	char text[20];
	//clrscr();

	for(i=1;i<=no;i++)
	{
		sprintf(text,"a%d.txt",i);
		fp=fopen(text,"w");
		fprintf(fp,"0\n");
		fclose(fp);
	}
}

//fn to check valid PRN
int isSpecial(char prn[15])
{
	FILE *fp;
	char sprn[15];
	fp=fopen("blank.txt","r");
	while(feof(fp)==0)
	{
	       fgets(sprn,99,fp);
		sprn[14]='\0';
		if(strcmp(sprn,prn)==0)
			return 1;
	}
	fclose(fp);
	return 0;
}

int isAuthentic(char prn[15])
{
	int i=0,j=0,no=0,yr=0;
	char br[6];
	char d;
	while(i<4)
	{
		d=prn[i];
		yr=(yr*10)+(d-48);
		i++;
	}
	if(yr!=year)
	{
		printf("\n  Invalid PRN(Incorrect Year)");
		return 0;
	}
	num1=yr;
	while(i<9)
	{
		br[j]=prn[i];
		j++;
		i++;
	}
	br[j]='\0';
	strcpy(br1,br);
	if(strcmp(br,branch))
	{
		printf("\n  Invalid PRN(Incorrect Branch)");
		return 0;
	}
	while(i<14)
	{
		d=prn[i];
		no=(no*10)+(d-48);
		i++;
	}
	if(no>maxrollno||no<0)
	{
		printf("\n  Invalid PRN(Incorrect Number)");
		return 0;
	}
	rno=no;
	return 1;
}

//fn to delete illegal vote
void delFromfile(char sprn[15],int fno)
{
	FILE*fp;
	int i=0,no,k=0,r=0,j=0,pos=0,flg=1;
	char str[16],vprn[16],text[20];
	//clrscr();
	no=cnt;
	if(flag!=1)
	{
		sprintf(text,"a%d.txt",fno);
		fp=fopen(text,"r");
		while(1)
		{
			fgets(str,99,fp);
			for(i=0;i<(strlen(str)-1);i++)
				vprn[i]=str[i];
			vprn[i]='\0';
			if(strcmp(sprn,vprn)==0)
			{
				pos=ftell(fp);
				fclose(fp);
				fp=fopen(text,"r+");
				fseek(fp, pos, SEEK_SET);
				fseek(fp, -16, SEEK_CUR);
				for(j=0;j<14;j++)
					fprintf( fp ,"%d", r);
				printf("\nVote for the PRN %s removed successfully",sprn);
				false1++;
				(a+fno-1)->count--;
				fseek(fp,0,SEEK_SET);
				fprintf(fp,"%d",(a+fno-1)->count);
				fclose(fp);
				getch();
				return;
			}
			if(feof(fp))
			{
				printf("\nNot Found");
				getch();
				fclose(fp);
				break;
			}
		}
	}
	else
	{
	while(k<no)
	{
		sprintf(text,"a%d.txt",k+1);
		fp=fopen(text,"r");
		flg=1;
		while(flg)
		{
			if(fp==NULL)
				printf("File Doesn't Exist");
			fgets(str,99,fp);
			for(i=0;i<(strlen(str)-1);i++)
					vprn[i]=str[i];
			vprn[i]='\0';
			if(strcmp(sprn,vprn)==0)
			{
				pos=ftell(fp);
				fclose(fp);
				fp=fopen(text,"r+");
				fseek(fp, pos, SEEK_SET);
				fseek(fp, -16, SEEK_CUR);
				for(j=0;j<14;j++)
					fprintf( fp ,"%d", r);
				(a+k)->count--;
				fseek(fp,0,SEEK_SET);
				fprintf(fp,"%d",(a+k)->count);
				fclose(fp);
				printf("\nVote for the PRN %s removed successfully",sprn);
				flg=2;
				false1++;
				break;
			}
			if(flg==2)
				break;
			if(feof(fp))
			{
				if(k==(no-1))
					printf("Not Found");
				flg=0;
				fclose(fp);
			}
		}
		k++;

	 }
	 }
	getch();
}


//Admin Panel
void admin()
{
	FILE* f1,*fp,*fpb;
	char user[15],pass[15],prn[15],text[20],nm[50],ch,sp;
	char str1[6]="Admin";
	char str2[8]="SR@3111";
	int i,no,yr,n,j,max,opt,no1;
	float tot=0.0;
	char null[2]="0";
	while(1)
	{
		//clrscr();
		printf("\nEnter username: ");
		scanf("%s",user);
		if((strcmp(user,str1))!=0)
		{
			printf("Wrong Username");
			getch();
			continue;
		}
		else
		{       password:
			printf("Enter Password: ");
			for(i=0;i<7;i++)
			{
				pass[i]=getch();
				printf("%c",'*');
			}
			pass[i]='\0';
			if((strcmp(pass,str2))!=0)
			{
				printf("\nWrong Password\n");
				getch();
				goto password;
			}
			else
			{

			printf("\n\nADMIN LOGIN SUCCESSFULL(Press Enter)");
			getch();
			while(1)
			{
				//clrscr();
				printf("\n1.New Election\n2.Continue Previous Election\n3.Delete Illegal Vote\n4.Result\n5.Logout\nOption:");
				scanf(" %c",&ch);
				switch(ch)
				{
					//TO TAKE NEW ELECTION
				  case '1':
					//clrscr();
					printf("\nNew Election Initiation:\n");
					f1=fopen("PreviousElection.txt","w");
					printf("\nElections for which Year: ");
					scanf("%d",&year);
					printf("Enter branch code:");
					scanf("%s",branch);
					printf("Enter max roll no.:");
					scanf("%d",&maxrollno);
					printf("Enter the no. of candidates:");
					scanf("%d",&no);
					ptr=(int*)malloc((maxrollno)*sizeof(int));
					for(i=0;i<maxrollno;i++)
						ptr[i]=0;
					fprintf(f1,"%d\n%s\n%d\n%d",year,branch,maxrollno,no);
					fclose(f1);
					flcreate(no);
					a=(CAND *)malloc(no*sizeof(CAND));
					cnt=no;

				       i=0;j=1;
				       while(i<no)
				       {
						printf("\n  %d.",j);
						candname((a+i));
						i++;j++;
					}

					while(1)
					{
					//clrscr();
					printf("\nPress 1 to exclude special PRNs\n(Press 0 to exit)");
					printf("\nOption:");
					scanf(" %c",&sp);
					if(sp=='0')
						return;
					else{
					if(sp=='1')
					{
							fpb=fopen("blank.txt","w");
							if(fpb==NULL)
							{
								printf("\nProcess Failed");
								getch();
								break;
							}
							printf("\nEnter 0 to stop\nEnter blank");
							while(strcmp(prn,null)!=0)
							{
								printf("PRN:");
								scanf("%s",prn);
								fprintf(fpb,"%s",prn);
								fputs("\n",fpb);
								printf("\n");
							}
							sprintf(prn,"null");
							fclose(fpb);
					 }
					 else
					 {
							printf("\nInvalid option");
							getch();
					 }
					 }
					 }

					return;


				//TO CONTINUE PREVIOUS ELECTION
				case '2':
					f1=fopen("PreviousElection.txt","r");
					if(f1==NULL)
						printf("Not Exist");
					fscanf(f1,"%d",&year);
					fseek(f1,2,SEEK_CUR);
					fscanf(f1,"%s",branch);
					fseek(f1,2,SEEK_CUR);
					fscanf(f1,"%d",&maxrollno);
					fseek(f1,2,SEEK_CUR);
					fscanf(f1,"%d",&cnt);
					a=(CAND *)malloc(cnt*sizeof(CAND));
					for(i=0;i<cnt;i++)
					{	fseek(f1,2,SEEK_CUR);
						fscanf(f1,"%s",(a+i)->nm);
					}
					fclose(f1);
					flag=1;
					for(i=1;i<=cnt;i++)
					{
						sprintf(text,"a%d.txt",i);
						fp=fopen(text,"r+");
						fscanf(fp,"%d",&((a+i-1)->count));
						fclose(fp);
					}
					printf("Election Continued");
					getch();
					break;

					//TO DELETE VOTE FOR SELECTED PRN
					case '3':
					printf("Search PRN:");
					scanf("%s",prn);
					if(flag!=1)
					{
						if(ptr[rno-1]!=0)
						{	delFromfile(prn,ptr[rno-1]);
							ptr[rno-1]=0;
						}
					}
					else
					{
						delFromfile(prn,ptr[rno-1]);
					}
					break;

				//TO DISPLAY RESULT
				 case '4':
					//clrscr();
					i=0;
					max=(a+i)->count;
					while(i<cnt-1)
					{
						if((a+i)->count>max)
							max=(a+i)->count;
						i++;
					}
					i=0;j=0;
					for(i=0;i<cnt-1;i++)
					{
						if(max==(a+i)->count)
						      j++;
					}
					if(j>1)
						printf("\n\n\n\t\tTIE");
					else
					{
						for(i=0;i<cnt-1;i++)
						{       if(max==(a+i)->count)
							{	printf("\n\n\n\t\t__________________________________________________");
								printf("\n\n\t\t      WINNER is %s with %d votes",(a+i)->nm,(a+i)->count);
								printf("\n\t\t__________________________________________________");
							 }
						}
					}
					tot=0;i=0;
					for(i=0;i<cnt;i++)
						tot+=((a+i)->count);
					printf("\n\n\n\t\t\t   Election statistics:\n");
					i=0;
					while(i<cnt)
					{
						printf("\n\t\t\tVotes for %s= %d",(a+i)->nm,(a+i)->count);
						i++;
					}

					printf("\n\n\t\t\tVoting Percentage:%0.2f %",(tot/maxrollno)*100);
					printf("\n\t\t\tTotal Illegal attempts:%d",false);
					getch();
				      //	flcreate(cnt);
					break;

				case '5':
					return;

				default:
					printf("Invalid Option");
					getch();

				}
			}
		}
	}
}
}

//Student Panel

void stu()
{
	FILE *fp,*f1;
	CAND *b;

	char prn[15],text[20],d;
	char str[16],vprn[16];
	char stp[2]="0";
	int flg=1;
	int len,num,i,opt,j,res,k=0,nos,choice,roll,val;
	char no,v1,v2;

	b=a;

	while(1)
	{
			prn:
			//clrscr();
			printf("\n\n  To exit press 0");
			printf("\n  Please Don't Use Capital Letters");
			printf("\n  Enter PRN no:");
			scanf("%s",prn);
			if(strcmp(stp,prn)==0)
				return;
			len=strlen(prn);
			if(len<14||len>14)
			{
				printf("\nInvalid PRN(Incorrect length)\nTry Again(Press Enter)");
				getch();
				continue;
			}
			val=isSpecial(prn);
			if(val==1)
			{
				printf("\n  Blank number");
				getch();
				false1++;
				continue;
			}
			res=isAuthentic(prn);
			if(res!=1)
			{
				printf("\n  Try Again(Press Enter)");
				getch();
				continue;
			}
			else
			{
				num=cnt;
				if(flag!=1)
				{	if(ptr[rno-1]!=0)
					{
						printf("\n  Your PRN entered is already voted\n  Contact Admin for furthur query");
						getch();
						continue;
					}
				}
				else
				{
				     //	checkfile:
					while(k<num)
					{
						sprintf(text,"a%d.txt",k+1);
						fp=fopen(text,"r");
						flg=1;
						while(flg)
						{
							fgets(str,99,fp);
							for(i=0;i<(strlen(str)-1);i++)
								vprn[i]=str[i];
							vprn[i]='\0';
							if(strcmp(prn,vprn)==0)
							{
								printf("\n  The PRN %s has already voted\nContact Admin if it weren't you...!",prn);
								fclose(fp);
								getch();
								goto prn;
							}
							if(feof(fp))
							{
								flg=0;
								fclose(fp);
							}
						}
						k++;

					 }

				}
				printf("\n\n  Candidates for election:");
				j=1;
				for(i=0;i<num;i++)
				{
					printf("\n  %d. %s",j,(b+i)->nm);
					j++;
				}
				vote :
				 while(1)
				 {
					printf("\n\n  Your Vote(Enter Number):");
					v1=getch();
					printf("*");
					getch();
					printf("\n  Confirm Your Vote:");
					v2=getch();
					printf("*");
					if(v1==v2)
						break;
					else
					{
					  //	getch();
						printf("\n\n   Mismatch(Try Again)");
						continue;
					}
				}

				if((v1-48)>num)
				{
					printf("\n  Invalid vote");
					getch();
					goto vote;
				       //	break;
				}
				else
				{
					printf("\n\nThanks for your precious vote(Press Enter)");


					ptr[rno-1]=(v1-48);
					getch();
					for(j=0;j<num;j++)
					{
						if((v1-48)==(j+1))
						{
							(a+j)->count++;
							sprintf(text,"a%d.txt",(j+1));
							fp=fopen(text,"r+");
							fprintf(fp,"%d",(a+j)->count);
							fseek(fp,0,SEEK_END);
							fprintf( fp ,"%s", prn);
							fputs("\n",fp);
							fclose(fp);
						}
					}
				}
			}

	}

}
