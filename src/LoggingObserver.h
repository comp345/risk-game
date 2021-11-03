#pragma once

#include <vector>
#include <string>
#include <list>
#include <iostream>

using namespace std;

class ILoggable {
public:
    ILoggable();

    ~ILoggable();

    virtual string stringToLog() = 0;

private:
};

class Observer {
public:
    ~Observer();

    virtual void update(ILoggable *) = 0;

protected:
    Observer();
};

class Subject {
public:
    virtual void detach(Observer *o);

    virtual void notify(ILoggable *);

    Subject();

    ~Subject();

    virtual void attach(Observer *o);

private:
    list<Observer *> *_observers;
};

class LogObserver : public Observer {
public:
    LogObserver();

    ~LogObserver();

    void update(ILoggable *) override;

private:
    Subject *_subject;
};

