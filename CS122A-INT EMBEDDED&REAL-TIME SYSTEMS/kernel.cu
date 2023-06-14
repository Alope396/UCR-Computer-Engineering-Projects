
#include <stdio.h>

__global__ void histo_kernel(unsigned int* input, unsigned int* bins, unsigned int num_elements, unsigned int num_bins)
{
	
    /*************************************************************************/
    // INSERT KERNEL CODE HERE
	__shared__ unsigned int private_histo[4096]; 
        int j= threadIdx.x; 
        while (j < 4096) { 
         __syncthreads(); 
                private_histo[j] = 0; 
                j += blockDim.x; 
        } 
         __syncthreads();
        int i = threadIdx.x + blockIdx.x * blockDim.x; 
        int stride = blockDim.x * gridDim.x; 
        while (i < size) {    
                atomicAdd( &(private_histo[input[i]]), 1 ); 
                i += stride; 
        } 
        __syncthreads();        
        j = threadIdx.x; 
        while (j < 4096) {    
                atomicAdd(&(histo[j]), private_histo[j] ); 
                j += blockDim.x; 
        } 
        __syncthreads();
	
	  /*************************************************************************/
}

void histogram(unsigned int* input, unsigned int* bins, unsigned int num_elements, unsigned int num_bins) {

	  /*************************************************************************/
    //INSERT CODE HERE
        dim3 DimGrid(16, 16, 1);
        dim3 DimBlock(512, 1, 1);

	  /*************************************************************************/

}