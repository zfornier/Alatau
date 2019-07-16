rm -rf CUDA_TEST
mkdir CUDA_TEST
cp *.h CUDA_TEST
cp *.cpp CUDA_TEST
cp *.c CUDA_TEST
cp *.cu CUDA_TEST
cp *.cxx CUDA_TEST
cp cmp CUDA_TEST
echo COPY FINSHED

cd CUDA_TEST
#ln -s /bioifs/STORE/icmmg/snytav/LOCAL_init/CLEAR_mi_1836e0_mel_1.0e0_melb_1.0e0_mfrq_0d0_Tex0_1.0d-3_rbd_2.0d-3_rimp_0.2d0_NL_100_NT_4_TB_0.14d0_xm_1.1424d0_ni0_1.0e0_tau_0.001d0_lp_100_procf_1_proc_1_bm_1/mumu* .


mv main.cpp main.cu
./cmp
./cuda_all >& cuda.out
pwd
tail -n 1 control_points.dat
pwd
