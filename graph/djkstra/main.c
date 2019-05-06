#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


int main(){
    int number_of_vertices = 0;
	int number_of_edges = 0;
    int start = 0;
    int finish = 0;
	if (scanf("%d%d%d%d", &number_of_vertices, &number_of_edges, &start, &finish) != 4){
		error("bad number of lines");
	}
    
    return 0;
}