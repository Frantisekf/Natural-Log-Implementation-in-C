#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

enum err{
  EOK,
  EBI,
  EPA,
};

const char *ERRMSG[] = {
  [EOK] = "Vsetko v poriadku\n",
  [EPA] = "Bola zadana neznama kombinacia parametrov\n",
  [EBI] = "Boli zadane nevhodne typy pre vypocet\n",
};  


enum paramFce{
  HELP,
  LOG,
  ITER,
  PARAM_ERR
};

typedef struct param{
  int fce;
  double num;
  int num_of_iters;
  double min;
  double max;
  double eps;
	
}SPARAM;


////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Funkcie //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

SPARAM parametry(int argc, char *argv[]){
  SPARAM param;
  
  if(argc == 4){
    if(strcmp (argv[1], "--log") == 0){
      if (((sscanf(argv[2], "%lf", &param.num)) == 1) && ((sscanf(argv[3], "%d", &param.num_of_iters)) == 1))
        param.fce = LOG;
      else 
        param.fce = PARAM_ERR;      
    }else{
		param.fce = PARAM_ERR;
	}		
   
  }     
  else if (argc == 5){
    if (strcmp (argv[1], "--iter") == 0){
      if (((sscanf(argv[2], "%lf", &param.min)) == 1) && 
        ((sscanf (argv[3], "%lf", &param.max)) == 1) &&
        ((sscanf (argv[4], "%lf", &param.eps)) == 1))
        param.fce = ITER;
    else 
      param.fce = PARAM_ERR;   
  }	
  else 
    param.fce = PARAM_ERR;	
  }  
  return param;
}



void printEMSG(int obsah){
  fprintf(stderr,"%s", ERRMSG[obsah]);
}	


/* *****************************************************************************
 * Vypocet prirodzeneho logaritmu pomocou taylorovho polynomu.
 */
 
double taylor_log(double x, unsigned int n){
	
	if(x > 0){
	
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
		
		for(unsigned int i = 2; i <= n; i++){
		
		dalsi_clen = prvy_clen * ((h2)*(i-1))/i;
		prvy_clen = dalsi_clen;
		result += dalsi_clen;
		
		
		}
		result = result * (-1);
	}else{
		
		return NAN;
	}
	return result;
	
	}else{
		
		return NAN;
	}
}
/* *****************************************************************************
 * Vypocet prirodzeneho logaritmu pomocou zretazenych zlomkou
 */

double cfrac_log(double x, unsigned int n){
	
	if(x > 0){
	
	double result;
	double clen = 0;
	double z = (x-1)/(1+x);
	double z2 = z*z;
	
	for(double i = n; i > 1; i--){
		
		clen = ((i-1)*(i-1)* z2 )/ ((2*i - 1) - clen);
	}
	
	result = (2*z) / (1 - clen);
	
	
	return result;
	
	}else{
		return NAN;
	}
}
/* *****************************************************************************
 * Funkcie pre vyhladavanie poctu iteracii
 */


// funkcia na porovnavanie cisel typu double 
 int compare_float(double f1, double f2, double precision)
 {
  
  if (((f1 - precision) < f2) && 
      ((f1 + precision) > f2))
   {
    return 1;
   }
  else
   {
    return 0;
   }
 }
 
 // povodna funkcia na vyhladanie poctu iteracii - nepouziva sa
 int cf_iteration(double num, double eps){

	unsigned int iterations = 0;

	double ref_val = log(num);
	
	
	while((compare_float(ref_val, cfrac_log(num, iterations), eps)) == 0){
	
		iterations++;
	
	}
	
	return iterations;

}

/* *****************************************************************************
 * Metoda bisekcie pre zretazene zlomky
 */

int bisection_cfrac(double min, double max, double eps){
		
	unsigned int iterations = 0;
	
	double min_value;
	double max_value;
	
	double mid;
	double mid_value;
	
	do{
		iterations++;
		
		min_value = cfrac_log(min, iterations);
		max_value = cfrac_log(max, iterations);
		
		mid = (min + max) / 2;
		mid_value = cfrac_log(mid, iterations);
		
		if(mid_value * max_value >= 0){
			
			max = mid;
			max_value = mid_value;
			
		}else{
			
			min = mid;
			min_value = mid_value;
			
			}	
		}while(fabs(max - min) > eps); 

	return iterations;

}

/* *****************************************************************************
 * Metoda bisekcie pre taylorov polynom
 */
 
int bisection_taylor(double min, double max, double eps){

	unsigned int iterations = 0;
	
	double min_value;
	double max_value;
	
	double mid;
	double mid_value;
	
	do{
		iterations++;
		
		min_value = taylor_log(min, iterations);
		max_value = taylor_log(max, iterations);
		
		mid = (min + max) / 2;
		mid_value = taylor_log(mid, iterations);
		
		if(mid_value * max_value >= 0){
			
			max = mid;
			max_value = mid_value;
			
			
		}else{
			
			min = mid;
			min_value = mid_value;
		
		}	
	}while(fabs(max - min) > eps);
		
		
	return iterations;
	

}

/* *****************************************************************************
 * Hlavna funkcia main. 
 */

int main(int argc, char *argv[]){
	
	SPARAM params = parametry(argc, argv);
	
	if (params.fce == PARAM_ERR){
    printEMSG(EPA);
    return EXIT_FAILURE;
	
	}
	else if(params.fce == LOG){
		printf("log(%.12g) = %.12g\n", params.num, log(params.num));
		printf("cf_log(%.12g) = %.12g\n", params.num, cfrac_log(params.num, params.num_of_iters));
		printf("taylor_log(%.12g) = %.12g\n",params.num, taylor_log(params.num, params.num_of_iters));		 
	
	}else if(params.fce == ITER){
		
		int taylor_iters = bisection_taylor(params.min,params.max, params.eps);
		int cf_iters = bisection_cfrac(params.min, params.max, params.eps);
		
		//int cf_iters = cf_iteration(params.max, params.eps);
		
		
		printf("log(%.12g) = %.12g\n", params.min, log(params.min));
		printf("log(%.12g) = %.12g\n", params.max, log(params.max));
		
		printf("continued fraction iterations = %d\n", cf_iters);
		printf("cf_log(%.12g) = %.12g\n",params.min, cfrac_log(params.min, cf_iters));
		printf("cf_log(%.12g) = %.12g\n",params.max, cfrac_log(params.max, cf_iters));
		
		printf("taylor_polynomial = %d\n", taylor_iters);
		printf("taylor_log(%.12g) = %.12g\n",params.min, taylor_log(params.min, taylor_iters));
		printf("taylor_log(%.12g) = %.12g\n",params.max, taylor_log(params.max, taylor_iters));
		
			
	
	}	
	
	return EXIT_SUCCESS;
}


	



