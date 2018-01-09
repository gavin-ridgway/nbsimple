/**
 * @file   nbsimple.h
 * @author gavin
 *
 * Created on 09 January 2018, 19:36
 */

#ifndef NBSIMPLE_H_INCLUDED
#define NBSIMPLE_H_INCLUDED

#include <memory>
#include <string>
#include <vector>

/*
 * Simple C++ Test Suite
 */

namespace NBSimple
{

class suite;

class ITest
{
public:
    virtual ~ITest() {}

    virtual void start() = 0;
    virtual void run() = 0;
    virtual void stop() = 0;
    virtual void attach(suite *s) = 0;
};

class suite
{
public:
    suite(const std::string &n) : name(n) {}
    virtual ~suite() {}

    std::string getname() const { return name; }

    void add_test(const std::shared_ptr<ITest> &t)
    {
        t->attach(this);
        tests.push_back(t);
    }

    void run()
    {
        std::cout << "%SUITE_STARTING% " << name << std::endl;
        std::cout << "%SUITE_STARTED%" << std::endl;
        // start suite timer

        for (auto test : tests)
        {
            test->run();
        }

        // stop suite timer
        std::cout << "%SUITE_FINISHED% time=0" << std::endl;
    }

protected:
    std::string name;
    std::vector<std::shared_ptr<ITest>> tests;
};

class Test : public ITest
{
public:
    Test(const std::string &n)
    : theSuite(0)
    , name(n)
    , passed(true)
    , fail_msg()
    {}
    Test(const Test &other)
    : theSuite(other.theSuite)
    , name(other.name)
    , passed(true)
    , fail_msg()
    {}

    virtual void operator()() = 0;

    void attach(suite *s) override
    {
        theSuite = s;
    }

    void start() override
    {
        std::cout << "%TEST_STARTED% " << name << " (" << theSuite->getname() << ")" << std::endl;
        // start test timer
    }

    void stop() override
    {
        // stop test timer
        if (passed)
            std::cout << "%TEST_FINISHED% time=0 " << name << " (" << theSuite->getname() << ")" << std::endl;
        else
            std::cout << "%TEST_FAILED% time=0 testname=" << name << " (" << theSuite->getname() << ") message=" << fail_msg << std::endl;
    }

    void run() override
    {
        start();
        this->operator()();
        stop();
    }

    void fail(const std::string &msg)
    {
        fail_msg = msg;
    }

private:
    suite *theSuite;
    std::string name;
    bool passed;
    std::string fail_msg;
};

} /* End of NBSimple */


#endif /* NBSIMPLE_H_INCLUDED */

