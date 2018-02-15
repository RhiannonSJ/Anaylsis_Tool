#ifndef RUN_ALL_PER_SIGNAL_H
#define RUN_ALL_PER_SIGNAL_H


#include "../include/RooUnfoldHeaders.h"
#include "../include/CovFunc.h"
#include "../include/UnfoldingFunctions.h"
#include "../include/CrossSection.h"
#include "../include/Slicing.h"
#include "../include/Event.h"
#include "../include/Particle.h"
#include "../include/EventSelectionTool.h"

namespace ana{

  TH2D *RunAll( TH1D *h_flux,
                const EventSelectionTool::EventList   &training_events,
                const EventSelectionTool::EventList   &testing_events,
                const TopologyMap &topology, 
                const char file_path[1024] );
}
#endif


