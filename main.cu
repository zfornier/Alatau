#include "xeon_plasma.h"
#include <stdlib.h>
#include "mpi_shortcut.h"

int main(int argc,char*argv[])
{
      XeonPlasma<GPUCell> *plasma;
   
      InitMPI(argc,argv);

      size_t sizeP;

      printf("oarticle size %d %d \n",sizeof(Particle),sizeof(Particle)/sizeof(double));
//      cudaDeviceGetLimit(&sizeP,cudaLimitPrintfFifoSize);

//      printf("printf default limit %d \n",sizeP/1024/1024);

      sizeP *= 10;
      sizeP *= 10;
      sizeP *= 10;
      sizeP *= 10;
//      cudaDeviceSetLimit(cudaLimitPrintfFifoSize, sizeP);

//      cudaDeviceGetLimit(&sizeP,cudaLimitPrintfFifoSize);



//      printf("printf limit set to %d \n",sizeP/1024/1024);

   
      int err = SetDevice(0);
   
//      printf("err %d \n",err);

   //plasma = new GPUPlasma<GPUCell>(100,4,4,1.2566,0.05,0.05,1.0,100,1.0,0.001);
   plasma = new XeonPlasma<GPUCell>(100,4,4,1.1424,0.05,0.05,1.0,2000,1.0,0.001);
 
   plasma->Initialize();


   

   double t = plasma->compareCPUtoGPU();
   printf("----------------------------------------------------------- plasma check before move %.5f\n",t);
   size_t m_free,m_total;

   GetDeviceMemory(&m_free,&m_total);
   struct sysinfo info;


   for(int nt = START_STEP_NUMBER;nt <= TOTAL_STEPS;nt++)
   {
	   GetDeviceMemory(&m_free,&m_total);
	   sysinfo(&info);
#ifdef MEMORY_PRINTS
       printf("before Step  %10d CPU memory free %10u GPU memory total %10d free %10d\n",
    		   nt,info.freeram/1024/1024,m_total/1024/1024,m_free/1024/1024);
#endif

       plasma->Step(nt);

       GetDeviceMemory(&m_free,&m_total);
       sysinfo(&info);
#ifdef MEMORY_PRINTS
       printf("after  Step  %10d CPU memory free %10u GPU memory total %10d free %10d\n",
    		   nt,info.freeram/1024/1024/1024,m_total/1024/1024/1024,m_free/1024/1024/1024);
#endif
   }

   t = plasma->compareCPUtoGPU();
   printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ plasma check after move %.5f\n",t);

   delete plasma;
   
   CloseMPI();

   return 0;
}
