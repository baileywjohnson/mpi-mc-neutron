#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char *argv[]){

	MPI_Init(NULL, NULL);

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	srand48(rank * time(NULL));

	double C, A, H;
	int n;

	if(argc != 9){
		if(rank == 0){
			printf("usage: ./nt-serial -C <double> -A <double> -H <double> -n <int>\nA has to be less than C, all parameters > 0\n");
		}
		MPI_Finalize();
		exit(0);
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

	int i;
	for(i=0; i<n; i++){
		if(i % size != rank) continue;

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

	int glob_r, glob_b, glob_t;
	MPI_Reduce(&r, &glob_r, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&b, &glob_b, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&t, &glob_t, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if(rank == 0){
		printf("reflected (r) = %i, absorbed (b) = %i, transmitted (t) = %i\nr/n = %f, b/n = %f, t/n = %f\n", glob_r, glob_b, glob_t, ((double)glob_r/(double)n), ((double)glob_b/(double)n), ((double)glob_t/(double)n));
	}

	MPI_Finalize();
	return 0;

}
