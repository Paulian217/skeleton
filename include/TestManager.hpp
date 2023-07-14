#ifndef _WORKSPACES_CPP_INCLUDE_TESTMANAGER_HPP_
#define _WORKSPACES_CPP_INCLUDE_TESTMANAGER_HPP_

#include <group/TestGroup.hpp>

class TestManager {
public:
    static TestManager& getInstance();
    void execute();

public:
    /* (Singleton) Remove =/copy constructor/move constructor */
    TestManager(const TestManager& other) = delete;
    TestManager(TestManager&& other) = delete;
    TestManager& operator=(const TestManager& rhs) = delete;
    TestManager& operator=(TestManager&& rhs) = delete;

private:
    TestManager();
    virtual ~TestManager();

private:
    std::vector<TestGroup> mTestGroup;
};

#endif  // _WORKSPACES_CPP_INCLUDE_TESTMANAGER_HPP_
