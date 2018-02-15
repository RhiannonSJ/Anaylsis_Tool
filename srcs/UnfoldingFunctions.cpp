#include "../include/UnfoldingFunctions.h"
#include "../include/EventSelectionTool.h"
#include "../include/Event.h"
#include "../include/Particle.h"

namespace ana{

  void GetResponse( const EventSelectionTool::EventList   & event_list,
                    const TopologyMap & topology,
                    RooUnfoldResponse & response ) {
      
    for(unsigned int i = 0; i < event_list.size(); ++i) {
        
      // Temporary event for ease
      Event ev = event_list[i];

      EventSelectionTool::ParticleList true_list = ev.GetMCParticleList();
      EventSelectionTool::ParticleList reco_list = ev.GetRecoParticleList();

      if(ev.CheckMCTopology(topology)) {
     
        unsigned int true_particles = true_list.size();
        Particle primary_true = ev.GetMostEnergeticTrueParticle();

        for(unsigned int j = 0; j < true_particles; ++j) {
          if(true_list[j].GetPdgCode() == 13) {
            primary_true = true_list[j];
            break;
          }
        }
        
        if(ev.CheckRecoTopology(topology)){
        
          unsigned int reco_particles = reco_list.size();
          Particle primary_good = ev.GetMostEnergeticRecoParticle();

          for(unsigned int j = 0; j < reco_particles; ++j) {
            if(reco_list[j].GetPdgCode() == 13) {
              primary_good = reco_list[j];
              break;
            }
          }
          
          // True and reconstructed therefore fill
          response.Fill(primary_good.GetAngle(), primary_good.GetKineticEnergy(), primary_true.GetAngle(), primary_true.GetKineticEnergy());
        }
        else{
          // True, not reconstructed therefore miss
          response.Miss(primary_true.GetAngle(), primary_true.GetKineticEnergy()); 
        }
      }
      else{
        
        if(ev.CheckRecoTopology(topology)){
          
          unsigned int reco_particles = reco_list.size();
          Particle primary_reco = ev.GetMostEnergeticRecoParticle();

          for(unsigned int j = 0; j < reco_particles; ++j) {
            if(reco_list[j].GetPdgCode() == 13) {
              Particle primary_reco = reco_list[j];
              break;
            }
          }
         
          // Not true, reco therefore fake
          response.Fake(primary_reco.GetAngle(), primary_reco.GetKineticEnergy());
        }
      }
    }
  } 

  void GetTrueRecoHists( const EventSelectionTool::EventList   & event_list,
                         const TopologyMap & topology,
                         TH2D *true_hist,
                         TH2D *reco_hist ) {
      
    for(unsigned int i = 0; i < event_list.size(); ++i) {
        
      // Temporary event for ease
      Event ev = event_list[i];

      EventSelectionTool::ParticleList true_list = ev.GetMCParticleList();
      EventSelectionTool::ParticleList reco_list = ev.GetRecoParticleList();
      
      if(ev.CheckMCTopology(topology)) {
     
        unsigned int true_particles = true_list.size();
        Particle primary_true = ev.GetMostEnergeticTrueParticle();

        for(unsigned int j = 0; j < true_particles; ++j) {
          if(true_list[j].GetPdgCode() == 13) {
            primary_true = true_list[j];
            break;
          }
        }
        
        // True
        true_hist->Fill(primary_true.GetAngle(), primary_true.GetKineticEnergy());
                  
      }
      else{
       
        if(ev.CheckRecoTopology(topology)){
          
          unsigned int reco_particles = reco_list.size();
          Particle primary_reco = ev.GetMostEnergeticRecoParticle();

          for(unsigned int j = 0; j < reco_particles; ++j) {
            if(reco_list[j].GetPdgCode() == 13) {
              primary_reco = reco_list[j];
              break;
            }
          }
         
          reco_hist->Fill(primary_reco.GetAngle(), primary_reco.GetKineticEnergy());
        }
      }
    }
  } 

  void GetRecoEventList( const EventSelectionTool::EventList   & event_list,
                         const TopologyMap & topology,
                         EventSelectionTool::ParticleList      & primary_list,
                         EventSelectionTool::EventList         & reco_event_list ) {
      
    for( unsigned int i = 0; i < event_list.size(); ++i ) {
        
      // Temporary event for ease
      Event ev = event_list[i];

      EventSelectionTool::ParticleList reco_list = ev.GetRecoParticleList();
      
      if(ev.CheckRecoTopology(topology)){
        
        unsigned int reco_particles = reco_list.size();
        Particle primary_reco = ev.GetMostEnergeticRecoParticle();

        for(unsigned int j = 0; j < reco_particles; ++j) {
          if(reco_list[j].GetPdgCode() == 13) {
            primary_reco = reco_list[j];
            break;
          }
        }
        primary_list.push_back(primary_reco);
        reco_event_list.push_back(ev);
      }
    }
  }

  void Set2DHistInfo( TH2D *hist, const char x_axis[1024], const char y_axis[1024], const char title[1024], const char draw_opt[1024] ){

    gStyle->SetPalette(55);
    gStyle->SetNumberContours(250);

    hist->SetStats(kFALSE);
    hist->GetXaxis()->SetTitle( x_axis );
    hist->GetYaxis()->SetTitle( y_axis );
    hist->SetTitle( title );
    hist->Draw( draw_opt );

  }
}
