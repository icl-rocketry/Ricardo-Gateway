
#include "groundstationGateway.h"
#include "stateMachine.h"

#include <rnp_default_address.h>
#include <rnp_routingtable.h>

#include "Commands/commandpacket.h"

#include "flags.h"

GroundstationGateway::GroundstationGateway(stateMachine* sm):
State(sm,SYSTEM_FLAG::STATE_GROUNDSTATION_GATEWAY)
{};

void GroundstationGateway::initialise(){
    State::initialise();
    //load the GroundstationGateway routing table
    RoutingTable routetable;
    routetable.setRoute((uint8_t)DEFAULT_ADDRESS::ROCKET,Route{3,1,{}});
    routetable.setRoute((uint8_t)DEFAULT_ADDRESS::GROUNDSTATION,Route{1,1,{}});

    _sm->networkmanager.setRoutingTable(routetable);
    _sm->networkmanager.updateBaseTable(); // save the new base table
    _sm->networkmanager.setAddress(static_cast<uint8_t>(DEFAULT_ADDRESS::GROUNDSTATION_GATEWAY));

    _sm->networkmanager.enableAutoRouteGen(false); // enable route learning
    _sm->networkmanager.setNoRouteAction(NOROUTE_ACTION::BROADCAST,{1,3}); // enable broadcast over serial and radio only


    // _sm->networkmanager.sendPacket(packet);
    // _sm->networkmanager.sendPacket(packet);
    // _sm->networkmanager.sendPacket(packet);
    // _sm->networkmanager.sendPacket(packet);
    // _sm->networkmanager.sendPacket(packet);
    // _sm->networkmanager.sendPacket(packet);

    
};

State* GroundstationGateway::update(){
    
    return this;//loopy loop
};

void GroundstationGateway::exitstate(){
    State::exitstate();
};