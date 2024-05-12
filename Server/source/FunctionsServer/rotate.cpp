#include <iostream>
#include <vector>

#include "../../include/Logger.h"
#include "../../include/FunctionsServerh/stb_image.h"
#include "../../include/FunctionsServerh/stb_image_write.h"

void rotate(const std::string& filename, const std::string& newfilename) {
    std::string fullPath = "../../../resources/" + filename;
    int width, height, channels;
    unsigned char* data = stbi_load(fullPath.c_str(), &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        logMessage("Error: Unable to open file rotate()");
        return;
    }

    std::cout << "Image loaded successfully" << std::endl;

    std::vector<unsigned char> rotatedData(width * height * channels);

    // Поворачиваем изображение на 180 градусов
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = (y * width + x) * channels;
            int rotatedIndex = ((height - y - 1) * width + (width - x - 1)) * channels;
            for (int c = 0; c < channels; ++c) {
                rotatedData[rotatedIndex + c] = data[index + c];
            }
        }
    }

    std::string fullPath2 = "../../../resources/" + newfilename;
    // Записываем повернутое изображение в новый файл
    stbi_write_jpg(fullPath2.c_str(), width, height, channels, rotatedData.data(), 100);
    logMessage("rotate() successfully");
    stbi_image_free(data);
}
