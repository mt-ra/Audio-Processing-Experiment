#pragma once

#include <vector>
#include <complex>
#include <portsf.h>

class psf_istream {
    int in_fd;
    int size;
    int position;
    PSF_PROPS props;

public:
    psf_istream(std::string filename);
    ~psf_istream();

public:
    friend psf_istream& operator>>(psf_istream& in, std::vector<std::complex<double>>& buf);

    PSF_PROPS get_props();

    bool eof();
};

class psf_ostream {
    int out_fd;
    PSF_PROPS props;

public:
    psf_ostream(std::string filename, PSF_PROPS props_);
    ~psf_ostream();

public:
    friend psf_ostream& operator<<(psf_ostream& out, std::vector<std::complex<double>> buf);

    PSF_PROPS get_props();
};
