#include "headers/definitions.hpp"

/**
 * Direct implementation of the DFT using the definition formula.
 *
 * @param source Complex array to transform.
 * @param size Size of the source array.
 * @param destination Destination address. Must have available memory to store size complex numbers.
 * @param inverse Indicates if the computed transform is the inverse, having only one implementation for both.
 */
void _dft(const complex_t *source, size_t size, complex_t *destination, bool inverse) {

    //Sign of the exponent depending if the inverse transform
    auto sign = (real_t) (inverse? 1: -1);

    complex_t aux;

    //DFT formula
    for (size_t k=0; k<size; k++) {

        aux = complex_t((real_t) 0.0);

        for (size_t n=0; n<size; n++) {
            aux += source[n] * std::polar<real_t>((real_t) 1, sign * _2PI * n * k / ((real_t) size));
        }

        destination[k] = aux;
    }

}

/**
 * Checks if the arguments passed to the dft function are valid. Valid arguments are non null source and destination.
 *
 * @param source Complex array to transform
 * @param size Size of the source array.
 * @param destination Destination address. Must have available memory to store size complex numbers.
 * @return true if source and destination are non null.
 */
bool _dft_check_arguments(const complex_t *source, size_t size, complex_t *destination) {
    return source != nullptr && destination != nullptr;

}

/**
 * Computes the DFT of the complex array source by definition. The used DFT has no scaling factor and includes
 * dividing by size the result for the IDFT.
 *
 * @param source Complex array to transform
 * @param size Size of the source array.
 * @param destination Destination address. Must have available memory to store size complex numbers.
 * @return true if the DFT was computed successfully.
 */
bool dft(const complex_t* source, size_t size, complex_t* destination) {

    if (!_dft_check_arguments(source, size, destination)) {
        return false;
    }

    _dft(source, size, destination, false);

    return true;
}

/**
 * Computes the IDFT of the complex array source by definition. The used IDFT definition includes dividing by size
 * the result and no scaling factor for the DFT.
 *
 * @param source Complex array to transform
 * @param size Size of the source array.
 * @param destination Destination address. Must have available memory to store size complex numbers.
 * @return true if the IDFT was computed successfully.
 */
bool idft(const complex_t* source, size_t size, complex_t* destination) {

    if(!_dft_check_arguments(source, size, destination)) {
        return false;
    }

    _dft(source, size, destination, true);

    //Divide all elements by the size according to the used definition of DFT
    for(size_t k=0; k<size; k++){
        destination[k]/=size;
    }

    return true;
}
