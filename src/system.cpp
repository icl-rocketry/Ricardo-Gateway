#include "system.h"

#include <memory>

#include <libriccore/riccoresystem.h>

#include <HardwareSerial.h>

#include <librnp/rnp_default_address.h>
#include <librnp/rnp_routingtable.h>

#include "Config/systemflags_config.h"
#include "Config/commands_config.h"
#include "Config/pinmap_config.h"
#include "Config/general_config.h"

#include "Commands/commands.h"

#include "States/idle.h"

#ifdef CONFIG_IDF_TARGET_ESP32S3
static constexpr int VSPI_BUS_NUM = 0;
static constexpr int HSPI_BUS_NUM = 1;
#else
static constexpr int VSPI_BUS_NUM = VSPI;
static constexpr int HSPI_BUS_NUM = HSPI;
#endif

System::System() : RicCoreSystem(Commands::command_map, Commands::defaultEnabledCommands, Serial),
                   hspi(HSPI_BUS_NUM), // CHANGE FOR esp32s3
                   radio(hspi,  PinMap::LoraCs, PinMap::LoraReset, -1, systemstatus, RADIO_MODE::TURN_TIMEOUT,  2)
{};


void System::systemSetup(){
    
    Serial.setRxBufferSize(GeneralConfig::SerialRxSize);
    Serial.begin(GeneralConfig::SerialBaud);
   
    //intialize rnp message logger
    loggerhandler.retrieve_logger<RicCoreLoggingConfig::LOGGERS::SYS>().initialize(networkmanager);

    //initialize statemachine with idle state
    statemachine.initalize(std::make_unique<Idle>(systemstatus,commandhandler));

    //any other setup goes here


    // network interfaces
    radio.setup();

    networkmanager.addInterface(&radio);

    networkmanager.setNodeType(NODETYPE::HUB);
    networkmanager.enableAutoRouteGen(true);
    networkmanager.setNoRouteAction(NOROUTE_ACTION::BROADCAST,{1,2});

    // command handler callback
    networkmanager.registerService(static_cast<uint8_t>(DEFAULT_SERVICES::COMMAND),commandhandler.getCallback());

};


void System::systemUpdate(){};