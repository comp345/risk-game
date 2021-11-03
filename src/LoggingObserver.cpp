#include "LoggingObserver.h"
#include <iostream>
#include <fstream>

using namespace std;

Observer::Observer() {
}

Observer::~Observer() {
}

Subject::Subject() {
    _observers = new list<Observer *>;
}

Subject::~Subject() {
    delete _observers;
}

void Subject::attach(Observer *o) {
    _observers->push_back(o);
}

void Subject::detach(Observer *o) {
    _observers->remove(o);
}

//notifies all observers
void Subject::notify(ILoggable *loggable) {
    list<Observer *>::iterator i = _observers->begin();
    for (; i != _observers->end(); ++i)
        (*i)->update(loggable);
}

ILoggable::ILoggable() {

}

ILoggable::~ILoggable() {

}

void LogObserver::update(ILoggable *iLoggable) {
    ofstream logFile;
    logFile.open("../gamelog.txt", fstream::out);
    logFile << iLoggable->stringToLog();
    logFile.close();
}

LogObserver::LogObserver() {

}

LogObserver::~LogObserver() {

}
