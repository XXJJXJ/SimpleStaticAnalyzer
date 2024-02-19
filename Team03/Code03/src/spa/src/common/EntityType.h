#ifndef ENTITYTYPE_H
#define ENTITYTYPE_H

// ai-gen start(gpt, 0, e)
// prompt: I can't get the link, got 'Sharing conversations with images is not yet supported'.
enum class EntityType {
    Stmt,       // Represents all statements
    Read,       // Represents read statements
    Print,      // Represents print statements
    Call,       // Represents call statements
    While,      // Represents while loops
    If,         // Represents if statements
    Assign,     // Represents assignment statements
    Variable,   // Represents variables
    Constant,   // Represents constants
    Procedure,   // Represents procedures
    Operation,  // Represents arithmetic/conditional/relational operations
    Arithmetic,  // Represents arithmetic operations
    Conditional,  // Represents conditional operations
    Relational,  // Represents relational operations
    // ai-gen end
    Unknown     // Represents unknown entity types
};

#endif //ENTITYTYPE_H