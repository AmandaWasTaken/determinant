#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <conio.h>
#endif

// Clear terminal
#define clear() do \
{ \
	printf("\e[1;1H\e[2J"); \
} while(0)	


int get_minor(int** m, char c){
  
  int min;
  switch(c){
	default: return 0;
	case 'a':
		min = m[1][1]*m[2][2] - m[1][2]*m[2][1];
		break;
      	case 'b':
        	min = m[1][0]*m[2][2] - m[1][2]*m[2][0];
        	break;
      	case 'c':
        	min = m[1][0]*m[2][1] - m[1][1]*m[2][0];
        	break;
  	}
  	return min;
}

int determinant(size_t size, int** m) {

	int det = 0;

	switch(size){
		case 1:
			return m[0][0];
			break;
		case 2:
			det = (m[0][0])*(m[1][1]) - (m[0][1])*(m[1][0]);  
			break;
		case 3:
	    		int a = m[0][0];
		    	int b = m[0][1];
		    	int c = m[0][2];
		   	int a_minor = get_minor(m, 'a');
		   	int b_minor = get_minor(m, 'b');   
		   	int c_minor = get_minor(m, 'c');
		   	det = a*a_minor - b*b_minor + c*c_minor; 
			break;
		default:
			fprintf(stderr, "Only 2x2 and 3x3 supported for now\n");
			exit(1);
	}
  	return det;
}

int** create_matrix(int row){

	int** mtx = malloc(row * sizeof(int *));
	if(!mtx){
		perror("Malloc failed");
		exit(1);
	}
	for(int i = 0; i < row; i++){
		mtx[i] = malloc(row * sizeof(int));
		for(int j = 0; j < row; j++){
			int n;
			printf("n: ");
			if(scanf("%i", &n) != 1){
				fprintf(stderr, "Invalid input\n");
				exit(1);
			}
			mtx[i][j] = n;
		}
	}
	return mtx;
}

void print_matrix(int** mtx, int row){

	clear();
	char idx = 'a';

	printf("Matrix:\n");
	for(int i = 0; i < row; i++){
		printf("[");
		for(int j = 0; j < row; j++){
			printf("%c: %3i ", idx, mtx[i][j]);
			idx++;
		}
		puts("]\n");
	}
}


void free_mtx(int** mtx, int row){

	for(int i = 0; i < row; i++){
        	free(mtx[i]);
	}
    	free(mtx);
}

int main(int argc, char** argv){

	if(argc < 2){
		fprintf(stderr, "Usage: %s (row length)", argv[0]);
		exit(1);
	}

	char* end;
	int rows = strtol(argv[1], &end, 10);
	if(*end != '\0'){
		printf("Couldn't convert rows\n");
		exit(1);
	}

	int** mtx = create_matrix(rows);
	print_matrix(mtx, rows);

	int det = determinant(rows, mtx);
	printf("Determinant: %i\n", det);
	free_mtx(mtx, rows);
	return 0;
}
