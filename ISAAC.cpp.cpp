#include<iostream.h>
#include<stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<math.h>
#include<bios.h>
#include<graphics.h>

void main()
{
 clrscr();
 int n,w1,w2,stime,etime,time,tformat,j,num[50];
 float m[25][10][6],outtemp,tcool[50],to1[50],to2[50],q[50],Ib[50],prob[5],refr1[50],k,tab[50],ta,s[50],tb[50],tr1,tr2,i,cosx[50],res,x[50],rb[50],w[50],refr[50],rho1[50],rho2[50],tr[50];
 double t1[50],t2[50],t3[50],t4[50],t5[50],t6[50],tf[50],no;
 cout<<"\nEnter the outdoor temperature:";
 cin>>outtemp;
 cout<<"\nEnter the start time:";
 cin>>stime;
 cout<<"choose-\n1 - am\n2 - pm\n";
 cin>>tformat;
 if(tformat==1)
 w1=(12-stime)*15;
 if(tformat==2)
 w1=-stime*15;
 cout<<"Enter the end time:";
 cin>>etime;
 cout<<"choose-\n1 - am\n2 - pm\n";
 cin>>tformat;
 if(tformat==1)
 w2=(12-etime)*15;
 if(tformat==2)
 w2=-etime*15;
 cout<<tformat<<"\nw1="<<w1<<"\nw2="<<w2;
 cout<<"\nChoose the resolution of time line\n1-1 hour\n2-0.5 hour\n3-0.25 hour\n";
 cin>>res;
 if(res==1)
 res=15;
 if(res==2)
 res=7.5;
 if(res==3)
 res=3.75;
 n=(w1-w2)/res;
 randomize();	           //Random numbers code//
 for(i=0;i<=n;i++)
 {
  num[i]=rand()%100;
 }
 cout<<"No. of steps="<<n;
 for(i=w1,j=0;i>=w2;i=i-res,j++)
 {
  cosx[j]=0.007569+0.986898*cos((i*3.14)/180);
  x[j]=acos(cosx[j]);
  x[j]=(x[j]*180)/3.14;    // The theta matrix in degrees //
  w[j]=i;                  // The w matrix //
 }
 clrscr();
 cout<<"\nEnter the cumulative probabilities for the day\n\nclear sky=";
 cin>>prob[0];
 prob[0]=prob[0]*100;
 cout<<"\nmostly clear=";
 cin>>prob[1];
 prob[1]=prob[1]*100;
 cout<<"\npartly cloudy=";
 cin>>prob[2];
 prob[2]=prob[2]*100;
 cout<<"\nmostly cloudy=";
 cin>>prob[3];
 prob[3]=prob[3]*100;
 cout<<"\novercast=";
 cin>>prob[4];
 prob[4]=prob[4]*100;
 clrscr();
 cout<<"\nEnter temp t1:";
 cin>>t1[0];
 cout<<"\nEnter temp t2:";
 cin>>t2[0];
 cout<<"\nEnter temp t3:";
 cin>>t3[0];
 cout<<"\nEnter temp t4:";
 cin>>t4[0];
 cout<<"\nEnter temp t5:";
 cin>>t5[0];
 cout<<"\nEnter temp t6:";
 cin>>t6[0];
 for(i=0;i<=20;i++)   //Clearing the matrix//
 Ib[i]=0;
 for(i=0;i<=n;i++)    //Sorting according to random numbers//
 {
  for(j=0;j<5;j++)
  {
   if(num[i]<=prob[j])
   Ib[i]=Ib[i]+145;
  }
 }

 for(i=0;i<=n;i++)          // Output for theta costheta and w //
 cout<<"\nx="<<x[i]<<"\tcosx="<<cosx[i]<<"\tw="<<w[i];
 for(i=0;i<=n;i++)    //Master loop for major iterative hourly calculations//
 {
  rb[i]=cosx[i]/(-0.017751+0.93151*cos((w[i]*3.14)/180));
  refr1[i]=sin(x[i]*3.14/180)/1.51;
  refr[i]=asin(refr1[i])*180/3.14;
  rho1[i]=pow(sin(((x[i]-refr[i])*3.14)/180),2)/pow(sin(((x[i]+refr[i])*3.14)/180),2);
  rho2[i]=pow(tan(((x[i]-refr[i])*3.14)/180),2)/pow(tan(((x[i]+refr[i])*3.14)/180),2);
  tr1=(1-rho1[i])/(1+rho1[i]);
  tr2=(1-rho2[i])/(1+rho2[i]);
  tr[i]=(tr1+tr2)/2;
  k=(-0.076/cos((x[i]/1.51)*3.14/180));
  ta=pow(2.7182818,k);
  tb[i]=ta*tr[i];
  tab[i]=(tb[i]*0.95)/0.99295;
  s[i]=(Ib[i]*tab[i]*rb[i])+(216.89+0.013*Ib[i])*0.737;
  q[i]=1.79208*(s[i]-140);
  to1[i]=(q[i]*0.014354)+60;
  to2[i]=(q[i]*0.014354)+to1[i];
  if((to2[i]>=90)&&(to2[i]<=95))
  tcool[i]=7;
  if((to2[i]>=85)&&(to2[i]<=89))
  tcool[i]=8;
  if((to2[i]>=80)&&(to2[i]<=84))
  tcool[i]=9;
  if((to2[i]>=75)&&(to2[i]<=79))
  tcool[i]=10;
  if((to2[i]>=70)&&(to2[i]<=74))
  tcool[i]=11;
  if((to2[i]>=65)&&(to2[i]<=69))
  tcool[i]=12;
  no=(13-tcool[i])/6;
  tf[6]=tcool[i];
  tf[5]=tf[6]+no;
  tf[4]=tf[5]+no;
  tf[3]=tf[4]+no;
  tf[2]=tf[3]+no;
  tf[1]=tf[2]+no;
  for(j=0;j<=6;j++)
  {
   t1[j+1]=t1[j]-((360*((500*(t1[j]-t2[j])-300*(tf[j]-tf[j-1])))/100000));
   t2[j+1]=t2[j]-((360*((500*(t2[j]-t3[j])-300*(tf[j]-tf[j-1])))/100000));
   t3[j+1]=t3[j]-((360*((500*(t3[j]-t4[j])-300*(tf[j]-tf[j-1])))/100000));
   t4[j+1]=t4[j]-((360*((500*(t4[j]-t5[j])-300*(tf[j]-tf[j-1])))/100000));
   t5[j+1]=t5[j]-((360*((500*(t5[j]-t6[j])-300*(tf[j]-tf[j-1])))/100000));
  }
  for(j=0;j<=6;j++)
  {
  m[i][j][0]=t1[j];
  m[i][j][1]=t2[j];
  m[i][j][2]=t3[j];
  m[i][j][3]=t4[j];
  m[i][j][4]=t5[j];
  m[i][j][5]=t6[j];
  }
 }
 for(i=0;i<50;i++)
 {
  if(Ib[i]<0)
  Ib[i]=0;
  if(t1[0]<0)
  t1[i]=0;
  if(t2[0]<0)
  t2[i]=0;
  if(t3[0]<0)
  t3[i]=0;
  if(t4[0]<0)
  t4[i]=0;
  if(t5[0]<0)
  t5[i]=0;
  if(t6[0]<0)
  t6[i]=0;
 }
 getch();
 clrscr();     //Output verification code//
 for(i=0;i<=n;i++)
 cout<<"\nrb="<<rb[i];
 getch();
 clrscr();
 for(i=0;i<=n;i++)
 cout<<"\nrefr="<<refr[i]<<"\trho1="<<rho1[i]<<"\trho2="<<rho2[i]<<"\ttr="<<tr[i];
 getch();
 clrscr();
 for(i=0;i<=n;i++)
 cout<<"\ntab="<<tab[i];
 getch();
 clrscr();
 cout<<"The values of incident flux:\n";
 time=etime;
 for(i=0;i<=n;i++)
 {
  if(stime<=12)
  {
   cout<<"\n"<<stime<<" am"<<"\tS="<<s[i]<<"\t"<<num[i]<<"\t"<<Ib[i]<<"\tq="<<q[i]<<"\tto="<<to2[i]<<"\tTABS="<<tcool[i];
   stime++;
  }
  else
  {
   cout<<"\n"<<time-etime+1<<" pm"<<"\tS="<<s[i]<<"\t"<<num[i]<<"\t"<<Ib[i]<<"\tq="<<q[i]<<"\tto="<<to2[i]<<"\tTABS="<<tcool[i];
   etime--;
  }
 }
 getch();
 clrscr();
 for(i=0;i<=n;i++)
 {
  for(j=0;j<6;j++)
  {
   cout<<"\nt1="<<m[i][j][0]<<"\tt2="<<m[i][j][1]<<"\tt3="<<m[i][j][2]<<"\tt4="<<m[i][j][3];
  }
  getch();
 }
 getch();
 clrscr();
 int gd=DETECT,gm;
 initgraph(&gd,&gm,"c:\\tc\\bgi");
  line(0,460,640,460);
  line(20,0,20,480);
 setcolor(RED);
 for(i=0;i<n;i++)
 {
   line(20+25+(i*25),460-(s[i]/2),20+25+((i+1)*25),460-(s[i+1]/2));
  }
 getch();
  clrscr();
 initgraph(&gd,&gm,"c:\\tc\\bgi");
  line(0,460,640,460);
  line(20,0,20,480);

 for(i=0;i<n;i++)
 {
  for(j=0;j<4;j++)
  {
   setcolor(RED);
   line(20+8+(i*48)+j*8,460-(m[i][j][0]*10),20+8+((i)*48)+(j+1)*8,460-(m[i][j+1][0]*10));
   setcolor(BLUE);
   line(20+8+(i*48)+j*8,460-(m[i][j][1]*10),20+8+((i)*48)+(j+1)*8,460-(m[i][j+1][1]*10));
   setcolor(MAGENTA);
   line(20+8+(i*48)+j*8,460-(m[i][j][2]*10),20+8+((i)*48)+(j+1)*8,460-(m[i][j+1][2]*10));
   setcolor(YELLOW);
   line(20+8+(i*48)+j*8,460-(m[i][j][3]*10),20+8+((i)*48)+(j+1)*8,460-(m[i][j+1][3]*10));
  }
 }
 getch();
}
