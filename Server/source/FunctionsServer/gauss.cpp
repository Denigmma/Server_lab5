#include "../../include/FunctionsServerh/gauss.h"
#include "../../include\Logger.h"

#include <iostream>
#include <fstream>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "../../include/FunctionsServerh/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../include/FunctionsServerh/stb_image_write.h"

void applyGaussianFilter(std::vector<RGB>& pixels, int width, int height) {
	std::vector<RGB> resultPixels(pixels.size());

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int sumR = 0, sumG = 0, sumB = 0;
			int count = 0;

			// Проходим по окрестности пикселя
			for (int dy = -1; dy <= 1; ++dy) {
				for (int dx = -1; dx <= 1; ++dx) {
					int nx = x + dx;
					int ny = y + dy;

					// Проверяем, чтобы координаты были в пределах изображения
					if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
						RGB& neighborPixel = pixels[ny * width + nx];
						sumR += neighborPixel.r;
						sumG += neighborPixel.g;
						sumB += neighborPixel.b;
						++count;
					}
				}
			}

			// Усредняем значения пикселей в окрестности
			resultPixels[y * width + x].r = sumR / count;
			resultPixels[y * width + x].g = sumG / count;
			resultPixels[y * width + x].b = sumB / count;
		}
	}

	// Заменяем исходные пиксели на результирующие
	pixels = resultPixels;

	// Пример реализации фильтра Гаусса здесь
	// Этот код будет применять фильтр к пикселям изображения
}

void gauss(const std::string& filename, const std::string& newfilename) {
	std::string fullPath = "../../../resources/" + filename;
	int width, height, channels;
	unsigned char* data = stbi_load(fullPath.c_str(), &width, &height, &channels, 0);
	if (!data) {
		std::cerr << "Error: Unable to open file " << filename << std::endl;
		logMessage("Error: Unable to open file gauss()");
		return;
	}
	// Конвертируем данные в вектор RGB
	std::vector<RGB> pixels(width * height);
	for (int i = 0; i < width * height; ++i) {
		pixels[i].r = data[i * channels];
		pixels[i].g = data[i * channels + 1];
		pixels[i].b = data[i * channels + 2];
	}

	// Применяем фильтр Гаусса к изображению
	applyGaussianFilter(pixels, width, height);

	// Конвертируем данные обратно в формат, подходящий для записи
	for (int i = 0; i < width * height; ++i) {
		data[i * channels] = pixels[i].r;
		data[i * channels + 1] = pixels[i].g;
		data[i * channels + 2] = pixels[i].b;
	}

	std::string fullPath2 = "../../../resources/" + newfilename;
	// Записываем измененное изображение
	stbi_write_jpg(fullPath2.c_str(), width, height, channels, data, 100);
	logMessage("gauss() successfully");
	stbi_image_free(data);
}
