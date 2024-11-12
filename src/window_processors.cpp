#include <vector>
#include <complex>
#include <window_processors.h>

#include <iostream>

std::vector<std::complex<double>> brickwall_lowpass(
    std::vector<std::complex<double>> const& signal,
    size_t amount,
    Transformer const& t
) {
    int n = signal.size();
    auto coeffs = t.dft(signal);
    for (int i = amount; i < n - amount; ++i) {
        coeffs[i] = 0;
    }
    return t.idft(coeffs);
}