#include <group/TestGroup.hpp>

TestGroup::TestGroup() : mTests() {}

TestGroup::~TestGroup() {}

void TestGroup::SetUp() {
    for (const auto& test : mTests) {
        test->SetUp();
    }
}

void TestGroup::Run() {
    for (const auto& test : mTests) {
        test->Run();
    }
}

void TestGroup::TearDown() {
    for (const auto& test : mTests) {
        test->TearDown();
    }
}

void TestGroup::AddTest(const std::shared_ptr<BaseTest>& test) { mTests.push_back(test); }

void TestGroup::GetTests(std::vector<std::shared_ptr<BaseTest>>& tests) { tests = mTests; }
