#include "filewrite.h"
#include "spotmenu.h"
extern unsigned char buf_weldpara[30*SIZE_WELDBUFF];
extern QVector<int> FstU, FstI, FstDeltaI, FstDeltaT, HafU, HafI, HafDeltaI, HafDeltaT,HafCycCount;
extern QVector<double>  Avg_U, Avg_I;
extern QVector<double> WeldTime;
extern QVector<double> R,L;
extern QVector<double> R_Avg;
extern QVector<int> duty_num;
extern QVector<double> Power;
extern QVector<double> Heat_Input;
extern QVector<int> I_AC,U_AC,UP_AC,fire_fai,conduct_theta,Data_Index;
extern int write_end_AC;
extern QVector<int> flag_1;
extern QVector<int> flag_2;
extern int Normal_or_Instant_or_AC,Instant_mode,Instant_halfcycCnt;
extern int CarType,CarNum,GroupNum,ProcessType,SpotNum,VoltRatio,CurRatio;
extern QVector<int> Instant_Curr,Instant_Volt,Instant_value;
extern int NeedCalcDetail,halfcyccount,temp_halfcyccount;
extern int last_rcv;
extern int rcvSPIdata_len;
extern int fd_calc;
extern int Volt_base,Cur_base;
extern int oversample;
int write_num(int fd,int num)
{
     char temp_str[50];
    snprintf(temp_str,16,"%d",num);
    write(fd,temp_str,strlen(temp_str));
}


//simple
int file_init(char *s,char *s_calc,char *time)
{
    int fd,buf[4]={0,1,2,3};
    char temp_str[50];
    char clear[]="";
    char *ptr_str;
    fd = open(s,O_CREAT|O_RDWR,0x777);
    if (NeedCalcDetail==1&&Normal_or_Instant_or_AC==0)
    {
        fd_calc = open(s_calc,O_CREAT|O_RDWR,0x777);
    }
    ptr_str="HIT RESISTANCE WELDING GROUP ALL RIGHT RESERVED!\n";
    write(fd,ptr_str,strlen(ptr_str));
    if (NeedCalcDetail==1&&Normal_or_Instant_or_AC==0)
    {
        write(fd_calc,ptr_str,strlen(ptr_str));
    }
    ptr_str="CAR_TYPE = ";
    write(fd,ptr_str,strlen(ptr_str));
    write_num(fd,CarType);
    if (NeedCalcDetail==1&&Normal_or_Instant_or_AC==0)
    {
        write(fd_calc,ptr_str,strlen(ptr_str));
        write_num(fd_calc,CarType);
    }

    ptr_str=" ,CAR_NUM = ";
    write(fd,ptr_str,strlen(ptr_str));
    write_num(fd,CarNum);
    if (NeedCalcDetail==1&&Normal_or_Instant_or_AC==0)
    {
        write(fd_calc,ptr_str,strlen(ptr_str));
        write_num(fd_calc,CarNum);
    }

    ptr_str=" ,GROUP_NUM = ";
    write(fd,ptr_str,strlen(ptr_str));
    write_num(fd,GroupNum);
    if (NeedCalcDetail==1&&Normal_or_Instant_or_AC==0)
    {
        write(fd_calc,ptr_str,strlen(ptr_str));
        write_num(fd_calc,GroupNum);
    }

    ptr_str=" ,PROCESS_TYPE = ";
    write(fd,ptr_str,strlen(ptr_str));
    write_num(fd,ProcessType);
    if (NeedCalcDetail==1&&Normal_or_Instant_or_AC==0)
    {
        write(fd_calc,ptr_str,strlen(ptr_str));
        write_num(fd_calc,ProcessType);
    }

    ptr_str=" ,SPOT_NUM = ";
    write(fd,ptr_str,strlen(ptr_str));
    write_num(fd,SpotNum);
    if (NeedCalcDetail==1&&Normal_or_Instant_or_AC==0)
    {
        write(fd_calc,ptr_str,strlen(ptr_str));
        write_num(fd_calc,SpotNum);
    }

    ptr_str=" ,VOLT_RATIO = ";
    write(fd,ptr_str,strlen(ptr_str));
    write_num(fd,VoltRatio);
    if (NeedCalcDetail==1&&Normal_or_Instant_or_AC==0)
    {
        write(fd_calc,ptr_str,strlen(ptr_str));
        write_num(fd_calc,VoltRatio);
    }

    ptr_str=" ,CURR_RATIO = ";
    write(fd,ptr_str,strlen(ptr_str));
    write_num(fd,CurRatio);
    if (NeedCalcDetail==1&&Normal_or_Instant_or_AC==0)
    {
        write(fd_calc,ptr_str,strlen(ptr_str));
        write_num(fd_calc,CurRatio);
    }

    ptr_str=" ,Cur_base = ";
    write(fd,ptr_str,strlen(ptr_str));
    write_num(fd,Cur_base);
    if (NeedCalcDetail==1&&Normal_or_Instant_or_AC==0)
    {
        write(fd_calc,ptr_str,strlen(ptr_str));
        write_num(fd_calc,Cur_base);
    }

    ptr_str=" ,Volt_base = ";
    write(fd,ptr_str,strlen(ptr_str));
    write_num(fd,Volt_base);
    if (NeedCalcDetail==1&&Normal_or_Instant_or_AC==0)
    {
        write(fd_calc,ptr_str,strlen(ptr_str));
        write_num(fd_calc,Volt_base);
    }

    ptr_str=" ,Oversample = ";
    write(fd,ptr_str,strlen(ptr_str));
    write_num(fd,oversample);
    if (NeedCalcDetail==1&&Normal_or_Instant_or_AC==0)
    {
        write(fd_calc,ptr_str,strlen(ptr_str));
        write_num(fd_calc,oversample);
    }

    ptr_str=" ,TIME = ";
    write(fd,ptr_str,strlen(ptr_str));
    write(fd,time,strlen(time));
    if (NeedCalcDetail==1&&Normal_or_Instant_or_AC==0)
    {
        write(fd_calc,ptr_str,strlen(ptr_str));
        write(fd_calc,time,strlen(time));
        write(fd_calc,"\n",1);
    }
    strcpy(temp_str,clear);
    write(fd,"\n",1);

    if (Normal_or_Instant_or_AC==0)
    {
        ptr_str="HafCycCount WeldTime Ratio Avg_I Avg_U Power Heat_Input R L R_Avg \n";
        write(fd,ptr_str,strlen(ptr_str));
        if (NeedCalcDetail==1&&Normal_or_Instant_or_AC==0)
        {
            ptr_str="HafCycCount FstU FstI FstDeltaI FstDeltaT HafU HafI HafDeltaI HafDeltaT\n";
            write(fd_calc,ptr_str,strlen(ptr_str));
        }
    }
    else if (Normal_or_Instant_or_AC==1)
    {
        if (Instant_mode==0)//电流瞬时值
        {
            ptr_str="HafCycCount I_value\n";
            write(fd,ptr_str,strlen(ptr_str));
        }
        if (Instant_mode==1)//电压瞬时值
        {
            ptr_str="HafCycCount V_value\n";
            write(fd,ptr_str,strlen(ptr_str));
        }
        else if (Instant_mode==2)//电流电压瞬时值
        {
            ptr_str="HafCycCount I_value V_value\n";
            write(fd,ptr_str,strlen(ptr_str));
        }
    }
    else
    {
        ptr_str="CycCount I_Value U_Value UP_Value (10 Items/Column)\n";
        write(fd,ptr_str,strlen(ptr_str));
    }
    //close(fd);
    return fd;
}
int file_write(int fd)
{
    char temp_str[20];
    char *ptr_str;
    int i,haf_column,total_column,row_num;
    int temp_record_num,total_time;
//format
//time:
  //  qDebug()<<"file_write";
  //  qDebug()<<WeldTime;
    if (Normal_or_Instant_or_AC==0)
    {
        for (i=0;i<HafCycCount.size();i++)
         {
            write_num(fd,HafCycCount[i]);//HafCycCount
            write(fd," ",strlen(" "));
            snprintf(temp_str,16,"%0.1lf",WeldTime[i]);//WeldTime
             write(fd,temp_str,strlen(temp_str));
            write(fd," ",strlen(" "));
            write_num(fd,duty_num[i]);//Ratio
            write(fd," ",strlen(" "));

            snprintf(temp_str,16,"%0.3lf",Avg_I[i]);//Avg_I
            write(fd,temp_str,strlen(temp_str));
            write(fd," ",strlen(" "));
            snprintf(temp_str,16,"%0.3lf",Avg_U[i]);//Avg_U
            write(fd,temp_str,strlen(temp_str));
            write(fd," ",strlen(" "));
            snprintf(temp_str,16,"%0.3lf",Power[i]);//Power
            write(fd,temp_str,strlen(temp_str));
            write(fd," ",strlen(" "));
            snprintf(temp_str,16,"%0.1lf",Heat_Input[i]);//Heat_Input
            write(fd,temp_str,strlen(temp_str));
            write(fd," ",strlen(" "));

            snprintf(temp_str,16,"%0.3lf",R[i]);//R
            write(fd,temp_str,strlen(temp_str));
            write(fd," ",strlen(" "));
            snprintf(temp_str,16,"%0.3lf",L[i]);//L
            write(fd,temp_str,strlen(temp_str));
            write(fd," ",strlen(" "));
            snprintf(temp_str,16,"%0.3lf",R_Avg[i]);//R_Avg
            write(fd,temp_str,strlen(temp_str));
          //  write(fd," ",strlen(" "));

           // write_num(fd,flag_1[i]);//HafCycCount
           // write(fd," ",strlen(" "));

          //  write_num(fd,flag_2[i]);//HafCycCount
          //  write(fd," ",strlen(" "));

            write(fd,"\n",strlen("\n"));
            }
    }
    else if (Normal_or_Instant_or_AC==2)//交流
    {
        //if (write_end_AC==0)
        //{
        total_time=Data_Index.size()-1;
        qDebug()<<"total_time="<<total_time;
        temp_record_num=0;
        for (int ii=0;ii<total_time;ii++)
        {
            haf_column=ceil(double(Data_Index[ii+1]-Data_Index[ii])/2/10);
            //qDebug()<<"temp_record_num="<<temp_record_num;
            total_column=2*haf_column;

            for (int i=0;i<total_column;i++)
            {
                if (i<haf_column)
                { //write_num(fd,temp_halfcyccount-1);
                write_num(fd,2*ii+1);}//HafCycCount
                else
                 { write_num(fd,2*ii+2);}//HafCycCount
                write(fd," ",strlen(" "));

                if (i!=haf_column-1 && i!=total_column-1)
                {
                    row_num=10;
                }
                else
                {
                    row_num=(Data_Index[ii+1]-Data_Index[ii])/2-(haf_column-1)*10;
                    //qDebug()<<"row_num="<<row_num;
                }

                for (int j=0;j<row_num;j++)
                 {
                   // snprintf(temp_str,16,"%.2f",I_AC[i*10+j]);
                   // write(fd,temp_str,strlen(temp_str));
                    write_num(fd,I_AC[temp_record_num+j]);
                    write(fd," ",strlen(" "));
                }
               write(fd,"\n",strlen("\n"));

                write(fd,"  ",strlen("  "));
                for (int j=0;j<row_num;j++)
                {
                  write_num(fd,U_AC[temp_record_num+j]);
                   write(fd," ",strlen(" "));
                }
                write(fd,"\n",strlen("\n"));

                write(fd,"  ",strlen("  "));
                for (int j=0;j<row_num;j++)
                {
                    write_num(fd,UP_AC[temp_record_num+j]);
                   write(fd," ",strlen(" "));
                 }
                write(fd,"\n",strlen("\n"));
                temp_record_num=temp_record_num+row_num;
            }
        }
              //  I_AC.clear();
               // U_AC.clear();
              //  UP_AC.clear();
       //}
       //else
       //{
           ptr_str="\nfai (10 Items/Column)\n";
           write(fd,ptr_str,strlen(ptr_str));
           haf_column=ceil(double(fire_fai.size())/10);
           for (int i=0;i<haf_column;i++)
           {
               if (i!=haf_column-1)
               {
                   row_num=10;
               }
               else
               {
                   row_num=fire_fai.size()-(haf_column-1)*10;
               }
               for (int j=0;j<row_num;j++)
               {
              // snprintf(temp_str,16,"%.1f",fire_fai[i*10+j]);
               write_num(fd,fire_fai[i*10+j]);
              //  write(fd,temp_str,strlen(temp_str));
                write(fd," ",strlen(" "));
               }
               write(fd,"\n",strlen("\n"));
           }
           write(fd,"\n",strlen("\n"));
           ptr_str="\ntheta (10 Items/Column)\n";
            write(fd,ptr_str,strlen(ptr_str));
            haf_column=ceil(conduct_theta.size()/10);
            for (int i=0;i<haf_column;i++)
            {
                if (i!=haf_column-1)
                {
                    row_num=10;
                }
                else
                {
                    row_num=conduct_theta.size()-(haf_column-1)*10;
                }
                for (int j=0;j<row_num;j++)
                {
                write_num(fd,conduct_theta[i*10+j]);
                 write(fd," ",strlen(" "));
                }
                write(fd,"\n",strlen("\n"));
            }
            write(fd,"\n",strlen("\n"));

            fire_fai.clear();
            conduct_theta.clear();
            write_end_AC=0;

        //}

    }
    else
    {
        if (Instant_mode==0)
        {
            for (int i=0;i<HafCycCount.size();i++)
            {
                write_num(fd,HafCycCount[i]);//HafCycCount
            write(fd," ",strlen(" "));
            for (int j=0;j<SIZE_INSTANT_LEN;j++)
            {
                snprintf(temp_str,16,"%d",Instant_Curr[i*SIZE_INSTANT_LEN+j]);
                write(fd,temp_str,strlen(temp_str));
                write(fd," ",strlen(" "));
            }
             write(fd,"\n",strlen("\n"));

            }
            Instant_Curr.clear();
            HafCycCount.clear();
        }
        if (Instant_mode==1)
        {
            for (int i=0;i<HafCycCount.size();i++)
            {
                write_num(fd,HafCycCount[i]);//HafCycCount
            write(fd," ",strlen(" "));
            for (int j=0;j<SIZE_INSTANT_LEN;j++)
            {
                snprintf(temp_str,16,"%d",Instant_Volt[i*SIZE_INSTANT_LEN+j]);
                write(fd,temp_str,strlen(temp_str));
                write(fd," ",strlen(" "));
            }
             write(fd,"\n",strlen("\n"));

            }
            Instant_Volt.clear();
            HafCycCount.clear();
        }
        else if (Instant_mode==2)
        {
            for (int i=0;i<HafCycCount.size();i++)
            {
                write_num(fd,HafCycCount[i]);//HafCycCount
            write(fd," ",strlen(" "));
            for (int j=0;j<SIZE_INSTANT_LEN/2;j++)
            {
                snprintf(temp_str,16,"%d",Instant_Curr[i*SIZE_INSTANT_LEN/2+j]);
                write(fd,temp_str,strlen(temp_str));
                write(fd," ",strlen(" "));
            }
            for (int j=0;j<SIZE_INSTANT_LEN/2;j++)
            {
                snprintf(temp_str,16,"%d",Instant_Volt[i*SIZE_INSTANT_LEN/2+j]);
                write(fd,temp_str,strlen(temp_str));
                write(fd," ",strlen(" "));
            }
             write(fd,"\n",strlen("\n"));

            }
            Instant_Curr.clear();
            Instant_Volt.clear();
            HafCycCount.clear();
        }
    }
}

int calc_detail_write(int fd)
{
    int i;
    for (i=0;i<HafCycCount.size()-1;i++)
     {
        write_num(fd,HafCycCount[i]);//HafCycCount
        write(fd," ",strlen(" "));
        write_num(fd,FstU[i]);//FstU
        write(fd," ",strlen(" "));
        write_num(fd,FstI[i]);//FstI
        write(fd," ",strlen(" "));
        write_num(fd,FstDeltaI[i]);//FstDeltaI
        write(fd," ",strlen(" "));
        write_num(fd,FstDeltaT[i]);//FstDeltaT
        write(fd," ",strlen(" "));
        write_num(fd,HafU[i]);//HafU
        write(fd," ",strlen(" "));
        write_num(fd,HafI[i]);//HafI
        write(fd," ",strlen(" "));
        write_num(fd,HafDeltaI[i]);//HafDeltaI
        write(fd," ",strlen(" "));
        write_num(fd,HafDeltaT[i]);//HafDeltaT
        write(fd," ",strlen(" "));
        write(fd,"\n",strlen("\n"));
    }

}

