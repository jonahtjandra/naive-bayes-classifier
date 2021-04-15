//
// Created by Jonah on 04/04/21.
//

#include "core/model.h"
#include <math.h>
#include <vector>

#include <utility>

namespace naivebayes{
naivebayes::model::model(size_t size) {
    size_ = size;
    //initializing space for features_probabilities
    features_probability_.resize(size);
    for (int i = 0; i < size; i++) {
        features_probability_[i].resize(size);
        for (int j = 0; j < size; j++) {
            features_probability_[i][j].resize(2);
            for (int k = 0; k < 2; k++ ) {
                features_probability_[i][j][k].resize(10);
                for (int l = 0; l < 10; l++) {
                }
            }
        }
    }
}

void model::Train(naivebayes::Images train) {
    CalculateFeaturesProbability(train.GetImages());
    CalculatePriorProbability(train.GetImages());
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

    //10 digits
    for (int i = 0; i < 10; i++) {
        model.prior_probability_[i] = probabilities.at(i);
    }

    //probabilites multidimensional array in the format: [i][j][shaded or unshaded][digit classes]
    for (int i = 0; i < model.size_; i++) {
        for (int j = 0; j < model.size_; j++) {
            for (int shade = 0; shade < 2; shade++) {
                for (int label = 0; label < 10; label++) {
                    //the first 10 lines are dedicated to prior probabilities instead of features
                    model.features_probability_[i][j][shade][label] = probabilities.at(10 + count);
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
        os << model.prior_probability_[i];
        os << separator;
    }

    //probabilites multidimensional array in the format: [i][j][shaded or unshaded][digit classes]
    for (int i = 0; i < model.size_; i++) {
        for (int j = 0; j < model.size_; j++) {
            for (int shade = 0; shade < 2; shade++) {
                for (int label = 0; label < 10; label++) {
                    os << model.features_probability_[i][j][shade][label];
                    os << separator;
                }
            }
        }
    }
    return os;
}

void model::CalculatePriorProbability(const std::vector<naivebayes::Images::Image>& images) {
    //10 is the number of digit classes
    for (int label = 0; label < 10; label++) {
        int num_of_image = 0;
        int total_num_of_image = 0;
        for (const Images::Image& image : images) {
            if (image.GetDigit() == label) {
                num_of_image++;
            }
            total_num_of_image++;
        }
        prior_probability_[label] = (laplace_smoothing_ + num_of_image) / (10 * laplace_smoothing_ + total_num_of_image);
    }
}

void model::CalculateFeaturesProbability(const std::vector<naivebayes::Images::Image>& images) {
    //probabilites multidimensional array in the format: [i][j][shaded or unshaded][digit classes]
    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            for (int shade = 0; shade < 2; shade++) {
                for (int label = 0; label < 10; label++) {
                    int num_of_image = 0;
                    int total_num_of_image = 0;
                    for (const Images::Image& image : images) {
                        if (image.GetDigit() == label) {
                            //total count for a particular class
                            total_num_of_image++;
                            //shaded and unshaded count for that particular class
                            if (shade == 0 && (image.GetImage().at(i * size_ + j) == '#' ||
                                image.GetImage().at(i * size_ + j) == '+')) {
                                num_of_image++;
                            } else if (shade == 1 && image.GetImage().at(i * size_ + j) == ' ') {
                                num_of_image++;
                            }
                        }
                    }
                    features_probability_[i][j][shade][label] = (laplace_smoothing_ + float(num_of_image))
                                                                / (2*laplace_smoothing_ + float(total_num_of_image));
                }
            }
        }
    }
}

float model::GetPrior(int i) const {
    return this->prior_probability_[i];
}

float model::GetFeatures(int i, int j, int shade, int label) const {
    return this->features_probability_[i][j][shade][label];
}

int model::Predict(std::vector<std::vector<char>> image) const {
    int prediction = 0;
    //likelihoods for each digit class
    float likelihoods[10] = {0};
    float highest_likelihood = INT32_MIN;
    int count = 0;
    //computing for likelihood score for each digit class
    for (int label = 0 ; label < 10; label++) {
        likelihoods[label] += log(prior_probability_[label]);
        for (int i = 0; i < size_; i++) {
            for (int j = 0; j < size_; j++) {
                count++;
                if (image[i][j] == '#' || image[i][j] == '+') {
                    //0 = shaded
                    likelihoods[label] += log(features_probability_[i][j][0][label]);
                } else {
                    //1 = unshaded
                    likelihoods[label] += log(features_probability_[i][j][1][label]);
                }
            }
        }
    }
    //finding highest likelihood
    for (int label = 0; label < 10; label++) {
        if (likelihoods[label] > highest_likelihood) {
            highest_likelihood = likelihoods[label];
            prediction = label;
        }
    }
    return prediction;
}

    double model::CalculateAccuracy(naivebayes::Images validation_data) const {
        int correct_predictions = 0;
        int count = 0;
        for (const Images::Image& image : validation_data.GetImages()) {
            count++;
            if (Predict(validation_data.To2dVec(image.GetImage())) == image.GetDigit()) {
                correct_predictions += 1;
            }
        }
        //ratio of right prediction in the validation dataset
        return float(correct_predictions)/float(count) * 100.0;
    }

    float model::GetHighestLikelihood(std::vector<std::vector<char>> image) const {
        //likelihoods for each digit class
        float likelihoods[10] = {0};
        float highest_likelihood = INT32_MIN;
        int count = 0;
        //computing for likelihood score for each digit class
        for (int label = 0 ; label < 10; label++) {
            likelihoods[label] += log(prior_probability_[label]);
            for (int i = 0; i < size_; i++) {
                for (int j = 0; j < size_; j++) {
                    count++;
                    if (image[i][j] == '#' || image[i][j] == '+') {
                        //0 = shaded
                        likelihoods[label] += log(features_probability_[i][j][0][label]);
                    } else {
                        //1 = unshaded
                        likelihoods[label] += log(features_probability_[i][j][1][label]);
                    }
                }
            }
        }
        //finding highest likelihood
        for (int label = 0; label < 10; label++) {
            if (likelihoods[label] > highest_likelihood) {
                highest_likelihood = likelihoods[label];
            }
        }
        return highest_likelihood;
    }


} // namespace naivebayes


