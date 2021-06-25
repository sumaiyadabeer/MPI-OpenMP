#!/bin/sh
#PBS -N col730A3
#PBS -P cse
#PBS -m bea
#PBS -M $USER@iitd.ac.in
#PBS -l select=4:ncpus=8:mpiprocs=8:mem=90GB
#PBS -l walltime=00:05:00
#PBS -o out
#PBS -e err

# After job starts, must goto working directory. 
# $PBS_O_WORKDIR is the directory from where the job is fired. 
echo "==============================="
echo $PBS_JOBID
cat $PBS_NODEFILE
echo "==============================="
cd $PBS_O_WORKDIR
echo $PBS_O_WORKDIR

module () {
        eval `/usr/share/Modules/$MODULE_VERSION/bin/modulecmd bash $*`
}

module load compiler/gcc/9.1/openmpi/4.0.2
mpicxx -fopenmp sort.cpp tester.cpp
mpirun -n 8 a.out
rm a.out    #removes the compiled file
