#include <window_processor_functors.h>
#include <Transformer.h>
#include <iostream>
#include <vector>

// FBrickwallLowpass

FBrickwallLowpass::FBrickwallLowpass(size_t cutoff, size_t win_size) : cutoff_(cutoff), transformer_(win_size) {}

std::vector<std::complex<double>> FBrickwallLowpass::operator()(
    std::vector<std::complex<double>> const& signal
) {
    return brickwall_lowpass(signal, cutoff_, transformer_);
}

// FBrickwallHighpass

FBrickwallHighpass::FBrickwallHighpass(size_t cutoff, size_t win_size) : cutoff_(cutoff), transformer_(win_size) {}

std::vector<std::complex<double>> FBrickwallHighpass::operator()(
    std::vector<std::complex<double>> const& signal
) {
    return brickwall_highpass(signal, cutoff_, transformer_);
}

// FConvLowpass

FConvLowpass::FConvLowpass(size_t width, size_t win_size) : width_(width), transformer_(win_size), kernel_(win_size, 0) {
    for (int i = 0; i < width; ++i) {
        kernel_[i] = 1/((double) width);
    }
}

std::vector<std::complex<double>> FConvLowpass::operator()(
    std::vector<std::complex<double>> const& signal
) {
    return convolve(signal, kernel_, transformer_);
}

// FConvHighpass

FConvHighpass::FConvHighpass(size_t width, size_t win_size) : width_(width), transformer_(win_size), kernel_(win_size, 0) {
    for (int i = 0; i < width; ++i) {
        kernel_[i] = -1/((double) width);
    }
    kernel_[0] += 1;
}

std::vector<std::complex<double>> FConvHighpass::operator()(
    std::vector<std::complex<double>> const& signal
) {
    return convolve(signal, kernel_, transformer_);
}
