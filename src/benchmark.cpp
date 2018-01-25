#include <random>
#include <iostream>
#include <ctime>
#include "headers/definitions.hpp"
#include "headers/dft.hpp"
#include "headers/fft.hpp"
#include "headers/convolution.hpp"
#include "headers/fast_convolution.hpp"

void set_random_values(complex_t* array, size_t size) {

    auto generator = std::uniform_real_distribution<real_t>(-1, 1);

    std::default_random_engine random_engine;
    std::uniform_real_distribution<real_t> dist(-1, 1);

    for(int k=0; k<size; k++) {
        array[k] = complex_t(dist(random_engine), dist(random_engine));
    }

}

double measure_dft(complex_t* source, size_t size, complex_t* destination) {

    std::clock_t begin = std::clock();

    dft(source, size, destination);

    std::clock_t end = std::clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;


    return elapsed_secs;
}

double measure_fft(complex_t* source, size_t size, complex_t* destination) {

    std::clock_t begin = std::clock();

    fft(source, size, destination);

    std::clock_t end = std::clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    return elapsed_secs;
}

void fft_benchmark() {

    size_t tests = 16;
    size_t size = 1;

    double fft_runtimes[tests];
    double dft_runtimes[tests];

    for (int i=0; i<tests; i++) {

        auto source = new complex_t[size];
        set_random_values(source, size);

        auto destination = new complex_t[size];

        fft_runtimes[i] = measure_fft(source, size, destination);
        printf("FFT: size: 2^%d = %d \t elapsed time: %.8f seconds\n", i, size, fft_runtimes[i]);

        dft_runtimes[i] = measure_dft(source, size, destination);
        printf("DFT: size: 2^%d = %d \t elapsed time: %.8f seconds\n\n", i, size, dft_runtimes[i]);

        delete[] source;
        delete[] destination;

        size *= 2;
    }

    printf("\nFFT\n");

    for (int i=0; i<tests; i++) {
        printf("%d, %d, %.8f\n", i, 1 << i, fft_runtimes[i]);
    }

    printf("\nDFT\n");

    for (int i=0; i<tests; i++) {
        printf("%d, %d, %.8f\n", i, 1 << i, dft_runtimes[i]);
    }

}

double measure_conv(complex_t* source1, complex_t* source2, size_t size, complex_t* destination) {

    std::clock_t begin = std::clock();

    circular_conv(source1, source2, size, destination);

    std::clock_t end = std::clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;


    return elapsed_secs;
}

double measure_fast_conv(complex_t* source1, complex_t* source2, size_t size, complex_t* destination) {

    std::clock_t begin = std::clock();

    fast_circular_conv(source1, source2, size, destination);

    std::clock_t end = std::clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    return elapsed_secs;
}

void convolution_benchmark() {

    size_t tests = 16;
    size_t size = 1;

    double fast_conv_runtimes[tests];
    double conv_runtimes[tests];

    for (int i=0; i<tests; i++) {

        auto source1 = new complex_t[size];
        set_random_values(source1, size);

        auto source2 = new complex_t[size];
        set_random_values(source2, size);

        auto destination = new complex_t[size];

        fast_conv_runtimes[i] = measure_fast_conv(source1, source2, size, destination);
        printf("Fast Conv: size: 2^%d =\t %d \t elapsed time: %.8f seconds\n", i, size, fast_conv_runtimes[i]);

        conv_runtimes[i] = measure_conv(source1, source2, size, destination);
        printf("Conv:      size: 2^%d =\t %d \t elapsed time: %.8f seconds\n\n", i, size, conv_runtimes[i]);

        delete[] source1;
        delete[] source2;
        delete[] destination;

        size *= 2;
    }

    printf("\nFast Convolution\n");

    for (int i=0; i<tests; i++) {
        printf("%d, %d, %.8f\n", i, 1 << i, fast_conv_runtimes[i]);
    }

    printf("\nConvolution\n");

    for (int i=0; i<tests; i++) {
        printf("%d, %d, %.8f\n", i, 1 << i, conv_runtimes[i]);
    }

}
