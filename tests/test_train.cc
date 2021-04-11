#include <catch2/catch.hpp>
#include <core/images.h>
#include <fstream>

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

