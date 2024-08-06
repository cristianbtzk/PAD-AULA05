#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
	const int ARRAY_SIZE = 10000;
	srand(time(NULL));

	int array[ARRAY_SIZE];

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		array[i] = 0;
	}

#pragma omp parallel
	{
		// Preenche o vetor
		int numeroThreads = omp_get_num_threads();
		int numThread = omp_get_thread_num();
		int indexInicial = ARRAY_SIZE / numeroThreads * numThread;
		int indexFinal;
		// Divisão de trabalho entre as threads
		// Não houve uso do omp for para não forçar a sincronização
		if (numeroThreads == numThread + 1)
			indexFinal = ARRAY_SIZE;
		else
			indexFinal = ARRAY_SIZE / numeroThreads * (numThread + 1);

		for (int i = indexInicial; i < indexFinal; i++)
		{
			array[i] = i;
		}

// Sem o barrier, nem todas as threads teriam atualizado o array antes do próximo trecho
#pragma omp barrier
#pragma omp single
		{
			for (int i = 0; i < ARRAY_SIZE; i++)
			{
				if (array[i] != i)
				{
					printf("Valor inválido: i = %d, valor = %d", i, array[i]);
				}
			}
		}
	}

	return 0;
}
