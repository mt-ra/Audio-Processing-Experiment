#include <iostream>

#include <portsf.h>
#include <Transformer.h>
#include <portsf_wrappers.h>
#include <StreamProcessor.h>
#include <window_processor_functors.h>

int main(int argc, char *argv[]) {
    if (argc != 5) {
        std::cout << "usage: ./app filename.wav <WINDOW_SIZE> <FILTER_TYPE> <PARAM_VAL>" << std::endl;
        std::cout << "eg: ./app countdown.wav 1024 bwlp 50" << std::endl;
        return 1;
    }

    psf_istream psfin(argv[1]);
    psf_ostream psfout("out.wav", psfin.get_props());

    // parse the rest of the arguments
    // argv[1] is the file to process
    int winsize = atoi(argv[2]); // argv[2] is window size
    std::string type = argv[3]; // argv[3] gives the type of filter
    int param = atoi(argv[4]);// argv[4] is the parameter for the filter

    // create all window processor objects
    FBrickwallLowpass bw_lp(param, winsize);
    FBrickwallHighpass bw_hp(param, winsize);
    FConvLowpass c_lp(param, winsize);
    FConvHighpass c_hp(param, winsize); // TODO: change

    WindowProcessor *win_proc;
    if (type == "bwlp") {
        win_proc = &bw_lp;
    } else if (type == "bwhp") {
        win_proc = &bw_hp;
    } else if (type == "clp") {
        win_proc = &c_lp;
    } else if (type == "chp") {
        win_proc = &c_hp;
    } else {
        std::cout << "filter types: bwlp, bwhp, clp, chp" << std::endl;
        return 1;
    }

    StreamProcessor processor(psfout, winsize, win_proc);

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