#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h>
#include <unistd.h>
typedef struct {
	int** matrix;
	int column;
	int lines;
	int sum;
} casual_struct;
void* sum(void* surprise)
{	
	casual_struct* element = (casual_struct*)surprise;
	element->sum = 0;
	for(int i=0; i<element->lines;i++)
		element->sum += element->matrix[i][element->column];
	return 0;

}
int main(int argc, char** argv)
{
	int nrLines, nrColumns;
	scanf("%d %d", &nrLines, &nrColumns);
	pthread_t threads[nrColumns];
	int** mat = (int**)malloc(nrLines*sizeof(int*));
	for(int i=0; i<nrLines; i++)
	{
		mat[i] = (int*)malloc(nrColumns*sizeof(int));
		for (int j=0; j<nrColumns; j++)
		{
			mat[i][j] = i*nrColumns + j;
			printf("%d ",mat[i][j]);
			//iscanf("%d", &mat[i][j]);
		}
		printf("\n");
	}
	casual_struct* casual_list = malloc(nrColumns * sizeof(casual_struct));
	for(int j=0; j<nrColumns; j++)
	{
		casual_list[j].matrix = mat;
		
		casual_list[j].column = j;
		casual_list[j].lines = nrLines;
		pthread_create(&threads[j], NULL, &sum,(void *)&casual_list[j]);
	}
	for(int j=0; j<nrColumns; j++)
	{
		pthread_join(threads[j], NULL);
		printf("For column %d, the sum is: %d\n",j, casual_list[j].sum);
	}
	return 0;
}
