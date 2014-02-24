#include<stdio.h>
#include<conio.h>
#include<time.h>

typedef struct
{
	char provider_name[15];
	int id;
} mob_provider;


mob_provider provider[3]={ {"BSNL",1},{"Idea",2},{"Vodafone",3}};

typedef struct
{
	char provider_name[15];
	int id;
} dth_provider;

dth_provider dt_provider[3]={ {"Sun Direct",1},{"DishTV",2},{"Tata Sky",3}};

typedef struct
{
 char mobtype[50];
 int id;
}data;
data d[10]={ {"DATA RECHARGE",1},{"MOBILE RECHARGE",2},{"DTH RECHARGE",3} };

typedef struct
{
int prov_id;
int typeid;
int type; // 1 - top-up  , 2- flexi
char mobno[20];
int amt;
}mobile;

typedef struct
{
int provider_id;
char cardno[15];
int amt;
}dth;
dth dt;

mobile mob;
void valid(char);
void typemob(void);
int len,pin,i,n;
int bal=1000;
char c;
void main()
{
//int i,pin;

FILE *fp;
time_t rawtime;
struct tm * timeinfo;
time ( &rawtime);
timeinfo=localtime( &rawtime);



clrscr();
do
{
printf("Select your recharge type\n");
for(i=0;i<3;i++)
	printf("%d : %s\n",d[i].id,d[i].mobtype);
printf("\nSelect : ");
scanf("%d",&mob.typeid);


if(mob.typeid==1)
{
	printf("\nSelect Your provider : \n");
	for(i=0;i<3;i++)
	{
	printf("%d : %s\n",provider[i].id,provider[i].provider_name);

	}
	printf("\nSelect : ");
	scanf("%d",&mob.prov_id);

   typemob();
   valid('D');
}

else if(mob.typeid==2)
{
	printf("\nSelect Your provider : \n");
	for(i=0;i<3;i++)
	{
	printf("%d : %s\n",provider[i].id,provider[i].provider_name);

	}
	printf("\nSelect : ");
	scanf("%d",&mob.prov_id);

	typemob();
	valid('M');
}
else if(mob.typeid==3)
{
    if(bal>200)
    {

	printf("\nSelect Your provider : \n");
	for(i=0;i<3;i++)
	{
	printf("%d : %s\n",dt_provider[i].id,dt_provider[i].provider_name);

	}
	scanf("%d", &dt.provider_id);
	printf("Enter the 16 digit number\n");
	scanf("%s", &dt.cardno);
	n=strlen(dt.cardno);
	printf("Enter the amount \n");
	scanf("%d",&dt.amt);
	if(n==16)
	{
	sleep(5);
	fflush(stdout);

	printf("\nDTH Recharged successfully\n");
	fp=fopen("dth.db", "a");
		if(fp == NULL)
			exit(-1);
	fprintf(fp,"%d ",dt.provider_id);
	fprintf(fp,"%s ",dt.cardno);
	fprintf(fp,"%d ",dt.amt);
	fprintf(fp,"%s",asctime(timeinfo));
	fclose(fp);

	}
	else
	{
	printf("Please enter a valid card number\n");
	}

    }
    else
    {
	printf("\n You dont have enough balance\n");
}   }

printf("\nDo you want to recharge again?\n");
scanf(" %c",&c);
clrscr();
}
while(c=='y'||c=='Y');

getch();

}

void valid(char choice)
{

FILE *fp;
time_t rawtime;
struct tm * timeinfo;
time ( &rawtime);
timeinfo=localtime( &rawtime);

 if(len==10)
{
  printf("\nEnter the amount\n");
  scanf("%d",&mob.amt);
   bal=bal-mob.amt;
if(bal>100)
{
pin :
printf("\nEnter PIN\n");
scanf("%d",&pin);
if( pin == 1430)
	{
	printf("\nProcessing Payment");
	sleep(5);
	fflush(stdout);
	printf("\nDone\n");
	fp=fopen("mobile.db", "a");
		if(fp == NULL)
			exit(-1);
	fprintf(fp,"%c ",choice);
	fprintf(fp,"%d ",mob.prov_id);
	fprintf(fp,"%s ",mob.mobno);
	fprintf(fp,"%d ",mob.amt);
	fprintf(fp,"%s",asctime(timeinfo));
	fclose(fp);
	}
	else
  {
   printf("\nInvalid PIN !");
   goto pin;
  }

}
if(bal==100&&bal<100)
 printf("Not sufficient balance\n");
}
else
{
 printf("Please enter a valid number :.\n");
 typemob();
}
}
void typemob()
{
printf("\nEnter your mobile number\n");
scanf("%s",mob.mobno);
len=strlen(mob.mobno);
}


