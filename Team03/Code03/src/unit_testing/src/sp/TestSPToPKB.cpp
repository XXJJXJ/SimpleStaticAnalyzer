#include <stdlib.h> 
#include <unordered_map>
#include "catch.hpp"
#include "sp/sp.h"
#include "pkb/QueryPKB.h"

TEST_CASE("1st SP-PKB integration Test: entity store test") {
    std::string simple_string = "procedure test {while (y < 3) {x = 1;read x;if (x < 10) then{z = ((x + 3) / 7) - (y + 11);}else {z = 0;}}print z;}";
    Sp sp = Sp();
    shared_ptr<Program> program = sp.triggerTokenizerAndParser(simple_string);
    shared_ptr<Populator> pkbPopulator = make_shared<Populator>();
    pkbPopulator->clear();
    shared_ptr<DesignExtractor> design_extractor = make_shared<DesignExtractor>(pkbPopulator);
    design_extractor->extractDesign(program);

    QueryManager qm;
    vector<shared_ptr<Variable>> varStore = qm.getAllVariables();
    vector<shared_ptr<Procedure>> procStore = qm.getAllProcedures();
    vector<shared_ptr<ReadStatement>> readStore = qm.getAllReadStatements();
    vector<shared_ptr<PrintStatement>> printStore = qm.getAllPrintStatements();
    vector<shared_ptr<IfStatement>> ifStore = qm.getAllIfStatements();
    vector<shared_ptr<WhileStatement>> whileStore = qm.getAllWhileStatements();

    REQUIRE(varStore.size() == 3);
    REQUIRE(procStore.size() == 1);
    REQUIRE(readStore.size() == 1);
    REQUIRE(printStore.size() == 1);
    REQUIRE(ifStore.size() == 1);
    REQUIRE(whileStore.size() == 1);
    pkbPopulator->clear();
}

TEST_CASE("2nd SP-PKB integration Test: relation store test") {
    std::string simple_string = "procedure test {while (y < 3) {x = 1;read x;if (x < 10) then{z = ((x + 3) / 7) - (y + 11);}else {z = 0;}}print z;}";
    Sp sp = Sp();
    shared_ptr<Program> program = sp.triggerTokenizerAndParser(simple_string);
    shared_ptr<Populator> pkbPopulator = make_shared<Populator>();
    pkbPopulator->clear();
    shared_ptr<DesignExtractor> design_extractor = make_shared<DesignExtractor>(pkbPopulator);
    design_extractor->extractDesign(program);

    QueryManager qm;
    vector<vector<shared_ptr<Entity>>> followsStore = qm.getFollowS();
    vector<vector<shared_ptr<Entity>>> parentStore = qm.getParentS();
    vector<vector<shared_ptr<Entity>>> usesStore = qm.getUseAll();
    vector<vector<shared_ptr<Entity>>> modifiesStore = qm.getModifyAll();

    REQUIRE(followsStore.size() == 3);
    REQUIRE(parentStore.size() == 5);
    REQUIRE(usesStore.size() == 7);
    REQUIRE(modifiesStore.size() == 7);
    pkbPopulator->clear();
}

//TEST_CASE("3rd SP-PKB integration Test: Uses store test") {
//    std::string simple_string = "procedure test {z = ((x + 3) / 7) - (y + 11);}";
//    Sp sp = Sp();
//    shared_ptr<Program> program = sp.triggerTokenizerAndParser(simple_string);
//    shared_ptr<Populator> pkbPopulator = make_shared<Populator>();
//    pkbPopulator->clear();
//    shared_ptr<DesignExtractor> design_extractor = make_shared<DesignExtractor>(pkbPopulator);
//    design_extractor->extractDesign(program);
//
//    QueryManager qm;
//    vector<shared_ptr<AssignStatement>> assgnStore = qm.getAllAssignStatements();
//    REQUIRE(assgnStore.size() == 1);
//    vector<vector<shared_ptr<Entity>>> usesStore = qm.getUseAll();
//    REQUIRE(usesStore.size() == 2);
//
//    unordered_map<shared_ptr<Entity>, shared_ptr<Entity>> uses_map;
//    shared_ptr<AssignStatement> assgnStmt = assgnStore[0];
//
//    for (auto u : usesStore) {
//        uses_map[u[0]] = u[1];
//    }
//
//    REQUIRE(uses_map.count(assgnStmt) == 2);
//
//    /*vector<shared_ptr<Entity>> usesZX = usesStore[0];
//    bool result1 = (usesZX[0]->getName().compare("1")) == 0 && (usesZX[1]->getName().compare("x") == 0);
//    REQUIRE(result1);
//
//    vector<shared_ptr<Entity>> usesZY = usesStore[1];
//    bool result2 = (usesZY[0]->getName().compare("1")) == 0 && (usesZY[1]->getName().compare("y") == 0);
//    REQUIRE(result2);*/
//    pkbPopulator->clear();
//}
//
//TEST_CASE("4th SP-PKB integration Test: Modifies store test") {
//    std::string simple_string = "procedure test {z = ((x + 3) / 7) - (y + 11);}";
//    Sp sp = Sp();
//    shared_ptr<Program> program = sp.triggerTokenizerAndParser(simple_string);
//    shared_ptr<Populator> pkbPopulator = make_shared<Populator>();
//    pkbPopulator->clear();
//    shared_ptr<DesignExtractor> design_extractor = make_shared<DesignExtractor>(pkbPopulator);
//    design_extractor->extractDesign(program);
//
//    QueryManager qm;
//    vector<vector<shared_ptr<Entity>>> modifiesStore = qm.getModifyAll();
//    REQUIRE(modifiesStore.size() == 1);
//
//    vector<shared_ptr<Entity>> modifiesZ = modifiesStore[0];
//    bool result = (modifiesZ[0]->getName().compare("1")) == 0 && (modifiesZ[1]->getName().compare("z") == 0);
//    REQUIRE(result);
//    pkbPopulator->clear();
//}
//
//TEST_CASE("5th SP-PKB integration Test: follow store test") {
//    std::string simple_string = "procedure test {read x;print x;y = x + 7;}";
//    Sp sp = Sp();
//    shared_ptr<Program> program = sp.triggerTokenizerAndParser(simple_string);
//    shared_ptr<Populator> pkbPopulator = make_shared<Populator>();
//    pkbPopulator->clear();
//    shared_ptr<DesignExtractor> design_extractor = make_shared<DesignExtractor>(pkbPopulator);
//    design_extractor->extractDesign(program);
//
//    QueryManager qm;
//    vector<vector<shared_ptr<Entity>>> followsStore = qm.getFollowS();
//    REQUIRE(followsStore.size() == 2);
//
//    vector<shared_ptr<Entity>> followsOneTwo = followsStore[0];
//    bool result1 = followsOneTwo[0]->getName().compare("1") == 0 && followsOneTwo[1]->getName().compare("2") == 0;
//    REQUIRE(result1);
//
//    vector<shared_ptr<Entity>> followsTwoThree = followsStore[1];
//    bool result2 = followsTwoThree[0]->getName().compare("2") == 0 && followsTwoThree[1]->getName().compare("3") == 0;
//    REQUIRE(result2);
//    pkbPopulator->clear();
//}
//
//TEST_CASE("6th SP-PKB integration Test: parent store test") {
//    std::string simple_string = "procedure test {read x;y = 0;while (x < 20) {y = x + 1;x = x * 2;}print x;print y;}";
//    Sp sp = Sp();
//    shared_ptr<Program> program = sp.triggerTokenizerAndParser(simple_string);
//    shared_ptr<Populator> pkbPopulator = make_shared<Populator>();
//    pkbPopulator->clear();
//    shared_ptr<DesignExtractor> design_extractor = make_shared<DesignExtractor>(pkbPopulator);
//    design_extractor->extractDesign(program);
//
//    QueryManager qm;
//    vector<vector<shared_ptr<Entity>>> parentStore = qm.getParentS();
//    REQUIRE(parentStore.size() == 2);
//
//    vector<shared_ptr<Entity>> parentThreeFour = parentStore[0];
//    bool result1 = parentThreeFour[0]->getName().compare("3") == 0 && parentThreeFour[1]->getName().compare("4") == 0;
//    REQUIRE(result1);
//
//    vector<shared_ptr<Entity>> parentThreeFive = parentStore[1];
//    bool result2 = parentThreeFive[0]->getName().compare("3") == 0 && parentThreeFive[1]->getName().compare("5") == 0;
//    REQUIRE(result2);
//    pkbPopulator->clear();
//}
//
//TEST_CASE("7th SP-PKB integration Test: container uses relation test") {
//    std::string simple_string = "procedure test {while (y < 3) {z = ((x + 3) / 7) - (y + 11);}}";
//    Sp sp = Sp();
//    shared_ptr<Program> program = sp.triggerTokenizerAndParser(simple_string);
//    shared_ptr<Populator> pkbPopulator = make_shared<Populator>();
//    pkbPopulator->clear();
//    shared_ptr<DesignExtractor> design_extractor = make_shared<DesignExtractor>(pkbPopulator);
//    design_extractor->extractDesign(program);
//
//    QueryManager qm;
//    vector<vector<shared_ptr<Entity>>> whileUsesStore = qm.getUseByIfWhile();
//    REQUIRE(whileUsesStore.size() == 2);
//
//    vector<shared_ptr<Entity>> usesOneX = whileUsesStore[0];
//    bool result1 = usesOneX[0]->getName().compare("1") == 0 && usesOneX[1]->getName().compare("x") == 0;
//    REQUIRE(result1);
//
//    vector<shared_ptr<Entity>> usesOneY = whileUsesStore[1];
//    bool result2 = usesOneY[0]->getName().compare("1") == 0 && usesOneY[1]->getName().compare("y") == 0;
//    REQUIRE(result2);
//    pkbPopulator->clear();
//}
//
//TEST_CASE("8th SP-PKB integration Test: container modifies relation test") {
//    std::string simple_string = "procedure test {while (y < 3) {z = ((x + 3) / 7) - (y + 11);}}";
//    Sp sp = Sp();
//    shared_ptr<Program> program = sp.triggerTokenizerAndParser(simple_string);
//    shared_ptr<Populator> pkbPopulator = make_shared<Populator>();
//    pkbPopulator->clear();
//    shared_ptr<DesignExtractor> design_extractor = make_shared<DesignExtractor>(pkbPopulator);
//    design_extractor->extractDesign(program);
//
//    QueryManager qm;
//    vector<vector<shared_ptr<Entity>>> whileModifiesStore = qm.getModifyByIfWhile();
//    REQUIRE(whileModifiesStore.size() == 1);
//
//    vector<shared_ptr<Entity>> modifiesOneZ = whileModifiesStore[0];
//    bool result = modifiesOneZ[0]->getName().compare("1") == 0 && modifiesOneZ[1]->getName().compare("z") == 0;
//    REQUIRE(result);
//    pkbPopulator->clear();
//}

TEST_CASE("9th SP-PKB integration Test: entity store test") {
    std::string simple_string = "procedure test {z = ((x + 3) / 7) - (y + 11);}";
    Sp sp = Sp();
    shared_ptr<Program> program = sp.triggerTokenizerAndParser(simple_string);
    shared_ptr<Populator> pkbPopulator = make_shared<Populator>();
    pkbPopulator->clear();
    shared_ptr<DesignExtractor> design_extractor = make_shared<DesignExtractor>(pkbPopulator);
    design_extractor->extractDesign(program);

    QueryManager qm;
    vector<shared_ptr<Variable>> varStore = qm.getAllVariables();
    REQUIRE(varStore.size() == 3);
    pkbPopulator->clear();
}