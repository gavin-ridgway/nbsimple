/* 
 * File:   NBSimpleTest.cpp
 * Author: gavin
 *
 * Created on 09 March 2018, 23:03
 */

#include <stdlib.h>
#include <iostream>

#include "nbsimple.h"

/*
 * Simple C++ Test Suite
 */

class Test1 : public NBSimple::Test
{
public:
    Test1(const std::string &n) : NBSimple::Test(n) {}

    void operator()() override
    {
        std::cout << "NBSimpleTest test 1" << std::endl;
    }
};

class Test2 : public NBSimple::Test
{
public:
    Test2(const std::string &n) : NBSimple::Test(n) {}

    void operator()() override
    {
        bool failureExpected = true;

        std::cout << "NBSimpleTest test 2" << std::endl;
        fail("error message sample", failureExpected);
    }
};

class Test3 : public NBSimple::Test
{
public:
    Test3(const std::string &n) : NBSimple::Test(n) {}

    void operator()() override
    {
        expect(std::runtime_error(""));

        std::cout << "NBSimpleTest test 3" << std::endl;
        throw std::runtime_error("run time exception");
    }
};

int main(void)
{
    NBSimple::suite s("NBSimpleTest");

    s.add_test(std::make_shared<Test1>("Test1"));
    s.add_test(std::make_shared<Test2>("Test2"));
    s.add_test(std::make_shared<Test3>("Test3"));

    s.run();

    return (EXIT_SUCCESS);
}

