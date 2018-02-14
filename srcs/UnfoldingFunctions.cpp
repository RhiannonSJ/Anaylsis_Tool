#ifndef UNFOLDING_FUNCTIONS_CPP
#define UNFOLDING_FUNCTIONS_CPP

#include "../include/UnfoldingFunctions.h"
#include "../include/EventSelectionTool.h"
#include "../include/Event.h"
#include "../include/Particle.h"

using namespace ana{

  void GetResponse( const EventList                  & event_list,
                    const TopologyMap                & topology,
                    RooUnfoldResponse                & response ) {
      
    for(unsigned int i = 0; i < event_list.size(); ++i) {
        
      // Temporary event for ease
      Event ev = event_list[i];

      ParticleList true_list = ev.GetMCParticleList();
      ParticleList reco_list = ev.GetRecoParticleList();

      if(ev.CheckMCTopology(topology)) {
     
        unsigned int true_particles = true_list.size();
        Particle primary_true;
        bool true_muon_found(false);

        for(int j = 0; j < true_particles; ++j) {
          if(true_list[j].GetPdgCode() == 13) {
            primary_true = true_list[j];
            true_muon_found = true;
            break;
          }
        }
        if(!true_muon_found) primary_true = ev.GetMostEnergeticTrueParticle();
        
        if(ev.CheckRecoTopology(topology)){
        
          unsigned int reco_particles = reco_list.size();
          Particle primary_good;
          bool good_muon_found(false);

          for(int j = 0; j < reco_particles; ++j) {
            if(reco_list[j].GetPdgCode() == 13) {
              primary_good = reco_list[j];
              good_muon_found = true;
              break;
            }
          }
          if(!good_muon_found) primary_good = ev.GetMostEnergeticRecoParticle();
          
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
          Particle primary_reco;
          bool reco_muon_found(false);

          for(int j = 0; j < reco_particles; ++j) {
            if(reco_list[j].GetPdgCode() == 13) {
              primary_reco = reco_list[j];
              reco_muon_found = true;
              break;
            }
          }
          if(!reco_muon_found) primary_reco = ev.GetMostEnergeticRecoParticle();
         
          // Not true, reco therefore fake
          response.Fake(primary_reco.GetAngle(), primary_reco.GetKineticEnergy());
        }
      }
    }
  } 

  void GetTrueRecoHists( const EventList   & event_list,
                         const TopologyMap & topology,
                         TH2D *true_hist,
                         TH2D *reco_hist ) {
      
    for(unsigned int i = 0; i < event_list.size(); ++i) {
        
      // Temporary event for ease
      Event ev = event_list[i];

      ParticleList true_list = ev.GetMCParticleList();
      ParticleList reco_list = ev.GetRecoParticleList();
      
      if(ev.CheckMCTopology(topology)) {
     
        unsigned int true_particles = true_list.size();
        Particle primary_true;
        bool true_muon_found(false);

        for(int j = 0; j < true_particles; ++j) {
          if(true_list[j].GetPdgCode() == 13) {
            primary_true = true_list[j];
            true_muon_found = true;
            break;
          }
        }
        if(!true_muon_found) primary_true = ev.GetMostEnergeticTrueParticle();
        
        // True
        true_hist->Fill(primary_true.GetAngle(), primary_true.GetKineticEnergy());
                  
      }
      else{
       
        if(ev.CheckRecoTopology(topology)){
          
          unsigned int reco_particles = reco_list.size();
          Particle primary_reco;
          bool reco_muon_found(false);

          for(int j = 0; j < reco_particles; ++j) {
            if(reco_list[j].GetPdgCode() == 13) {
              primary_reco = reco_list[j];
              reco_muon_found = true;
              break;
            }
          }
          if(!reco_muon_found) primary_reco = ev.GetMostEnergeticRecoParticle();
         
          reco_hist->Fill(primary_reco.GetAngle(), primary_reco.GetKineticEnergy());
        }
      }
    }
  } 

  void GetRecoEventList( const EventList   & event_list,
                         const TopologyMap & topology,
                         ParticleList      & primary_list,
                         EventList         & reco_event_list ) {
      
    for( unsigned int i = 0; i < event_list.size(); ++i ) {
        
      // Temporary event for ease
      Event ev = event_list[i];

      if(ev.CheckRecoTopology(topology)){
        
        unsigned int reco_particles = reco_list.size();
        Particle primary_reco;
        bool reco_muon_found(false);

        for(int j = 0; j < reco_particles; ++j) {
          if(reco_list[j].GetPdgCode() == 13) {
            primary_reco = reco_list[j];
            reco_muon_found = true;
            break;
          }
        }
        if(!reco_muon_found) primary_reco = ev.GetMostEnergeticRecoParticle();
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
#endif
