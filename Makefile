COMPILER=gnu


CUDACC=nvcc

ifeq ($(COMPILER),gnu)
  
  MPICC=mpicxx
  CC=mpicxx
  LD=mpicxx
  FLAGS=-c -g
  LDFLAGS=-fopenmp -g -L/opt/intel/impi/2019.4.243/intel64/lib -L /usr/lib/x86_64-linux-gnu/hdf5/serial/ -lnetcdf -lhdf5_hl -lhdf5 -lz -lm
else ifeq ($(COMPILER),intel)
       MPICC=mpiicpc
       LD=mpiicpc
       CC=mpiicpc
       FLAGS=-c -g -fPIC
       LDFLAGS=-fopenmp -g -L/opt/intel/impi/2019.4.243/intel64/lib -L /usr/lib/x86_64-linux-gnu/hdf5/serial/ -lnetcdf -lhdf5_hl -lhdf5 -lz -lm
endif

OBJS=main.o init.o params.o diagnose.o read_particles.o mpi_shortcut.o archAPI.o

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
 
