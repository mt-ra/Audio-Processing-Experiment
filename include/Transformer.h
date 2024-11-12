#pragma once

#include <vector>
#include <complex>
#include <fftw3.h>

class Transformer {
    size_t n;
    fftw_complex *in_buf;
    fftw_complex *out_buf;
    fftw_plan forward_plan;
    fftw_plan backward_plan;

public:
    Transformer(size_t n_);
    ~Transformer();
    Transformer(Transformer& t) = delete;
    Transformer& operator=(const Transformer& other) = delete;

public:
    std::vector<std::complex<double>> dft(const std::vector<std::complex<double>>& c);
    std::vector<std::complex<double>> idft(const std::vector<std::complex<double>>& ch);
};