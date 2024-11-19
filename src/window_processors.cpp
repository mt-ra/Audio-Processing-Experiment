#include <vector>
#include <complex>
#include <window_processors.h>

#include <iostream>

std::vector<std::complex<double>> brickwall_lowpass(
    std::vector<std::complex<double>> const& signal,
    size_t cutoff,
    Transformer const& t
) {
    int n = signal.size();
    auto coeffs = t.dft(signal);
    for (int i = cutoff; i < n - cutoff; ++i) {
        coeffs[i] = 0;
    }
    return t.idft(coeffs);
}

std::vector<std::complex<double>> brickwall_highpass(
    std::vector<std::complex<double>> const& signal,
    size_t cutoff,
    Transformer const& t
) {
    int n = signal.size();
    auto coeffs = t.dft(signal);
    for (int i = 0; i < cutoff; ++i) {
        coeffs[1 + i] = 0;
        coeffs[n - 1 - i] = 0;
    }
    return t.idft(coeffs);
}