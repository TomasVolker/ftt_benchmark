#ifndef FTT_BENCHMARK_CONVOLUTION_HPP
#define FTT_BENCHMARK_CONVOLUTION_HPP

#include "definitions.hpp"

void circular_conv(const complex_t* x, const complex_t* y, size_t size, complex_t* destination);

#endif //FTT_BENCHMARK_CONVOLUTION_HPP
