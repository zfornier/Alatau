#export PATH=/usr/local/cuda-7.0/bin:/home/snytav/backUp/WRFV35/external/io_netcdf:$PATH
#export PATH=/usr/local/cuda/bin:/home/snytav/backUp/WRFV35/external/io_netcdf:$PATH

#export LD_LIBRARY_PATH=/opt/cuda_6.5/lib/:$LD_LIBRARY_PATH
#export LD_LIBRARY_PATH=/usr/local/cuda-7.0/lib64/:/ifs/opt/2013/intel/impi/4.1.3.049/intel64/lib:$LD_LIBRARY_PATH

rm *.o all
#icc -m64 -c rnd.cpp
icc -c -g main.cpp >&err_main
mpiicc -c -g mpi_shortcut.cxx >&mpi_err.txt
icc -c -g init.cpp
icc -c -g params.cxx
icc -c -g diagnose.cxx 2>&1 > err_diagnose
icc -c -g read_particles.c
mpiicc -o all *.o -fopenmp -L/opt/intel/impi/2019.4.243/intel64/lib 
#-L/opt/intel/impi/5.0.1.035/intel64/lib/ -fopenmp -L/Compiler/11.1/038/lib/intel64/
#nvcc -O2 -lineinfo -c main.cu --ptxas-options=-v --keep -arch=sm_35 -I/usr/local/cuda-7.0/include >&c_out

ls -l all
date
