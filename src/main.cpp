#include <windows.h>
#include "coverter.h"
#include "inverted_index.h"
#include "gtest/gtest.h"
TEST(sample_test_case, sample_test)
{
    EXPECT_EQ(1, 1);
}


int main() {
    SetConsoleOutputCP(CP_UTF8);

    InvertedIndex gal;
    ConverterJSON file_request;
    file_request.get_path();
    file_request.GetRequests();
    file_request.request_apdeit();
    file_request.find_request(gal.UpdateDocumentBase(file_request.GetTextDocuments()));
    file_request.printResults();
}


