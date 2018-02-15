/* The Main 
 *
 *  Run all functions to get the cross section distributions
 *  for various final state topologies
 *
 * =============================================
 *
 *  Author: Rhiannon Jones
 *  Date  : July 2017
 *
 * =============================================
 */

#include "../include/RooUnfoldHeaders.h"
#include "../include/CovFunc.h"
#include "../include/UnfoldingFunctions.h"
#include "../include/CrossSection.h"
#include "../include/Slicing.h"
#include "../include/Event.h"
#include "../include/Particle.h"
#include "../include/EventSelectionTool.h"
#include "../include/RunAllPerSignal.h"

using namespace ana;

int MainCC1pi(){
   
  time_t rawtime;
  struct tm * timeinfo;
  time (&rawtime);
  timeinfo = localtime (&rawtime);
  std::cout << "-----------------------------------------------------------" << std::endl;
  std::cout << " Start: Local time and date:  " << asctime(timeinfo)         << std::endl;
  std::cout << "-----------------------------------------------------------" << std::endl;
  std::cout << " Running all files " << std::endl;
  
  //==============================================================================
  // Reading in the flux root file 
  //==============================================================================
  TFile fflux("/hepstore/rjones/Exercises/Fluxes/sbn_FHC_flux_hist.root");
  if(fflux.IsZombie()){
      std::cerr << " Error opening file " << endl;
      exit(1);
  }
  else{
      cout << "============================ SBND flux file open ==============================" << endl;
  }

  //==============================================================================
  //         Get the SBND flux histogram and trees from the root files
  //==============================================================================
  
  TH1D *h_flux = (TH1D*) fflux.Get("h_numu_110m");

  // Test the filling of the event list and cout some events
  
  // Define the vectors of events
  EventSelectionTool::EventList training_events;
  EventSelectionTool::EventList testing_events;
  
  for( unsigned int i = 0; i < 198; ++i ){
  
    // Get the filename for each 2D histogram
    std::stringstream ss;
    ss.clear();
    
    std::string name;
    name.clear();
    
    char file_name[1024];
    
    ss << "/hepstore/rjones/Samples/FNAL/analysis_trees/all/3486578_" << i <<"/output_file.root";
    name = ss.str();
            
    strcpy( file_name, name.c_str() );
      
    EventSelectionTool::LoadEventList(file_name, training_events);
  }
  std::cout << "Training : " << training_events.size() << std::endl;

  for( unsigned int i = 198; i < 398; ++i ){
  
    // Get the filename for each 2D histogram
    std::stringstream ss;
    ss.clear();
    
    std::string name;
    name.clear();
    
    char file_name[1024];
    
    ss << "/hepstore/rjones/Samples/FNAL/analysis_trees/all/3486578_" << i <<"/output_file.root";
    name = ss.str();
            
    strcpy( file_name, name.c_str() );
      
    EventSelectionTool::LoadEventList(file_name, testing_events);
  }
  
  std::cout << "Testing : " << testing_events.size() << std::endl;
  
  // Define the chosen signal and background interactions 
  // For the purpose of testing, use 
  //      signal: CC 0pi, N protons  
  //      backgrounds: NC 1pi+
  //                 : NC 1pi-
  // Maps
  TopologyMap signal_all;
  TopologyMap signal_pip;
  //TopologyMap signal_pim;
 
  std::vector< int > mu;
  std::vector< int > pi;
  //std::vector< int > pip;
  //std::vector< int > pim;
  
  mu.push_back(   13 );
  pi.push_back(  211 );
  pi.push_back( -211 );
  //pip.push_back( 211 );
  //pim.push_back(-211 );
  
  signal_all.insert( std::make_pair( mu, 1 ) );
  signal_all.insert( std::make_pair( pi, 1 ) );
  /*
  signal_pip.insert( std::make_pair( mu,  1 ) );
  signal_pip.insert( std::make_pair( pip, 1 ) );
  signal_pip.insert( std::make_pair( pim, 0 ) );
  
  signal_pim.insert( std::make_pair( mu,  1 ) );
  signal_pim.insert( std::make_pair( pip, 0 ) );
  signal_pim.insert( std::make_pair( pim, 1 ) );
  */
  // File path
  const char file_path[1024]  = "/hepstore/rjones/Exercises/Anaylsis_Tool/plots/CC1Pi/all/";
  //const char file_path1[1024] = "/hepstore/rjones/Exercises/Anaylsis_Tool/plots/CC1Pi/pip/";
  //const char file_path2[1024] = "/hepstore/rjones/Exercises/Anaylsis_Tool/plots/CC1Pi/pim/";
 
  TH2D *h_ddxsec_all = RunAll( h_flux, training_events, testing_events, signal_all,  file_path );
 // TH2D *h_ddxsec_pip = RunAll( h_flux, training_events, testing_events, signal_pip, file_path1 );
 // TH2D *h_ddxsec_pim = RunAll( h_flux, training_events, testing_events, signal_pim,   file_path2 );

  std::vector< std::string > names;
  names.push_back( "CC 1#pi^{#pm}" );
  //names.push_back( "CC 1#pi^{+}" );
  //names.push_back( "CC 1#pi^{-}" );

  std::vector< TH2D* > ddxsec;
  ddxsec.push_back( h_ddxsec_all );
  //ddxsec.push_back( h_ddxsec_pip );
  //ddxsec.push_back( h_ddxsec_pim );
  
  SignalComparison( ddxsec, "/hepstore/rjones/Exercises/Anaylsis_Tool/plots/CC1Pi/comparison/", names ); 

  delete h_ddxsec_all;
  //delete h_ddxsec_pip;
  //delete h_ddxsec_pim;
  
  time_t rawtime_end;
  struct tm * timeinfo_end;
  time (&rawtime_end);
  timeinfo_end = localtime (&rawtime_end);
  std::cout << " End: Local time and date:  " << asctime(timeinfo_end) << std::endl;
  std::cout << "-----------------------------------------------------------" << std::endl;

  return 0;

}
