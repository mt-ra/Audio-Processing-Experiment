#pragma once

#include <window_processors.h>
#include <Transformer.h>

#include <vector>
#include <complex>

// window processor interface
struct WindowProcessor {
    virtual std::vector<std::complex<double>> operator()(
        std::vector<std::complex<double>> const& signal
    ) = 0;
};

// concrete functor classes

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

struct FConvLowpass : public WindowProcessor {
    size_t width_;
    Transformer transformer_;
    std::vector<std::complex<double>> kernel_;

    FConvLowpass(size_t width, size_t win_size);

    std::vector<std::complex<double>> operator()(
        std::vector<std::complex<double>> const& signal
    ) override;
};

struct FConvHighpass : public WindowProcessor {
    size_t width_;
    Transformer transformer_;
    std::vector<std::complex<double>> kernel_;

    FConvHighpass(size_t width, size_t win_size);

    std::vector<std::complex<double>> operator()(
        std::vector<std::complex<double>> const& signal
    ) override;
};