#ifndef FTT_BENCHMARK_FFT_HPP
#define FTT_BENCHMARK_FFT_HPP

#include "definitions.hpp"

bool fft(const complex_t* source, size_t size, complex_t* destination);
bool ifft(const complex_t* source, size_t size, complex_t* destination);

#endif //FTT_BENCHMARK_FFT_HPP
