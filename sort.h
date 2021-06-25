#pragma once

#define LOADSIZE 40

class pSort {

public:
   typedef enum {
   	BEST,
   	QUICK,
   	MERGE   	
   }  SortType;

   typedef struct {
      long long key;
      char payload[LOADSIZE];
   } dataType;
/*    void init(); // Initialize called before sorting
   void close(); // Initialize called after sorting/searching
   int sort(dataType **data, int *ndata, SortType sorter); // Return 0 on success, 1 on failure
   char *search(dataType *data, int ndata, long long key); // Return the payload pointer*/

   void init();
   void print(dataType *data, long long low, long long high);
   void close();
   void sort(dataType *data, long long ndata, SortType sorter=BEST); 
   void swap(dataType *data1, dataType *data2);
   long long partition (dataType *data, long long low, long long high); 
   void quick_sort(dataType *data, long long low, long long high);
   //int getMaximum(dataType *data, int low, int high); 
   //void unit_sort(dataType *data, int low, int high, int exp); 
   //void radix_sort(dataType *data, int low, int high);
   void merge(dataType *data, long long low, long long center, long long high);
   void merge_sort(dataType *data, long long low, long long high);
   void heapify(dataType *data, long long n, long long i); 
   void heap_sort(dataType *data, long long n); 
   void Rearrange(dataType *data, long long ndata, long long size, long long index, long long offset);
   bool search(dataType *data, long long low, long long high, long long key, char* result); 


};
