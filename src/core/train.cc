//
// Created by Jonah on 05/04/21.
//

#include <core/images.h>
#include <core/train.h>
#include <sstream>

namespace naivebayes {

naivebayes::Train::Train() {}

std::vector<naivebayes::Images> naivebayes::Train::GetImages() const {
    return images_;
}

std::istream &operator>>(std::istream &is, Train &train) {
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
        if (count == naivebayes::Train::kSize_ * naivebayes::Train::kSize_ + 1)  {
            //making sure images are n by n
            if (chars.size() == naivebayes::Train::kSize_ * naivebayes::Train::kSize_) {
                train.images_.emplace_back(actual, chars);
            }
            chars.clear();
            count = 0;
        }
    }
    return is;
}
} // namespace naivebayes