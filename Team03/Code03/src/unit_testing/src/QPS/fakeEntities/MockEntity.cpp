#include "common/Entity.h"

// MockEntity inheriting from Entity for test purposes
class MockEntity : public Entity {
    std::string name;
public:
    explicit MockEntity(const std::string& name) : name(name) {}
    std::string getName() const override { return name; } // Assuming Entity has getName()
    void accept(shared_ptr<Visitor> visitor) override {}
};