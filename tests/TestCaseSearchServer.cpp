#include "tests.hpp"

TEST(TestCaseSearchServer, TestSimple)
{
    const std::vector<std::string> docs =
    {
        "milk milk milk milk water water water",
        "milk water water",
        "milk milk milk milk milk water water water water water",
        "americano cappuccino"
    };
    const std::vector<std::string> request = { "milk water", "sugar" };
    const std::vector<std::vector<RelativeIndex>> expected =
    {
        {
            { 2, 1 },
            { 0, 0.7 },
            { 1, 0.3 }
        },
        {

        }
    };

    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    SearchServer srv(idx);
    std::vector<std::vector<RelativeIndex>> result = srv.search(request);
    ASSERT_EQ(result, expected);
}

TEST(TestCaseSearchServer, TestTop5)
{
    const std::vector<std::string> docs =
    {
        "london is the capital of great britain",
        "paris is the capital of france",
        "berlin is the capital of germany",
        "rome is the capital of italy",
        "madrid is the capital of spain",
        "lisboa is the capital of portugal",
        "bern is the capital of switzerland",
        "moscow is the capital of russia",
        "kiev is the capital of ukraine",
        "minsk is the capital of belarus",
        "astana is the capital of kazakhstan",
        "beijing is the capital of china",
        "tokyo is the capital of japan",
        "bangkok is the capital of thailand",
        "welcome to moscow the capital of russia the third rome",
        "amsterdam is the capital of netherlands",
        "helsinki is the capital of finland",
        "oslo is the capital of norway",
        "stockholm is the capital of sweden",
        "riga is the capital of latvia",
        "tallinn is the capital of estonia",
        "warsaw is the capital of poland"
    };
    const std::vector<std::string> request = { "moscow is the capital of russia" };
    std::vector<std::vector<RelativeIndex>> expected =
    {
        {
            { 7, 1 },
            { 14, 1 },
            { 0, 0.666666687 },
            { 1, 0.666666687 },
            { 2, 0.666666687 },
            { 3, 0.666666687 },
            { 4, 0.666666687 },
            { 5, 0.666666687 },
            { 6, 0.666666687 },
            { 8, 0.666666687 },
            { 9, 0.666666687 },
            { 10, 0.666666687 },
            { 11, 0.666666687 },
            { 12, 0.666666687 },
            { 13, 0.666666687 },
            { 15, 0.666666687 },
            { 16, 0.666666687 },
            { 17, 0.666666687 },
            { 18, 0.666666687 },
            { 19, 0.666666687 },
            { 20, 0.666666687 },
            { 21, 0.666666687 }
        }
    };

    ConverterJSON converter;
    expected[0].resize(converter.GetResponsesLimit());
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    SearchServer srv(idx);
    std::vector<std::vector<RelativeIndex>> result = srv.search(request);
    ASSERT_EQ(result, expected);
}
