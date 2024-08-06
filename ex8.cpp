#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
	const int ARRAY_SIZE = 100;
	srand(time(NULL));

	int maxValue = 100;
	int classes = 10;
	int array[ARRAY_SIZE];
	int histograma[classes];

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		array[i] = rand() % maxValue;
	}

	for (int i = 0; i < classes; i++)
	{
		histograma[i] = 0;
	}
	

#pragma omp parallel
	{
#pragma omp for
		for (int i = 0; i < ARRAY_SIZE; i++)
		{
			int classe = array[i] / classes;

#pragma omp critical
			histograma[classe] += 1;
		}
	}
	printf("Vetor gerado:\n");
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\nHistograma:\n");
	for (int i = 0; i < classes; i++)
	{
		printf("%d-%d - %d", i * classes, (i + 1) * classes - 1, histograma[i]);
		printf("\n");
	}

	return 0;
}
