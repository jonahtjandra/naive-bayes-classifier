#include <catch2/catch.hpp>
#include <core/train.h>
#include <fstream>

TEST_CASE(">> operator overload") {
    naivebayes::Train train(3);
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

