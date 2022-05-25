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

pthread_t thread0;

int main()
{

	srand(time(NULL));

    pthread_create( &thread0,
    		        NULL    ,
		            &thread0_func,
		            NULL
		          );

	pthread_join(thread0,NULL);


}
