#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OP_SIZE 5
#define ARG_SIZE 1000
#define MAX_LINES 1000

int* add(int* a1,int* a2,int l1,int l2){

	int* opt = (int*)malloc(10000*sizeof(int));
	int* b[2]; 
	b[0] = a1;
	b[1] = a2;
	int temp;
	int length;
	int carry=0;  
	int len1 = l1;
	int len2 = l2; 

	for(int i=0;i<len2;i++){
		temp = (b[0][len1-i-1])+(b[1][len2-i-1])+carry;
		if(temp>9){
			carry = 1;
			temp = temp-10;
		}else{
			carry = 0;
		}
		opt[len1-i-1]= temp;
	}
	for(int i=0; i<len1-len2;i++){
		temp = (b[0][len1-len2-i-1])+carry;
		if(temp>9){
			carry = 1;
			temp = temp-10;
		}else{
			carry = 0;
		}
		opt[len1-len2-i-1]=temp; 
	}
	length = len1;
	if(carry==1){
		for(int i=len1;i>0;i--){
			opt[i]=opt[i-1];
		}
		opt[0]=carry;
		length = len1+1;
	}
	opt[length]=-1;
	
	return opt;
}
