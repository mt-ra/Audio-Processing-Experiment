#pragma once

#include <vector>
#include <complex>
#include <Transformer.h>

std::vector<std::complex<double>> brickwall_lowpass(
    std::vector<std::complex<double>> const& signal,
    size_t amount,
    Transformer const& t
);

std::vector<std::complex<double>> frequency_snap(
    std::vector<std::complex<double>> const& signal,
    size_t target,
    Transformer const& t,
    std::vector<std::complex<double>>& hann
);