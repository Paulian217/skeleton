#ifndef _WORKSPACES_CPP_INCLUDE_TESTCASE_SIMPLE_SIMPLETESTB_HPP_
#define _WORKSPACES_CPP_INCLUDE_TESTCASE_SIMPLE_SIMPLETESTB_HPP_

#include <BaseTest.hpp>

class SimpleTestB : public BaseTest {
public:
    SimpleTestB();
    virtual ~SimpleTestB();

private:
    void init() override;
    void deinit() override;
    void start() override;
    void execute() override;
    void end() override;
};

#endif  // _WORKSPACES_CPP_INCLUDE_TESTCASE_SIMPLE_SIMPLETESTB_HPP_