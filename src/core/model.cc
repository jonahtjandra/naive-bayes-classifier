//
// Created by Jonah on 04/04/21.
//

#include "core/model.h"

#include <utility>

namespace naivebayes{
naivebayes::model::model() {}

void model::Train(naivebayes::Images train) {
    CalculateProbability(train.GetImages());
    CalculatePrior(train.GetImages());
}

std::istream &operator>>(std::istream &is, model &model) {
    std::string line = "";
    std::string text;
    std::vector<float> probabilities;
    int count = 0;

    //convert file from istream into a string so it can be easily parsed.
    while (std::getline(is, line)) {
        probabilities.push_back(std::stof(line));
    }

    for (int i = 0; i < 10; i++) {
        model.prior_[i] = probabilities.at(i);
    }

    for (int i = 0; i < naivebayes::model::kSize; i++) {
        for (int j = 0; j < naivebayes::model::kSize; j++) {
            for (int k = 0; k < 2; k++) {
                for (int l = 0; l < 10; l++) {
                    model.probabilities_[i][j][k][l] = probabilities.at(10 + count);
                    count++;
                }
            }
        }
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, model &model) {
    std::string separator = "\n";
    for (int i = 0; i < 10; i++) {
        os << model.prior_[i];
        os << separator;
    }

    for (int i = 0; i < naivebayes::model::kSize; i++) {
        for (int j = 0; j < naivebayes::model::kSize; j++) {
            for (int k = 0; k < 2; k++) {
                for (int l = 0; l < 10; l++) {
                    os << model.probabilities_[i][j][k][l];
                    os << separator;
                }
            }
        }
    }
    return os;
}

void model::CalculatePrior(const std::vector<naivebayes::Images::Image>& images) {
    for (int i = 0; i < 10; i++) {
        int num_of_image = 0;
        int total_num_of_image = 0;
        for (const Images::Image& image : images) {
            if (image.GetDigit() == i) {
                num_of_image++;
            }
            total_num_of_image++;
        }
        prior_[i] = (laplace_smoothing_+num_of_image)/(10*laplace_smoothing_+total_num_of_image);
    }
}

void model::CalculateProbability(const std::vector<naivebayes::Images::Image>& images) {
    for (int i = 0; i < kSize; i++) {
        for (int j = 0; j < kSize; j++) {
            for (int k = 0; k < 2; k++) {
                for (int l = 0; l < 10; l++) {
                    int num_of_image = 0;
                    int total_num_of_image = 0;
                    for (const Images::Image& image : images) {
                        if (image.GetDigit() == l) {
                            total_num_of_image++;
                            //shaded
                            if (k == 0) {
                                if (image.GetImage().at(i * kSize + j) == '#' ||
                                    image.GetImage().at(i * kSize + j) == '+') {
                                    num_of_image++;
                                }
                            } else {
                                //unshaded
                                if (image.GetImage().at(i * kSize + j) == ' ') {
                                    num_of_image++;
                                }
                            }
                        }
                    }
                    probabilities_[i][j][k][l] = (laplace_smoothing_ + float(num_of_image))
                                                 /(2*laplace_smoothing_ + float(total_num_of_image));
                }
            }
        }
    }
}

float model::GetPrior(int i) const {
    return this->prior_[i];
}

float model::GetProbability(int i, int j, int k, int l) const {
    return this->probabilities_[i][j][k][l];
}


} // namespace naivebayes


