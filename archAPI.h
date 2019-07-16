/*
 * archAPI.h
 *
 *  Created on: Nov 9, 2015
 *      Author: snytav
 */

#ifndef ARCHAPI_H_
#define ARCHAPI_H_

#include "read_particles.h"

#define HOST_TO_DEVICE   -131313
#define HOST_TO_HOST     -131314
#define DEVICE_TO_HOST   -131315
#define DEVICE_TO_DEVICE -131316

//#define DETAILED_CURRENTS_WRITE
//#define OMP_DETAILED_OUTPUT
//#define OMP_OUTPUT
#define OMP_NUM_THREADS 100

#ifndef __CUDACC__
typedef struct
{
    double x, y, z;
} double3;

typedef struct
{
    int x, y, z;
} int3;

struct uint3
{
    unsigned int x, y, z;
};

struct dim3
{
    unsigned int x, y, z;
#if defined(__cplusplus)
    dim3(unsigned int vx = 1, unsigned int vy = 1, unsigned int vz = 1) : x(vx), y(vy), z(vz) {}
    dim3(uint3 v) : x(v.x), y(v.y), z(v.z) {}
    operator uint3(void) { uint3 t; t.x = x; t.y = y; t.z = z; return t; }
#endif /* __cplusplus */
};

typedef struct dim3 dim3;

#define __device__
#define __host__
#define __global__
#define __shared__

#endif


typedef struct {
	double d_ee; //electric energy
	double *d_Ex,*d_Ey,*d_Ez; // electric field
	double *d_Hx,*d_Hy,*d_Hz; // magnetic field
	double *d_Jx,*d_Jy,*d_Jz; // currents
	double *d_Rho;
	int nt;                                 // timestep
	int *d_stage;                           // checking system (e.g. for flow-out particles)
	int *numbers;                            // number of particles in each cell
	double mass,q_mass;
	double *d_ctrlParticles;
	int jmp;
//	                                        for periodical FIELDS
	int i_s,k_s;                        //
	double *E;                              //the field
	int dir;                                // the direction being processed
	int to,from;                            // the range along the direction

//	                                        for periodical CURRENTS
	int dirE;                           // directions
	int N;                           // variables

//                                          electric field solver
	int l_s;                        // variables
	double *H1,*H2;                          // magnetic fields (orthogonal)
	double *J;                              // current
	double c1,c2,tau;                       //grid steps squared
	int dx1,dy1,dz1,dx2,dy2,dz2;            //shifts

	double B0;                               //constant magnetic field

//	                                        magnetic field solver
	double *Q;                              // magnetic field at half-step
	double *H;                              // magnetic field
	double *E1,*E2;                         // electric fields (orthogonal)
	int particles_processed_by_a_single_thread;
	unsigned int blockDim_x,blockDim_y,blockDim_z; // block for field solver

	int component_total,sorts;               //for diagnostic particles
	ParticleFloatArraysGroup *d_part_diag;

	int *d_p_send_array;
	int p_send_array_size;

	double flown_beam_particles;
} KernelParams;

#ifdef __CUDACC__
#define COPY_FUNCTION_POINTER(dst,src) 	cudaMemcpyFromSymbol( (dst),(src), sizeof( SingleNodeFunctionType ) );
#else
#define COPY_FUNCTION_POINTER(dst,src) {*(dst) = src;}
#endif

#ifdef __CUDACC__
__device__ void BlockThreadSynchronize()
{
    __syncthreads();
}
#else
void BlockThreadSynchronize(){}
#endif

#ifdef __CUDACC__
__device__
#endif
double MultiThreadAdd(double *address, double val)
{
//	double assumed,old=*address;
#ifdef __CUDACC__
    double assumed,old=*address;
    do {
        assumed=old;
        old= __longlong_as_double(atomicCAS((unsigned long long int*)address,
                    __double_as_longlong(assumed),
                    __double_as_longlong(val+assumed)));
    }while (assumed!=old);
#else
    double old;

#ifdef OMP_THREADS
#pragma omp atomic
#endif

    *address += val;

    old = *address;
#endif

    return old;
}

//class cudaAPI{
//public:
//	cudaAPI(){}

 const char *getErrorString(int err)
{
#ifdef __CUDACC__
	return cudaGetErrorString((cudaError_t)err);
#else
	return "";
#endif
}

int SetDevice(int n)
{
#ifdef __CUDACC__
	return cudaSetDevice(n);
#endif
}

#ifdef __CUDACC__
__device__
#endif
void AsyncCopy(double *dst,double *src,int n,int size)
{
	int j;
#ifdef __CUDACC__
	j = n;
	if(j < size)
#else
	for(j = 0;j < size;j++)
#endif
	{
	   dst[j] = src[j];
	}

}

 int MemoryCopy(void* dst,void *src,size_t size,int dir)
{
	int err = 0;

#ifdef __CUDACC__
	cudaMemcpyKind cuda_dir;

	if(dir == HOST_TO_DEVICE) cuda_dir = cudaMemcpyHostToDevice;
	if(dir == HOST_TO_HOST) cuda_dir = cudaMemcpyHostToHost;
	if(dir == DEVICE_TO_HOST) cuda_dir = cudaMemcpyDeviceToHost;
	if(dir == DEVICE_TO_DEVICE) cuda_dir = cudaMemcpyDeviceToDevice;



	return err = (int)cudaMemcpy(dst,src,size,cuda_dir);
#else
	memcpy(dst,src,size);
#endif
	return err;
}

 int MemoryAllocate(void** dst,size_t size)
{
#ifdef __CUDACC__
	cudaMalloc(dst,size);
#else
	*dst = malloc(size);
#endif
}

 int GetDeviceMemory(size_t *m_free,size_t *m_total)
{
#ifdef __CUDACC__
	return cudaMemGetInfo(m_free,m_total);
#else
	*m_free = 0;
	*m_total = 0;
	return 0;
#endif
}

 int MemorySet(void *s, int c, size_t n)
{
#ifdef __CUDACC__
	cudaMemset(s,c,n);
#else
	memset(s,c,n);

#endif
}



 int DeviceSynchronize()
{
#ifdef __CUDACC__
	return cudaDeviceSynchronize();
#endif
}

 int ThreadSynchronize()
{
#ifdef __CUDACC__
	return cudaThreadSynchronize();
#endif
}

 int getLastError()
{
#ifdef __CUDACC__
	return cudaGetLastError();
#endif
	return 0;
}


//virtual ~cudaAPI(){}
//
//};


#endif /* ARCHAPI_H_ */
