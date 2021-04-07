#include <__bit_reference>

#ifndef NAIVE_BAYES_MODEL_H
#define NAIVE_BAYES_MODEL_H

#include <vector>
#include <iostream>
#include "images.h"
#include "train.h"

namespace naivebayes {

class model {
public:
    model();
    void Train(naivebayes::Train train);
    void CalculateProbabilty(const std::vector<naivebayes::Images>& images);
    void CalculatePrior(const std::vector<naivebayes::Images>& images);
    friend std::istream& operator>>(std::istream& is, model& model);
    friend std::ostream& operator<<(std::ostream& os, model& model);
    float GetPrior(int i);
    float GetProbability(int i, int j, int k, int l);


private:
    float const laplace_smoothing_ = 1;
    //stored at index referring to the class of digit, so index 0 = class 0
    static const size_t kSize = 3;
    //probabilites multidimensional array in the format: [i][j][2][10]
    float probabilities_[kSize][kSize][2][10];
    float prior_ [10];
};

} // namespace naivebayes
#endif //NAIVE_BAYES_MODEL_H
