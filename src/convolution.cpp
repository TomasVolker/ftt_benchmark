#include "headers/definitions.hpp"

/**
 * Checks if the arguments passed to the circular_conv function are valid. Valid arguments are
 * non null x, y and destination and a size which is a power of 2
 *
 * @param x First complex array.
 * @param y Second complex array.
 * @param size Size of the inputs.
 * @param destination Destination address. Must have available memory to store size complex numbers.
 * @return true if source and destination are non null
 */
void _circular_conv_check_arguments(const complex_t* x, const complex_t* y, size_t size, complex_t* destination) {

    if (x == nullptr)
        throw std::invalid_argument("x null");

    if (y == nullptr)
        throw std::invalid_argument("y null");

    if (destination == nullptr)
        throw std::invalid_argument("destination null");

}

/**
 * Direct implementation of a complex circular convolution
 *
 * @param x First complex array.
 * @param y Second complex array.
 * @param size Size of the inputs.
 * @param destination Destination address. Must have available memory to store size complex numbers.
 */
void circular_conv(const complex_t* x, const complex_t* y, size_t size, complex_t* destination) {

    _circular_conv_check_arguments(x, y, size, destination);

    complex_t aux;

    //Circular convolution formula
    for (size_t m=0; m<size; m++) {

        aux = complex_t((real_t) 0);

        for (size_t n=0; n<size; n++) {
            aux += x[n] * y[(m - n) % size];
        }

        destination[m] = aux;
    }

}
