#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *do_something(void*arg){
	int *thread_id = (int *)arg;
	printf("Thread %d : I'm alive! \n", *thread_id);
	sleep(2);
	return NULL;
}

int main() {
  int num_threads = 3;
  pthread_t threads[num_threads];

  // Create threads
  for (int i = 0; i < num_threads; i++) {
    int *thread_id = malloc(sizeof(int));
    *thread_id = i;
    if (pthread_create(&threads[i], NULL, do_something, thread_id) != 0) {
      perror("pthread_create failed");
      return 1;
    }
printf("Main thread: I created %d threads.\n", num_threads);

  // Join threads (optional, not shown here)
  // for (int i = 0; i < num_threads; i++) {
  //   pthread_join(threads[i], NULL);
  // }

  // Simulate main thread work
  sleep(5);

  printf("Main thread: Finishing...\n");

  // Free memory allocated for thread IDs (avoid memory leaks)
  for (int i = 0; i < num_threads; i++) {
    free(thread_id);
  }

  return 0;
}

