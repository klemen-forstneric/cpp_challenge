#ifndef IMAGE_HELPER_H_
#define IMAGE_HELPER_H_

#include <vector>

namespace image_helper {

struct Image {
  size_t width, height;
  std::vector<uint8_t> pixels;

  bool IsEmpty() { return pixels.empty() || width == 0 || height == 0; }
};

Image DecodeJpegFromBuffer(const std::vector<uint8_t>& buffer);
uint32_t GetAveragePixelValue(const Image& image);

}  // namespace image_helper

#endif  // IMAGE_HELPER_H_
