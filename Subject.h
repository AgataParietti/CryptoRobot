//
// Created by Agata Parietti on 2019-09-03.
//

#ifndef CRYPTOROBOT_SUBJECT_H
#define CRYPTOROBOT_SUBJECT_H

#include "Observer.h"

class Subject {
public:
    virtual ~Subject() = default;

    virtual void subscribe(Observer* o) = 0;
    virtual void unsubscribe (Observer* o) = 0;
    virtual void notify() = 0;
};


#endif //CRYPTOROBOT_SUBJECT_H
