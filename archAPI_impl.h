#include <stdlib.h>
#include <stdio.h>

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
 int ThreadSynchronize()
{
#ifdef __CUDACC__
       return cudaThreadSynchronize();
#endif
}
 int ThreadSynchronize();

 int getLastError()
{
#ifdef __CUDACC__
       return cudaGetLastError();
#endif
       return 0;
}

int DeviceSynchronize()
{
#ifdef __CUDACC__
       return cudaDeviceSynchronize();
#endif
}

