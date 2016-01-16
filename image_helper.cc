#include "image_helper.h"

#include <iostream>
#include <numeric>

#include <opencv/cv.hpp>

namespace image_helper {

Image DecodeJpegFromBuffer(const std::vector<uint8_t>& buffer) {
  cv::Mat matrix = cv::imdecode(buffer, cv::IMREAD_GRAYSCALE);

  if (!matrix.data)
    return {};

  Image image;
  image.width = matrix.cols;
  image.height = matrix.rows;

  size_t pixel_count = matrix.cols * matrix.rows;
  image.pixels.reserve(pixel_count);

  std::copy(matrix.data, matrix.data + pixel_count,
            std::back_inserter(image.pixels));

  return image;
}

uint32_t GetAveragePixelValue(const Image& image) {
  cv::Scalar average = cv::mean(image.pixels);
  return static_cast<uint32_t>(average.val[0]);
}

}  // namespace image_helper
