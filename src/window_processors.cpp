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

std::vector<std::complex<double>> frequency_snap(
    std::vector<std::complex<double>> const& signal,
    size_t target, // target frequency
    Transformer const& t, // thing used to do the dft and idft
    std::vector<std::complex<double>>& hann // lookup table for hann window
) {
    int n = signal.size();
    auto coeffs = t.dft(signal);

    // i represents the angular frequency
    std::vector<std::complex<double>> result(n, 0);
    for (int i = 0; i < target; ++i) {
        std::vector<std::complex<double>> filtered(n, 0);

        // filter for frequencies that are approximately conguent to i mod target
        for (int j = 0; j < n/2 - 1; ++j) {
            if (j % target == i) {
                int snapto = j - (j%target);
                filtered[1 + snapto] = coeffs[i + j];
                filtered[n - 1 - snapto] = coeffs[n - 1 - j];
            }
            filtered[0] = 0;
            filtered[n/2 + 1] = 0;
        }

        auto time_domain = t.idft(filtered);
        for (int j = 0; j < n; ++j) {
            result[j] += time_domain[j];
        }
    }

    for (int i = 0; i < n; ++i) {
        result[i] = result[i] * hann[i];
    }

    return result;
}