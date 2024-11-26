#pragma once

#include <window_processors.h>
#include <Transformer.h>

// window processor interface
struct WindowProcessor {
    virtual std::vector<std::complex<double>> operator()(
        std::vector<std::complex<double>> const& signal
    ) = 0;
};

struct FBrickwallLowpass : public WindowProcessor {
    size_t cutoff_;
    Transformer transformer_;

    FBrickwallLowpass(size_t cutoff, size_t win_size);

    std::vector<std::complex<double>> operator()(
        std::vector<std::complex<double>> const& signal
    ) override;
};

struct FBrickwallHighpass : public WindowProcessor {
    size_t cutoff_;
    Transformer transformer_;

    FBrickwallHighpass(size_t cutoff, size_t win_size);

    std::vector<std::complex<double>> operator()(
        std::vector<std::complex<double>> const& signal
    ) override;
};