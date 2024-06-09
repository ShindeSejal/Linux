#include<stdio.h>
#include<pthread.h>

int shared_resource = 0;
pthread_mutex_t lock;

void *increment_resource(void *arg);


int main()
{

	pthread_t threads[2];

	if(pthread_mutex_init(&lock, NULL) != 0)
	{
		printf("Mutex init failed\n");
		return 1;
	
	}

	for(int i=0;i<2;i++)
	{
		if(pthread_create(&threads[i], NULL, increment_resource, NULL) != 0)
		{
			printf("Thread creation failed\n");
			return 1;
			
		}
	
	}

	for(int i=0;i<2;i++)
	{
		pthread_join(threads[i],NULL);
	
	}

	pthread_mutex_destroy(&lock);

	printf("Final value of shared resource : %d\n",shared_resource);

	return 0;

}

void *increment_resource(void *arg)
{
	for(int i = 0 ; i < 100000 ; i++ )
	{
		pthread_mutex_lock(&lock);

		shared_resource++;

		pthread_mutex_unlock(&lock);
	}
	return NULL;
}
