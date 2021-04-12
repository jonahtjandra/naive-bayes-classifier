#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <core/images.h>
#include <core/model.h>

TEST_CASE(">> operator overload") {
    naivebayes::Images train(3);
    std::string file_path = "/Users/jonah/Desktop/SP2021/Cinder/my-projects/naive-bayes-jonahtjandra/tests/test_train_images.txt";
    std::ifstream input_file(file_path);
    if (input_file.is_open()) {
        input_file >> train;
        input_file.close();
    }
    SECTION("Make sure that it correctly parses the digits") {
        REQUIRE(train.GetImages().at(1).GetDigit() == 0);
    }

    SECTION("Make sure that it correctly parses the images") {
        REQUIRE(train.GetImages().at(1).GetImage().size() == 9);
    }

    SECTION("Make sure that it parses all the images") {
        REQUIRE(train.GetImages().size() == 5);
    }
}

TEST_CASE("Parsing different image sizes") {
    naivebayes::Images train(5);
    std::string file_path = "/Users/jonah/Desktop/SP2021/Cinder/my-projects/naive-bayes-jonahtjandra/tests/test_train_images_length_5";
    std::ifstream input_file(file_path);
    if (input_file.is_open()) {
        input_file >> train;
        input_file.close();
    }
    SECTION("Make sure that it correctly parses the digits") {
        REQUIRE(train.GetImages().at(1).GetDigit() == 3);
    }

    SECTION("Make sure that it correctly parses the images") {
        REQUIRE(train.GetImages().at(1).GetImage().size() == 25);
    }

    SECTION("Make sure that it parses all the images") {
        REQUIRE(train.GetImages().size() == 2);
    }
}

TEST_CASE("Calculating Probabilities") {
    //load images
    naivebayes::Images train(3);
    std::string file_path = "/Users/jonah/Desktop/SP2021/Cinder/my-projects/naive-bayes-jonahtjandra/tests/test_train_images.txt";
    std::ifstream input_file(file_path);

    if (input_file.is_open()) {
        input_file >> train;
        input_file.close();
    }

    naivebayes::model model(3);
    model.Train(train);

    SECTION("Feature Probability Check") {
        REQUIRE(model.GetProbability(0,0,0,0) == Approx(float(2.0/3.0)).epsilon(0.00001));
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

    naivebayes::model model(3);
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

    naivebayes::model model(3);
    model.Train(train);

    if (output_file.is_open()) {
        output_file << model;
    }

    SECTION("Load model") {
        naivebayes::model model_new(3);
        if (model_file.is_open()) {
            model_file >> model_new;
            model_file.close();
        }
        SECTION("Feature Probability Check") {
            REQUIRE(model_new.GetProbability(0,0,0,0) == Approx(float(2.0/3.0)).epsilon(0.00001));
        }
        SECTION("Prior Probability Check") {
            REQUIRE(model.GetPrior(0) == Approx(float(2.0/15.0)).epsilon(0.00001));
        }
    }

}
TEST_CASE("Test model accuracy") {
    //loading model
    std::string model_path = "/Users/jonah/Desktop/SP2021/Cinder/my-projects/naive-bayes-jonahtjandra/data/savedmodel.txt";
    std::ifstream model_file(model_path);
    naivebayes::model model(28);
    if (model_file.is_open()) {
        model_file >> model;
        model_file.close();
    }
    //loading validation data set
    naivebayes::Images test_images = naivebayes::Images(28);
    std::string test_path = "/Users/jonah/Desktop/SP2021/Cinder/my-projects/naive-bayes-jonahtjandra/data/testimagesandlabels.txt";
    std::ifstream test_file(test_path);
    if (test_file.is_open()) {
        test_file >> test_images;
        test_file.close();
    }

    SECTION("Test Calculate Accuracy") {
        REQUIRE(model.CalculateAccuracy(test_images) > 0.7);
    }

}

TEST_CASE() {

}

