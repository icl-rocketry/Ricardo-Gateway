
#include "groundstationGateway.h"
#include "stateMachine.h"

#include <rnp_default_address.h>
#include <rnp_routingtable.h>


#include "flags.h"

GroundstationGateway::GroundstationGateway(stateMachine* sm):
State(sm,SYSTEM_FLAG::STATE_GROUNDSTATION_GATEWAY)
{};

void GroundstationGateway::initialise(){
    State::initialise();
    //load the GroundstationGateway routing table
    RoutingTable routetable;
    routetable.setRoute((uint8_t)DEFAULT_ADDRESS::ROCKET,Route{2,1,{}});
    routetable.setRoute(20,Route{1,1,{}});

    _sm->networkmanager.setRoutingTable(routetable);
    _sm->networkmanager.updateBaseTable(); // save the new base table
    _sm->networkmanager.setAddress(19);

    _sm->networkmanager.enableAutoRouteGen(true); // enable route learning
    _sm->networkmanager.setNoRouteAction(NOROUTE_ACTION::BROADCAST,{1,2}); // enable broadcast over serial and radio only
    

};

State* GroundstationGateway::update(){
    
    return this;//loopy loop
};

void GroundstationGateway::exitstate(){
    State::exitstate();
};