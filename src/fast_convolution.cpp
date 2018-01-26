
#include "headers/definitions.hpp"
#include "headers/fft.hpp"

/**
 * Checks if the arguments passed to the fast_circular_conv function are valid. Valid arguments are
 * non null x, y and destination and a size which is a power of 2
 *
 * @param x First complex array.
 * @param y Second complex array.
 * @param size Size of the inputs. Must be a power of 2.
 * @param destination Destination address. Must have available memory to store size complex numbers.
 * @return true if source and destination are non null and size is a power of 2
 */
void _fast_circular_conv_check_arguments(const complex_t* x, const complex_t* y, size_t size, complex_t* destination) {

    if (x == nullptr)
        throw std::invalid_argument("x null");

    if (y == nullptr)
        throw std::invalid_argument("y null");

    if (destination == nullptr)
        throw std::invalid_argument("destination null");

    size_t value = size;

    //Check power of 2
    while (value!=1){

        if(value%2!=0)
            throw std::invalid_argument("size not power of two");

        value/=2;
    }

}

/**
 * Implementation of a circular convolution of two complex arrays using FFT. The arrays must have a size which is
 * a power of 2. The algorithm transforms both inputs x and y using FFT, multiplies element wise and applies the
 * inverse transform using IFFT.
 *
 * @param x First complex array.
 * @param y Second complex array.
 * @param size Size of the inputs. Must be a power of 2.
 * @param destination Destination address. Must have available memory to store size complex numbers.
 * @return true if the convolution was computed successfully.
 */
void fast_circular_conv(const complex_t* x, const complex_t* y, size_t size, complex_t* destination) {

    _fast_circular_conv_check_arguments(x, y, size, destination);

    //Allocate transformed arrays memory
    auto* x_fft = new complex_t[size];
    auto* y_fft = new complex_t[size];
    auto* result_fft = new complex_t[size];

    //Transform inputs
    fft(x, size, x_fft);
    fft(y, size, y_fft);

    //Element wise multiplication. Includes size scaling according to our FFT definition
    for (size_t k=0; k<size; k++) {
        result_fft[k] = x_fft[k] * y_fft[k] * (real_t) size;
    }

    //Inverse transform of the result
    ifft(result_fft, size, destination);

    //Free allocated memory
    delete[] x_fft;
    delete[] y_fft;
    delete[] result_fft;

}
