#ifndef BLACK_AND_WHITE_FILTER_H
#define BLACK_AND_WHITE_FILTER_H
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

void applyBlackAndWhiteFilter(std::vector<RGB>& pixels);
void blackAndWhite(const std::string& filename, const std::string& newfilename);

#endif // BLACK_AND_WHITE_FILTER_H
