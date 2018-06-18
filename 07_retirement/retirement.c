#include <stdlib.h>
#include <stdio.h>

struct _retire_info{
  int month; //number of months its applicable
  double contribution; //contribution in a month in dollars
  double rate_of_return; //rate of return after inflation
};
typedef struct _retire_info retire_info;

double actAcount(double actual, retire_info acount, int startAge){
  double balance = actual;
  for (int i = 0; i < acount.month; i++){
    int ageYears = startAge/12;
    int ageMonth = startAge - ageYears*12;
    printf("Age %3d month %2d you have $%.2lf\n", ageYears, ageMonth, balance);
    balance = balance*(1 + acount.rate_of_return/12) + acount.contribution;
    startAge = startAge + 1;
  }
  return balance;
}

void retirement (int startAge, //in month
		 double initial, //initial savings in dollars
		 retire_info working, //info about working
		 retire_info retired){  //info about being retired
  double afterRet = actAcount(initial, working, startAge);
  int actAge = startAge + working.month;
  actAcount(afterRet, retired, actAge);
}
int main (void){
  retire_info working;
  working.month = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045;
  retire_info retired;
  retired.month = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01;
  retirement(327, 21345, working, retired);
  return 0;
}
