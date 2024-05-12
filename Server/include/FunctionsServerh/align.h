#ifndef ALIGN_H
#define ALIGN_H

#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

struct Pixel {
    unsigned char r, g, b;
};

std::vector<std::vector<Pixel>> loadImage(const char* filename, int& width, int& height);

void rotateImage(const std::vector<std::vector<Pixel>>& image, float angle, const char* filename);

float findRotationAngle(const std::vector<std::vector<Pixel>>& image);

void align(const std::string& filename, const std::string& newfilename);

#endif // ALIGN_H
