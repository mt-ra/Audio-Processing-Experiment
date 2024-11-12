#pragma once

#include <vector>
#include <boost/circular_buffer.hpp> // TODO: INSTALL BOOST LIBRARIES

#include <portsf_wrappers.h>
#include <lookup_gens.h>
#include <window_processors.h>

class StreamProcessor {
    boost::circular_buffer<std::complex<double>> pre_buf; // where samples are stored before processing
    boost::circular_buffer<std::complex<double>> post_buf; // where samples are stored after processing
    size_t window_size;
    size_t sample_rate;
    psf_ostream& psfout;

    std::vector<std::complex<double>> hann;
    Transformer transformer;

public:
    StreamProcessor(   
        psf_ostream& psfout_, 
        size_t window_size_
    );

public:

    // writing to the stream
    friend StreamProcessor& operator<<(StreamProcessor& proc, std::vector<std::complex<double>> in);

private:
    void try_to_consume_pre_buf();
    void try_to_consume_post_buf();
};