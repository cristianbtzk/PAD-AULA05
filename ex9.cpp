#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
	const int ARRAY_SIZE = 100;
	srand(time(NULL));

	int array[ARRAY_SIZE];

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		array[i] = rand() % 10;
	}

	int countPar;
	int countImpar;

#pragma omp parallel
	{
#pragma omp for
		for (int i = 0; i < ARRAY_SIZE; i++)
		{
			bool par = array[i] % 2 == 0;

			if (par)

#pragma omp atomic
				countPar += 1;
			else
#pragma omp atomic
				countImpar += 1;
		}
	}
	printf("Vetor gerado:\n");
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\nPares: %d. Ímpares: %d\n", countPar, countImpar);

	return 0;
}
