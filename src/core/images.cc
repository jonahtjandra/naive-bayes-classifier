#include "core/images.h"

namespace naivebayes {
naivebayes::Images::Images(int digit, std::vector<char> image) {
    digit_ = digit;
    image_ = image;
}

int Images::GetDigit() const {
    return digit_;
}

std::vector<char> Images::GetImage() const {
    return image_;
}

} // namespace naivebayes

