// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/7c590366-8e0e-40e2-863f-2862fa1ae192

#include "qps/entity/evaluation/HeaderTable.h"
#include "qps/entity/evaluation/TableRow.h"
#include "../fakeEntities/MockEntity.cpp"
#include "catch.hpp"
#include "../fakeEntities/FakeQueryManager.cpp"

TEST_CASE("HeaderTable Join Functionality", "[HeaderTable]") {
    using std::make_shared;
    using std::dynamic_pointer_cast;

    SECTION("Empty table with headers joins empty table") {
        HeaderTable table1;
        table1.setHeaders({make_shared<Synonym>(EntityType::Variable, "A"),
                           make_shared<Synonym>(EntityType::Variable, "B")});
        HeaderTable table2; // Empty table

        auto resultBaseTable = table1.join(table2);
        auto resultTable = dynamic_pointer_cast<HeaderTable>(resultBaseTable);

        REQUIRE(resultTable->getSize() == 0);
        REQUIRE(resultTable->getHeaders().size() == 2); // Headers are unchanged
    }

    SECTION("Empty table without rows joins non-empty table") {
        HeaderTable table1;
        table1.setHeaders({make_shared<Synonym>(EntityType::Variable, "A"),
                           make_shared<Synonym>(EntityType::Variable, "B")});

        HeaderTable table2;
        table2.setHeaders({make_shared<Synonym>(EntityType::Variable, "B"),
                           make_shared<Synonym>(EntityType::Variable, "C")});
        table2.addRow(TableRow({make_shared<MockEntity>("Entity2B"), make_shared<MockEntity>("Entity2C")}));

        auto resultBaseTable = table1.join(table2);
        auto resultTable = dynamic_pointer_cast<HeaderTable>(resultBaseTable);

        REQUIRE(resultTable->getSize() == 0); // No rows to join, but headers should be updated
        REQUIRE(resultTable->getHeaders().size() == 3); // "A", "B", and "C"
    }

    SECTION("Empty table without rows and headers joins non-empty table") {
        HeaderTable table1; // Completely empty table

        HeaderTable table2;
        table2.setHeaders({make_shared<Synonym>(EntityType::Variable, "B"),
                           make_shared<Synonym>(EntityType::Variable, "C")});
        table2.addRow(TableRow({make_shared<MockEntity>("Entity2B"), make_shared<MockEntity>("Entity2C")}));

        auto resultBaseTable = table1.join(table2);
        auto resultTable = dynamic_pointer_cast<HeaderTable>(resultBaseTable);

        REQUIRE(resultTable->getSize() == 0); // Still no rows
        REQUIRE(resultTable->getHeaders().size() == 2); // Headers from table2 are copied
    }

    SECTION("Normal join") {
        HeaderTable table1;
        table1.setHeaders({make_shared<Synonym>(EntityType::Variable, "A"),
                           make_shared<Synonym>(EntityType::Variable, "B")});
        table1.addRow(TableRow({make_shared<MockEntity>("Entity1A"), make_shared<MockEntity>("Entity1B")}));

        HeaderTable table2;
        table2.setHeaders({make_shared<Synonym>(EntityType::Variable, "B"),
                           make_shared<Synonym>(EntityType::Variable, "C")});
        table2.addRow(TableRow({make_shared<MockEntity>("Entity1B"), make_shared<MockEntity>("Entity2C")}));

        auto resultBaseTable = table1.join(table2);
        auto resultTable = dynamic_pointer_cast<HeaderTable>(resultBaseTable);

        REQUIRE(resultTable->getSize() == 1);
        REQUIRE(resultTable->getHeaders().size() == 3); // Joined headers "A", "B", and "C"
    }

    SECTION("The table to be joined with current one is a subset of current table") {
        HeaderTable table1;
        table1.setHeaders({make_shared<Synonym>(EntityType::Stmt, "A"), make_shared<Synonym>(EntityType::Variable, "B"),
                           make_shared<Synonym>(EntityType::Procedure, "C")});
        table1.addRow(TableRow({make_shared<MockEntity>("Entity1A"), make_shared<MockEntity>("Entity1B"),
                                make_shared<MockEntity>("Entity1C")}));

        HeaderTable table2;
        table2.setHeaders({make_shared<Synonym>(EntityType::Variable, "B")});
        table2.addRow(TableRow({make_shared<MockEntity>("Entity1B")}));

        auto resultBaseTable = table1.join(table2);
        auto resultTable = dynamic_pointer_cast<HeaderTable>(resultBaseTable);

        REQUIRE(resultTable->getSize() == 1);
        REQUIRE(resultTable->getHeaders().size() == 3); // Headers are unchanged
    }

    SECTION("No common columns") {
        HeaderTable table1;
        table1.setHeaders({make_shared<Synonym>(EntityType::Stmt, "A")});
        table1.addRow(TableRow({make_shared<MockEntity>("Entity1A")}));

        HeaderTable table2;
        table2.setHeaders({make_shared<Synonym>(EntityType::Print, "B")});
        table2.addRow(TableRow({make_shared<MockEntity>("Entity2B")}));

        auto resultBaseTable = table1.join(table2);
        auto resultTable = dynamic_pointer_cast<HeaderTable>(resultBaseTable);

        REQUIRE(resultTable->getSize() == 1); // Cartesian product results in 1 row since both tables have 1 row each.
        REQUIRE(resultTable->getHeaders().size() == 2); // "A" and "B"
    }

    SECTION("Tables with multiple rows and common column") {
        HeaderTable table1;
        table1.setHeaders({make_shared<Synonym>(EntityType::Stmt, "A"),
                           make_shared<Synonym>(EntityType::Variable, "B")});
        table1.addRow(TableRow({make_shared<MockEntity>("Entity1A"), make_shared<MockEntity>("Entity1B")}));
        table1.addRow(TableRow({make_shared<MockEntity>("Entity2A"), make_shared<MockEntity>("Entity2B")}));

        HeaderTable table2;
        table2.setHeaders({make_shared<Synonym>(EntityType::Variable, "B"),
                           make_shared<Synonym>(EntityType::Call, "C")});
        table2.addRow(TableRow({make_shared<MockEntity>("Entity1B"), make_shared<MockEntity>("Entity2C")}));
        table2.addRow(TableRow({make_shared<MockEntity>("Entity2B"), make_shared<MockEntity>("Entity3C")}));

        auto resultBaseTable = table1.join(table2);
        auto resultTable = dynamic_pointer_cast<HeaderTable>(resultBaseTable);

        REQUIRE(resultTable->getSize() == 2); // Assuming join condition matches for both rows
        REQUIRE(resultTable->getHeaders().size() == 3); // "A", "B", and "C"
    }
}
// ai-gen end
// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/25403a81-bbde-4bdc-8a8d-4e317bd1a40a
TEST_CASE("HeaderTable getComplement Functionality", "[HeaderTable]") {
    FakeQueryManager qm;

    // Setup mock data for testing
    shared_ptr<Synonym> synonymA = make_shared<Synonym>(EntityType::Stmt, "A");
    shared_ptr<Synonym> synonymB = make_shared<Synonym>(EntityType::Variable, "B");
    vector<shared_ptr<Entity>> allEntitiesA =
        {make_shared<MockEntity>("1", EntityType::Stmt), make_shared<MockEntity>("2", EntityType::Stmt),
         make_shared<MockEntity>("3", EntityType::Stmt)};
    vector<shared_ptr<Entity>> allEntitiesB =
        {make_shared<MockEntity>("x", EntityType::Variable), make_shared<MockEntity>("y", EntityType::Variable)};
    qm.addFakeResponse(EntityType::Stmt, allEntitiesA);
    qm.addFakeResponse(EntityType::Variable, allEntitiesB);

    SECTION("Complement with non-empty table") {
        HeaderTable table;
        table.setHeaders({synonymA, synonymB});
        // Assume the original table has only one row: ("1", "x")
        table.addRow(TableRow({allEntitiesA[0], allEntitiesB[0]}));

        auto complementTable = table.getComplement(qm);
        REQUIRE(complementTable->getSize() == 5); // 6 possible combinations - 1 existing row = 5
    }

    SECTION("Complement of an empty table") {
        HeaderTable table;
        table.setHeaders({synonymA, synonymB});

        auto complementTable = table.getComplement(qm);
        REQUIRE(complementTable->getSize() == 6); // All combinations are part of the complement
    }

    SECTION("Complement with full table") {
        HeaderTable table;
        table.setHeaders({synonymA, synonymB});
        // Add all possible rows to simulate a full table
        for (const auto &entityA : allEntitiesA) {
            for (const auto &entityB : allEntitiesB) {
                table.addRow(TableRow({entityA, entityB}));
            }
        }

        auto complementTable = table.getComplement(qm);
        REQUIRE(complementTable->getSize() == 0); // No rows should be in the complement
    }

    SECTION("Table with single synonym") {
        HeaderTable table;
        table.setHeaders({synonymA});
        // Assume the original table has two rows: "1" and "2"
        table.addRow(TableRow({allEntitiesA[0]}));
        table.addRow(TableRow({allEntitiesA[1]}));

        auto complementTable = table.getComplement(qm);
        REQUIRE(complementTable->getSize() == 1); // Only "3" should be in the complement
    }
}

TEST_CASE("Complete HeaderTable getComplement Functionality Tests", "[HeaderTable]") {
    using std::make_shared;
    using std::shared_ptr;
    using std::vector;

    FakeQueryManager qm;

    // Setup mock data for testing
    shared_ptr<Synonym> synonymA = make_shared<Synonym>(EntityType::Stmt, "A");
    shared_ptr<Synonym> synonymB = make_shared<Synonym>(EntityType::Variable, "B");
    shared_ptr<Synonym> synonymC = make_shared<Synonym>(EntityType::Procedure, "C");
    vector<shared_ptr<Entity>> allEntitiesA =
        {make_shared<MockEntity>("1", EntityType::Stmt), make_shared<MockEntity>("2", EntityType::Stmt),
         make_shared<MockEntity>("3", EntityType::Stmt)};
    vector<shared_ptr<Entity>> allEntitiesB =
        {make_shared<MockEntity>("x", EntityType::Variable), make_shared<MockEntity>("y", EntityType::Variable)};
    vector<shared_ptr<Entity>> allEntitiesC = {make_shared<MockEntity>("alpha", EntityType::Procedure),
                                               make_shared<MockEntity>("beta", EntityType::Procedure)};
    qm.addFakeResponse(EntityType::Stmt, allEntitiesA);
    qm.addFakeResponse(EntityType::Variable, allEntitiesB);
    qm.addFakeResponse(EntityType::Procedure, allEntitiesC);

    SECTION("Complement with three headers") {
        HeaderTable table;
        table.setHeaders({synonymA, synonymB, synonymC});
        // Add a single row as an example
        table.addRow(TableRow({allEntitiesA[0], allEntitiesB[0], allEntitiesC[0]}));

        auto complementTable = table.getComplement(qm);
        // For 3 entities with sizes 3, 2, and 2, the total combinations are 3*2*2 = 12
        // Subtract 1 for the existing row to get 11 as the expected complement size
        REQUIRE(complementTable->getSize() == 11);
    }

    SECTION("Zero headers (error scenario)") {
        HeaderTable table;

        // This test depends on your system's handling of zero headers:
        // If an exception is expected:
        REQUIRE_THROWS_AS(table.getComplement(qm),
                          std::exception); // Replace std::exception with your specific exception type
        // If a specific behavior is defined without throwing, adjust the test accordingly.
    }

    SECTION("Tables with duplicated rows") {
        HeaderTable table;
        table.setHeaders({synonymA});
        // Add duplicated rows
        table.addRow(TableRow({allEntitiesA[0]}));
        table.addRow(TableRow({allEntitiesA[0]})); // Duplicate

        auto complementTable = table.getComplement(qm);
        // With only A as the header and duplicated rows, the complement size should be 2, assuming A has 3 entities and one is used
        REQUIRE(complementTable->getSize() == 2);
    }

    SECTION("Tables with completely unrelated rows") {
        HeaderTable table;
        table.setHeaders({synonymA, synonymB});
        // Add a row that does not match any possible combinations (e.g., using entities not in the mock responses)
        table.addRow(TableRow({make_shared<MockEntity>("4", EntityType::Stmt),
                               make_shared<MockEntity>("z", EntityType::Variable)}));

        auto complementTable = table.getComplement(qm);
        // Since the unrelated row doesn't match possible combinations, the full complement should match all valid combinations
        // For entities A and B, the total combinations are 3*2 = 6
        REQUIRE(complementTable->getSize() == 6);
    }

    SECTION("Complement with empty table") {
        HeaderTable table;
        table.setHeaders({synonymA, synonymB});
        // reset qm
        qm = FakeQueryManager();

        auto complementTable = table.getComplement(qm);
        REQUIRE(complementTable->getSize() == 0);
    }
}
// ai-gen end