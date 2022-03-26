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

# Workflow of CUDA programs

1. Allocate host memory and initialized host data
2. Allocate device memory
3. Transfer input data from host to device memory
4. Execute kernels
5. Transfer output from device memory to host

### 2. Allocate Device Memory

CUDA provides several functions for allocating device memory. The most common ones are cudaMalloc() and cudaFree(). The syntax for both functions are as follow

```
cudaMalloc(void **devPtr, size_t count);
cudaFree(void *devPtr);
```

cudaMalloc() allocates memory of size count in the device memory and updates the device pointer devPtr to the allocated memory. cudaFree() deallocates a region of the device memory where the device pointer devPtr points to. They are comparable to malloc() and free() in C, respectively

### 3. Transfer input data from host to device memory

Transfering data between host and device memory can be done through cudaMemcpy function, which is similar to memcpy in C. The syntax of cudaMemcpy is as follow
```
cudaMemcpy(void *dst, void *src, size_t count, cudaMemcpyKind kind)
```
The function copy a memory of size count from src to dst. kind indicates the direction. For typical usage, the value of kind is either cudaMemcpyHostToDevice or cudaMemcpyDeviceToHost. There are other possible values but we will not touch them in this tutorial.


