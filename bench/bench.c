#include <stdio.h>
#include <time.h>

#include "xof.h"

int main()
{
    printf("\n******************************************");
    fflush(stdout);

    int num_tests = 1000000;

    // 16 32 64
    int in_len = 64;
    int out_len = 64;

    unsigned char in1[in_len];
    unsigned char in2[in_len];
    unsigned char in3[in_len];
    unsigned char in4[in_len];
    unsigned char out1[out_len];
    unsigned char out2[out_len];
    unsigned char out3[out_len];
    unsigned char out4[out_len];
    clock_t t_parallel, t_serial; 

    // PARALLEL
    t_parallel = clock(); 
    for(int i=0; i<num_tests; i++) {
        xof_x4_cycle(in1,in2,in3,in4,in_len,out1,out2,out3,out4,out_len);
    }
    t_parallel = clock() - t_parallel;

    // SERIAL
    t_serial = clock(); 
    for(int i=0; i<num_tests; i++) {
        xof_cycle(in1,in_len,out1,out_len);
    }
    t_serial = clock() - t_serial; 

    // RESULTS
    //double time_taken_serial = ((double)t_serial)/CLOCKS_PER_SEC;
    //double time_taken_parallel = ((double)t_parallel)/CLOCKS_PER_SEC;
    double percent = ((double)t_parallel - (double)t_serial)/(double)t_serial*100;
    printf("\nSERIAL:\t\t %i", t_serial);
    printf("\nPARALLEL:\t %i\t%+.2f", t_parallel, percent);
    printf("\nSPEEDUP:\t x%.2f", (double)t_serial / ((double)t_parallel/4) );
    printf("\n******************************************\n");
    fflush(stdout);
}
