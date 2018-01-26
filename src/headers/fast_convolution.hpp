#ifndef FTT_BENCHMARK_FAST_CONVOLUTION_HPP
#define FTT_BENCHMARK_FAST_CONVOLUTION_HPP

#include "definitions.hpp"

void fast_circular_conv(const complex_t* x, const complex_t* y, size_t size, complex_t* destination);

#endif //FTT_BENCHMARK_FAST_CONVOLUTION_HPP
