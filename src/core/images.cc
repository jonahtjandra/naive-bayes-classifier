//
// Created by Jonah on 05/04/21.
//

#include <core/images.h>
#include <core/images.h>
#include <sstream>
#include <vector>

namespace naivebayes{

Images::Images(size_t size) {
    size_ = size;
}

std::vector<Images::Image> naivebayes::Images::GetImages() const {
    return images_;
}

std::istream &operator>>(std::istream &is, Images &train) {
    std::string line;
    std::string text;
    int count = 0;
    int actual;
    std::vector<char> chars;
    //convert file from istream into a string so it can be easily parsed.
    while (std::getline(is, line)) {
        text.append(line);
    }
    for (char c : text) {
        //actual digit values are always in start of a 28 by 28 images so they are always in the 0 order of every 29 chars.
        if (count == 0) {
            //ASCII code for single digits starts at 48
            actual = c - 48;
            //make sure that count isn't staying at zero since we continue after this line
            count++;
            //make sure that the actual value, the 0 order doesn't get appended as a char in the image
            continue;
        }
        chars.push_back(c);
        count++;
        //every time it reaches n by n create a new image and emplace into the image vector
        if (count == train.size_ * train.size_ + 1)  {
            //making sure images are n by n
            if (chars.size() == train.size_ * train.size_) {
                train.images_.emplace_back(Images::Image{actual, chars});
            }
            chars.clear();
            count = 0;
        }
    }
    return is;
}

std::vector<std::vector<char>> Images::To2dVec(std::vector<char> image) {
    int count = 0;
    std::vector<std::vector<char>> toReturn;
    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            toReturn[i][j] = image[count];
            count++;
        }
    }
    return toReturn;
}

    int Images::Image::GetDigit() const {
    return digit_;
}

std::vector<char> Images::Image::GetImage() const {
    return image_;
}

Images::Image::Image(int digit, std::vector<char> image) {
    digit_ = digit;
    image_ = image;
}

} // namespace naivebayes
