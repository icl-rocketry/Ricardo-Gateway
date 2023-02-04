/* 
state for groundstation use as reciever
*/
#pragma once

#include "state.h"

#include "rnp_routingtable.h"

class GroundSupportGateway: public State {
    public:
        GroundSupportGateway(stateMachine* sm);
        void initialise();
        State* update();
        void exitstate();
    private:


};
