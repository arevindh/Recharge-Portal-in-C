/* 
login system 
date 2/9/14
*/

#include<stdio.h>
#include<conio.h>
#include<string.h>

typedef struct
{
	char username[30];
	char password[30];
} login;

int checklogin(void);

login ulog={{"admin"},{"pass"}};

void main()

{
clrscr();
if(checklogin()==1)
	{
	printf("\nLogin Success");
	}
else
	{
	printf("\n Opps.. You Missed !!");
	}
getch();
}

int checklogin()
{
	char ch,user[30],pass[30]={0};
	int i;
	clrscr();
	printf("\n---------------------------------");
	printf("\nLogin to OxyPay");
	printf("\n\nEnter your Username\t:\t");
	gets(user);
	printf("\nEnter your password  \t:\t ");
	i=-10;
	while(1)
{
	if(i<0)
		{
		i=0;
		}
	ch=getch();
	if(ch==13)
		{
		break; /*13 is ASCII value of ENTER*/
		}
	if(ch==8) /*ASCII value of BACKSPACE*/
	{
		putch('\b');
		putch(NULL);
		putch('\b');
		--i;
		continue;
	}

	pass[i++]=ch;
	ch='*';
	putch(ch);

	}
	pass[i]='\0';
	clrscr();
	printf("\n\nPlease wait");
	for (i=1;i<5;i++)
	{
		sleep(1);
		printf(".");
		fflush(stdout);
	}
	clrscr();
	if(strcmp(ulog.username,user)==0 && strcmp(ulog.password,pass)==0)
	{
	return(1);
	}
	else
	{
	return(0);
	}
}
