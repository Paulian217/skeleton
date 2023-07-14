#include <stdio.h>

#include <TestManager.hpp>

int main() {
    printf(">> Hello Tester!\n");
    TestManager::getInstance().execute();
    printf(">> Bye Tester!\n");
    return 0;
}