
#include "groundSupportGateway.h"
#include "stateMachine.h"

#include <rnp_default_address.h>
#include <rnp_routingtable.h>


#include "flags.h"

GroundSupportGateway::GroundSupportGateway(stateMachine* sm):
State(sm,SYSTEM_FLAG::STATE_GROUNDSTATION_GATEWAY)
{};

void GroundSupportGateway::initialise(){
    State::initialise();
    //load the GroundSupportGateway routing table
    RoutingTable routetable;
    routetable.setRoute((uint8_t)DEFAULT_ADDRESS::ROCKET,Route{3,1,{}});
    routetable.setRoute((uint8_t)DEFAULT_ADDRESS::GROUNDSTATION,Route{3,1,{}});
    routetable.setRoute(20,Route{2,1,{}});
    routetable.setRoute(12,Route{3,1,{}});
    routetable.setRoute(13,Route{3,1,{}});
    routetable.setRoute(16,Route{3,1,{}});
    routetable.setRoute(17,Route{3,1,{}});

    _sm->networkmanager.setRoutingTable(routetable);
    _sm->networkmanager.updateBaseTable(); // save the new base table
    _sm->networkmanager.setAddress(18);


    // _sm->networkmanager.enableAutoRouteGen(true); // enable route learning
    _sm->networkmanager.setNoRouteAction(NOROUTE_ACTION::BROADCAST,{1,2,3}); // enable broadcast over serial and radio only
    

};

State* GroundSupportGateway::update(){
    
    return this;//loopy loop
};

void GroundSupportGateway::exitstate(){
    State::exitstate();
};