#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

void sleep( time_t );
void smsgateway(char sender[10],char pno[16],int amt, int rtype);
void header();
void footer();
void recharge_datacard();
void intro();
void recharge_dth();
void recharge_mobile();
int check_bal(int);
int check_pin();
void read_all_data();
void read_all_data_dth();
void load_balace();
void save_balace();

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
data d[10]={ {"DATA RECHARGE",1},{"MOBILE RECHARGE",2},{"DTH RECHARGE",3},{"SHOW TRANS",4},{"DTH TRANS",5},{"ABOUT",6},{"EXiT PrOGrAM",7} };

typedef struct
{
    int amt;
    char s_provider[15];
    char type[10];
    char mobno[20];
    char time[26];

}mobile;
mobile mob;




void valid(char);
void typemob(void);
//int len,pin,i,n;
int bal=1000;
char c;
struct tm * timeinfo;
int main()
{


    int i,id;
    char mobile[10];
    FILE *fp;
    time_t rawtime;
   // struct tm * timeinfo;
    time ( &rawtime);
    timeinfo=localtime( &rawtime);
    intro();
    load_balace();
    starts :

	system("cls");
do
{
    header();
    printf("\n\tSelect your recharge type\n\n");
    for(i=0;i<7;i++)
	printf("\t%d : %s\n",d[i].id,d[i].mobtype);
    printf("\n\tSelect : ");
    scanf("%d",&id);


    switch(id)
    {
	case 1 : recharge_datacard(); break;
	case 2 : recharge_mobile(); break;
	case 3 : recharge_dth(); break;
	case 4 : read_all_data(); break;
	case 5 : read_all_data_dth(); break;
	case 6 : intro(); break;
	case 7 : exit(0); break;
	default : goto starts;
    }

    getch();
    system("cls");

}while(1);

//getch();
//return(0);

}

void recharge_mobile()
    {
	int i,len,id,eror;
	FILE *fp;
	// time start
time_t rawtime;
   // struct tm * timeinfo;
    time ( &rawtime);
    timeinfo=localtime( &rawtime);

        // time end

            printf("\n\tSelect Your provider \n");
            for(i=0;i<3;i++)
            {
                printf("\t%d : %s\n",provider[i].id,provider[i].provider_name);

            }
            enter_id :
            printf("\n\tSelect : ");
            scanf("%d",&id);
            if(id<1 || id > 3)
            {
                goto enter_id;
            }

            strcpy(mob.s_provider,provider[id-1].provider_name);
            strcpy(mob.type,"Mobile");

			redo :
            printf("\n\tEnter your mobile number  : ");
            scanf("%s",mob.mobno);
            len=strlen(mob.mobno);
            printf("\n\tEnter the amount          :");
            scanf("%d",&mob.amt);
			//check PIN
			if(check_pin()!=1)
				{
					printf("]\n\tIncorrect PIN !");
					goto redo;
				}
			//Check Bal
			if(check_bal(mob.amt)!=1)
				{
					printf("\n\tNot sufficient balance !");
					goto redo;
				}
			//Check Length
			if(len!=10)
				{
					printf("\n\tPlease enter a valid number :.\n");
					goto redo;
				}

            if(1)
            {

                printf("\n\tProcessing Payment");
                sleep(5);
                fflush(stdout);


                //sent sms
                smsgateway(mob.mobno,mob.mobno,mob.amt,1);
                //strcpy(mob.time,asctime(timeinfo));
                sprintf(mob.time,"%s",asctime (timeinfo));
                printf("\n\n\tMobile Recharged Successfully \n");
                bal-=mob.amt;
				fp=fopen("recharge.txt", "a");
					if(fp == NULL)
                        printf("\n\tError\n");

                mob.time[24]='\0';

                

				fwrite(&mob,sizeof(mob),1,fp);
				save_balace();
				
                fclose(fp);


			}

    }

void recharge_datacard()
    {
	int i,len,id,eror;
	FILE *fp;
	// time start
    time_t rawtime;
   // struct tm * timeinfo;
    time ( &rawtime);
    timeinfo=localtime( &rawtime);
        // time end

            printf("\n\tSelect Your provider \n");
            for(i=0;i<3;i++)
            {
                printf("\t%d : %s\n",provider[i].id,provider[i].provider_name);

            }
            enter_id :
            printf("\n\tSelect : ");
            scanf("%d",&id);
            if(id<1 || id > 3)
            {
                goto enter_id;
            }

            strcpy(mob.s_provider,provider[id-1].provider_name);
            strcpy(mob.type,"Data Card");

			redo :
            printf("\n\tEnter your mobile number  :");
            scanf("%s",mob.mobno);
            len=strlen(mob.mobno);
            printf("\n\tEnter the amount          :");
            scanf("%d",&mob.amt);
			//check PIN
			if(check_pin()!=1)
				{
					printf("]\n\tIncorrect PIN !");
					goto redo;
				}
			//Check Bal
			if(check_bal(mob.amt)!=1)
				{
					printf("\n\tNot sufficient balance !");
					goto redo;
				}
			//Check Length
			if(len!=10)
				{
					printf("\n\tPlease enter a valid number :.\n");
					goto redo;
				}

            if(1)
            {

                printf("\n\tProcessing Payment");
                sleep(5);
                fflush(stdout);


                //sent sms
                smsgateway(mob.mobno,mob.mobno,mob.amt,2);
                //strcpy(mob.time,asctime(timeinfo));
                sprintf(mob.time,"%s",asctime (timeinfo));
                printf("\n\n\tDatacard Recharged Successfully \n");
                bal-=mob.amt;
				fp=fopen("recharge.txt", "a");
					if(fp == NULL)
                        printf("\n\tError\n");

                mob.time[24]='\0';

                

				fwrite(&mob,sizeof(mob),1,fp);
				save_balace();
				//printf("\n%s %d\n",mob.time,mob.amt);
                fclose(fp);


			}

    }

// DTH RECHARGE
void recharge_dth()
{       int i,id;
	char mobile[10];
	int n,eror;
	FILE *fp;

    time_t rawtime;
    // struct tm * timeinfo;
    time ( &rawtime);
    timeinfo=localtime( &rawtime);
	header();
	    printf("\n\tSelect Your provider : \n");
	    for(i=0;i<3;i++)
		{

		    printf("\t%d : %s\n",dt_provider[i].id,dt_provider[i].provider_name);

		}
		printf("\n\tEnter Choice : ");
	    scanf("%d", &id);

	    strcpy(mob.s_provider,dt_provider[id].provider_name);
	    strcpy(mob.type,"DTH");

	    entercard :
	    printf("\n\tEnter the 16 digit number  : ");
	    scanf("%s", &mob.mobno);
	    n=strlen(mob.mobno);

	    printf("\n\tEnter the amount           : ");
	    scanf("%d",&mob.amt);

	    printf("\n\tEnter your mobile number   : ");
	    scanf("%10s",mobile);

	if(check_bal(mob.amt)==1)
	{
	    if(n==16)
	    {
		sleep(2);
		fflush(stdout);
		smsgateway(mobile,mob.mobno,mob.amt,3);
		
		sprintf(mob.time,"%s",asctime (timeinfo));
		printf("\n\\\tDTH Recharged successfully\n");
		bal-=mob.amt;
		
        mob.time[24]='\0';
		fp=fopen("recharge.txt", "a");
		    if(fp == NULL)
			 printf("\n\tError\n");
		fwrite(&mob,sizeof(mob),1,fp);
		save_balace();
		fclose(fp);
	    }
	    else
	    {
		printf("\n\tPlease enter a valid card number ");
	        goto entercard;
	    }

	}
    else
	{
	    printf("\n\tYou dont have enough balance\n");
	}


}


void sleep( time_t delay )
    {
	time_t timer0, timer1;
	time( &timer0 );
	do
	    {
	    time( &timer1 );
	    } while (( timer1 - timer0 ) < delay );
    }

void smsgateway(char sender[10],char pno[16],int amt, int rtype)
    {
	char msg[100],no[4],ctype[2];
	strcpy(msg,"php sendsms.php ");
	strcat(msg,sender);
	strcat(msg," ");
	pno[16]='\0';
	strcat(msg,pno);
	strcat(msg," ");
	sprintf(no, "%d", amt);
	strcat(msg,no);
	sprintf(ctype, "%d", rtype);
	strcat(msg," ");
	strcat(msg,ctype);
	strcat(msg," \0");
	//printf("\n\t%s",msg);
	//sent sms
	system(msg);
    }

void header()
{
    system("cls");
    printf("\n\t================================================================\n");
    printf("\n\t==================   Welcome to Oxypay    ======================\n");
    printf("\n\t================================================================\n");
    printf("\n\n");
}
void footer()
{
    printf("\n\t===============================================================\n");
    printf("\n\t=====================   By Mary & Sid  ========================\n");
    printf("\n\t===============================================================\n");
    printf("\n\n");
}

int check_bal(int camt)
{       int cal;
	cal=bal-camt;
    if(cal > 100)
	return(1);
    else
	return(0);
}
int check_pin()
{
    int pin;
    printf("\n\tEnter PIN : ");
    fflush(stdin);
    scanf("%d",&pin);
    if( pin == 1430)
	{
	    return(1);
	}
    else
	  {
	   return(0);
	  }
}


void read_all_data()
{
    FILE *fp;
    fp=fopen("recharge.txt","r");
    header();
    printf("\n\t Current Balance : %d \n",bal);
    printf("\n\t%10s %10s %8s %26s %5s\n","User id /no ","Type","Provider","Timestamp","Amount");
    while( (fread(&mob,sizeof(mob),1,fp)) == 1)
    {
        if(strcmp(mob.type,"DTH")!=0)
            printf("\n\t%10s %10s %8s %26s %5d",mob.mobno,mob.type,mob.s_provider,mob.time,mob.amt);
    }
    fclose(fp);

}

void read_all_data_dth()
{
    FILE *fp;
    fp=fopen("recharge.txt","r");
    header();
    printf("\n\t%16s %8s %26s %5s\n","User id /no ","Provider","Timestamp","Amount");
    while( (fread(&mob,sizeof(mob),1,fp)) == 1)
    {   if(strcmp(mob.type,"DTH")==0)
            printf("\n\t%16s %8s %26s %5d",mob.mobno,mob.s_provider,mob.time,mob.amt);
    }
    fclose(fp);

}

void intro()
{
    header();
    printf("\n\n\tTHis program is written by SiD and Mary \n\n");



printf("\n\t         :';`                     ;;;;                                   ");
printf("\n\t       ';;;;;;                   :;;:                                    ");
printf("\n\t     ,:;;;;;;;:                 :;;;`                                    ");
printf("\n\t  ;;;;;;;;;;;;;;               ;::.'                                     ");
printf("\n\t  ;;;;;;;:::;;;;              ;;  ;;;                                    ");
printf("\n\t  ;;',;;;   ;;;;'            ;;;.;;;`                                    ");
printf("\n\t  `,';;:     ;;;;           ;;;;;;;                                      ");
printf("\n\t  ;;;;;:     ;;;:          ';;;'                                         ");
printf("\n\t  ;;;;:      ;;;; '''+    ';;;'+'''  '''' ;'.      ';' +''' ''''     '''+");
printf("\n\t ';;;;;      ;;;; ;;;;   ';;;' :;;; `;;;';;;;'   `:;;;;;;;; ;;;;    ';;; ");
printf("\n\t ;;;;;      .;;;: ,;;;; ';;;'  ;;;' ;;;;;;;;;;   ;;;;;;;;;' ';;;   `;;;' ");
printf("\n\t :;;;;      ';;;;  :;;;;;;;;  :;;;, ;;;;;,,;;;; ;;;;';;;;;` ';;;`  ;;;:  ");
printf("\n\t ;;;;'      ;;;;'  ';;;;;;;   ;;;;  :;;;,  ;;;':;;;'  ;;;;  ;;;;, ;;;;;  ");
printf("\n\t ;;;;:     `;;;;.   ;;;;;;    :;;; `;;;;   ;;;';;;:   ;;;;  :;;;; ;;;;   ");
printf("\n\t ;;;;.     ';;;:    ;;;;:     ;;;' ';;;:  `;;;:;;;'   ;;;'  .;;;'';;;    ");
printf("\n\t ;;;;.     ;;;;'   `;;;;'    ';;;, ;;;;   ';;;:;;;.  ';;;`   ;;;';;;'    ");
printf("\n\t :;;;:    ;;;;:    ;;;;;:    ;;;;  ;;;;   ;;;;;;;;   :;;;    ;;;;;;:     ");
printf("\n\t ';;;;   ';;;;:   :;;;;;;:   :;;; .;;;;` ;;;;,;;;;, ;;;;;    ;;;;;;:     ");
printf("\n\t  ;;;;',;;;;;'   :;;;.;;;;  `;;;' ';;;;;;;;;; ,;;;;;;;;;;;   :;;;;;      ");
printf("\n\t  ';;;;;;;;;;   ;;;;, ';;;  ;;;;. ;;;;;;;;;;   :;;;;;;;;;;   ;;;;;`      ");
printf("\n\t   ;;;;;;;;'   ;;;;:   ;;;' ;;;;  ;;;;';;;;    :;;;;+;;;;;   ;;;;'       ");
printf("\n\t    ':;;;;.   ;;;;;    ```` .... .;;;;  .        ;:  `''     ;;;:        ");
printf("\n\t             ';;;'               ';;;`                      ;;;;:        ");
printf("\n\t            ';;;'                ;;;:                    ';;;;;;         ");
printf("\n\t           ';;;'                 ;;;;                   .;;;;;;          ");
printf("\n\t          ';;;;                 .;;;;                   ;;;;;'           ");
printf("\n\t         ;;;;;                  ';;;                     ';'`            ");

printf("\n\n");
footer();

sleep(5);


}

void load_balace()
{
    FILE *fp1;
    fp1=fopen("balacedb.txt","r");
        if(fp1==NULL)
        {
            fp1=fopen("balacedb.txt","w+");
            fprintf(fp1,"%d",100);
        }
        else
            fscanf(fp1,"%d",&bal);

    fclose(fp1);
}

void save_balace()
{   FILE *fp1;
    fp1=fopen("balacedb.txt","w+");
    fprintf(fp1,"%d",bal);
    fclose(fp1);
    printf("\n\tBalance : %d",bal);
}
