//
// Created by Jonah on 04/04/21.
//

#ifndef NAIVE_BAYES_IMAGES_H
#define NAIVE_BAYES_IMAGES_H

#include <vector>
#include <iostream>

//make struct
namespace naivebayes {
class Images {
public:
    /**
     * Constructor for Images
     * @param digit the actual digit of the image
     * @param image the vector representation of the image
     */
    Images(int digit, std::vector<char> image);

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

} //namespace naivebayes

#endif //NAIVE_BAYES_IMAGES_H
