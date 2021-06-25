# MPI-OpenMP
Hybrid Sorting Algorithm and review paper
## Sorting Algorithms: Quick Sort, Merge Sort, Heap Sort
We have used two phase sorting algorithm where we have sorted the data locally in phase
one and then combined them in phase two to get sorted sequence globally. For local sorting we have
done quick sort, merge sort and heap sort and got the comparison result that quick sort is fastest
among all. Time complexity of each is bounded by O(nlog n) <br />
Local sorting is backed up by thread programming using OpenMP and each thread sort a
subpart of process’s data and then combined it. This strategy gives a boost in overall speedup.  <br />
In phase two global sorting is done to properly sort the data by rearranging the data
according to its distribution. After this step we can call the search procedure for each process that is
explained in the next section.  <br />
## Searching Algorithm:
We have implemented a search procedure that is doing binary search for each procedure that
is returning bool variable, which is has value true if search function found the key element and
return false if search procedure is unable to get element. <br />
To remove the problem induced by return of reference of local variable of function we have
modified the skeleton of given search procedure by passing the reference to result variable. <br />
We have implemented binary search within each process to get the desired element. We can
use binary search in this case as data is sorted within each process. This search procedure is having
complexity of O(log n). <br />

## Program Execution:
Makefile is provided with the code. The program can be executed by giving following
command.
### Create executable file using:
mpiCC -fopenmp -c -o sort.o sort.cpp sort.h
ar -rsc libpsort.a sort.o
### Run the tester code file using:
mpicxx -fopenmp tester.cpp libpsort.a
mpirun -n 64 a.out
