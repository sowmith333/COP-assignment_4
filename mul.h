#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OP_SIZE 5
#define ARG_SIZE 1000
#define MAX_LINES 1000

int* mul(int* a1,int* a2,int l1,int l2){

	int* opt = (int*)malloc(10000*sizeof(int));
	int len1 = l1;
	int len2 = l2;
	int length=1;
	opt[0]=0;

	for(int i=0;i<len2;i++){
		int* temp = (int*)malloc(10000*sizeof(int));	
		int p = a2[len2-i-1];
		int q=0;
		int r=0;
		for(int j=0;j<len1;j++){
			q = p*a1[len1-j-1]+q;
			r=q%10;
			q=q/10;
			temp[len1-j] = r;
		} 	 
		temp[0]=q;
		for (int j=0;j<i;j++){
			temp[len1+j]=0;
			}
		opt = add(temp,opt,len1+i+1,length);
		length=len1+i+1;
	}
	length=length-6;
	opt[length]=-1;
	return opt;
}
