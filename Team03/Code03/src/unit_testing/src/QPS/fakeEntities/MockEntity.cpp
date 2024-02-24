#include "common/Entity.h"

// MockEntity inheriting from Entity for test purposes
class MockEntity : public Entity {
    std::string name;
    EntityType type;
public:
    // TODO: remove this and refactor tests to use the constructor with type
    explicit MockEntity(const std::string& name) : name(name) {}
    explicit MockEntity(const std::string& name, EntityType type) : name(name), type(type) {}
    std::string getName() const override { return name; } // Assuming Entity has getName()
    void accept(shared_ptr<Visitor> visitor) override {}
    [[nodiscard]] EntityType getType() const override { return type; }
};


