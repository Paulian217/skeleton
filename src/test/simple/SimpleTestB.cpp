#include <stdio.h>

#include <simple/SimpleTestB.hpp>

SimpleTestB::SimpleTestB() : BaseTest("Simple", "TestB") {}

SimpleTestB::~SimpleTestB() {}

void SimpleTestB::init() {
    BaseTest::init();
    printf("SimpleTestB::%s() called\n", __func__);
}

void SimpleTestB::deinit() {
    BaseTest::deinit();
    printf("SimpleTestB::%s() called\n", __func__);
}

void SimpleTestB::start() {
    BaseTest::start();
    printf("SimpleTestB::%s() called\n", __func__);
}

void SimpleTestB::execute() {
    BaseTest::execute();
    printf("SimpleTestB::%s() called\n", __func__);
}

void SimpleTestB::end() {
    printf("SimpleTestB::%s() called\n", __func__);
    BaseTest::end();
}
