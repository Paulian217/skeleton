#include <group/TestGroupFactory.hpp>
#include <simple/SimpleTestA.hpp>
#include <simple/SimpleTestB.hpp>

TestGroup TestGroupFactory::createSimpleTestGroup() {
    TestGroup group;
    group.AddTest(std::make_shared<SimpleTestA>());
    group.AddTest(std::make_shared<SimpleTestB>());
    return group;
}