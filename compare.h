#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OP_SIZE 5
#define ARG_SIZE 1000
#define MAX_LINES 1000

int compare(int* a1,int* a2,int l1,int l2){

	int len1 = l1;
	int len2 = l2;
	int opt=0;

	if(len1>len2){
		opt = 1;	
	}else if(len2>len1){
		opt =0;
	}else {
		for(int i=0;i<len1;i++){
			if(a1[i]>a2[i]){
				opt = 1;
				break;
			}else if(a2[i]>a1[i]){
				opt = 0;
				break;
			}
		}
	}
	return opt;
}