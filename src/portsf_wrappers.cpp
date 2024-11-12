#include <vector>
#include <complex>
#include <iostream>

#include <portsf.h>
#include <portsf_wrappers.h>

/// ISTREAM

psf_istream::psf_istream(std::string filename) {
    in_fd = psf_sndOpen(filename.c_str(), &props, 0);
    size = psf_sndSize(in_fd);
    position = 0;
}

psf_istream::~psf_istream() {
    psf_sndClose(in_fd);
}

psf_istream& operator>>(psf_istream& in, std::vector<std::complex<double>>& buf) {
    size_t n = buf.size();
    float *buffer = new float[n];
    psf_sndReadFloatFrames(in.in_fd, buffer, n/2);
    in.position += n/2;
    for (int i = 0; i < n; ++i) {
        buf[i] = buffer[i]; // cast to std::complex<double>
    }
    delete[] buffer;
    return in;
}

PSF_PROPS psf_istream::get_props() {
    return props;
}

bool psf_istream::eof() {
    return position >= size;
}

/// OSTREAM

psf_ostream::psf_ostream(std::string filename, PSF_PROPS props_) {
    props = props_;
    out_fd = psf_sndCreate(filename.c_str(), &props, 1, 0, PSF_CREATE_RDWR);
}

psf_ostream::~psf_ostream() {
    psf_sndClose(out_fd);
}

psf_ostream& operator<<(psf_ostream& out, std::vector<std::complex<double>> buf) {
    size_t n = buf.size();
    float *buffer = new float[n];
    for (int i = 0; i < n; ++i) {
        buffer[i] = (float) buf[i].real();
    }
    psf_sndWriteFloatFrames(out.out_fd, buffer, n/2);
    delete[] buffer;
    return out;
}

PSF_PROPS psf_ostream::get_props() {
    return props;
}
