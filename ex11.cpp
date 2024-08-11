#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <queue>

using namespace std;

int main(int argc, char *argv[])
{
	srand(time(NULL));

  int lastPosition = 0;

  queue<int> queue;
  int currentAmount = 0;
  const int MAX_SIZE = 10;

#pragma omp parallel shared(queue, currentAmount)
	{
    #pragma omp single nowait
{
  while(true) {
    if(currentAmount >= 10)
     continue;

    int number = rand();
    printf("Thread %d produziu %d\n",omp_get_thread_num() ,number);

    queue.push(number);

    #pragma omp atomic
    currentAmount ++;
  }

}

  while(true) {
    #pragma omp critical
    {
      if(currentAmount > 0) {
        int numero;
        numero = queue.front();
        queue.pop();
        currentAmount--;

        printf("Thread %d consumiu %d\n",omp_get_thread_num() ,numero);
      }
    }
  }
    
		
	}

	return 0;
}