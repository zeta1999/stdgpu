/*
 *  Copyright 2019 Patrick Stotko
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef STDGPU_PLATFORM_H
#define STDGPU_PLATFORM_H

/**
 * \file stdgpu/platform.h
 */

#include <stdgpu/config.h>



namespace stdgpu
{

/**
 * \hideinitializer
 * \brief Host compiler: Unknown
 */
#define STDGPU_HOST_COMPILER_UNKNOWN -1
/**
 * \hideinitializer
 * \brief Host compiler: GCC
 */
#define STDGPU_HOST_COMPILER_GCC      0
/**
 * \hideinitializer
 * \brief Host compiler: Clang
 */
#define STDGPU_HOST_COMPILER_CLANG    1
/**
 * \hideinitializer
 * \brief Host compiler: Microsoft Visual C++
 */
#define STDGPU_HOST_COMPILER_MSVC     2

/**
 * \hideinitializer
 * \brief Device compiler: Unknown
 */
#define STDGPU_DEVICE_COMPILER_UNKNOWN -1
/**
 * \hideinitializer
 * \brief Device compiler: NVCC
 */
#define STDGPU_DEVICE_COMPILER_NVCC     0

/**
 * \def STDGPU_HOST_COMPILER
 * \hideinitializer
 * \brief The detected host compiler
 */
#if defined(__GNUC__) && !defined(__clang__)
    #define STDGPU_HOST_COMPILER STDGPU_HOST_COMPILER_GCC
#elif defined(__clang__)
    #define STDGPU_HOST_COMPILER STDGPU_HOST_COMPILER_CLANG
#elif defined(_MSC_VER)
    #define STDGPU_HOST_COMPILER STDGPU_HOST_COMPILER_MSVC
#else
    #define STDGPU_HOST_COMPILER STDGPU_HOST_COMPILER_UNKNOWN
#endif

/**
 * \def STDGPU_DEVICE_COMPILER
 * \hideinitializer
 * \brief The detected device compiler
 */
#if defined(__CUDACC__)
    #define STDGPU_DEVICE_COMPILER STDGPU_DEVICE_COMPILER_NVCC
#else
    #define STDGPU_DEVICE_COMPILER STDGPU_DEVICE_COMPILER_UNKNOWN
#endif



/**
 * \def STDGPU_HAS_CXX_17
 * \hideinitializer
 * \brief Indicator of C++17 availability
 */
#if defined(__cplusplus) && __cplusplus >= 201703L
    #define STDGPU_HAS_CXX_17 1
#else
    #define STDGPU_HAS_CXX_17 0
#endif



/**
 * \hideinitializer
 * \brief Backend: CUDA
 */
#define STDGPU_BACKEND_CUDA   0
/**
 * \hideinitializer
 * \brief Backend: OpenMP
 */
#define STDGPU_BACKEND_OPENMP 1


// STDGPU_BACKEND is defined in stdgpu/config.h



/**
 * \def STDGPU_HOST_DEVICE
 * \hideinitializer
 * \brief Platform-independent host device function annotation
 */
#if STDGPU_BACKEND == STDGPU_BACKEND_CUDA
    #if STDGPU_DEVICE_COMPILER == STDGPU_DEVICE_COMPILER_NVCC
        #define STDGPU_HOST_DEVICE __host__ __device__
    #else
        #define STDGPU_HOST_DEVICE
    #endif
#elif STDGPU_BACKEND == STDGPU_BACKEND_OPENMP
    #define STDGPU_HOST_DEVICE
#endif


/**
 * \def STDGPU_DEVICE_ONLY
 * \hideinitializer
 * \brief Platform-independent device function annotation
 */
#if STDGPU_BACKEND == STDGPU_BACKEND_CUDA
    #if STDGPU_DEVICE_COMPILER == STDGPU_DEVICE_COMPILER_NVCC
        #define STDGPU_DEVICE_ONLY __device__
    #else
        // Should trigger a compact error message containing the error string
        #define STDGPU_DEVICE_ONLY sizeof("STDGPU ERROR: Wrong compiler detected! Device-only functions must be compiled with the device compiler!")
    #endif
#elif STDGPU_BACKEND == STDGPU_BACKEND_OPENMP
    #define STDGPU_DEVICE_ONLY
#endif


/**
 * \def STDGPU_CONSTANT
 * \hideinitializer
 * \brief Platform-independent constant variable annotation
 */
#if STDGPU_BACKEND == STDGPU_BACKEND_CUDA
    #if STDGPU_DEVICE_COMPILER == STDGPU_DEVICE_COMPILER_NVCC
        #define STDGPU_CONSTANT __constant__
    #else
        #define STDGPU_CONSTANT
    #endif
#elif STDGPU_BACKEND == STDGPU_BACKEND_OPENMP
    #define STDGPU_CONSTANT
#endif


/**
 * \hideinitializer
 * \brief Code path: Host
 */
#define STDGPU_CODE_HOST   0
/**
 * \hideinitializer
 * \brief Code path: Device
 */
#define STDGPU_CODE_DEVICE 1

/**
 * \def STDGPU_CODE
 * \hideinitializer
 * \brief The code path
 */
#if STDGPU_BACKEND == STDGPU_BACKEND_CUDA
    #if defined(__CUDA_ARCH__)
        #define STDGPU_CODE STDGPU_CODE_DEVICE
    #else
        #define STDGPU_CODE STDGPU_CODE_HOST
    #endif
#elif STDGPU_BACKEND == STDGPU_BACKEND_OPENMP
    #define STDGPU_CODE STDGPU_CODE_HOST
#endif

} // namespace stdgpu



#endif // STDGPU_PLATFORM_H
