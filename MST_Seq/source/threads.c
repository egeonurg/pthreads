/*
 * threads.c
 *
 *  Created on: May 9, 2022
 *      Author: ege
 */

#include <time.h>
#include <stdio.h>

#include <stdlib.h>
#include "mst_algorithm.h"

pathtype_t path_result;
treetype_t mst ;
double time_spent = 0 ;

void thread0_func(void *p)
	{
		mst_init(&mst);
		random_edge_generator();

		clock_t begin = clock();  // To get run-time stats

		while(mst.edges_left)
			{
				path_result = find_min_edge_in_active_nodes(&mst);
				add_path_to_tree(&mst, &path_result);
			}

		clock_t end = clock();    // To get run-time stats

		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;     // To get run-time stats

		printf("Minimum weighted tree is = %d \n\n", mst.weight);

		printf("\n %f", time_spent);

//#if ( PRINT_TREE_ARRAYS)
//		for(int i = 0 ; i< NUMBER_OF_NODES; i++)
//			{
//				for(int j = 0 ; j< NBER_OF_NODES; j++)
//					{
//						printf("  %d  ",mst.tree[i][j]);
//					}
//				printf("\n");
//			}
//#endif


		pthread_exit(NULL);
	}
