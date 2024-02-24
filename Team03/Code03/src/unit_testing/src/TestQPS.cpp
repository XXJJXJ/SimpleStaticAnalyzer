//
// Created by Stephanie Chen on 10/2/24.
//

//#include "catch.hpp"
//
//#include "qps/QpsManager.h"
//#include <filesystem>
//#include <iostream>
//
//using namespace std;
//
//// Tests that QpsManager can properly read and write the correct files
//TEST_CASE("Test QpsManager") {
//    QpsManager q;
//
//    std::filesystem::path currentPath = std::filesystem::current_path();
//
//    std::cout << currentPath << std::endl;
//
//    // Relative paths to input and output files
//    std::string inputFile = currentPath.parent_path().parent_path().parent_path() / "tests" / "Sample_queries.txt";
//    std::cout << inputFile << std::endl;
//
//    std::string outputFile = currentPath.parent_path().parent_path().parent_path() / "tests" / "out.xml";
//
//    q.processQueries(inputFile, outputFile);
//}
//