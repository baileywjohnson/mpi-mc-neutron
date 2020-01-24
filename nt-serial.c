#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

int main(int argc, char *argv[]){

	double C, A, H;
	int n;

	if(argc != 9){
		printf("usage: ./nt-serial -C <double> -A <double> -H <double> -n <int>\nA has to be less than C, all parameters > 0\n");
		exit(1);
	}

	int c;
	while((c = getopt(argc, argv, "C:A:H:n:")) != -1){
		switch(c){
			case 'C':
				C = atof(optarg);
				break;
			case 'A':
				A = atof(optarg);
				break;
			case 'H':
				H = atof(optarg);
				break;
			case 'n':
				n = atoi(optarg);
				break;
			case '?':
				exit(1);
				break;
			default:
				break;
		}
	}

	int r = 0;
	int b = 0;
	int t = 0;

	srand48(time(NULL));

	int i;
	for(i = 0; i < n; i++){
		double d = 0;
		double x = 0;
		bool a = true;
		while(a){
			double u = drand48();
			double L = ((-1) * (1/C)) * (log(u));
			x = x + L * cos(d);
			if(x < 0){
				r = r + 1;
				a = false;
			}
			else if(x >= H){
				t = t + 1;
				a = false;
			}
			else if(u < (A/C)){
				b = b + 1;
				a = false;
			}
			else{
				d = u * M_PI;
			}	
		}
	}
	//printf("reflected (r) = %i, absorbed (b) = %i, transmitted (t) = %i\nr/n = %f, b/n = %f, t/n = %f\n", r, b, t, ((double)r/(double)n), ((double)b/(double)n), ((double)t/(double)n));	
	printf("%f\n%f\n%f", ((double)r/(double)n), ((double)b/(double)n), ((double)t/(double)n));	
}
