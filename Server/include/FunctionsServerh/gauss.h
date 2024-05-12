#ifndef GAUSSIAN_FILTER_H
#define GAUSSIAN_FILTER_H

#include <string>
#include <vector>

#ifndef RGB_DEFINED
#define RGB_DEFINED

struct RGB {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

#endif // RGB_DEFINED

void applyGaussianFilter(std::vector<RGB>& pixels, int width, int height);
void gauss(const std::string& filename, const std::string& newfilename);

#endif // GAUSSIAN_FILTER_H


