/*
 * main.c
 *
 *  Created on: Mar 7, 2022
 *      Author: ege
 */

#include <sched.h>
#include <unistd.h>
#include <pthread.h>
#include "threads.h"
#include "mst_algorithm.h"

pthread_t slave_thread0, slave_thread1, slave_thread2, slave_thread3, master_thread;

sem_t sem_thread0, sem_thread1, sem_thread2, sem_thread3;
sem_t sem_master0, sem_master1, sem_master2, sem_master3;


treetype_t mst ;


int main()
{
	srand(time(NULL));

	mst_init(&mst);
	random_edge_generator();
	thread_node_assign();

	/* Semaphores for the slave tasks, which synchronizes it to the master */

	sem_init(&sem_thread0, 0, 0);
	sem_init(&sem_thread1, 0, 0);
	sem_init(&sem_thread2, 0, 0);
	sem_init(&sem_thread3, 0, 0);

	/* Semaphores for the master task, which synchronizes master task to the end of slave task events */
	sem_init(&sem_master0, 0, 1);
	sem_init(&sem_master1, 0, 1);
	sem_init(&sem_master2, 0, 1);
	sem_init(&sem_master3, 0, 1);

    pthread_create( &slave_thread0, NULL, &slave_thread0_func, NULL);
    pthread_create( &slave_thread1, NULL, &slave_thread1_func, NULL);
    pthread_create( &slave_thread2, NULL, &slave_thread2_func, NULL);
    pthread_create( &slave_thread3, NULL, &slave_thread3_func, NULL);
    pthread_create( &master_thread, NULL, &master_thread_func, NULL);

	pthread_join(master_thread,NULL);
	pthread_join(slave_thread0,NULL);
	pthread_join(slave_thread1,NULL);
	pthread_join(slave_thread2,NULL);
	pthread_join(slave_thread3,NULL);

	while(1)
		{

		}
}
