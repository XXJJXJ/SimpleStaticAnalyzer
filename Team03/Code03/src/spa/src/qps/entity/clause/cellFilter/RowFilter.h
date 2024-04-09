#ifndef SPA_ROWFILTER_H
#define SPA_ROWFILTER_H

#include <vector>
#include "qps/entity/evaluation/TableRow.h"
#include "CellFilter.h"
#include <functional>
#include <memory>

class RowFilter {
private:
    std::function<bool(const TableRow&)> filterFunction; // User-defined filter function
public:
    // Constructor
    explicit RowFilter(std::function<bool(const TableRow&)> func);
//    explicit RowFilter(vector<shared_ptr<CellFilter>> filters);

    // Filters a table row
    bool filterRow(const TableRow& row) const;
};

#endif //SPA_ROWFILTER_H
