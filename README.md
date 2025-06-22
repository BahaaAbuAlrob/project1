# Matrix Multiplication Projects – Project 1 (Sequential + Pthreads) & Project 2 (OpenMP)

# Project 1 (Sequential + Pthreads) by use Matrix Multiplication Project

## Compilation
g++ generate.cpp -o generate
g++ sequential.cpp -o sequential
g++ parallel.cpp -pthread -o parallel

## Execution
./generate      # Generates matrixA.txt and matrixB.txt
./sequential    # Loads matrices and performs sequential multiplication
./parallel      # Loads matrices and performs parallel multiplication

## Output
- result_sequential.txt: Contains execution time and checksum for sequential version
- result_parallel.txt:   Contains execution time and checksum for parallel version

##============================


Matrix Multiplication with OpenMP
==============================

Project 2 – OpenMP Parallelization

##  Description

In Project 2, we re-implemented the original sequential code from Project 1 using **OpenMP** to exploit multi-core processing and improve performance by parallelizing compute-intensive loops. OpenMP directives such as `#pragma omp parallel for` were used to distribute loop iterations across threads and reduce execution time significantly.

---

##  Compilation & Execution

To compile and run the programs:

### 1. Compile Input Generator
```bash
g++ -o generate generate.cpp
```

### 2. Compile the Sequential Version
```bash
g++ -o sequential_exec src/sequential.cpp
```

### 3. Compile the Pthreads Version (from Project 1)
```bash
g++ -o pthread_exec src/parallel.cpp -lpthread
```

### 4. Compile the OpenMP Version
```bash
g++ -fopenmp -o omp_exec Omp.cpp
```

---

###  Run Instructions

To test the programs:

```bash
# Generate input data (1000×1000 matrix for example)
./generate 1000 > input.txt

# Run the sequential version
./sequential_exec input.txt

# Run the pthread version with 4 threads
./pthread_exec input.txt 4

# Run the OpenMP version with 4 threads
./omp_exec input.txt 4
```

---

##  Performance Results


###  Hardware Used

- **CPU:** Intel Core i7-9750H, 6 cores / 12 threads @ 2.60GHz  
- **RAM:** 16 GB DDR4  
- **Operating System:** Ubuntu 22.04

###  Matrix Sizes Tested

- 500 × 500  
- 1000 × 1000

###  Performance Table

| Version      | Matrix Size | # Threads | Run 1 (ms) | Run 2 (ms) | Run 3 (ms) | Avg Time (ms) | Speedup |
|--------------|-------------|-----------|------------|------------|------------|----------------|---------|
| Sequential   | 500         | 1         | 5928       | 5275       | 5165       | 5456.00        | —       |
| OpenMP       | 500         | 2         | 3021       | 2708       | 2669       | 2799.33        | 1.95×   |
| OpenMP       | 500         | 3         | 2736       | 2701       | 2662       | 2699.67        | 2.02×   |
| OpenMP       | 500         | 4         | 2749       | 2866       | 2650       | 2755.00        | 1.98×   |
| Sequential   | 1000        | 1         | 48698      | 44349      | 43264      | 45437.00       | —       |
| OpenMP       | 1000        | 2         | 25508      | 24905      | 25086      | 25166.33       | 1.81×   |
| OpenMP       | 1000        | 4         | 25160      | 24327      | 23759      | 24415.33       | 1.86×   |

**Speedup Formula:**
```
Speedup = Avg_Time_Sequential / Avg_Time_OpenMP
```

---

##  Discussion

###  Observations

- **Notable improvement**: With 2 threads, OpenMP nearly doubled performance on 500×500 input (≈2×) and improved by ~1.8× for 1000×1000.
- **Diminishing returns**: Increasing from 2 to 4 threads offered minor speedup gains, showing synchronization overheads as per **Amdahl’s Law**.
- **Cache advantage**: Smaller matrices benefited more due to fitting within CPU cache, while larger matrices incurred memory access delays.

---

##  Challenges & Solutions

- **Correctness Validation**: Compared OpenMP output with the sequential version to confirm accuracy.
- **Stable Timing**: Executed each test three times and used the average to minimize timing noise.
- **Thread Tuning**: Experimented with various thread counts (2, 3, 4, 8) to observe impact on performance and find optimal balance.

---

##  Code Organization

```
project2/
│
├── generate.cpp               # Matrix input generator
├── src/
│   ├── sequential.cpp         # Sequential version (from Project 1)
│   └── pthread_version.cpp    # Pthreads version (Project 1)
├── Omp.cpp                    # OpenMP parallel version (Project 2)
├── results/
│   ├── timing_data.csv        # Raw execution times
│   └── speedup.csv            # Speedup analysis
├── README.md                  # This file
```

---



https://github.com/BahaaAbuAlrob/project1

---

