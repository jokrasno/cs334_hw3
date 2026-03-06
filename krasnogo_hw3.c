/*
 * A multithreaded sorting application
 *
 * Concepts: implicit threading, global variables,
 * 	     structure, parallel tasks, fork-join 
 * 	     strategy, sorting algorithms, etc.
 *
 * CS334: Operating Systems homework assignment 3
 * TOTAL POINTS: 100
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// #include "DataSet1000.c"

/* preprocessor constants */
#define SIZE 10
#define NUM_THREADS 3

/* declaration of thread entry points */
void *sorter(void *param);	// thread for basic sorting algorithm
void *merger(void *param);	// thread for merging sorted data subsets

/* global variables for sorting data */
int dataSet[SIZE] = {7,12,19,3,18,4,2,6,15,8};
int result[SIZE];

/**
 * This structure will be used to pass parameters to both sorter and merger threads.
 * In case of sorter thread, startIndex and endIndex represent the subrange of dataset.
 * In case of merger thread, the startIndex and endIndex represent the staring indexes of the 
 * first and the second subranges of the entire dataset
 */
struct subRange{ 	// a structure for passing the subrange of the dataset
	int startIndex;	
	int endIndex;
};
typedef struct subRange SubRange;


/**
 * main method 
 *
 * Note: entry point of the parent thread
 */
int main(int argc, char *argv[])
{
  /* local variable declarations */
  pthread_t tid[NUM_THREADS];

 
  //======================>> 15 POINTS <<=====================
  /* create the first sorter thread (thread_0) with appropriate subrange */
  SubRange *sRange = (SubRange *)malloc(sizeof(SubRange));	// create a SubRange pointer variable to set the 
  								// subrange of dataset before passing to the thread

  // initialize attributes
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  
  sRange->startIndex = 0;
  sRange->endIndex = SIZE/2;
  pthread_create(&tid[0], &attr, sorter, sRange);


  
  //======================>> 15 POINTS <<=====================
  /* create the second sorter thread (thread_1) with appropriate subrange -- as above */
  // -----DUMMIED UP -- WRITE YOUR CODE HERE------ //

  SubRange *sRange2 = (SubRange *)malloc(sizeof(SubRange));
  sRange2->startIndex = SIZE/2;
  sRange2->endIndex = SIZE;
  pthread_create(&tid[1], &attr, sorter, sRange2);



  //======================>> 10 POINTS <<=====================
  /* wait for the sorter threads to return to the parent thread -- fork-join strategy */
  for(int i = 0; i < NUM_THREADS-1; i++) {
  	// -----DUMMIED UP -- WRITE YOUR CODE HERE------- //
    pthread_join(tid[i], NULL);
  } // end of for


  //======================>> 15 POINTS <<=====================
  /* Now created the merger thread with appropriate subrange 
   *
   * Note: Here, the 'SubRange' struct will contain the startIndex values of
   * thread_0 and thread_1 in the startIndex and endIndex, respectively.
   * */
   SubRange *mRange = (SubRange *)malloc(sizeof(SubRange));
   mRange->startIndex = 0;
   mRange->endIndex = SIZE/2;
   pthread_create(&tid[2], &attr, merger, mRange);
  



  //======================>> 5 POINTS <<=====================
  /* wait for the merger thread to finish */
  // -----DUMMIED UP -- WRITE YOUR CODE HERE------ //
  pthread_join(tid[2], NULL);



  /* output the sorted array */
  printf("\nSorted data set: ");
  for(int i = 0; i < SIZE; i++) {
  	printf("%d ", dataSet[i]);	// currently prints unsorted data set
  }
  printf("\n");

  return 0;
} // end of main

/* comparison algorithm for quicksort */
int comp(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}

/*
 * definition of the entry point for sorter thread
 *
 * Note: implement any sorting algorithm of your choice
 */
void *sorter(void *param)
{
    SubRange *range = (SubRange *)param;

    //======================>> 20 POINTS <<=====================
    // -----DUMMIED UP -- WRITE YOUR CODE HERE------ //
    // just used the built in quicksort
    qsort(dataSet + range->startIndex, range->endIndex - range->startIndex, sizeof(int), comp);

    /* exit sorter thread */
    // -----DUMMIED UP -- WRITE YOUR CODE HERE------ //
    pthread_exit(0);

} // end of sorter

/**
 * definition of the entry point for the  merger thread
 *
 * Note: Use merge sort for merging two lists (subranges)
 *       passed to 'thread_0' and 'thread_1'
 */
void *merger(void *param) 
{
    SubRange *range = (SubRange *)param;
    int sorted[SIZE];
    //======================>> 20 POINTS <<=====================
    /* Implement merge sort for merging the two sublist of the dataset */
    // -----DUMMIED UP -- WRITE YOUR CODE HERE------ //
    int p1 = range->startIndex;
    int p2 = range->endIndex;

    for (int i = 0; i < SIZE; i++)
    {
      // base cases
      if (p1 >= range->endIndex) 
      {
        sorted[i] = dataSet[p2];
        p2++;
      }
      else if (p2 >= SIZE) 
      {
        sorted[i] = dataSet[p1];
        p1++;
      }
      // if element in first half less than element in second, first goes first
      else if (dataSet[p1] <= dataSet[p2])
      {
        sorted[i] = dataSet[p1];
        p1++;
      }
      // otherwise second goes first
      else 
      {
        sorted[i] = dataSet[p2];
        p2++;
      }
    }
    
    // copy sorted array over
    for (int i = 0; i < SIZE; i++)
    {
      dataSet[i] = sorted[i];
    }
    /* exit merger thread */
    // -----DUMMIED UP -- WRITE YOUR CODE HERE------ //
    pthread_exit(0);

} // end of merger
