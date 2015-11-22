#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>


double taylor_log(double x, unsigned int n){
	double result;
	double prvy_clen;
	double dalsi_clen;	
	
	if(x >= 1){
	
	prvy_clen = (x-1)/x;
	result = prvy_clen;	
	double h1 = prvy_clen;
	
	
	for(double i = 2; i <= n; i++){
		
		dalsi_clen = prvy_clen * h1 * ((i-1)/(i));
		prvy_clen = dalsi_clen;
		result += dalsi_clen;
	}
	
	
	}else if(x < 1 && x > 0){
		prvy_clen = 1 - x;	
		result = prvy_clen;
		double h2 = prvy_clen;
		
		for(int i = 2; i <= n; i++){
		
		dalsi_clen = prvy_clen * ((h2)*(i-1))/i;
		prvy_clen = dalsi_clen;
		result += dalsi_clen;
		
		
		}
		result = result * (-1);
	}
	else{
		
		return NAN;
	}
	return result;
}


double cfrac_log(double x, unsigned int n){
	double result;
	double clen = 0;
	double z = (x-1)/(1+x);
	double z2 = z*z;
	
	for(double i = n; i > 1; i--){
		
		clen = ((i-1)*(i-1)* z2 )/ ((2*i - 1) - clen);
	}
	
	result = (2*z) / (1 - clen);
	
	
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
	/*
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
	* */
	
	
	double result_log = log(1000000000);
	printf("log: %f\n", result_log);
	
	double result = taylor_log(1000000000, 1000000); 
	printf("taylor: %f\n", result);
	
	double result2 = cfrac_log(1000000000, 1000000);
	printf("cf: %f\n", result2);
	
	
	return 1;
	}


	




