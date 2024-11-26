#include <StreamProcessor.h>
#include <iostream>
#include <window_processors.h>
#include <window_processor_functors.h>

StreamProcessor::StreamProcessor(
    psf_ostream& psfout_, 
    size_t window_size_,
    WindowProcessor *win_processor_
) : 
    psfout(psfout_), 
    window_size(window_size_), 
    win_processor(win_processor_),
    pre_buf(8 * window_size_),
    post_buf(8 * window_size_)
{
    sample_rate = psfout.get_props().srate;
    hann = hann_window_lookup(window_size);

    // some dummy stuff at the beginning for the edge case
    for (int i = 0; i < window_size/2; ++i) {
        post_buf.push_back(0);
    }
}

// friend function
StreamProcessor& operator<<(StreamProcessor& proc, std::vector<std::complex<double>> in) {
    for (auto e : in) {
        proc.pre_buf.push_back(e);
    }
    
    proc.try_to_consume_pre_buf();
    proc.try_to_consume_post_buf();

    return proc;
}

void StreamProcessor::try_to_consume_pre_buf() {
    while (pre_buf.size() >= window_size) {
        std::vector<std::complex<double>> window{};
        for (int i = 0; i < window_size; ++i) {
            window.push_back(hann[i] * pre_buf[i]);
        }

        for (int i = 0; i < window_size/2; ++i) {
            pre_buf.pop_front();
        }

        // then process it using the window processing function
        auto processed_window = win_processor->operator()(window);

        for (auto e : processed_window) {
            // don't overlap the windows just yet
            post_buf.push_back(e);
        }
    }
}

void StreamProcessor::try_to_consume_post_buf() {
    while (post_buf.size() >= window_size) {
        std::vector<std::complex<double>> out_buf;
        for (int i = 0; i < window_size/2; ++i) {
            out_buf.push_back(post_buf[i] + post_buf[window_size/2 + i]);
            out_buf.push_back(post_buf[i] + post_buf[window_size/2 + i]); // do it again cos stereo
        }
        for (int i = 0; i < window_size; ++i) {
            post_buf.pop_front();
        }
        psfout << out_buf;
    }
}