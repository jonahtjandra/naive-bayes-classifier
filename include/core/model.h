#include <__bit_reference>

#ifndef NAIVE_BAYES_MODEL_H
#define NAIVE_BAYES_MODEL_H

#include <vector>
#include <iostream>

namespace naivebayes {

class model {
public:
    model();
    void train();
    void save();

private:
    std::string save_path = "";
    std::vector<float> class_probability;
    static const size_t kSize = 28;
    float probabilities[10][2][kSize][kSize];

};

} // namespace naivebayes
#endif //NAIVE_BAYES_MODEL_H
