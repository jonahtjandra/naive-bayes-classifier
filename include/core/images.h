//
// Created by Jonah on 04/04/21.
//

#ifndef NAIVE_BAYES_IMAGES_H
#define NAIVE_BAYES_IMAGES_H

#include <vector>
#include <iostream>

namespace naivebayes {
class Images {
public:
    Images(int digit, std::vector<char> image);
private:
    int digit_;
    std::vector<char> image_;
};

} //namespace naivebayes

#endif //NAIVE_BAYES_IMAGES_H
