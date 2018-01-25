#include "headers/definitions.hpp"

/**
 * Implementation of the Cooley-Tukey algorithm for computing the DFT of a complex array with a size of a power of 2.
 * This function includes a stride parameter, allowing a recursive implementation.
 *
 * @param source Complex array to transform.
 * @param size Size of the source array. Must be a power of 2.
 * @param stride Distance between two consecutive elements in the array.
 * @param destination Destination address. Must have available memory to store size complex numbers.
 * @param inverse Indicates if the computed transform is the inverse, having only one implementation for both.
 */
void _ftt_cooley_tukey(const complex_t *source, size_t size, size_t stride, complex_t *destination, bool inverse){

    //Recursion termination, trivial transform of size 1
    if(size==1){
        *destination = *source;
        return;
    }

    size_t half_size = size/2;

    //Even elements transform
    _ftt_cooley_tukey(source, half_size, 2*stride, destination, inverse);

    //Odd elements transform
    _ftt_cooley_tukey(source+stride, half_size, 2*stride, destination+half_size, inverse);

    //Twiddle exponent sign depending if the transform is inverse
    auto sign = (real_t) (inverse? 1: -1);

    //Auxiliar variables
    complex_t twiddle, even, odd;

    //For each element
    for(size_t k=0; k<half_size; k++){

        //Twiddle factor (one sample delay)
        twiddle = std::polar<real_t>(
                (real_t) 1,
                sign * _2PI * ((real_t) k) / ((real_t) size)
        );

        //Butterfly formula
        even = destination[k];
        odd  = destination[k + half_size];

        destination[k]             = even + twiddle * odd;
        destination[k + half_size] = even - twiddle * odd;

    }

}

/**
 * Checks if the arguments passed to the fft function are valid. Valid arguments are non null source and destination
 * and a size which is a power of 2
 *
 * @param source Complex array to transform
 * @param size Size of the source array.
 * @param destination Destination address. Must have available memory to store size complex numbers.
 * @return true if source and destination are non null and size is a power of 2
 */
bool _ftt_check_arguments(const complex_t *source, size_t size, complex_t *destination) {

    if(source == nullptr || destination == nullptr)
        return false;

    size_t value = size;

    //Check power of 2
    while (value!=1){

        if(value%2!=0)
            return false;

        value/=2;
    }

    return true;
}

/**
 * Computes the DFT of the complex array source using the Cooley-Tukey algorithm. The size must be a power of 2.
 * The used DFT definition has no scaling factor and includes dividing by size the result for the IDFT.
 *
 * @param source Complex array to transform
 * @param size Size of the source array. Must be a power of 2.
 * @param destination Destination address. Must have available memory to store size complex numbers.
 * @return true if the FFT was computed successfully.
 */
bool fft(const complex_t* source, size_t size, complex_t* destination) {

    if (!_ftt_check_arguments(source, size, destination)) {
        return false;
    }

    _ftt_cooley_tukey(source, size, 1, destination, false);

    return true;
}

/**
 * Computes the inverse DFT of the complex array source using the Cooley-Tukey algorithm. The size must be a power of 2.
 * The used IDFT definition includes dividing by size the result and no scaling factor for the DFT.
 *
 * @param source Complex array to transform
 * @param size Size of the source array.
 * @param destination Destination address. Must have available memory to store size complex numbers.
 * @return true if the IFFT was computed successfully.
 */
bool ifft(const complex_t* source, size_t size, complex_t* destination) {

    if(!_ftt_check_arguments(source, size, destination)) {
        return false;
    }

    _ftt_cooley_tukey(source, size, 1, destination, true);

    //Divide all elements by the size according to the used definition of DFT
    for(size_t k=0; k<size; k++){
        destination[k]/=size;
    }

    return true;
}
