#pragma once

#include <vector>
#include <complex>
#include <Transformer.h>

std::vector<std::complex<double>> brickwall_lowpass(
    std::vector<std::complex<double>> const& signal,
    size_t cutoff,
    Transformer const& t
);

std::vector<std::complex<double>> brickwall_highpass(
    std::vector<std::complex<double>> const& signal,
    size_t cutoff,
    Transformer const& t
);

std::vector<std::complex<double>> fir_lowpass(
    std::vector<std::complex<double>> const& signal,
    std::vector<std::complex<double>> const& kernel,
    Transformer const& t
);
