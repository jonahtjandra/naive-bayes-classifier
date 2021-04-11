//
// Created by Jonah on 05/04/21.
//

#ifndef NAIVE_BAYES_IMAGES_H
#define NAIVE_BAYES_IMAGES_H

#include <vector>
#include <iostream>
#include "images.h"

namespace naivebayes {
class Images {
public:
    struct Image {
        public:
            /**
             * Constructor for Images
             * @param digit the actual digit of the image
             * @param image the vector representation of the image
             */
            Image(int digit, std::vector<char> image);

            /**
             * Getter for image digit
             * @return the digit of the image
             */
            int GetDigit() const;

            /**
             * Getter for the image
             * @return the vector representation of the image
             */
            std::vector<char> GetImage() const;
        private:
            int digit_;
            std::vector<char> image_;
    };
    /**
     * Images constructor
     * @param size the size of the image
     */
    Images(size_t size);

    /**
     * Getter for the set of training images
     * @return the vector of training images
     */
    std::vector<Image> GetImages() const;

    /**
     * >> operator overload used for loading in the training images
     * @param is the istream in this case a txt file containing the images
     * @param train the train object
     * @return the istream
     */
    friend std::istream& operator>>(std::istream& is, Images& train);

    private:
        std::vector<Image> images_;
        size_t size_;
};

} // namespace naivebayes

#endif //NAIVE_BAYES_IMAGES_H
