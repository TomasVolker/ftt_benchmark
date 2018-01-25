#ifndef FTT_BENCHMARK_DFT_HPP
#define FTT_BENCHMARK_DFT_HPP

#include "definitions.hpp"

bool dft(const complex_t* source, size_t size, complex_t* destination);
bool idft(const complex_t* source, size_t size, complex_t* destination);

#endif //FTT_BENCHMARK_FFT_HPP
