#include <__bit_reference>

#ifndef NAIVE_BAYES_MODEL_H
#define NAIVE_BAYES_MODEL_H

#include <vector>
#include <iostream>
#include "images.h"

namespace naivebayes {

class model {
public:
    model();
    void train(std::vector<naivebayes::Images> images);
    void save();

private:
    float CalculatePrior(int c);
    float CalculateProbability(std::vector<naivebayes::Images> images);
    float const laplace_smoothing_ = 1;
    //std::string save_path_ = "";
    //stored at index referring to the class of digit, so index 0 = class 0
    std::vector<float> prior;
    static const size_t kSize = 28;
    //probabilites multidimensional array in the format: [i][j][2][10]
    float probabilities_[kSize][kSize][2][10];

};

} // namespace naivebayes
#endif //NAIVE_BAYES_MODEL_H
