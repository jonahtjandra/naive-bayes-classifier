#include <__bit_reference>

#ifndef NAIVE_BAYES_MODEL_H
#define NAIVE_BAYES_MODEL_H

#include <vector>
#include <iostream>
#include "images.h"

namespace naivebayes {

    class model {
    public:
        /**
         * Default constructor
         */
        model(size_t size);

        /**
         * Images method for training from a train object
         * @param train the train object used in training
         */
        void Train(naivebayes::Images train);

        /**
         * Method used for calculating features probability
         * @param images the set of images used to calculate these probabilities from
         */
        void CalculateProbability(const std::vector<naivebayes::Images::Image> &images);

        /**
         * Method used for calculating prior probabilities
         * @param images the set of images used to calculate these probabilities from
         */
        void CalculatePrior(const std::vector<naivebayes::Images::Image> &images);

        /**
         * Method for overloading the >> operator used for loading in a model
         * @param is the istream in this case a txt file
         * @param model the instance of model
         * @return an istream
         */
        friend std::istream &operator>>(std::istream &is, model &model);

        /**
         * Method for overloading the << operator used for storing a model
         * @param os the ostream in this case a txt file
         * @param model the instance of model
         * @return an ostream
         */
        friend std::ostream &operator<<(std::ostream &os, model &model);

        /**
         * Getter for prior probabilities
         * @param i the class of the prior
         * @return the prior probability
         */
        float GetPrior(int i) const;

        /**
         * Getter for feature probabilities
         * @param i the i index of the 2d image
         * @param j the j index of the 2d image
         * @param k shaded or unshaded
         * @param l the class of image
         * @return the feature probability
         */
        float GetProbability(int i, int j, int k, int l) const;

        /**
         * Method for making a prediction given an image
         * @param image a 2d vector representation of an image
         * @return the digit of the image
         */
        int MakePrediction(std::vector<std::vector<char>> image) const;

        /**
         * Method for calculating accuracy of the model
         * @param validation_data the validation images dataset
         * @return accuracy of the model
         */
        double CalculateAccuracy(naivebayes::Images validation_data) const;


    private:
        float const laplace_smoothing_ = 1;
        //size of the image
        size_t size_;
        //probabilites multidimensional array in the format: [i][j][shaded or unshaded][label]
        //i,j is position in the 2d array; k is the shaded or unshaded where 0 = shaded and 1 = unshaded; l is the label
        std::vector<std::vector<std::vector<std::vector<float>>>> features_prob;
        //there are 10 different digits
        float prior_[10];
    };

} // namespace naivebayes
#endif //NAIVE_BAYES_MODEL_H
