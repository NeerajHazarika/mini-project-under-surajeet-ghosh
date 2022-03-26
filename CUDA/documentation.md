# What is CUDA ?

CUDA is a platform and programming model for CUDA-enabled GPUs. The platform exposes GPUs for general purpose computing. CUDA provides C/C++ language extension and APIs for programming and managing GPUs.

In CUDA programming, both CPUs and GPUs are used for computing. Typically, we refer to CPU and GPU system as host and device, respectively. CPUs and GPUs are separated platforms with their own memory space. Typically, we run serial workload on CPU and offload parallel computation to GPUs.

# Difference between C and CUDA C

The major difference between C and CUDA implementation is __global__ specifier and <<<...>>> syntax. The __global__ specifier indicates a function that runs on device (GPU). Such function can be called through host code, e.g. the main() function in the example, and is also known as "kernels".

When a kernel is called, its execution configuration is provided through <<<...>>> syntax, e.g. cuda_hello<<<1,1>>>(). In CUDA terminology, this is called "kernel launch". 

```
__global__ void cuda_hello(){
    printf("Hello World from GPU!\n");
}

int main() {
    cuda_hello<<<1,1>>>(); 
    return 0;
}
```
