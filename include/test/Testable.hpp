#ifndef _WORKSPACES_CPP_INCLUDE_TESTABLE_HPP_
#define _WORKSPACES_CPP_INCLUDE_TESTABLE_HPP_

class Testable {
public:
    virtual void SetUp() = 0;
    virtual void Run() = 0;
    virtual void TearDown() = 0;
};

#endif  // _WORKSPACES_CPP_INCLUDE_TESTABLE_HPP_
