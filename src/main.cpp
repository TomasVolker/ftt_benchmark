#include <iostream>
#include "headers/definitions.hpp"
#include "headers/dft.hpp"
#include "headers/fft.hpp"
#include "headers/convolution.hpp"
#include "headers/fast_convolution.hpp"
#include "headers/benchmark.hpp"

complex_t test_function1(size_t i) {
    float x;

    switch (i) {
        case 0:
            x = 1.0f;
            break;
        case 1:
            x = 0.0f;
            break;
        default:
            x = 0.0f;
    }

    return complex_t(x);
}

complex_t test_function2(size_t i) {
    float x;

    switch (i) {
        case 5:
            x = 1.0f;
            break;
        case 3:
            x = 0.5f;
            break;
        default:
            x = 0.0f;
    }

    return complex_t(x);
}

void print_array(const complex_t* array, size_t size) {

    for (size_t i=0; i<size; i++) {
        std::cout << array[i] << std::endl;
    }

}

void test_fft() {

    size_t size = 8;

    complex_t z[size];

    for (size_t i=0; i<size; i++) {
        z[i] = test_function1(i);
    }

    std::cout << "Original" << std::endl;

    print_array(z, size);

    complex_t z_fft[size];

    fft(z, size, z_fft);

    std::cout << std::endl;

    std::cout << "Transformed" << std::endl;

    print_array(z_fft, size);

    complex_t z_ifft[size];

    ifft(z_fft, size, z_ifft);

    std::cout << std::endl;

    std::cout << "Reconstructed" << std::endl;

    print_array(z_ifft, size);

}

void test_dft() {

    size_t size = 8;

    complex_t z[size];

    for (size_t i=0; i<size; i++) {
        z[i] = test_function1(i);
    }

    std::cout << "Original" << std::endl;

    print_array(z, size);

    complex_t z_dft[size];

    dft(z, size, z_dft);

    std::cout << std::endl;

    std::cout << "Transformed" << std::endl;

    print_array(z_dft, size);

    complex_t z_idft[size];

    idft(z_dft, size, z_idft);

    std::cout << std::endl;

    std::cout << "Reconstructed" << std::endl;

    print_array(z_idft, size);

}

void test_convolution() {

    size_t size = 8;

    complex_t x[size];

    for (size_t i=0; i<size; i++) {
        x[i] = test_function1(i);
    }
    std::cout << std::endl;
    std::cout << "X" << std::endl;
    print_array(x, size);

    complex_t y[size];

    for (size_t i=0; i<size; i++) {
        y[i] = test_function2(i);
    }

    std::cout << std::endl;
    std::cout << "Y" << std::endl;
    print_array(y, size);

    complex_t z[size];

    circular_conv(x, y, size, z);

    std::cout << std::endl;
    std::cout << "Z" << std::endl;
    print_array(z, size);

}

void test_fast_convolution() {

    size_t size = 8;

    complex_t x[size];

    for (size_t i=0; i<size; i++) {
        x[i] = test_function1(i);
    }
    std::cout << std::endl;
    std::cout << "X" << std::endl;
    print_array(x, size);

    complex_t y[size];

    for (size_t i=0; i<size; i++) {
        y[i] = test_function2(i);
    }

    std::cout << std::endl;
    std::cout << "Y" << std::endl;
    print_array(y, size);

    complex_t z[size];

    fast_circular_conv(x, y, size, z);

    std::cout << std::endl;
    std::cout << "Z" << std::endl;
    print_array(z, size);

}

int main() {

    //test_dft();
    //test_fft();
    //test_convolution();
    //test_fast_convolution();

    //fft_benchmark();

    convolution_benchmark();

    return 0;
}
