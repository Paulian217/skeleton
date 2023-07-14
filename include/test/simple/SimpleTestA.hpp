#ifndef _WORKSPACES_CPP_INCLUDE_TESTCASE_SIMPLE_SIMPLETESTA_HPP_
#define _WORKSPACES_CPP_INCLUDE_TESTCASE_SIMPLE_SIMPLETESTA_HPP_

#include <BaseTest.hpp>

class SimpleTestA : public BaseTest {
public:
    SimpleTestA();
    virtual ~SimpleTestA();

private:
    void init() override;
    void deinit() override;
    void start() override;
    void execute() override;
    void end() override;
};

#endif  // _WORKSPACES_CPP_INCLUDE_TESTCASE_SIMPLE_SIMPLETESTA_HPP_