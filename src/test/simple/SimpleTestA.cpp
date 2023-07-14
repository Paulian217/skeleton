#include <stdio.h>

#include <simple/SimpleTestA.hpp>

SimpleTestA::SimpleTestA() : BaseTest("Simple", "TestA") {}

SimpleTestA::~SimpleTestA() {}

void SimpleTestA::init() {
    BaseTest::init();
    printf("SimpleTestA::%s() called\n", __func__);
}

void SimpleTestA::deinit() {
    BaseTest::deinit();
    printf("SimpleTestA::%s() called\n", __func__);
}

void SimpleTestA::start() {
    BaseTest::start();
    printf("SimpleTestA::%s() called\n", __func__);
}

void SimpleTestA::execute() {
    BaseTest::execute();
    printf("SimpleTestA::%s() called\n", __func__);
}

void SimpleTestA::end() {
    printf("SimpleTestA::%s() called\n", __func__);
    BaseTest::end();
}
