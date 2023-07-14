#include <test/BaseTest.hpp>

BaseTest::BaseTest(const std::string& service, const std::string& name) : mTestService(service), mTestName(name) {}

BaseTest::~BaseTest() {}

void BaseTest::SetUp() { init(); }

void BaseTest::Run() {
    start();
    execute();
    end();
}

void BaseTest::TearDown() { deinit(); }

void BaseTest::init() {
    // printf("%s::%s::%s()\n", mTestService.c_str(), mTestName.c_str(), __func__);
}

void BaseTest::deinit() {
    // printf("%s::%s::%s()\n", mTestService.c_str(), mTestName.c_str(), __func__);
}

void BaseTest::start() { printf("<< START: %s/%s >>\n", mTestService.c_str(), mTestName.c_str()); }

void BaseTest::execute() { printf("<< RUNNING: %s/%s >>\n", mTestService.c_str(), mTestName.c_str()); }

void BaseTest::end() { printf("<< END: %s/%s >>\n", mTestService.c_str(), mTestName.c_str()); }
