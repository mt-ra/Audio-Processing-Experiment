#include <iostream>

#include <portsf.h>
#include <Transformer.h>
#include <portsf_wrappers.h>
#include <StreamProcessor.h>

int main(int argc, char *argv[]) {
    psf_istream psfin(argv[1]);
    psf_ostream psfout("out.wav", psfin.get_props());
    int winsize = atoi(argv[2]);

    StreamProcessor processor(psfout, winsize);

    // buffer gets overwritten each iteration
    // basically these behave as fixed size arrays after initialization
    std::vector<std::complex<double>> stereo(2 * winsize, 0);
    std::vector<std::complex<double>> mono_left(winsize, 0);

    // i'm lazy so I will discard the right channel
    while (!psfin.eof()) {
        psfin >> stereo;
        for (int i = 0; i < winsize; ++i) {
            mono_left[i] = stereo[2*i];
        }

        processor << mono_left;
    }
}