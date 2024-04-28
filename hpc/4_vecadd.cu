#include <iostream>
using namespace std;

__global__ void add(int* A, int* B, int* C, int size) {

    //calculates the unique thread index (tid) for each thread.
    /*
    blockIdx.x is the block index in the grid.
    blockDim.x is the number of threads in a block.
    threadIdx.x is the index of the current thread within its block*/
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    /*checks whether the calculated thread index (tid) is within the bounds of the vector size (size).
    This ensures that each thread only processes valid elements within the range of the vectors.*/
    if (tid < size) {

        // performs the element-wise addition of vectors A and B at the index tid.
        C[tid] = A[tid] + B[tid];
    }
}

// initializes the A and B vectors with random integers between 0 and 9.
void initialize(int* vector, int size) {
    for (int i = 0; i < size; i++) {
        vector[i] = rand() % 10;
    }
}

void print(int* vector, int size) {
    for (int i = 0; i < size; i++) {
        cout << vector[i] << " ";
    }
    cout << endl;
}

int main() {
    int N = 8;
    int * A, * B, * C;

    int vectorSize = N;
    size_t vectorBytes = vectorSize * sizeof(int);

    A = new int[vectorSize];
    B = new int[vectorSize];
    C = new int[vectorSize];

    initialize(A, vectorSize);
    initialize(B, vectorSize);

    cout << "Vector A: ";
    print(A, N);
    cout << "Vector B: ";
    print(B, N);

    int * X, * Y, * Z;
    
    //memory for the vectors is allocated on the GPU using cudaMalloc.
    cudaMalloc(&X, vectorBytes);
    cudaMalloc(&Y, vectorBytes);
    cudaMalloc(&Z, vectorBytes);
    
    //The cudaMemcpy function is used to copy data from the host vectors CPU (A and B) to the device vectors GPU(X and Y).
    cudaMemcpy(X, A, vectorBytes, cudaMemcpyHostToDevice);
    cudaMemcpy(Y, B, vectorBytes, cudaMemcpyHostToDevice);

    //The kernel launch parameters are defined: threadsPerBlock is set to 256 threads per block for good balance between performance and efficiency, 
    //and blocksPerGrid is calculated to ensure all elements of the vectors are processed.
    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;
    
    //The add function adds elements from vectors X and Y and stores the result in vector Z.
    add<<<blocksPerGrid, threadsPerBlock>>>(X, Y, Z, N);
    
    //The result vector Z on the device is copied back to the host using cudaMemcpy.
    cudaMemcpy(C, Z, vectorBytes, cudaMemcpyDeviceToHost);

    cout << "Addition: ";
    print(C, N);

    delete[] A;
    delete[] B;
    delete[] C;

    cudaFree(X);
    cudaFree(Y);
    cudaFree(Z);

    return 0;

    // nvcc 4_vecadd.cu -o 4_vecadd && ./4_vecadd
}

/*
CUDA (Compute Unified Device Architecture) is a parallel computing platform and programming model developed by NVIDIA for general-purpose computing on its graphics processing units (GPUs). It allows developers to write programs that can execute concurrently on thousands of small processing cores within a GPU, making it ideal for accelerating complex computations, such as scientific simulations, image processing, and machine learning. CUDA provides an API and language extensions (based on C/C++) for creating and managing GPU kernels, memory, and synchronization.
*/
