COMPILER=gnu


CUDACC=nvcc

ifeq ($(COMPILER),intel)
  
  MPICC=mpiicc
  CC=mpiicc
  LD=mpiicc
  FLAGS=-c -g
  LDFLAGS=-fopenmp -g -L/opt/intel/impi/2019.4.243/intel64/lib -L /usr/lib/x86_64-linux-gnu/hdf5/serial/ -lnetcdf -lhdf5_hl -lhdf5 -lz -lm
else ifeq ($(COMPILER),gnu)
       MPICC=mpicxx
       CC=mpicxx
       FLAGS=-c -g
       LDFLAGS=-fopenmp -g -lnetcdf -lhdf5_hl -lhdf5 -lz -lm -shared
endif

OBJS=main.o init.o params.o diagnose.o read_particles.o mpi_shortcut.o 

#main.o:
#		$(CUDACC) -c  main.cu
		
all: $(OBJS)
		$(LD) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.cpp
		$(CC) $(FLAGS) -o $@ $<

%.o: %.cxx
		$(CC) $(FLAGS) -o $@ $< 


clean:
	rm all; rm $(OBJS)
 
