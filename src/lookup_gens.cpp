#include <vector>
#include <complex>

std::vector<std::complex<double>> const hann_window_lookup(size_t n) {
    double phi = 0;
    auto lookup = std::vector<std::complex<double>>();
    for (int i = 0; i < n; ++i) {
        lookup.push_back((1 - cos(phi))/2);
        phi += 2*M_PI/n;
    }
    return lookup;
}