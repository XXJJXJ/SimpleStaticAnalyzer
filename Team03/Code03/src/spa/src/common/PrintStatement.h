#pragma once

#include "Statement.h"
#include "Variable.h"

class PrintStatement : public Statement {
public:
	PrintStatement(
		int statement_number, 
		shared_ptr<Variable> variable, 
		string procedureName);
	void accept(shared_ptr<Visitor> visitor) override;
	shared_ptr<Variable> getVariable() const;

private:
	const shared_ptr<Variable> variable;
};

namespace std {
    template <>
    struct hash<shared_ptr<PrintStatement>> {
        std::size_t operator()(const shared_ptr<PrintStatement>& obj) const {
            return obj->hash();
        }
    };

    template <>
    struct equal_to<shared_ptr<PrintStatement>> {
        bool operator()(const shared_ptr<PrintStatement>& lhs, const shared_ptr<PrintStatement>& rhs) const {
            return *lhs == *rhs;
        }
    };
}