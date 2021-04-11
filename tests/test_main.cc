#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <core/images.h>
#include <core/model.h>

TEST_CASE("Calculating Probabilities") {
    naivebayes::Images train(3);
    std::string file_path = "/Users/jonah/Desktop/SP2021/Cinder/my-projects/naive-bayes-jonahtjandra/tests/test_train_images.txt";
    std::ifstream input_file(file_path);

    if (input_file.is_open()) {
        input_file >> train;
        input_file.close();
    }

    naivebayes::model model;
    model.Train(train);

    SECTION("Feature Probability Check") {
        REQUIRE(model.GetProbability(0,0,0,0) == Approx(2.0/3.0).epsilon(0.00001));
    }

    SECTION("Prior Probability Check") {
        REQUIRE(model.GetPrior(0) == Approx(float(2.0/15.0)).epsilon(0.00001));
    }

}

TEST_CASE("Saving model into a file") {
    naivebayes::Images train(3);
    std::string file_path = "/Users/jonah/Desktop/SP2021/Cinder/my-projects/naive-bayes-jonahtjandra/tests/test_train_images.txt";
    std::string out_path = "/Users/jonah/Desktop/SP2021/Cinder/my-projects/naive-bayes-jonahtjandra/tests/test_output_model.txt";
    std::ifstream input_file(file_path);
    std::ofstream output_file(out_path);

    if (input_file.is_open()) {
        input_file >> train;
        input_file.close();
    }

    naivebayes::model model;
    model.Train(train);

    if (output_file.is_open()) {
        output_file << model;
    }
}

TEST_CASE("Saving model into a file and loading it back") {
    naivebayes::Images train(3);
    std::string file_path = "/Users/jonah/Desktop/SP2021/Cinder/my-projects/naive-bayes-jonahtjandra/tests/test_train_images.txt";
    std::string out_path = "/Users/jonah/Desktop/SP2021/Cinder/my-projects/naive-bayes-jonahtjandra/tests/test_output_model.txt";
    std::string model_path = "/Users/jonah/Desktop/SP2021/Cinder/my-projects/naive-bayes-jonahtjandra/tests/test_load_model.txt";
    std::ifstream input_file(file_path);
    std::ofstream output_file(out_path);
    std::ifstream model_file(model_path);

    if (input_file.is_open()) {
        input_file >> train;
        input_file.close();
    }

    naivebayes::model model;
    model.Train(train);

    if (output_file.is_open()) {
        output_file << model;
    }

    SECTION("Load model") {
        naivebayes::model model_new;
        if (model_file.is_open()) {
            model_file >> model_new;
            model_file.close();
        }
        SECTION("Feature Probability Check") {
            REQUIRE(model_new.GetProbability(0,0,0,0) == Approx(2.0/3.0).epsilon(0.00001));
        }
        SECTION("Prior Probability Check") {
            REQUIRE(model.GetPrior(0) == Approx(float(2.0/15.0)).epsilon(0.00001));
        }
    }

}

