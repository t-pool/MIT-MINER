#include "Miner.h"
#include "MitashAux.h"

using namespace dev;
using namespace mit;

unsigned dev::mit::Miner::s_dagLoadMode = 0;

unsigned dev::mit::Miner::s_dagLoadIndex = 0;

unsigned dev::mit::Miner::s_dagCreateDevice = 0;

uint8_t* dev::mit::Miner::s_dagInHostMemory = nullptr;

bool dev::mit::Miner::s_exit = false;

bool dev::mit::Miner::s_noeval = false;
