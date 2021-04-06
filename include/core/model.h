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
    void Train(const std::vector<naivebayes::Images>& images);
    void Save();
    void Load();
    void CalculateProbabilty(const std::vector<naivebayes::Images>& images);
    void CalculatePrior(const std::vector<naivebayes::Images>& images);
    friend std::istream& operator>>(std::istream& is, model& model);
    friend std::ostream& operator<<(std::ostream& os, model& model);

private:
    float const laplace_smoothing_ = 1;
    //std::string save_path_ = "";
    //stored at index referring to the class of digit, so index 0 = class 0
    static const size_t kSize = 28;
    //probabilites multidimensional array in the format: [i][j][2][10]
    float probabilities_[kSize][kSize][2][10];
    float prior_ [10];

};

} // namespace naivebayes
#endif //NAIVE_BAYES_MODEL_H
