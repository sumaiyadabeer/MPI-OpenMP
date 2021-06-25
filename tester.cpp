#include <iostream>
#include <ctime> 
#include <time.h> 
#include <cstdlib>
#define LOADSIZE	40
#include <mpi.h>
#include "sort.h"
#include <bits/stdc++.h>
const int MINCOUNT = 100;
const int MAXCOUNT = 200;

inline int randomCount() { return MINCOUNT + rand()%(MAXCOUNT-MINCOUNT+1); }
char randomChar() {
    
    std::string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int pos = rand()%str.size();
    return str[pos];
}

pSort::dataType* generate(long num_of_records)
{
    //Creating an array of structure of type "dataType" declared in sort.h

    pSort::dataType *data = new pSort::dataType[num_of_records];

    srand(time(0));
    for (long long i = 0; i < num_of_records; i++) {
        data[i].key = rand(); 
	//data[i].key = -1*rand(); 
        for(int j=0; j<LOADSIZE; j++) data[i].payload[j] = randomChar();
        //printf("(%d: %d %c%c%c%c) ",  i,  data[i].key,  data[i].payload[0],  data[i].payload[1], data[i].payload[2],  data[i].payload[3]);
    }

    return data;
}

bool check_sorted(pSort::dataType *test_data,long long num_of_records)
{
   int rank, size;

   MPI_Comm_rank(MPI_COMM_WORLD , &rank);
   MPI_Comm_size(MPI_COMM_WORLD , &size);
    // I expect the same number num_of_records here as the input set at this rank
   if(rank != size-1) {
      if(MPI_SUCCESS != MPI_Send(&test_data[num_of_records-1], 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD)) {
         std::cerr << "End Data sending fails" << rank << std::endl;
         return false;
      }
   }
   if(rank != 0) {
      int previouskey;
      MPI_Status status;
      if(MPI_SUCCESS != MPI_Recv(&previouskey, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &status)) {
         std::cerr << "Previous receiving fails " << rank << std::endl;
         return false;
      }
      if(test_data[0].key < previouskey) return false;
   }
   for(long long i=1; i<num_of_records; i++)
      if(test_data[i].key < test_data[i-1].key) return false;

   // Also check that payload intact for each key -- TO BE IMPLEMENTED

   return true;
}


bool compare_payload(char* p1, char* p2){
bool result=false;
int i=0;
while(i<LOADSIZE){
//std::cout<<i<<std::endl;
if(p1[i]!=p2[i])
break;
i++;
}

if(i==LOADSIZE)
result=true;

return result;
}
void runExperiment(pSort sorter, long long num_of_records=0, pSort::SortType type = pSort::BEST, bool term=true)
{
    /*Processing command line arguments supplied with mpirun*/
    if(num_of_records == 0) num_of_records = (int)(pow(2,10)+0.5); //randomCount();
    
    //Creating an array of structure of type "dataType" declared in sort.h
    //pSort::dataType *test_data  = generate(num_of_records);
    pSort::dataType *test_data  = generate(num_of_records);

    /*Calling functions defined in pSort library to sort records stored in test_data[]*/
    time_t begin,end;
    time(&begin);
    sorter.sort(test_data, num_of_records, type);
    time(&end);
    //
   
    double timetaken = difftime(end,begin);
    if(check_sorted(test_data,num_of_records)) {
       std::cout << type << " Successful in " << timetaken << std::endl;
    }else{
       std::cout<<"OOPS !!!!!!!!!!!!!!!!!!!";
    }
	char payload_results[LOADSIZE];

	pSort::dataType search_item;
	search_item.key = (test_data+22)->key;
	for(int i=0;i<LOADSIZE;i++)
	search_item.payload[i] = (test_data+22)->payload[i]; //(randomCount()%num_of_records)

	//std::cout<<search_item.payload<<"...................."<<search_item.key<<std::endl;
       
        sorter.search(test_data,0,  num_of_records-1, search_item.key, payload_results);
	if(compare_payload(payload_results,search_item.payload)){
	std::cout<<  " Successful search with payload "  << payload_results << std::endl;
	}else{
	std::cout<<   search_item.key  << " Key Not found " << std::endl;
	}

	//std::cout<<payload_results;

    if(term) delete test_data;
}


int main(int argc, char *argv[]){
    

    pSort sorter;

    //Calling your init() to set up MPI	
    sorter.init();

    /*=================================================================*/
    //runExperiment(sorter, 0, pSort::RADIX); // For example
    runExperiment(sorter, 0, pSort::QUICK);
    runExperiment(sorter, 0, pSort::MERGE);
    runExperiment(sorter, 0, pSort::BEST); //getting problem

    //Calling your close() to finalize MPI 
    sorter.close();

    return 0;
}
