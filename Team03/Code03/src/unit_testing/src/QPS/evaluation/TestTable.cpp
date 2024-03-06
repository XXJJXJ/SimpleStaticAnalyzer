// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/7c590366-8e0e-40e2-863f-2862fa1ae192

#include "qps/entity/evaluation/HeaderTable.h"
#include "qps/entity/evaluation/TableRow.h"
#include "../fakeEntities/MockEntity.cpp"
#include "catch.hpp"

TEST_CASE("HeaderTable Join Functionality", "[HeaderTable]") {
    using std::make_shared;
    using std::dynamic_pointer_cast;

    SECTION("Empty table with headers joins empty table") {
        HeaderTable table1;
        table1.setHeaders({make_shared<Synonym>(EntityType::Variable, "A"), make_shared<Synonym>(EntityType::Variable, "B")});
        HeaderTable table2; // Empty table

        auto resultBaseTable = table1.join(table2);
        auto resultTable = dynamic_pointer_cast<HeaderTable>(resultBaseTable);

        REQUIRE(resultTable->getSize() == 0);
        REQUIRE(resultTable->getHeaders().size() == 2); // Headers are unchanged
    }

    SECTION("Empty table without rows joins non-empty table") {
        HeaderTable table1;
        table1.setHeaders({make_shared<Synonym>(EntityType::Variable, "A"), make_shared<Synonym>(EntityType::Variable, "B")});

        HeaderTable table2;
        table2.setHeaders({make_shared<Synonym>(EntityType::Variable, "B"), make_shared<Synonym>(EntityType::Variable, "C")});
        table2.addRow(TableRow({make_shared<MockEntity>("Entity2B"), make_shared<MockEntity>("Entity2C")}));

        auto resultBaseTable = table1.join(table2);
        auto resultTable = dynamic_pointer_cast<HeaderTable>(resultBaseTable);

        REQUIRE(resultTable->getSize() == 0); // No rows to join, but headers should be updated
        REQUIRE(resultTable->getHeaders().size() == 3); // "A", "B", and "C"
    }

    SECTION("Empty table without rows and headers joins non-empty table") {
        HeaderTable table1; // Completely empty table

        HeaderTable table2;
        table2.setHeaders({make_shared<Synonym>(EntityType::Variable, "B"), make_shared<Synonym>(EntityType::Variable, "C")});
        table2.addRow(TableRow({make_shared<MockEntity>("Entity2B"), make_shared<MockEntity>("Entity2C")}));

        auto resultBaseTable = table1.join(table2);
        auto resultTable = dynamic_pointer_cast<HeaderTable>(resultBaseTable);

        REQUIRE(resultTable->getSize() == 0); // Still no rows
        REQUIRE(resultTable->getHeaders().size() == 2); // Headers from table2 are copied
    }

    SECTION("Normal join") {
        HeaderTable table1;
        table1.setHeaders({make_shared<Synonym>(EntityType::Variable, "A"), make_shared<Synonym>(EntityType::Variable, "B")});
        table1.addRow(TableRow({make_shared<MockEntity>("Entity1A"), make_shared<MockEntity>("Entity1B")}));

        HeaderTable table2;
        table2.setHeaders({make_shared<Synonym>(EntityType::Variable, "B"), make_shared<Synonym>(EntityType::Variable, "C")});
        table2.addRow(TableRow({make_shared<MockEntity>("Entity1B"), make_shared<MockEntity>("Entity2C")}));

        auto resultBaseTable = table1.join(table2);
        auto resultTable = dynamic_pointer_cast<HeaderTable>(resultBaseTable);

        REQUIRE(resultTable->getSize() == 1);
        REQUIRE(resultTable->getHeaders().size() == 3); // Joined headers "A", "B", and "C"
    }

    SECTION("The table to be joined with current one is a subset of current table") {
        HeaderTable table1;
        table1.setHeaders({make_shared<Synonym>(EntityType::Stmt, "A"), make_shared<Synonym>(EntityType::Variable, "B"), make_shared<Synonym>(EntityType::Procedure, "C")});
        table1.addRow(TableRow({make_shared<MockEntity>("Entity1A"), make_shared<MockEntity>("Entity1B"), make_shared<MockEntity>("Entity1C")}));

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
        table1.setHeaders({make_shared<Synonym>(EntityType::Stmt, "A"), make_shared<Synonym>(EntityType::Variable, "B")});
        table1.addRow(TableRow({make_shared<MockEntity>("Entity1A"), make_shared<MockEntity>("Entity1B")}));
        table1.addRow(TableRow({make_shared<MockEntity>("Entity2A"), make_shared<MockEntity>("Entity2B")}));

        HeaderTable table2;
        table2.setHeaders({make_shared<Synonym>(EntityType::Variable, "B"), make_shared<Synonym>(EntityType::Call, "C")});
        table2.addRow(TableRow({make_shared<MockEntity>("Entity1B"), make_shared<MockEntity>("Entity2C")}));
        table2.addRow(TableRow({make_shared<MockEntity>("Entity2B"), make_shared<MockEntity>("Entity3C")}));

        auto resultBaseTable = table1.join(table2);
        auto resultTable = dynamic_pointer_cast<HeaderTable>(resultBaseTable);

        REQUIRE(resultTable->getSize() == 2); // Assuming join condition matches for both rows
        REQUIRE(resultTable->getHeaders().size() == 3); // "A", "B", and "C"
    }
}

// ai-gen end