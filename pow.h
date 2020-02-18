#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OP_SIZE 5
#define ARG_SIZE 1000
#define MAX_LINES 1000

int* power(int* a1,int* a2,int l1,int l2){
	int* opt = (int*)malloc(10000*sizeof(int));
	int k=0;
	opt	= a1;
	int length = l1;
	for(int i=0; i<l2;i++){
		k = (k*10)+a2[i]; 
	}
	k=k/1000000;
	for(int i=0; i<k-1; i++){
		opt = mul(opt,a1,length,l1);
		int j=0;
		while(opt[j]!= -1){
			j++;
		}
		length = j;
	}
	return opt;	
}