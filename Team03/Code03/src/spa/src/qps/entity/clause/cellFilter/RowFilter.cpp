#include "RowFilter.h"
#include <stdexcept>

// Constructor implementation
RowFilter::RowFilter(std::function<bool(const TableRow &)> func) : filterFunction(std::move(func)) {}

//// Initialize the row filter with a list of cell filters
//RowFilter::RowFilter(vector<shared_ptr<CellFilter>> filters) {
//    filterFunction = [filters = std::move(filters)](TableRow& row) {
//        if (row.size() != filters.size()) {
//            throw QPSEvaluationException("RowFilter: mismatch between row size and filter size");
//        }
//        for (int i = 0; i < row.size(); i++) {
//            if (!filters[i]->passFilter(row.getByIndex(i))) {
//                return false;
//            }
//        }
//        return true;
//    };
//}


// Filters a table row implementation
bool RowFilter::filterRow(const TableRow &row) const {
    return filterFunction(row);
}

