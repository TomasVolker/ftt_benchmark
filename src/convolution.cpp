#include "headers/definitions.hpp"

/**
 * Direct implementation of a complex circular convolution
 *
 * @param x First complex array.
 * @param y Second complex array.
 * @param size Size of the inputs.
 * @param destination Destination address. Must have available memory to store size complex numbers.
 */
void circular_conv(const complex_t* x, const complex_t* y, size_t size, complex_t* destination) {

    //Argument check
    if (x == nullptr || y == nullptr || destination == nullptr) {
        return;
    }

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
