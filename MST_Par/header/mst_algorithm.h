/*
 * mst_algorithm.h
 *
 *  Created on: May 9, 2022
 *      Author: ege
 */

#ifndef MST_ALGORITHM_H_
#define MST_ALGORITHM_H_

#include  <semaphore.h>
#include  <stdint.h>


#define EMPTY                        (255)

#define NODE_IS_ACTIVE               (1)
#define NODE_IS_NOT_ACTIVE           (0)

#define NUMBER_OF_NODES              (2048)
#define NUMBER_OF_EDGE_LIM           (NUMBER_OF_NODES - 1)

#define PRINT_TREE_ARRAYS            (0)

#define NUMBER_OF_THREADS            (4)
#define NUMBER_OF_NODES_PER_THREAD   (NUMBER_OF_NODES)/NUMBER_OF_THREADS

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

	typedef struct
	{
		unsigned int src_index;
		unsigned int dest_index;
		unsigned int value;
	}local_min_type_t;

	typedef struct
	{
	  unsigned int id;
	  unsigned int nodes[2];
	  local_min_type_t min;
	}mst_thread_type_t;


extern unsigned int edges[NUMBER_OF_NODES][NUMBER_OF_NODES];

void random_edge_generator();
void mst_init(treetype_t *mst);
pathtype_t find_min_edge_in_active_nodes(treetype_t *mst, uint8_t start_node, uint8_t end_node);
void add_path_to_tree(treetype_t *mst, pathtype_t *path_result);

void slave_thread0_func (void *p);
void slave_thread1_func (void *p);
void slave_thread2_func (void *p);
void slave_thread3_func (void *p);
void master_thread_func (void *p);

void thread_node_assign();

extern treetype_t mst ;
extern sem_t sem_thread0, sem_thread1,sem_thread2, sem_thread3;
extern sem_t sem_master0, sem_master1, sem_master2, sem_master3;

#endif /* MST_ALGORITHM_H_ */
