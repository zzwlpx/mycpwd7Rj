// type7.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
char DecPwd[255]={0};
char xlatRJ[] = {
        0x2a, 0x40, 0x23, 0x23, 0x57, 0x78, 0x66, 0x5e,
        0x63, 0x4f, 0x75, 0x72, 0x47, 0x65, 0x72, 0x2a,
        0x6d, 0x41, 0x72, 0x4b, 0x4c, 0x65, 0x48, 0x53 , 0x55, 0x42
 };
 int  decpwd(char * pOriPwd){ //解密函数
 int pp = 0;
 
    int iOriPwdLen = strlen(pOriPwd);
    int seed,i,j=0;
    seed = (pOriPwd[0]-'0')*10 + (pOriPwd[1]-'0');
    printf("intilize seed is %d\n",seed);
    for (i=2;i<=iOriPwdLen;i++){
 
 if (i>2 && i%2 == 0){
   DecPwd[j++] = pp ^ xlatRJ[seed++];
 pp =0 ;
 seed %= 26;
 }
        pp*=16;
 char lala = toupper(pOriPwd[i]);
 if(lala >= '0' && lala<='9')
 {
  pp+=lala-'0';
  continue;
 }else if (lala>='A'&& lala<='F'){
  pp+=lala-'A'+10; 
  continue;
 }
        if (i != iOriPwdLen)
  return -1;
    }
    DecPwd[j]='\0';
    return 0;
}
char enccode[255]={0};
int encpwd(char *pwd) //加密函数
{
 int seed=0;
 srand((unsigned)time(NULL));
 rand();
 seed = (double)rand()/(RAND_MAX+1)*25;
 printf("intilize seed is %d/n",seed);
 int i ,iCode= 0;
    int iLeft,iRight;
 enccode[0] = seed /10 + '0';
 enccode[1] = seed %10 + '0';
 
 for (i = 0 ; i <= strlen(pwd)-1 ; i++)
 {
  iCode = xlatRJ[seed++] ^ pwd[i];
  seed %= 26;
  iLeft = iCode /16 ;
  if (iLeft > 9)
   iLeft = iLeft -10 +'A';
  else
   iLeft +='0';
  iRight = iCode % 16 ;
  if (iRight > 9)
   iRight = iRight -10 + 'A';
  else
   iRight+='0';
  enccode[i*2+2] = iLeft;
  enccode[i*2+3] = iRight;
    }
 enccode[i*2+2] = 0;
 return 0;
 
}
int main(int argc,char * argv[])
{
 if (argc == 3 && strcmp(argv[1],"-e") == 0 && strlen(argv[2])<=16)
 {
  if (encpwd(argv[2]) == 0)
   printf("结果是:%s",enccode);
  else
   printf("I'm so sorry,encrypt is failed,please try again!");
  return 1;
 }
 if (argc <2 || strlen(argv[1]) %2 !=0 || strlen(argv[1]) <4 ){
  printf("Cisco Type-7 password decrpter !Programmed by fuyewei at 2010-06-03./nPlease Enter Cisco Type-7 Code Correctly! //ne.g. 095F41041C480713181F13253920 and so on");
 return -1;
 }
 
 if(decpwd(argv[1]) == 0)
  printf("解密成功，密码是:%s",DecPwd);
 return 0;
 
}