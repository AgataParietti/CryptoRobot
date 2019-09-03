//
// Created by Agata Parietti on 2019-09-03.
//

#ifndef CRYPTOROBOT_OBSERVER_H
#define CRYPTOROBOT_OBSERVER_H

class Observer {
public:
    virtual ~Observer() = default;

    virtual void update() = 0;
    virtual void attach() = 0;
    virtual void detach() = 0;
};


#endif //CRYPTOROBOT_OBSERVER_H
