#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <complex.h>
#include "operations.h"
#include "comp.h"

#define OP_SIZE 5
#define ARG_SIZE 1000
#define MAX_LINES 1000

int main(int argc, char* argv[])
{
  // Read file name from user
  	const char* file_name;
  	const char* out_name; 
    const char* cout_name;

  	if (argc == 4){
    file_name = argv[1];
    out_name = argv[2];
	  cout_name = argv[3];
  	}else{
    fprintf(stderr, "Expected format: <exec> <input_file> <output_file> <output_file>\n");
    exit(EXIT_FAILURE);
  	}
  // Open file in read mode
  	FILE* in_file = fopen(file_name, "r");
  // Report error on failure and exit
  	if (in_file == NULL) {
    	fprintf(stderr, "Unable to read %s file\n", file_name);
    	exit(EXIT_FAILURE);
  	}

  	int line_count = 0;     //!< Maintains the count of lines in the file
  	int max_length = 0;     //!< Longest line in the file
  	char* lines[MAX_LINES]; //!< The lines in the input file

  	size_t len = 0;         //!< Dummy variable for getline()
  	size_t line_length = 0; //!< Dummy variable for finding longest line

  // Read the file line by line and update the number of lines
    while ((line_length = getline(&lines[line_count], &len, in_file)) != -1) {
    	if (line_length > max_length) max_length = line_length;
    	line_count++;
  	}
  // Close the file
    fclose(in_file);
  // Time 
    double time1[line_count],time2[line_count]; 	
  // Break the string into arguments
    char op_id[OP_SIZE];                     //!< Operation identifier
    char* arg[2]; //!< The arguments for the operation
	  arg[0] = (char*)malloc(1000*sizeof(char));
	  arg[1] = (char*)malloc(1000*sizeof(char));
  
  // Break every line into operation and arguments
  	FILE* out_file = fopen(out_name,"w");
  	for(int j=0;j<line_count;j++){
      clock_t start = clock();    
      sscanf(lines[j], "%s %s %s", op_id, arg[0], arg[1]);
	  
      char* r[2];
      char* i[2];

      r[0] = real(arg[0]);
      r[1] = real(arg[1]);
      i[0] = img(arg[0]);
      i[1] = img(arg[1]);
      
      char* temp;
      char* itemp;

      if(strcmp(op_id,"ADD")==0){
        temp=test(op_id,r);
        itemp=test(op_id,i);
      }else if(strcmp(op_id,"SUB")==0){
        temp=test(op_id,r);
        itemp=test(op_id,i);
      }else if(strcmp(op_id,"PROD")==0){
        char* a[2]; 
        char* b[2];
        char* c[2];

        b[0] = (char*)malloc(10000*sizeof(char));
        b[1] = (char*)malloc(10000*sizeof(char));


        a[0]=test("MUL",r);
        a[1]=test("MUL",i);
        temp = test("SUB",a);

        strcpy(a[0],r[0]);
        a[0][strlen(a[0])] = '\0';
        strcpy(a[1],i[1]);
        a[1][strlen(a[1])] = '\0';
        strcpy(b[0],r[1]);
        b[0][strlen(b[0])] = '\0';
        strcpy(b[1],i[0]);
        b[1][strlen(b[1])] = '\0';
        
        c[0] = test("MUL",a);
        c[1] = test("MUL",b);
        itemp = test("ADD",c); 
      }else if(strcmp(op_id,"ABS")==0){
        temp = test(op_id,r);
        itemp = test(op_id,i);
      }else {
        temp = "I DIDN'T";
        itemp = "CODE THIS";
      }
      fprintf(out_file,"(");
      for(int i=0;temp[i]!='\0';i++){
      fprintf(out_file,"%c",temp[i]);
      }
      fprintf(out_file,",");
      for(int i=0;itemp[i]!='\0';i++){
      fprintf(out_file,"%c",itemp[i]);
      }
      fprintf(out_file,")");
      fprintf(out_file,"\n");

      clock_t end = clock();
      time1[j]= (double)(end-start)/ 100000.0;       
    }
	  fclose(out_file);
    
    //DOING THE SAME BUT WITH COMPLEX NUMBERS
    FILE* cout_file = fopen(cout_name,"w");
    for(int j=0;j<line_count;j++){
      clock_t start = clock();    
      sscanf(lines[j], "%s %s %s", op_id, arg[0], arg[1]);
    
      char* r[2];
      char* i[2];

      r[0] = real(arg[0]);
      r[1] = real(arg[1]);
      i[0] = img(arg[0]);
      i[1] = img(arg[1]);
      
      double temp;
      double itemp;

      double complex z1 = atof(r[0]) + atof(i[0])* I;
      double complex z2 = atof(r[1]) + atof(i[1])* I;  
      
      if(strcmp(op_id,"ADD")==0){
        double complex opt = z1+z2;
        temp=creal(opt); 
        itemp=cimag(opt);
      }else if(strcmp(op_id,"SUB")==0){
        double complex opt = z1-z2;
        temp=creal(opt); 
        itemp=cimag(opt);
      }else if(strcmp(op_id,"PROD")==0){
        double complex opt = z1*z2;
        temp=creal(opt); 
        itemp=cimag(opt); 
      }else if(strcmp(op_id,"ABS")==0){
        temp = abs(creal(z1));
        itemp = abs(cimag(z1));
      }else {
        temp = 0.0;
        itemp = 0.0;
      }
      fprintf(out_file,"(");
      fprintf(out_file,"%lf",temp);
      fprintf(out_file,",");
      fprintf(out_file,"%lf",itemp);
      fprintf(out_file,")");
      fprintf(out_file,"\n");

      clock_t end = clock();
      time2[j]= (double)(end-start)/100000.0;       
    }
    fclose(cout_file);

    char * commandsForGnuplot[] = {"set title \"GRAPH\"","plot 'data.temp' using 1:2 with linespoints,'data.temp' using 1:3 with linespoints", "set terminal 'png'", "set output 'graph.png'"};
    FILE * temp = fopen("data.temp", "w");
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    fprintf(temp, "%d %lf %lf\n",0,0.0,0.0);
    
    for(int i=0; i<line_count; i++){
      fprintf(temp, "%d %lf %lf\n", i+1, time1[i], time2[i]); //Write the data to a temporary file
    }

    for (int i=0; i<4; i++)
    {
      fprintf(gnuplotPipe, "%s\n", commandsForGnuplot[i]); 
    }
      fprintf(gnuplotPipe, "%s\n", commandsForGnuplot[1]); 

    return 0;
}
