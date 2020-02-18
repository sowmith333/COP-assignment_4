#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

char* real(char* a){

	char* b = (char*)malloc(10000*sizeof(char));
	char check[]=",";
	int t=strcspn(a,check);
	strncpy(b,a+1,t-1);
	b[t-1] = '\0';	
	return b;
}

char* img(char* a){

	char* b = (char*)malloc(10000*sizeof(char));
	char check[]=",";
	int t=strcspn(a,check);
 	strcpy(b,a+t+1);
	b[strlen(b)-1] = '\0';
	return b;	
}
