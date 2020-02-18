#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OP_SIZE 5
#define ARG_SIZE 1000
#define MAX_LINES 1000

int* sub(int* a1,int* a2,int l1,int l2){

	int* opt = (int*)malloc(10000*sizeof(int));
	int len1 = l1;
	int len2 = l2;
	int k=0;
	
	int carry =0;
		for(int i=0;i<len2;i++){
	
		if(carry==1){
	

			if(a1[len1-i-1]>0){
				a1[len1-i-1]=a1[len2-i-1]-1;
				carry=0;
			}else{
				a1[len1-i-1]=10;
				carry=1;
			}
		}
		if(a1[len1-i-1]>=a2[len2-i-1]){ 
	

			opt[len1-i-1]=a1[len1-i-1]-a2[len2-i-1];
		}else{
	

			opt[len1-i-1]=a1[len1-i-1]-a2[len2-i-1]+10;
			carry=1;
		}
	}
	for(int i=0;i<len1-len2;i++){
		if(carry==1){
			if(a1[len1-len2-i-1]>0){
				opt[len1-len2-i-1]=a1[len1-len2-i-1]-1;
				carry=0;
			}else{
				opt[len1-len2-i-1]=9;
				carry=1;
			}
		}else{
			opt[len1-len2-i-1]=a1[len1-len2-i-1];
		}
	}
	opt[l1]=-1;
	return opt;
}