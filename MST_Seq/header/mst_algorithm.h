/*
 * mst_algorithm.h
 *
 *  Created on: May 9, 2022
 *      Author: ege
 */

#ifndef MST_ALGORITHM_H_
#define MST_ALGORITHM_H_

#define EMPTY                      (255)

#define NODE_IS_ACTIVE               (1)
#define NODE_IS_NOT_ACTIVE           (0)

#define NUMBER_OF_NODES              (2048)
#define NUMBER_OF_EDGE_LIM           (NUMBER_OF_NODES - 1)

#define PRINT_TREE_ARRAYS            (0)

typedef struct
	{
		unsigned int edges_left;
		unsigned int nodes[NUMBER_OF_NODES];
		unsigned int tree [NUMBER_OF_NODES][NUMBER_OF_NODES];
		unsigned int weight;
	}treetype_t;

typedef struct
	{
		unsigned int src_index;
		unsigned int dest_index;
		unsigned int weight;
	}pathtype_t;

extern unsigned int edges[NUMBER_OF_NODES][NUMBER_OF_NODES];

void random_edge_generator();
void mst_init(treetype_t *mst);
pathtype_t find_min_edge_in_active_nodes(treetype_t *mst);
void add_path_to_tree(treetype_t *mst, pathtype_t *path_result);


#endif /* MST_ALGORITHM_H_ */
