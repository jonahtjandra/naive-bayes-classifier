//
// Created by Jonah on 04/04/21.
//

#include "core/model.h"

namespace naivebayes{
naivebayes::model::model() {

}

void model::train(std::vector<naivebayes::Images> images) {
    float all_pixel_values;
    std::vector<naivebayes::Images> image_class;
    for (int i = 0; i < kSize; i++) {
        for (int j = 0; j < kSize; j++) {
            for (int k = 0; k < 2; k++) {
                for (int l = 0; l < 10; l++) {
                    int num_of_image = 0;
                    int total_num_of_image = 0;
                    for (Images image : images) {
                        if (image.GetDigit() == l) {
                            total_num_of_image++;
                        }
                        if (image.)
                    }
                    probabilities_[i][j][k][l] = 0;
                }
            }
        }
    }
}

float model::CalculatePrior(int c) {
    return 0;
}

float model::CalculateProbability(int c) {
    return 0;
}

void model::save() {

}
} // namespace naivebayes


