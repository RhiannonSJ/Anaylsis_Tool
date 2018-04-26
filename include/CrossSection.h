#ifndef CROSS_SECTION_H
#define CROSS_SECTION_H

#include "../src/RooUnfoldResponse.h"
#include "../src/RooUnfoldBayes.h"

#include "../include/RooUnfoldHeaders.h"
#include "../include/CovFunc.h"
#include "../include/Event.h"
#include "../include/Particle.h"
#include "../include/EventSelectionTool.h"
#include "../include/CC0piAnalysisHelper.h"
#include "../include/CC1piAnalysisHelper.h"
#include "../include/GeneralAnalysisHelper.h"

namespace ana{

  // Cross section scaling calculation
  float GetCrossSectionScale( TH2D *unfold, TH1D *flux );

  // Linearisation function
  void GetLinearisatedHistogram( TH2D *xsec, TH1D *linear);

  // Get covariance matrix
  TMatrixDSym GetCovariance( TH1D *linear, float flux_err, const char file[1024] );

  // Set errors on the linear histogram
  void SetLinearErrors( TMatrixDSym covariance, TH1D *linear, const char file[1024] );

  // Set errors on the 2D histogram from the covariance matrix
  void SetDDXSecErrors( TH1D *linear, TH2D *xsec, TMatrixDSym covariance );

  // Set total errors due to flux and statistics
  void SetFluxStatsErrors( TH2D *unfold, TH2D *xsec, float norm );

  // Get errors using linearisation
  void Set2DErrors( TH2D *xsec, TH2D *unfold, TH1D *linear, float flux_err, const char file[1024], float norm );
}
#endif


