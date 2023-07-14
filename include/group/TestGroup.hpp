#ifndef _WORKSPACES_CPP_INCLUDE_TESTCASE_GROUP_TESTGROUP_HPP_
#define _WORKSPACES_CPP_INCLUDE_TESTCASE_GROUP_TESTGROUP_HPP_

#include <memory>
#include <test/BaseTest.hpp>
#include <vector>

class TestGroup : public Testable {
public:
    TestGroup();
    virtual ~TestGroup();

    void SetUp() override;
    void Run() override;
    void TearDown() override;

    void AddTest(const std::shared_ptr<BaseTest>& test);
    void GetTests(std::vector<std::shared_ptr<BaseTest>>& tests);

private:
    std::vector<std::shared_ptr<BaseTest>> mTests;
};

#endif  // _WORKSPACES_CPP_INCLUDE_TESTCASE_GROUP_TESTGROUP_HPP_