#ifndef _WORKSPACES_CPP_INCLUDE_BASETEST_HPP_
#define _WORKSPACES_CPP_INCLUDE_BASETEST_HPP_

#include <ITest.hpp>
#include <Testable.hpp>
#include <string>

class BaseTest : public ITest, public Testable {
public:
    explicit BaseTest(const std::string& service, const std::string& name);
    virtual ~BaseTest();

    void SetUp();
    void Run();
    void TearDown();

protected:
    virtual void init();
    virtual void deinit();
    virtual void start();
    virtual void execute();
    virtual void end();

private:
    const std::string mTestService;
    const std::string mTestName;
};

#endif  // _WORKSPACES_CPP_INCLUDE_BASETEST_HPP_
