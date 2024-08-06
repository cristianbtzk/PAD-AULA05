#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <thread>

int main(int argc, char *argv[])
{
	const int ARRAY_SIZE = 1000;

	srand(time(NULL));
	int pontosCirculo, pontosQuadrado = 0;

#pragma omp parallel
	{
#pragma omp for
		for (int i = 0; i < ARRAY_SIZE; i++)
		{
			float x = (float)rand() / RAND_MAX;
			float y = (float)rand() / RAND_MAX;
			float d = x * x + y * y;
#pragma omp critical
			{
				pontosQuadrado++;
				if (d <= 1)
				{
					pontosCirculo++;
				}
			}
		}
	}
	printf("PC: %d\n", pontosCirculo);
	printf("PQ: %d\n", pontosQuadrado);
	float estimativaPI = 4 * static_cast<float>(pontosCirculo) / pontosQuadrado;

	printf("Estimativa de PI: %f\n", estimativaPI);
	return 0;
}
