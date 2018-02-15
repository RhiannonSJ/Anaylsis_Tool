#ifndef SLICING_H
#define SLICING_H

#include "../include/RooUnfoldHeaders.h"
#include "../include/CovFunc.h"
#include "../include/UnfoldingFunctions.h"
#include "../include/CrossSection.h"
#include "../include/Event.h"
#include "../include/Particle.h"
#include "../include/EventSelectionTool.h"

namespace ana{

  // Unfolding, reco and truth comparison slices
  void Slices ( TH2D *h_unfolded, TH2D *h_true, TH2D *h_reco, const char file[1024] );

  // Cross-section slices with errors
  void Slices ( TH2D *h_ddxsec, const char file[1024] );

  // Get the characterised slices
  void Characterisation ( TH2D *h_smeared, EventSelectionTool::ParticleList primary, EventSelectionTool::EventList reco_events,  const char file_path[1024] );

  // Slice up the different signal histograms and compare
  void SignalComparison( const std::vector< TH2D* > &vect_ddxsec, const char file_path[1024], std::vector< std::string > &names );

}//ana

#endif


