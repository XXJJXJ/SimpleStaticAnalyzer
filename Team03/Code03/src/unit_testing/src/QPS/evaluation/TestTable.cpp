#include "qps/entity/evaluation/Table.h"
#include "qps/entity/evaluation/TableRow.h"
#include "../fakeEntities/MockEntity.cpp"
#include "catch.hpp"

TEST_CASE("Table Join Functionality", "[Table]") {
    SECTION("Empty table with headers joins empty table") {
        Table table1;
        table1.setHeaders({Synonym(EntityType::Variable, "A"), Synonym(EntityType::Variable, "B")});
        Table table2; // Empty table

        auto resultTable = table1.join(table2);

        REQUIRE(resultTable->getSize() == 0);
        REQUIRE(resultTable->getHeaders().size() == 2); // Headers are unchanged
    }

    SECTION("Empty table without rows joins non-empty table") {
        Table table1;
        table1.setHeaders({Synonym(EntityType::Variable, "A"), Synonym(EntityType::Variable, "B")});

        Table table2;
        table2.setHeaders({Synonym(EntityType::Variable, "B"), Synonym(EntityType::Variable, "C")});
        table2.addRow(TableRow({std::make_shared<MockEntity>("Entity2B"), std::make_shared<MockEntity>("Entity2C")}));

        auto resultTable = table1.join(table2);

        REQUIRE(resultTable->getSize() == 0); // No rows to join, but headers should be updated
        REQUIRE(resultTable->getHeaders().size() == 3); // "A", "B", and "C"
    }

    SECTION("Empty table without rows and headers joins non-empty table") {
        Table table1; // Completely empty table

        Table table2;
        table2.setHeaders({Synonym(EntityType::Variable, "B"), Synonym(EntityType::Variable, "C")});
        table2.addRow(TableRow({std::make_shared<MockEntity>("Entity2B"), std::make_shared<MockEntity>("Entity2C")}));

        auto resultTable = table1.join(table2);

        REQUIRE(resultTable->getSize() == 0); // Still no rows
        REQUIRE(resultTable->getHeaders().size() == 2); // Headers from table2 are copied
    }

    SECTION("Normal join") {
        Table table1;
        table1.setHeaders({Synonym(EntityType::Variable, "A"), Synonym(EntityType::Variable, "B")});
        table1.addRow(TableRow({std::make_shared<MockEntity>("Entity1A"), std::make_shared<MockEntity>("Entity1B")}));

        Table table2;
        table2.setHeaders({Synonym(EntityType::Variable, "B"), Synonym(EntityType::Variable, "C")});
        table2.addRow(TableRow({std::make_shared<MockEntity>("Entity1B"), std::make_shared<MockEntity>("Entity2C")}));

        auto resultTable = table1.join(table2);

        REQUIRE(resultTable->getSize() == 1);
        REQUIRE(resultTable->getHeaders().size() == 3); // Joined headers "A", "B", and "C"
    }

    SECTION("The table to be joined with current one is a subset of current table") {
        Table table1;
        table1.setHeaders({Synonym(EntityType::Stmt, "A"), Synonym(EntityType::Variable, "B"), Synonym(EntityType::Procedure, "C")});
        table1.addRow(TableRow({std::make_shared<MockEntity>("Entity1A"), std::make_shared<MockEntity>("Entity1B"), std::make_shared<MockEntity>("Entity1C")}));

        Table table2;
        table2.setHeaders({Synonym(EntityType::Variable, "B")});
        table2.addRow(TableRow({std::make_shared<MockEntity>("Entity1B")}));

        auto resultTable = table1.join(table2);

        REQUIRE(resultTable->getSize() == 1);
        REQUIRE(resultTable->getHeaders().size() == 3); // Headers are unchanged
    }

    SECTION("No common columns") {
        Table table1;
        table1.setHeaders({Synonym(EntityType::Stmt, "A")});
        table1.addRow(TableRow({std::make_shared<MockEntity>("Entity1A")}));

        Table table2;
        table2.setHeaders({Synonym(EntityType::Print, "B")});
        table2.addRow(TableRow({std::make_shared<MockEntity>("Entity2B")}));

        auto resultTable = table1.join(table2);

        REQUIRE(resultTable->getSize() == 1); // Cartesian product results in 1 row since both tables have 1 row each.
        REQUIRE(resultTable->getHeaders().size() == 2); // "A" and "B"
    }

    SECTION("Tables with multiple rows and common column") {
        Table table1;
        table1.setHeaders({Synonym(EntityType::Stmt, "A"), Synonym(EntityType::Variable, "B")});
        table1.addRow(TableRow({std::make_shared<MockEntity>("Entity1A"), std::make_shared<MockEntity>("Entity1B")}));
        table1.addRow(TableRow({std::make_shared<MockEntity>("Entity2A"), std::make_shared<MockEntity>("Entity2B")}));

        Table table2;
        table2.setHeaders({Synonym(EntityType::Variable, "B"), Synonym(EntityType::Call, "C")});
        table2.addRow(TableRow({std::make_shared<MockEntity>("Entity1B"), std::make_shared<MockEntity>("Entity2C")}));
        table2.addRow(TableRow({std::make_shared<MockEntity>("Entity2B"), std::make_shared<MockEntity>("Entity3C")}));

        auto resultTable = table1.join(table2);

        REQUIRE(resultTable->getSize() == 2); // Assuming join condition matches for both rows
        REQUIRE(resultTable->getHeaders().size() == 3); // "A", "B", and "C"
    }
}
