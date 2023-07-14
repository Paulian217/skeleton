#ifndef _WORKSPACES_CPP_INCLUDE_ITEST_HPP_
#define _WORKSPACES_CPP_INCLUDE_ITEST_HPP_

class ITest {
protected:
    virtual void init() = 0;
    virtual void deinit() = 0;
    virtual void start() = 0;
    virtual void execute() = 0;
    virtual void end() = 0;
};

#endif  // _WORKSPACES_CPP_INCLUDE_ITEST_HPP_
