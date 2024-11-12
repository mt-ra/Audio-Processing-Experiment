#include <iostream>

#include <portsf.h>
#include <fftw3.h>
#include <Transformer.h>

int main(int argc, char *argv[]) {
    PSF_PROPS props;
    int in_fd = psf_sndOpen(argv[1], &props, 0);
    props.srate = 44100;
    int out_fd = psf_sndCreate("alt.wav", &props, 1, 0, PSF_CREATE_RDWR);
    float buffer[2048];

    Transformer t(1024);

    int amt = atoi(argv[2]);

    // number of windows is 1000
    // each window contains 1024 frames
    for (int w = 0; w < 1000; ++w) {
        psf_sndReadFloatFrames(in_fd, buffer, 1024);
        std::vector<std::complex<double>> left_buf;
        std::vector<std::complex<double>> right_buf;

        // split into two channels
        for (int i = 0; i < 2048; i += 2) {
            left_buf.push_back(buffer[i]);
        }
        for (int i = 1; i < 2048; i += 2) {
            right_buf.push_back(buffer[i]);
        }

        // process channels separately
        auto lf = t.dft(left_buf);
        auto rf = t.dft(right_buf);

        for (int i = amt; i < 1024 - amt; ++i) {
            lf[i] = 0;
            rf[i] = 0;
        }

        left_buf = t.idft(lf);
        right_buf = t.idft(rf);

        // recombine into stereo
        for (int i = 0; i < 2048; i += 2) {
            buffer[i] = left_buf[i/2].real();
        }
        for (int i = 1; i < 2048; i += 2) {
            buffer[i] = right_buf[(i-1)/2].real();
        }
        
        psf_sndWriteFloatFrames(out_fd, buffer, 1024);
    }
}