/*
 * mst_algorithm.c
 *
 *  Created on: May 9, 2022
 *      Author: ege
 */
#include <stdio.h>
#include <stdlib.h>
#include "mst_algorithm.h"

unsigned int edges[NUMBER_OF_NODES][NUMBER_OF_NODES];

// A C program for Prim's Minimum
// Spanning Tree (MST) algorithm. The program is
// for adjacency matrix representation of the graph

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

void random_edge_generator()
	{
		unsigned int buffer = 0 ;

		for(unsigned int i = 0 ; i< NUMBER_OF_NODES; i++)
			{
				for(unsigned int j = 0 ; j< NUMBER_OF_NODES; j++)
					{
						if(i==j) // Diagonal is equal to zero paths to itself
							{
								edges[i][j] = EMPTY;
							}
						else if (j < i) // Random number assignment for lower triangle
							{

								buffer = rand() % 9 + 1;

								if(buffer == 0 )
									{
										edges[i][j] = 0;
									}
								else
									{
										edges[i][j] = buffer;
									}
							}
					}
			}
		for(unsigned int i = 0 ; i< NUMBER_OF_NODES; i++)
					{
						for(unsigned int j = 0 ; j< NUMBER_OF_NODES; j++)
							{
								edges[i][j] = edges[j][i];
		#if ( PRINT_TREE_ARRAYS)
								printf("   %d   ",edges[i][j]);
		#endif
							}
		#if ( PRINT_TREE_ARRAYS)
						printf("\n");
		#endif
					}
				printf("\n");

	}


void mst_init(treetype_t *mst)
{
	mst->edges_left     = NUMBER_OF_EDGE_LIM;
	mst->weight         = 0;
	mst->nodes[0]       = NODE_IS_ACTIVE;
}

pathtype_t find_min_edge_in_active_nodes(treetype_t *mst)
	{
		pathtype_t path;
		int min = 255;

		for(unsigned int src_node = 0 ; src_node < NUMBER_OF_NODES ; src_node++)
			{
				if(mst->nodes[src_node] == NODE_IS_ACTIVE)
					{
						for(unsigned int dest_node = 0 ; dest_node < NUMBER_OF_NODES ; dest_node++)
							{
								if((edges[dest_node][src_node] < min) && (mst->nodes[dest_node] == NODE_IS_NOT_ACTIVE))
									{
										min = edges[dest_node][src_node];

										path.dest_index = dest_node;
										path.src_index  = src_node;
										path.weight     = edges[dest_node][src_node];
									}
							}
					}
			}

		return(path);
	}

void add_path_to_tree(treetype_t *mst, pathtype_t *path_result)
	{

		mst->nodes[path_result->dest_index] = NODE_IS_ACTIVE;

		mst->tree[path_result->dest_index][path_result->src_index] =
				edges[path_result->dest_index][path_result->src_index];

		edges[path_result->dest_index][path_result->src_index] = 255;
		edges[path_result->src_index][path_result->dest_index] = 255;

#if ( PRINT_TREE_ARRAYS)
		printf("Source = %d  -- Destination = %d -- Weight = %d\n",path_result->src_index,path_result->dest_index, path_result->weight);
#endif


		mst->weight = mst->weight + path_result->weight;
		mst->edges_left -- ;
	}









