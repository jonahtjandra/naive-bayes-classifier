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
    /**
     * Train constructor
     * @param size the size of the image
     */
    Train(size_t size);

    /**
     * Getter for the set of training images
     * @return the vector of training images
     */
    std::vector<naivebayes::Images> GetImages() const;

    /**
     * >> operator overload used for loading in the training images
     * @param is the istream in this case a txt file containing the images
     * @param train the train object
     * @return the istream
     */
    friend std::istream& operator>>(std::istream& is, Train& train);

private:
    size_t size_;
    std::vector<naivebayes::Images> images_;
};

}; // namespace naivebayes

#endif //NAIVE_BAYES_TRAIN_H
