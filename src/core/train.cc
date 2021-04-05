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
    while (std::getline(is, line)) {
        text.append(line);
    }
    for (char c : text) {
        //actual digit values are always in start of a 28 by 28 images so they are always in the n by nth multiple order
        //in the text file, when the index is starts with zero
        if (count == 0) {
            actual = c;
            count++;
            continue;
        }
        chars.push_back(c);
        count++;
        //every time it reaches n by n create a new image and emplace into the image vector
        if (count == 785) {
            //making sure images are n by n
            if (chars.size() == 784) {
                train.images_.emplace_back(actual, chars);
            }
            chars.clear();
            count = 0;
        }
    }
    return is;
}
} // namespace naivebayes