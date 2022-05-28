/*
 * threads.c
 *
 *  Created on: May 9, 2022
 *      Author: ege
 */

#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "mst_algorithm.h"

double time_spent = 0 ;
int first_tour = 0 ;
pathtype_t path_result ;

#define GLOBAL_MINIMUM 1

mst_thread_type_t threads[NUMBER_OF_THREADS];

void thread_node_assign()
	{
		for(int j = 0 ; j< NUMBER_OF_THREADS; j++)
			{
				threads[j].id = j;

				for(int i = 0 ; i< NUMBER_OF_NODES_PER_THREAD; i++)
					{
						threads[j].nodes[0] = NUMBER_OF_NODES_PER_THREAD*threads[j].id  ;
						threads[j].nodes[1] = NUMBER_OF_NODES_PER_THREAD -1 + NUMBER_OF_NODES_PER_THREAD*threads[j].id   ;
					}
				threads[j].min.value      = 0 ;
				threads[j].min.src_index  = 0 ;
				threads[j].min.dest_index = 0 ;
			}
	}

void master_sem_wait_all(void)
	{
		sem_wait(&sem_master0);
		sem_wait(&sem_master1);
		sem_wait(&sem_master2);
		sem_wait(&sem_master3);
	}

void master_sem_post_all(void)
	{
		sem_post(&sem_thread0);
		sem_post(&sem_thread1);
		sem_post(&sem_thread2);
		sem_post(&sem_thread3);
	}

void slave_thread0_func(void *p)
	{
		uint8_t slave_thread0_id = 0 ;
		pathtype_t local_min ;

		while(1)
			{
		        sem_wait(&sem_thread0);
		       // local_min = find_min_edge_in_active_nodes(&mst, threads[slave_thread0_id].nodes[0], threads[slave_thread0_id].nodes[NUMBER_OF_NODES_PER_THREAD-1]);
		        // Critical Section
				pathtype_t path;

					path.dest_index = 0xFF;
					path.src_index  = 0xFF;
					path.weight     = 0xFF;

					int min = 255;

					for (int src_node = threads[slave_thread0_id].nodes[0]; src_node < threads[slave_thread0_id].nodes[1] + 1; src_node++)
						{

							if (mst.nodes[src_node] == NODE_IS_ACTIVE)
								{
									for (int dest_node = 0; dest_node < NUMBER_OF_NODES; dest_node++)
										{
											if ((edges[dest_node][src_node] < min) && (mst.nodes[dest_node] == NODE_IS_NOT_ACTIVE))
												{
													min = edges[dest_node][src_node];

													path.dest_index = dest_node;
													path.src_index = src_node;
													path.weight = edges[dest_node][src_node];
													if (min == GLOBAL_MINIMUM)
														{
															break;
														}
												}
										}
								}
						}
		        threads[slave_thread0_id].min.src_index  = path.src_index;
		        threads[slave_thread0_id].min.dest_index = path.dest_index;
		        threads[slave_thread0_id].min.value      = path.weight;

			 //   printf(" THREAD %d WORKING !!! \n", id);
		        sem_post(&sem_master0);
			}

		pthread_exit(NULL);
	}

void slave_thread1_func(void *p)
	{
		uint8_t slave_thread1_id = 1 ;
		pathtype_t local_min  ;

		while(1)
			{
		        sem_wait(&sem_thread1);
		      //  local_min = find_min_edge_in_active_nodes(&mst, threads[slave_thread1_id].nodes[0], threads[slave_thread1_id].nodes[1]);
		        // Critical Section
				pathtype_t path;

					path.dest_index = 0xFF;
					path.src_index  = 0xFF;
					path.weight     = 0xFF;

					int min = 255;

					for (int src_node = threads[slave_thread1_id].nodes[0]; src_node < threads[slave_thread1_id].nodes[1] + 1; src_node++)
						{
							if (mst.nodes[src_node] == NODE_IS_ACTIVE)
								{
									for (int dest_node = 0; dest_node < NUMBER_OF_NODES; dest_node++)
										{
											if ((edges[dest_node][src_node] < min) && (mst.nodes[dest_node] == NODE_IS_NOT_ACTIVE))
												{
													min = edges[dest_node][src_node];

													path.dest_index = dest_node;
													path.src_index = src_node;
													path.weight = edges[dest_node][src_node];

												}
										}
								}
						}
		        threads[slave_thread1_id].min.src_index  = path.src_index;
		        threads[slave_thread1_id].min.dest_index = path.dest_index;
		        threads[slave_thread1_id].min.value      = path.weight;

			  //  printf(" THREAD %d WORKING !!! \n", id);
		        sem_post(&sem_master1);
			}

		pthread_exit(NULL);
	}

void slave_thread2_func(void *p)
	{
		uint8_t slave_thread2_id = 2 ;
		pathtype_t local_min  ;

		while(1)
			{
		        sem_wait(&sem_thread2);
//		        local_min = find_min_edge_in_active_nodes(&mst, threads[slave_thread2_id].nodes[0], threads[slave_thread2_id].nodes[1]);
		        // Critical Section
				pathtype_t path;

				path.dest_index = 0xFF;
				path.src_index  = 0xFF;
				path.weight     = 0xFF;

				int min = 255;

				for (int src_node = threads[slave_thread2_id].nodes[0]; src_node < threads[slave_thread2_id].nodes[1] + 1; src_node++)
					{

						if (mst.nodes[src_node] == NODE_IS_ACTIVE)
							{
								for (int dest_node = 0; dest_node < NUMBER_OF_NODES; dest_node++)
									{
										if ((edges[dest_node][src_node] < min) && (mst.nodes[dest_node] == NODE_IS_NOT_ACTIVE))
											{
												min = edges[dest_node][src_node];

												path.dest_index = dest_node;
												path.src_index = src_node;
												path.weight = edges[dest_node][src_node];
											}


									}
							}
					}


		        threads[slave_thread2_id].min.src_index  = path.src_index;
		        threads[slave_thread2_id].min.dest_index = path.dest_index;
		        threads[slave_thread2_id].min.value      = path.weight;

			   // printf(" THREAD %d WORKING !!! \n", id);
			    sem_post(&sem_master2);
			}

		pthread_exit(NULL);
	}

void slave_thread3_func(void *p)
	{
		uint8_t slave_thread3_id = 3;
		pathtype_t local_min  ;

		while(1)
			{
		        sem_wait(&sem_thread3);
		        //local_min = find_min_edge_in_active_nodes(&mst, threads[slave_thread3_id].nodes[0], threads[slave_thread3_id].nodes[1]);
		        // Critical Section
				pathtype_t path;

				path.dest_index = 0xFF;
				path.src_index  = 0xFF;
				path.weight     = 0xFF;

				int min = 255;

				for (int src_node = threads[slave_thread3_id].nodes[0]; src_node < threads[slave_thread3_id].nodes[1] + 1; src_node++)
					{

						if (mst.nodes[src_node] == NODE_IS_ACTIVE)
							{
								for (int dest_node = 0; dest_node < NUMBER_OF_NODES; dest_node++)
									{
										if ((edges[dest_node][src_node] < min) && (mst.nodes[dest_node] == NODE_IS_NOT_ACTIVE))
											{
												min = edges[dest_node][src_node];

												path.dest_index = dest_node;
												path.src_index = src_node;
												path.weight = edges[dest_node][src_node];
											}
									}
							}
					}

		        threads[slave_thread3_id].min.src_index  = path.src_index;
		        threads[slave_thread3_id].min.dest_index = path.dest_index;
		        threads[slave_thread3_id].min.value      = path.weight;

			   // printf(" THREAD %d WORKING !!! \n", id);
		        sem_post(&sem_master3);
			}

		pthread_exit(NULL);
	}

void master_thread_func(void *p)

	{
		int min       = 255 ;
		int min_index = 255 ;
		clock_t begin = 0 ;



		while (1)
			{
				master_sem_wait_all();

				if (first_tour != 0)
					{

						//printf(" MASTER THREAD IS CALCULATING !!! \n");

						if (mst.edges_left != 0)
							{
								min = 255;
								min_index = 255;

								for (int i = 0; i < NUMBER_OF_THREADS; i++)
									{
										if (threads[i].min.value <= min )
											{
												min = threads[i].min.value;
												min_index = i;
											}
									}
								// printf("-------MIN VAL IS THE E %d TH TREAD------- \n ", min_index);

								path_result.dest_index =	threads[min_index].min.dest_index;
								path_result.src_index  =	threads[min_index].min.src_index;
								path_result.weight     = 	threads[min_index].min.value;


								add_path_to_tree(&mst, &path_result);
							}
						else
							{
								clock_t end = clock();  // To get run-time stats

								time_spent = (double) (end - begin)/CLOCKS_PER_SEC; // To get run-time stats
								printf("TIME SPENT IS = == = = %f", time_spent);
								printf("Minimum weighted tree is = %d \n\n",
										mst.weight);

#if ( PRINT_TREE_ARRAYS)
//														for (int i = 0; i < NUMBER_OF_NODES; i++)
//															{
//																for (int j = 0; j < NUMBER_OF_NODES; j++)
//																	{
//																		printf("  %d  ", mst.tree[i][j]);
//																	}
//																printf("\n");
//															}
#endif
														pthread_exit(NULL);

							}


					}
				else
					{
						printf(" MASTER THREAD FIRST TOUR !!! \n");
						first_tour++;
						 begin = clock();  // To get run-time stats
					}

				master_sem_post_all();

			}

		pthread_exit(NULL);
	}
