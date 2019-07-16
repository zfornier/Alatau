{
   a[NR]=$n
}
END{
   diff = 0.0
   for(i = 1;i <= NR/2;i++)
   {
       t = a[i] - a[i+NR/2]
       if(t < 0) t = -t

       if (t > diff) diff = t
       printf("%10d %25.15e %25.15e %e\n",i,a[i],a[i+NR/2],t)
   }

   printf("%e\n",diff) 
   
}
