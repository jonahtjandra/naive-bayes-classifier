//
// Created by Jonah on 05/04/21.
//

#ifndef NAIVE_BAYES_TRAIN_H
#define NAIVE_BAYES_TRAIN_H

#include <vector>
#include <iostream>
#include "images.h"

namespace naivebayes {
class Train {
public:
    Train();
    std::vector<naivebayes::Images> GetImages() const;
    friend std::istream& operator>>(std::istream& is, Train& train);
    std::vector<naivebayes::Images> images_;
private:
    //const size_t kSize_ = 28;

};

}; // namespace naivebayes

#endif //NAIVE_BAYES_TRAIN_H
