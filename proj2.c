#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>


double taylor_log(double x, unsigned int n){
	double result;
	
	return result;	
	
}

double cf_log(double x, unsigned int n){
	
	double result;
	
	return result;

}

double cfrag_log(double x, unsigned int n){
	double result;
	
	return result;
}



bool is_number(char *str){
	for(int i = 0; str[i] != 0; i++){
		
		if(!isdigit(str[i])){
			return false;
		}
	}
	return true;
	
}
int main(int argc, char *argv[]){
		double min, max, eps;	
	
	if(!strcmp(argv[1], "--iter")){
			if(is_number(argv[2]) && is_number(argv[3]) && is_number(argv[4])){
			sscanf(argv[2],"%lf", &min);
			sscanf(argv[3], "%lf", &max);
			sscanf(argv[4], "%lf", &eps);
			printf("min: %lf\nmax: %lf\neps: %lf\n", min, max, eps);
		}
		
	}else if(strcmp(argv[1], "--log")){
		printf("%s", argv[1]);
	
	}
	
	return 1;
	}


	



