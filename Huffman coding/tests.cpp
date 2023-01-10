#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "HTree.cpp"

TEST_CASE("FREQUENCY TABLE"){
    HTree htree1;

    std::map<char, int> frequencyTable1 = htree1.createFriquencyTable("abracadabra");

    CHECK(frequencyTable1['a'] == 5);
    CHECK(frequencyTable1['b'] == 2);
    CHECK(frequencyTable1['r'] == 2);
    CHECK(frequencyTable1['c'] == 1);
    CHECK(frequencyTable1['d'] == 1);
}

TEST_CASE("COMPRESS"){
    HTree htree1;
    std::string compressed1 = htree1.compress("abracadabra");

    CHECK(compressed1 == "01101110100010101101110");

    HTree htree2;
    std::string compressed2 = htree2.compress("this is sentence.");

    CHECK(compressed2 == "10100001011110001011110011111000110111000101111100110");
}

TEST_CASE("DEBUG COMPRESS"){
    HTree htree1;
    std::string compressed1 = htree1.compress("abracadabra");

    std::vector<int> debugCompress1 = htree1.debugCompress(compressed1);

    CHECK(debugCompress1[0] == 110);
    CHECK(debugCompress1[1] == 138);
    CHECK(debugCompress1[2] == 110);


    HTree htree2;
    std::string compressed2 = htree2.compress("this is sentence.");

    std::vector<int> debugCompress2 = htree2.debugCompress(compressed2);

    CHECK(debugCompress2[0] == 161);
    CHECK(debugCompress2[1] == 120);
    CHECK(debugCompress2[2] == 188);
    CHECK(debugCompress2[3] == 248);
    CHECK(debugCompress2[4] == 220);
    CHECK(debugCompress2[5] == 95);
    CHECK(debugCompress2[6] == 6);
}

TEST_CASE("DEGREE OF COMPRESSION"){
    HTree htree1;
    std::string compressed1 = htree1.compress("abracadabra");

    double degreeOfCompression1 = htree1.degreeOfCompression("abracadabra", compressed1);

    CHECK(std::to_string(degreeOfCompression1) == "0.261364");

    HTree htree2;
    std::string compressed2 = htree2.compress("this is sentence.");

    double degreeOfCompression2 = htree2.degreeOfCompression("this is sentence.", compressed2);

    CHECK(std::to_string(degreeOfCompression2) == "0.389706");
}

TEST_CASE("DECOMPRESS"){
    HTree htree1;
    std::string compressed1 = htree1.compress("abracadabra");

    std::string decompressed1 = htree1.decompress(htree1.getRoot(), compressed1);

    CHECK(decompressed1 == "abracadabra");

    HTree htree2;
    std::string compressed2 = htree2.compress("this is sentence.");

    std::string decompressed2 = htree2.decompress(htree2.getRoot(), compressed2);

    CHECK(decompressed2 == "this is sentence.");
}

int main(){
    doctest::Context().run();

    return 0;
}