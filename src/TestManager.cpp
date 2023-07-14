#include <TestManager.hpp>
#include <group/TestGroupFactory.hpp>

TestManager& TestManager::getInstance() {
    static TestManager instance;
    return instance;
}

TestManager::TestManager() { mTestGroup.push_back(TestGroupFactory::createSimpleTestGroup()); }

TestManager::~TestManager() {}

void TestManager::execute() {
    for (auto& group : mTestGroup) {
        group.SetUp();
        group.Run();
        group.TearDown();
    }
}