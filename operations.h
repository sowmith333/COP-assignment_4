#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "add.h"
#include "compare.h"
#include "sub.h"
#include "mul.h"
#include "pow.h"
#define OP_SIZE 5
#define ARG_SIZE 1000
#define MAX_LINES 1000

struct dats {
	int* num;
	int sign;
	int len;
}z[2];

char* test(char* b1,char* b[2]){

	z[0].num = (int*)malloc(10000*sizeof(int));
	z[1].num = (int*)malloc(10000*sizeof(int));
	for (int i = 0; i < 2; i++){
		if(b[i][0]!='-'){
			z[i].sign = 1;
		}else {
			z[i].sign = -1;
		}
		char check[]=".";
		int t=strcspn(b[i],check);
		char temp;
		if(t!=strlen(b[i])){
			if(z[i].sign==1){
				for(int j=0;j<t;j++){
					 z[i].num[j]= b[i][j] -'0'; 
				}
				for(int j=0;j<6;j++){
					if(((int) strlen(b[i])-j-t-1) > 0){
						z[i].num[t+j]=b[i][t+j+1]-'0';
					}else{
						z[i].num[t+j]=0;
					}
				}
				z[i].len = t+6;
			}else{
				for(int j=0; j<t-1; j++){
					z[i].num[j]=b[i][j+1]-'0';
					}
				for(int j=0;j<6;j++){
					if(((int)strlen(b[i])-j-t-1)>0){
						z[i].num[t+j-1]=b[i][t+j+1]-'0';
					}else{
						z[i].num[t+j-1]=0;
					}
				}
				z[i].len = t+5;
			}
		}else{
			if(z[i].sign==1){
				for(int j=0; j<t+6; j++){
					if(((int) strlen(b[i])-j) > 0){
						z[i].num[j] = b[i][j]-'0';
					}else{
						z[i].num[j]=0;
					} 				
				}
				z[i].len = t+6;
			}else{
				for(int j=0; j<t+6; j++){
					if((int)(strlen(b[i])-1-j) > 0){
						z[i].num[j] = b[i][j+1]-'0';
					}else{
						z[i].num[j] = 0; 
						}
					}
				z[i].len = t+5;	
				}	
			}
	}

	int k= compare(z[0].num,z[1].num,z[0].len,z[1].len);

	int* opt;
	int sign;
	if(strcmp(b1,"ADD")==0){
		if(z[0].sign*z[1].sign==1){
		 opt = add(z[0].num,z[1].num,z[0].len,z[1].len);
		 sign = z[0].sign;
		}else if(k==1){
		 opt = sub(z[0].num,z[1].num,z[0].len,z[1].len);
		 sign = 1;
		}else{
		 opt = sub(z[1].num,z[0].num,z[1].len,z[0].len);
		 sign=-1;
		}
	}else if(strcmp(b1,"SUB")==0){
		if(z[1].sign==1){
			if(z[0].sign==1){
				if(k==1){ opt = sub(z[0].num,z[1].num,z[0].len,z[1].len);sign=1;}
				else{ opt = sub(z[1].num,z[0].num,z[1].len,z[0].len);sign=-1;}		
			}else{
		 		opt = add(z[0].num,z[1].num,z[0].len,z[1].len);
		 		sign=-1;
			}
		}else{
			if(z[0].sign==1){
				opt = add(z[0].num,z[1].num,z[0].len,z[1].len);
				sign=1;
			}else{
				if(k==1){ opt = sub(z[0].num,z[1].num,z[0].len,z[1].len);sign=-1;}
				else{ opt = sub(z[1].num,z[0].num,z[1].len,z[0].len);sign=1;}
			}
		}
	}else if(strcmp(b1,"MUL")==0){
			if(k==1){ opt = mul(z[0].num,z[1].num,z[0].len,z[1].len);}
			else{ opt = mul(z[1].num,z[0].num,z[1].len,z[0].len);}
			sign = (z[0].sign*z[1].sign);
	}else if(strcmp(b1,"ABS")==0){
	 		opt = z[0].num;
	 		sign = 1;
	 		opt[z[0].len]=-1;
	 }else if(strcmp(b1,"POW")==0){
	 		opt = power(z[0].num,z[1].num,z[0].len,z[1].len);
	 		if(z[0].sign==1){
	 		sign=1;
	 		}else{
	 			if(((z[1].num[z[1].len-7])%2)==0){
	 			sign=1;
	 		}else{sign=-1;}
	 	}
	}else{
		opt = z[0].num;
		sign =1;
	 	opt[z[0].len]=-1;
	}

	char* temp = (char*)malloc(1000*sizeof(char));
	int i=0;
	int j=0;
	if(sign==-1){
		*(temp+i)='-';
		i++;
		}

	while(opt[j]!=-1){
		*(temp+i+j)=opt[j]+'0';
		j++;
	}
	char w=*(temp+i+j-6);
	for(int k=6;k>0;k--){
		char t;
		t=*(temp+i+j-k+1);
		*(temp+i+j-k+1)=w;
		w=t;
	}
	*(temp+i+j-6)='.';
	*(temp+i+j+1)='\0';

	return temp; 	
}