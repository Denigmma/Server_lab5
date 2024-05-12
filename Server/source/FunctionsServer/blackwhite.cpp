#include "../../include/FunctionsServerh/blackwhite.h"
#include "../../include/FunctionsServerh/stb_image.h"
#include "../../include/FunctionsServerh/stb_image_write.h"
#include "../../include/Logger.h"
#include <iostream>

void applyBlackAndWhiteFilter(std::vector<RGB>& pixels) {
    for (auto& pixel : pixels) {
        // Среднее значение компонентов RGB
        unsigned char gray = (pixel.r + pixel.g + pixel.b) / 3;
        // Задаем одинаковые значения для всех компонентов
        pixel.r = pixel.g = pixel.b = gray;
    }
}

void blackAndWhite(const std::string& filename, const std::string& newfilename) {
    std::string fullPath = "../../../resources/" + filename;
    int width, height, channels;
    unsigned char* data = stbi_load(fullPath.c_str(), &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        logMessage("Error: Unable to open file blackwhite()");
        return;
    }

    // Конвертируем данные в вектор RGB
    std::vector<RGB> pixels(width * height);
    for (int i = 0; i < width * height; ++i) {
        pixels[i].r = data[i * channels];
        pixels[i].g = data[i * channels + 1];
        pixels[i].b = data[i * channels + 2];
    }

    // Применяем черно-белый фильтр
    applyBlackAndWhiteFilter(pixels);

    // Конвертируем данные обратно в формат, подходящий для записи
    for (int i = 0; i < width * height; ++i) {
        data[i * channels] = pixels[i].r;
        data[i * channels + 1] = pixels[i].g;
        data[i * channels + 2] = pixels[i].b;
    }

    std::string fullPath2 = "../../../resources/" + newfilename;
    // Записываем измененное изображение
    stbi_write_jpg(fullPath2.c_str(), width, height, channels, data, 100);
    logMessage("The black and white filter has been successfully applied");
    stbi_image_free(data);
}
