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

int MainCC0pi(){
   
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
  TopologyMap signal_1p;
  TopologyMap signal_2p;
  TopologyMap signal_3p;
 
  std::vector< int > mu;
  std::vector< int > pi;
  std::vector< int > pi0;
  std::vector< int > p;
  
  mu.push_back(  13 );
  pi.push_back( 111 );
  pi.push_back( 211 );
  pi.push_back(-211 );
  p.push_back( 2212 );
  
  signal_all.insert( std::make_pair( mu, 1 ) );
  signal_all.insert( std::make_pair( pi, 0 ) );
  
  signal_1p.insert( std::make_pair( mu, 1 ) );
  signal_1p.insert( std::make_pair( pi, 0 ) );
  signal_1p.insert( std::make_pair( p,  1 ) );
  
  signal_2p.insert( std::make_pair( mu, 1 ) );
  signal_2p.insert( std::make_pair( pi, 0 ) );
  signal_2p.insert( std::make_pair( p,  2 ) );
  
  signal_3p.insert( std::make_pair( mu, 1 ) );
  signal_3p.insert( std::make_pair( pi, 0 ) );
  signal_3p.insert( std::make_pair( p,  3 ) );
 
  // File path
  const char file_path[1024]  = "/hepstore/rjones/Exercises/Anaylsis_Tool/plots/CC0Pi/all_signal/";
  const char file_path1[1024] = "/hepstore/rjones/Exercises/Anaylsis_Tool/plots/CC0Pi/1_p/";
  const char file_path2[1024] = "/hepstore/rjones/Exercises/Anaylsis_Tool/plots/CC0Pi/2_p/";
  const char file_path3[1024] = "/hepstore/rjones/Exercises/Anaylsis_Tool/plots/CC0Pi/3_p/";
 
  TH2D *h_ddxsec_all = RunAll( h_flux, training_events, testing_events, signal_all, file_path );
  TH2D *h_ddxsec_1p  = RunAll( h_flux, training_events, testing_events, signal_1p,  file_path1 );
  TH2D *h_ddxsec_2p  = RunAll( h_flux, training_events, testing_events, signal_2p,  file_path2 );
  TH2D *h_ddxsec_3p  = RunAll( h_flux, training_events, testing_events, signal_3p,  file_path3 );

  std::vector< std::string > names;
  names.push_back( "CC 0#pi, Np" );
  names.push_back( "CC 0#pi, 1p" );
  names.push_back( "CC 0#pi, 2p" );
  names.push_back( "CC 0#pi, 3p" );

  std::vector< TH2D* > ddxsec;
  ddxsec.push_back( h_ddxsec_all );
  ddxsec.push_back( h_ddxsec_1p );
  ddxsec.push_back( h_ddxsec_2p );
  ddxsec.push_back( h_ddxsec_3p );
  
  SignalComparison( ddxsec, "/hepstore/rjones/Exercises/Anaylsis_Tool/plots/CC0Pi/comparison/", names ); 

  delete h_ddxsec_all;
  delete h_ddxsec_1p;
  delete h_ddxsec_2p;
  delete h_ddxsec_3p;
  
  time_t rawtime_end;
  struct tm * timeinfo_end;
  time (&rawtime_end);
  timeinfo_end = localtime (&rawtime_end);
  std::cout << " End: Local time and date:  " << asctime(timeinfo_end) << std::endl;
  std::cout << "-----------------------------------------------------------" << std::endl;

  return 0;

}
