#pragma once

#include <libriccore/riccoresystem.h>

#include "Config/systemflags_config.h"
#include "Config/commands_config.h"
#include "Config/pinmap_config.h"

#include "Network/Interfaces/radio.h"
#include "SPI.h"

#include "Commands/commands.h"

class System : public RicCoreSystem<System,SYSTEM_FLAG,Commands::ID>
{
    public:

        System();
        
        void systemSetup();

        void systemUpdate();

        SPIClass hspi;
        Radio radio;

    private:
        void setupSPI();
    
    


};