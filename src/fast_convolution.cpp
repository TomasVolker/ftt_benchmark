
#include "headers/definitions.hpp"
#include "headers/fft.hpp"

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
bool fast_circular_conv(const complex_t* x, const complex_t* y, size_t size, complex_t* destination) {

    //Argument check
    if (x == nullptr || y == nullptr || destination == nullptr) {
        return false;
    }

    //Allocate transformed arrays memory
    auto* x_fft = new complex_t[size];
    auto* y_fft = new complex_t[size];
    auto* result_fft = new complex_t[size];

    //Transform inputs
    if (!fft(x, size, x_fft)) {
        return false;
    }

    if (!fft(y, size, y_fft)) {
        return false;
    }

    //Element wise multiplication. Includes size scaling according to our FFT definition
    for (size_t k=0; k<size; k++) {
        result_fft[k] = x_fft[k] * y_fft[k] * (real_t) size;
    }

    //Inverse transform of the result
    if (!ifft(result_fft, size, destination)) {
        return false;
    }

    //Free allocated memory
    delete[] x_fft;
    delete[] y_fft;
    delete[] result_fft;

    return true;
}
