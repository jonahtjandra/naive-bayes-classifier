#include "core/images.h"

namespace naivebayes {
naivebayes::Images::Images(int digit, std::vector<char> image) {
    digit_ = digit;
    image_ = image;
}
} // namespace naivebayes

