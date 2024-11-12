#include <Transformer.h>

#include <vector>
#include <complex>
#include <fftw3.h>

Transformer::Transformer(size_t n_) : n(n_) {
    in_buf = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * n);
    out_buf = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * n);
    forward_plan = fftw_plan_dft_1d(n, in_buf, out_buf, FFTW_FORWARD, FFTW_ESTIMATE);
    backward_plan = fftw_plan_dft_1d(n, in_buf, out_buf, FFTW_BACKWARD, FFTW_ESTIMATE);
}

Transformer::~Transformer() {
    fftw_destroy_plan(forward_plan);
    fftw_destroy_plan(backward_plan);
    fftw_free(in_buf);
    fftw_free(out_buf);
}

std::vector<std::complex<double>> Transformer::dft(const std::vector<std::complex<double>>& c) const {
    for (int i = 0; i < n; ++i) {
        in_buf[i][0] = c[i].real();
        in_buf[i][1] = c[i].imag();
    }
    fftw_execute(forward_plan);
    std::vector<std::complex<double>> ch;
    for (int i = 0; i < n; ++i) {
        ch.push_back({out_buf[i][0], out_buf[i][1]});
    }
    return ch;
}

std::vector<std::complex<double>> Transformer::idft(const std::vector<std::complex<double>>& ch) const {
    for (int i = 0; i < n; ++i) {
        in_buf[i][0] = ch[i].real();
        in_buf[i][1] = ch[i].imag();
    }
    fftw_execute(backward_plan);
    std::vector<std::complex<double>> c;
    for (int i = 0; i < n; ++i) {
        c.push_back({out_buf[i][0]/n, out_buf[i][1]/n});
    }
    return c;
}