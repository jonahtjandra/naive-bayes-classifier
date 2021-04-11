#include <catch2/catch.hpp>
#include <core/images.h>

TEST_CASE("Constructor") {
    std::vector<char> charvec = {' ','*','#'};
    SECTION("Creating a new image object, make sure digit is properly instantiated") {
        naivebayes::Images::Image image = naivebayes::Images::Image{3, charvec};
        REQUIRE(image.GetDigit() == 3);
    }
    SECTION("Creating a new image object, make sure vector is properly instantiated") {
        naivebayes::Images::Image image = naivebayes::Images::Image{3, charvec};
        REQUIRE(image.GetImage().at(1) == '*');
    }
}
