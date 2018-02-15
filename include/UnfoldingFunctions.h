#ifndef UNFOLDING_FUNCTIONS_H
#define UNFOLDING_FUNCTIONS_H

#include "../src/RooUnfoldResponse.h"
#include "../src/RooUnfoldBayes.h"

#include "../include/RooUnfoldHeaders.h"
#include "../include/EventSelectionTool.h"
#include "../include/Particle.h"
#include "../include/Event.h"

namespace ana{

  // Get the response matrix for the chosen topology
  void GetResponse( const EventSelectionTool::EventList   & event_list,
                    const TopologyMap & topology,
                    RooUnfoldResponse & response );
                               
  // Get the true and reconstructed histograms
  void GetTrueRecoHists( const EventSelectionTool::EventList   & event_list,
                         const TopologyMap                     & topology,
                         TH2D *true_hist,
                         TH2D *reco_hist );

  // Get event list of reconstructed events
  void GetRecoEventList( const EventSelectionTool::EventList   & event_list,
                         const TopologyMap                     & topology,
                         EventSelectionTool::ParticleList      & primary_list,
                         EventSelectionTool::EventList         & reco_event_list );

  // Set info for 2D histograms
  void Set2DHistInfo( TH2D *hist, const char x_axis[1024], const char y_axis[1024], const char title[1024], const char draw_opt[1024] );

}
#endif


