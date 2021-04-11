//
// Created by Jonah on 04/04/21.
//

#include "core/model.h"
#include <math.h>

#include <utility>

namespace naivebayes{
naivebayes::model::model() {}

void model::Train(naivebayes::Images train) {
    CalculateProbability(train.GetImages());
    CalculatePrior(train.GetImages());
}

//loading in model
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

    //probabilites multidimensional array in the format: [i][j][shaded or unshaded][digit classes]
    for (int i = 0; i < naivebayes::model::kSize; i++) {
        for (int j = 0; j < naivebayes::model::kSize; j++) {
            for (int k = 0; k < 2; k++) {
                for (int l = 0; l < 10; l++) {
                    //the first 10 lines are dedicated to prior probabilities instead of features
                    model.features_prob[i][j][k][l] = probabilities.at(10 + count);
                    count++;
                }
            }
        }
    }
    return is;
}

//saving model
std::ostream &operator<<(std::ostream &os, model &model) {
    std::string separator = "\n";
    for (int i = 0; i < 10; i++) {
        os << model.prior_[i];
        os << separator;
    }

    //probabilites multidimensional array in the format: [i][j][shaded or unshaded][digit classes]
    for (int i = 0; i < naivebayes::model::kSize; i++) {
        for (int j = 0; j < naivebayes::model::kSize; j++) {
            for (int k = 0; k < 2; k++) {
                for (int l = 0; l < 10; l++) {
                    os << model.features_prob[i][j][k][l];
                    os << separator;
                }
            }
        }
    }
    return os;
}

void model::CalculatePrior(const std::vector<naivebayes::Images::Image>& images) {
    //10 is the number of digit classes
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
    //probabilites multidimensional array in the format: [i][j][shaded or unshaded][digit classes]
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
                    features_prob[i][j][k][l] = (laplace_smoothing_ + float(num_of_image))
                                                / (2*laplace_smoothing_ + float(total_num_of_image));
                }
            }
        }
    }
}

float model::GetPrior(int i) const {
    return this->prior_[i];
}

float model::GetProbability(int i, int j, int k, int l) const {
    return this->features_prob[i][j][k][l];
}

int model::MakePrediction(std::vector<std::vector<char>> image) const {
    int prediction = 0;
    //likelihoods for each digit class
    float likelihoods[10] = {0};
    float highest_likelihood = INT32_MIN;
    int count = 0;
    //computing for likelihood score for each digit class
    for (int l = 0 ; l < 10; l++) {
        likelihoods[l] += log(prior_[l]);
        for (int i = 0; i < kSize; i++) {
            for (int j = 0; j < kSize; j++) {
                count++;
                if (image[i][j] == '#' || image[i][j] == '+') {
                    likelihoods[l] += log(features_prob[i][j][0][l]);
                } else {
                    likelihoods[l] += log(features_prob[i][j][1][l]);
                }
            }
        }
    }
    //finding highest likelihood
    for (int i = 0; i < 10; i++) {
        if (likelihoods[i] > highest_likelihood) {
            highest_likelihood = likelihoods[i];
            prediction = i;
        }
    }
    return prediction;
}

    double model::CalculateAccuracy(naivebayes::Images validation_data) const {
        int correct_predictions = 0;
        int count = 0;
        for (const Images::Image& image : validation_data.GetImages()) {
            count++;
            if (MakePrediction(validation_data.To2dVec(image.GetImage())) == image.GetDigit()) {
                correct_predictions += 1;
            }
        }
        return float(correct_predictions)/float(count);
    }


} // namespace naivebayes


