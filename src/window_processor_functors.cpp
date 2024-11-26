#include <window_processor_functors.h>
#include <Transformer.h>

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