#include "../include/Slicing.h"

namespace ana{

  void Slices ( TH2D *h_unfolded, TH2D *h_true, TH2D *h_reco, const char file[1024] ){

      // Firstly, loop over all T bins on draw slices in cos theta mu
      // Take the bin edges to be the title
      int x_bins = h_unfolded->GetNbinsX(); // Cos theta
      int y_bins = h_unfolded->GetNbinsY(); // T

      TCanvas *c_T   = new TCanvas ( "c_T", "", 800, 600 );
     
      TLegend *leg_T   = new TLegend( 0.12, 0.68, 0.42, 0.88 );

      TH1D *h_T      = new TH1D ( "h_T", "", x_bins, -1, 1 );
      TH1D *h_T_true = new TH1D ( "h_T_true", "", x_bins, -1, 1 );
      TH1D *h_T_reco = new TH1D ( "h_T_reco", "", x_bins, -1, 1 );
      
      leg_T->AddEntry( h_T, " Unfolded ", "l" );
      leg_T->AddEntry( h_T_true, " True ", "l" );
      leg_T->AddEntry( h_T_reco, " Reco ", "l" );
      leg_T->SetBorderSize(0);
      
      for ( int i = 1; i <= y_bins; ++i ){

          // Define the histograms
          // Get the lower and upper bin edges of the y axis
          double low_edge_T;
          double up_edge_T;

          low_edge_T = h_unfolded->GetYaxis()->GetBinLowEdge(i);
          up_edge_T = h_unfolded->GetYaxis()->GetBinLowEdge(i + 1);
     
          // Make the title for the current histogram and the file name
          // Clear the title for the new loop
          stringstream conv;
          conv.clear();

          string title;
          title.clear();

          char file_name[1024];

          conv << setprecision(4) << file << "comp_T_slice_" << low_edge_T << ";" << up_edge_T << ".png";
          title = conv.str();
          
          strcpy( file_name, title.c_str() );

          // For the title of the histogram
          stringstream hist;
          hist.clear();

          char hist_name[1024];
          string temp1;

          hist << setprecision(4) << "T_{#mu} in [" << low_edge_T << "," << up_edge_T << "], GeV ";
          temp1 = hist.str();

          strcpy( hist_name, temp1.c_str() );

          // Fill the histogram
          for ( int j = 1; j <= x_bins; ++j ){
              h_T->SetBinContent( j, h_unfolded->GetBinContent(j, i) );
              h_T_true->SetBinContent( j, h_true->GetBinContent(j, i) );
              h_T_reco->SetBinContent( j, h_reco->GetBinContent(j, i) );
          }

          double unfo_max = h_T->GetBinContent(h_T->GetMaximumBin());
          double true_max = h_T_true->GetBinContent(h_T_true->GetMaximumBin());
          double reco_max = h_T_reco->GetBinContent(h_T_reco->GetMaximumBin());

          double max = 1.1 * TMath::Max(unfo_max, TMath::Max(true_max, reco_max)); 

          h_T->Draw();
          h_T_true->Draw("same");
          h_T_reco->Draw("same");
          h_T->SetTitle(hist_name);
          h_T->GetYaxis()->SetRangeUser(0,max);
          h_T->GetXaxis()->SetTitle("cos#theta_{#mu}");   
          h_T->GetYaxis()->SetTitle("Event rate");   
          h_T->SetLineColor( kRed + 2 );
          h_T_true->SetLineColor( kGreen + 2 );
          h_T_reco->SetLineColor( kBlue + 2 );
          h_T_reco->SetLineStyle( 7 );

          h_T->SetTitleOffset(1.45, "Y");
          h_T->SetStats(kFALSE);

          leg_T->Draw();
          c_T->SaveAs(file_name);

      } 
     
      delete h_T;
      delete h_T_true;
      delete h_T_reco;

      delete c_T;
      
      delete leg_T;

      TCanvas *c_cos   = new TCanvas ( "c_cos", "", 800, 600 );
      
      TLegend *leg_c     = new TLegend( 0.58, 0.58, 0.88, 0.88 );

      TH1D *h_cos      = new TH1D ( "h_cos", "", y_bins, 0.2, 2 );
      TH1D *h_cos_true = new TH1D ( "h_cos_true", "", y_bins, 0.2, 2 );
      TH1D *h_cos_reco = new TH1D ( "h_cos_reco", "", y_bins, 0.2, 2 );
       
      leg_c->AddEntry( h_cos, " Unfolded ", "l" );
      leg_c->AddEntry( h_cos_true, " True ", "l" );
      leg_c->AddEntry( h_cos_reco, " Reco ", "l" );
      leg_c->SetBorderSize(0);
      
      // Cos theta mu slices
      for ( int i = 1; i <= x_bins; ++i ){

          // Define the histograms
          // Get the lower and upper bin edges of the y axis
          double low_edge_cos;
          double up_edge_cos;

          low_edge_cos = h_unfolded->GetXaxis()->GetBinLowEdge(i);
          up_edge_cos = h_unfolded->GetXaxis()->GetBinLowEdge(i + 1);
     
          // Make the title for the current histogram and the file name
          // Clear the title for the new loop
          stringstream conv1;
          conv1.clear();

          string title1;
          title1.clear();

          char file_name1[1024];

          conv1 << setprecision(4) << file << "comp_cos_thetamu_slice_" << low_edge_cos << ";" << up_edge_cos << ".png";
          title1 = conv1.str();
          
          strcpy( file_name1, title1.c_str() );

          // For the title of the histogram
          stringstream hist1;
          hist1.clear();

          char hist_name1[1024];
          string temp2;

          hist1 << setprecision(4) << "cos#theta_{#mu} in [" << low_edge_cos << "," << up_edge_cos << "]";
          temp2 = hist1.str();

          strcpy( hist_name1, temp2.c_str() );

          // Fill the histogram
          for ( int j = 1; j <= y_bins; ++j ){
              h_cos->SetBinContent( j, h_unfolded->GetBinContent(i, j) );
              h_cos_true->SetBinContent( j, h_true->GetBinContent(i, j) );
              h_cos_reco->SetBinContent( j, h_reco->GetBinContent(i, j) );
          }

          double unfo_max_c = h_cos->GetBinContent(h_cos->GetMaximumBin());
          double true_max_c = h_cos_true->GetBinContent(h_cos_true->GetMaximumBin());
          double reco_max_c = h_cos_reco->GetBinContent(h_cos_reco->GetMaximumBin());

          double max_c = 1.1 * TMath::Max(unfo_max_c, TMath::Max(true_max_c, reco_max_c)); 
          
          h_cos->Draw();
          h_cos_true->Draw("same");
          h_cos_reco->Draw("same");
          h_cos->SetTitle(hist_name1);
          h_cos->GetYaxis()->SetRangeUser(0,max_c);
          h_cos->GetXaxis()->SetTitle("T_{#mu}");   
          h_cos->GetYaxis()->SetTitle("Event rate");   
          h_cos->SetLineColor( kRed + 2 );
          h_cos_true->SetLineColor( kGreen + 2 );
          h_cos_reco->SetLineColor( kBlue + 2 );
          h_cos_reco->SetLineStyle( 7 );
          h_cos->SetTitleOffset(1.45, "Y");
          h_cos->SetStats(kFALSE);

          leg_c->Draw();
          c_cos->SaveAs(file_name1);

      } 
      
      delete h_cos;
      delete h_cos_true;
      delete h_cos_reco;

      delete c_cos;

      delete leg_c;

  }

  void Slices ( TH2D *h_ddxsec, const char file[1024] ){

      // Firstly, loop over all T bins on draw slices in cos theta mu
      // Take the bin edges to be the title
      int x_bins = h_ddxsec->GetNbinsX(); // Cos theta
      int y_bins = h_ddxsec->GetNbinsY(); // T

      TCanvas *c_T   = new TCanvas ( "c_T", "", 800, 600 );
     
      TH1D *h_T      = new TH1D ( "h_T", "", x_bins, -1, 1 );
      
      for ( int i = 1; i <= y_bins; ++i ){

          // Define the histograms
          // Get the lower and upper bin edges of the y axis
          double low_edge_T;
          double up_edge_T;

          low_edge_T = h_ddxsec->GetYaxis()->GetBinLowEdge(i);
          up_edge_T = h_ddxsec->GetYaxis()->GetBinLowEdge(i + 1);
     
          // Make the title for the current histogram and the file name
          // Clear the title for the new loop
          stringstream conv;
          conv.clear();

          string title;
          title.clear();

          char file_name[1024];

          conv << setprecision(4) << file << "xsec_T_slice_" << low_edge_T << ";" << up_edge_T << ".png";
          title = conv.str();
          
          strcpy( file_name, title.c_str() );

          // For the title of the histogram
          stringstream hist;
          hist.clear();

          char hist_name[1024];
          string temp1;

          hist << setprecision(4) << "T_{#mu} in [" << low_edge_T << "," << up_edge_T << "], GeV ";
          temp1 = hist.str();

          strcpy( hist_name, temp1.c_str() );

          // Fill the histogram
          for ( int j = 1; j <= x_bins; ++j ){
              h_T->SetBinContent( j, h_ddxsec->GetBinContent(j, i) );
              h_T->SetBinError( j, h_ddxsec->GetBinError(j, i) ); 
          }

          double max = 1.2 * h_T->GetBinContent(h_T->GetMaximumBin());

          h_T->Draw("e1x0");
          h_T->SetTitle(hist_name);
          h_T->GetYaxis()->SetRangeUser(0,max);
          h_T->GetXaxis()->SetTitle("cos#theta_{#mu}");   
          h_T->GetYaxis()->SetTitle("CC0#pi, d^{2}#sigma / dcos#theta_{#mu}dT_{#mu} [ 10^{-38} cm^{2} / GeV / n ]");

          h_T->SetTitleOffset(1.2, "Y");
          h_T->SetStats(kFALSE);

          c_T->SaveAs(file_name);

      } 
     
      delete h_T;

      delete c_T;

      TCanvas *c_cos   = new TCanvas ( "c_cos", "", 800, 600 );
      
      TH1D *h_cos      = new TH1D ( "h_cos", "", y_bins, 0.2, 2 );
       
      // Cos theta mu slices
      for ( int i = 1; i <= x_bins; ++i ){

          // Define the histograms
          // Get the lower and upper bin edges of the y axis
          double low_edge_cos;
          double up_edge_cos;

          low_edge_cos = h_ddxsec->GetXaxis()->GetBinLowEdge(i);
          up_edge_cos = h_ddxsec->GetXaxis()->GetBinLowEdge(i + 1);
     
          // Make the title for the current histogram and the file name
          // Clear the title for the new loop
          stringstream conv1;
          conv1.clear();

          string title1;
          title1.clear();

          char file_name1[1024];

          conv1 << setprecision(4) << file << "xsec_cos_thetamu_slice_" << low_edge_cos << ";" << up_edge_cos << ".png";
          title1 = conv1.str();
          
          strcpy( file_name1, title1.c_str() );

          // For the title of the histogram
          stringstream hist1;
          hist1.clear();

          char hist_name1[1024];
          string temp2;

          hist1 << setprecision(4) << "cos#theta_{#mu} in [" << low_edge_cos << "," << up_edge_cos << "]";
          temp2 = hist1.str();

          strcpy( hist_name1, temp2.c_str() );

          // Fill the histogram
          for ( int j = 1; j <= y_bins; ++j ){
              h_cos->SetBinContent( j, h_ddxsec->GetBinContent(i, j) );
              h_cos->SetBinError( j, h_ddxsec->GetBinError(i, j) ); 
          }

          double max_c = 1.2 * h_cos->GetBinContent(h_cos->GetMaximumBin());
          
          h_cos->Draw("e1x0");
          h_cos->SetTitle(hist_name1);
          h_cos->GetYaxis()->SetRangeUser(0,max_c);
          h_cos->GetXaxis()->SetTitle("T_{#mu}");   
          h_cos->GetYaxis()->SetTitle("CC0#pi, d^{2}#sigma / dcos#theta_{#mu}dT_{#mu} [ 10^{-38} cm^{2} / GeV / n ]");
          h_cos->SetTitleOffset(1.2, "Y");
          h_cos->SetStats(kFALSE);

          c_cos->SaveAs(file_name1);

      } 
      
      delete h_cos;

      delete c_cos;

  }

  void Characterisation ( TH2D *h_smeared, EventSelectionTool::ParticleList primary, EventSelectionTool::EventList reco_events,  const char file_path[1024] ){

      int n_entries  = reco_events.size();

      // Count the number of events with each type of physical process
      int qel        = 0;
      int mec        = 0;
      int res        = 0;
      int dis        = 0;
      int coh        = 0;
      int other      = 0;
      
      // Find the physical process of the event and enumerate according to 
      //  QE           : 1
      //  MEC          : 10
      //  RES          : 4
      //  DIS          : 3
      //  COH          : 5
      for ( int i = 0; i < n_entries; ++i ){
      
        if( reco_events[i].GetPhysicalProcess() == 1 ){
          ++qel; 
        }
        else if( reco_events[i].GetPhysicalProcess() == 10 ){
          ++mec; 
        }
        else if( reco_events[i].GetPhysicalProcess() == 4 ){
          ++res; 
        }
        else if( reco_events[i].GetPhysicalProcess() == 3 ){
          ++dis; 
        }
        else if( reco_events[i].GetPhysicalProcess() == 5 ){
          ++coh; 
        }
        else{
          ++other; 
        }
      }

      std::cout << " QEL : " << qel << std::endl;
      std::cout << " MEC : " << mec << std::endl;
      std::cout << " RES : " << res << std::endl;
      std::cout << " DIS : " << dis << std::endl;
      std::cout << " COH : " << coh << std::endl;
      std::cout << " Oth : " << other << std::endl;
      
      // Take the bin edges to be the title
      int x_bins = h_smeared->GetNbinsX(); // Cos theta
      int y_bins = h_smeared->GetNbinsY(); // T
    
      // T histograms
      std::vector< TH1D* > signal_h;
      
      TLegend *leg_T         = new TLegend( 0.16, 0.56, 0.40, 0.88 );
      leg_T->SetBorderSize(0);

      TH1D *h_T_muccqe     = new TH1D ( "h_T_muccqe",    "", x_bins, -1, 1 );
      TH1D *h_T_muccmec    = new TH1D ( "h_T_muccmec",   "", x_bins, -1, 1 );
      TH1D *h_T_muccres    = new TH1D ( "h_T_muccres",   "", x_bins, -1, 1 );
      TH1D *h_T_muccdis    = new TH1D ( "h_T_muccdis",   "", x_bins, -1, 1 );
      TH1D *h_T_mucccoh    = new TH1D ( "h_T_mucccoh",   "", x_bins, -1, 1 );
      TH1D *h_T_muccother  = new TH1D ( "h_T_muccother", "", x_bins, -1, 1 );

      // Cos histograms
      std::vector< TH1D* > signal_c_h;
      
      TLegend *leg_cos = new TLegend( 0.62, 0.56, 0.86, 0.88 );
      leg_cos->SetBorderSize(0);
   
      TH1D *h_cos_muccqe     = new TH1D ( "h_cos_muccqe",     "", y_bins, 0.2, 2 );
      TH1D *h_cos_muccmec    = new TH1D ( "h_cos_muccmec",    "", y_bins, 0.2, 2 );
      TH1D *h_cos_muccres    = new TH1D ( "h_cos_muccres",    "", y_bins, 0.2, 2 );
      TH1D *h_cos_muccdis    = new TH1D ( "h_cos_muccdis",    "", y_bins, 0.2, 2 );
      TH1D *h_cos_mucccoh    = new TH1D ( "h_cos_mucccoh",    "", y_bins, 0.2, 2 );
      TH1D *h_cos_muccother  = new TH1D ( "h_cos_muccother",  "", y_bins, 0.2, 2 );

      std::vector< TH1D * > all_histograms;
      all_histograms.push_back( h_T_muccqe );
      all_histograms.push_back( h_T_muccmec );
      all_histograms.push_back( h_T_muccres );
      all_histograms.push_back( h_T_muccdis );
      all_histograms.push_back( h_T_mucccoh );
      all_histograms.push_back( h_T_muccother );

      all_histograms.push_back( h_cos_muccqe );
      all_histograms.push_back( h_cos_muccmec );
      all_histograms.push_back( h_cos_muccres );
      all_histograms.push_back( h_cos_muccdis );
      all_histograms.push_back( h_cos_mucccoh );
      all_histograms.push_back( h_cos_muccother );

      // For any counters that don't = 0, initialise the histogram and legend entry
      if( qel > 0 ){
          
          leg_T->AddEntry( h_T_muccqe,     " #nu_{#mu} CC QE ", "f" );
          leg_cos->AddEntry( h_cos_muccqe,     " #nu_{#mu} CCQE ", "f" );
          
          signal_h.push_back(h_T_muccqe); 
          signal_c_h.push_back(h_cos_muccqe);

      }
      if( mec > 0 ){

          leg_T->AddEntry( h_T_muccmec,    " #nu_{#mu} CC MEC ", "f" );
          leg_cos->AddEntry( h_cos_muccmec,    " #nu_{#mu} CCMEC ", "f" );
          
          signal_h.push_back(h_T_muccmec);
          signal_c_h.push_back(h_cos_muccmec);

      }
      if( res > 0 ){

          leg_T->AddEntry( h_T_muccres, " #nu_{#mu} CC RES ", "f" );
          leg_cos->AddEntry( h_cos_muccres, " #nu_{#mu} CCRES ", "f" );
          
          signal_h.push_back(h_T_muccres);
          signal_c_h.push_back(h_cos_muccres);

      }
      if( dis > 0 ){

          leg_T->AddEntry( h_T_muccdis, " #nu_{#mu} CC DIS ", "f" );
          leg_cos->AddEntry( h_cos_muccdis, " #nu_{#mu} CC DIS ", "f" );
          
          signal_h.push_back(h_T_muccdis);
          signal_c_h.push_back(h_cos_muccdis);

      }
      if( coh > 0 ){

          leg_T->AddEntry( h_T_mucccoh, " #nu_{#mu} CC COH ", "f" );
          leg_cos->AddEntry( h_cos_mucccoh, " #nu_{#mu} CC COH ", "f" );
          
          signal_h.push_back(h_T_mucccoh);
          signal_c_h.push_back(h_cos_mucccoh);

      }
      if( other > 0 ){
          
          leg_T->AddEntry( h_T_muccother,  " #nu_{#mu} CC Other ", "f" );
          leg_cos->AddEntry( h_cos_muccother,  " #nu_{#mu} CCOther ", "f" );
          
          signal_h.push_back(h_T_muccother);
          signal_c_h.push_back(h_cos_muccother);

      }

      TCanvas *c_T         = new TCanvas ( "c_T", "", 800, 600 );
      
      // Firstly, loop over all T bins on draw slices in cos theta mu
      for ( int i = 1; i <= y_bins; ++i ){

          // Define the histograms
          // Get the lower and upper bin edges of the y axis
          double low_edge_T;
          double up_edge_T;

          low_edge_T = h_smeared->GetYaxis()->GetBinLowEdge(i);
          up_edge_T  = h_smeared->GetYaxis()->GetBinLowEdge(i + 1);
     
          // Make the title for the current histogram and the file name
          // Clear the title for the new loop
          // Filenames for signal histograms
          stringstream conv;
          conv.clear();

          string title;
          title.clear();

          char file_name[1024];

          conv << setprecision(4) << file_path << "pre_FSI_T_slice_" << low_edge_T << "_" << up_edge_T << ".png";
          title = conv.str();
          
          strcpy( file_name, title.c_str() );

          // For the title of the histogram
          stringstream hist;
          hist.clear();

          char hist_name[1024];
          string temp;

          hist << setprecision(4) << "T_{#mu} in [" << low_edge_T << "," << up_edge_T << "], GeV ";
          temp = hist.str();

          strcpy( hist_name, temp.c_str() );

          for( unsigned int i = 0; i < signal_h.size(); ++i ){
              signal_h[i]->Reset("M");
          }  

          for ( int k = 0; k < n_entries; ++k ){
        
              Event ev    = reco_events[k];            
              int process = ev.GetPhysicalProcess();
              
              Particle p  = primary[k];
              double cth  = p.GetCosTheta();
              double T    = p.GetKineticEnergy();


              // Muon neutrino in this bin
              if ( T >= low_edge_T 
                && T < up_edge_T
                && ev.GetNeutrinoPdgCode() == 14
                && ev.GetIsCC() ){
                  
                  // CCQE
                  if ( process == 1  ) {
                      h_T_muccqe->Fill( cth,1 );
                  }
                  
                  // CCMEC
                  else if ( process == 10 ){
                      h_T_muccmec->Fill( cth, 1 );
                  }
                  
                  // CCRES
                  else if ( process == 4 ){
                      h_T_muccres->Fill( cth, 1 );
                  }
                  
                  // CCDIS
                  else if ( process == 3 ){
                      h_T_muccdis->Fill( cth, 1 );
                  }
                  
                  // CCCOH
                  else if ( process == 5 ){
                      h_T_mucccoh->Fill( cth, 1 );
                  }
                  
                  // CCOther
                  else{
                      h_T_muccother->Fill( cth, 1 );
                  }
              }    
          }

          int pal[12];
          pal[0]  = kRed;
          pal[1]  = kGreen + 2;
          pal[2]  = kOrange + 7;
          pal[3]  = kBlue;
          pal[4]  = kMagenta + 1;
          pal[5]  = kCyan + 2;
          pal[6]  = kYellow + 1;
          pal[7]  = kAzure + 2;
          pal[8]  = kViolet + 2;
          pal[9]  = kTeal - 1;
          pal[10] = kPink + 2;
          pal[11] = kSpring + 2;
          
          gStyle->SetPalette( 12, pal );
          gStyle->SetHatchesLineWidth( 1 );
          gStyle->SetHatchesSpacing( 0.5 );
          gStyle->SetTitleOffset(1.5, "Y");
          gStyle->SetOptStat( 0 );

          double norm_T = 0;
          
          THStack *hsT         = new THStack("hsT","pre-FSI ");
          
          for ( unsigned int i = 0; i < signal_h.size(); ++i ){
              norm_T += signal_h[i]->Integral();
          }

          for ( unsigned int i = 0; i < signal_h.size(); ++i ){

              signal_h[i]->SetFillColor(pal[i]);
              signal_h[i]->SetLineColor(pal[i]);

              signal_h[i]->Scale(1/norm_T);

              hsT->Add(signal_h[i]);
              
          }
          
          // Fill the stacks 
          // Signal
          hsT->Draw();
          
          hsT->SetTitle(hist_name);
          hsT->GetXaxis()->SetTitle("cos#theta_{#mu}");   
          hsT->GetYaxis()->SetTitle("Normalised event rate");   
          
          leg_T->Draw();
          c_T->SaveAs(file_name);

          delete hsT;
      } 

      /*
      for ( unsigned int i = 0; i < signal_h.size(); ++i ){
          delete signal_h[i];
      }
      */
      delete c_T;
      
      delete leg_T;
     
      // ------------------------------------------------------------------------------
      //                              Cos slices
      // ------------------------------------------------------------------------------
      
      TCanvas *c_cos = new TCanvas ( "c_cos", "", 800, 600 );
      
      for ( int i = 1; i <= x_bins; ++i ){

          // Define the histograms
          // Get the lower and upper bin edges of the y axis
          double low_edge_cos;
          double up_edge_cos;

          low_edge_cos = h_smeared->GetXaxis()->GetBinLowEdge(i);
          up_edge_cos  = h_smeared->GetXaxis()->GetBinLowEdge(i + 1);
     
          // Make the title for the current histogram and the file name
          // Clear the title for the new loop
          // Filenames for signal histograms
          stringstream conv_c;
          conv_c.clear();

          string title_c;
          title_c.clear();

          char file_name_c[1024];

          conv_c << setprecision(4) << file_path << "pre_FSI_cos_slice_" << low_edge_cos << "_" << up_edge_cos << ".png";
          title_c = conv_c.str();
          
          strcpy( file_name_c, title_c.c_str() );

          // For the title of the histogram
          stringstream hist_c;
          hist_c.clear();

          char hist_name_c[1024];
          string temp_c;

          hist_c << setprecision(4) << "cos#theta_{#mu} in [" << low_edge_cos << "," << up_edge_cos << "]";
          temp_c = hist_c.str();

          strcpy( hist_name_c, temp_c.c_str() );


          for( unsigned int i = 0; i < signal_c_h.size(); ++i ){
              signal_c_h[i]->Reset("M");
          }  

          THStack *hscos = new THStack("hscos","pre_FSI");
              
          for ( int k = 0; k < n_entries; ++k ){
         
              Event ev    = reco_events[k];            
              int process = ev.GetPhysicalProcess();
              
              Particle p  = primary[k];
              double cth  = p.GetCosTheta();
              double T    = p.GetKineticEnergy();

              // Muon neutrino in this bin
              if ( cth >= low_edge_cos 
                && cth < up_edge_cos
                && ev.GetNeutrinoPdgCode() == 14
                && ev.GetIsCC() ){
                  
                  // CCQE
                  if ( process == 1 ) {
                      h_cos_muccqe->Fill( T, 1 );
                  }
                  
                  // CCMEC
                  else if ( process == 10 ){
                      h_cos_muccmec->Fill( T, 1 );
                  }
                  
                  // CCRES, 1Pi
                  else if ( process == 4 ){
                      h_cos_muccres->Fill( T, 1 );
                  }
                  // CCDIS
                  else if ( process == 3 ){
                      h_cos_muccdis->Fill( T, 1 );
                  }
                  
                  // CCCOH
                  else if ( process == 5 ){
                      h_cos_mucccoh->Fill( T, 1 );
                  }
                  
                  // CCOther
                  else{
                      h_cos_muccother->Fill( T, 1 );
                  }
              }   
          }
          
          int pal[12];
          pal[0]  = kRed;
          pal[1]  = kGreen + 2;
          pal[2]  = kOrange + 7;
          pal[3]  = kBlue;
          pal[4]  = kMagenta + 1;
          pal[5]  = kCyan + 2;
          pal[6]  = kYellow + 1;
          pal[7]  = kAzure + 2;
          pal[8]  = kViolet + 2;
          pal[9]  = kTeal - 1;
          pal[10] = kPink + 2;
          pal[11] = kSpring + 2;
          
          gStyle->SetPalette( 12, pal );
          gStyle->SetHatchesLineWidth( 1 );
          gStyle->SetHatchesSpacing( 0.5 );
          gStyle->SetTitleOffset(1.5, "Y");
          gStyle->SetOptStat(0);

          double norm_cos = 0;
         
          for ( unsigned int i = 0; i < signal_c_h.size(); ++i ){
              norm_cos += signal_c_h[i]->Integral();
          }
          
          for ( unsigned int i = 0; i < signal_c_h.size(); ++i ){

              signal_c_h[i]->SetFillColor(pal[i]);
              signal_c_h[i]->SetLineColor(pal[i]);

              signal_c_h[i]->Scale(1/norm_cos);

              hscos->Add(signal_c_h[i]);
          }
          
          // Fill the stacks 
          // Signal
          hscos->Draw();
          
          hscos->SetTitle(hist_name_c);
          hscos->GetXaxis()->SetTitle("T_{#mu} [GeV]");   
          hscos->GetYaxis()->SetTitle("Normalised event rate");   
      
          leg_cos->Draw();
          c_cos->SaveAs(file_name_c);

          delete hscos;
      } 

      /*
      for ( unsigned int i = 0; i < signal_c_h.size(); ++i ){
          delete signal_c_h[i];
      }
      */
      
      for ( unsigned int i = 0; i < all_histograms.size(); ++i ){
          delete all_histograms[i];
      }
      delete c_cos;
      
      delete leg_cos;
  }

  void SignalComparison( const std::vector< TH2D* > &vect_ddxsec, const char file_path[1024], std::vector< std::string > &names ){

      // Firstly, loop over all T bins on draw slices in cos theta mu
      // Take the bin edges to be the title
      int x_bins = vect_ddxsec[0]->GetNbinsX(); // Cos theta
      int y_bins = vect_ddxsec[0]->GetNbinsY(); // T

      int pal[12];
      pal[0]  = kRed;
      pal[1]  = kGreen + 2;
      pal[2]  = kOrange + 7;
      pal[3]  = kBlue;
      pal[4]  = kMagenta + 1;
      pal[5]  = kCyan + 2;
      pal[6]  = kYellow + 1;
      pal[7]  = kAzure + 2;
      pal[8]  = kViolet + 2;
      pal[9]  = kTeal - 1;
      pal[10] = kPink + 2;
      pal[11] = kSpring + 2;
          
      gStyle->SetPalette( 12, pal );
      gStyle->SetHatchesLineWidth( 1 );
      gStyle->SetHatchesSpacing( 0.5 );
      gStyle->SetTitleOffset(1.5, "Y");
      gStyle->SetOptStat(0);
      
      TCanvas *c_T   = new TCanvas ( "c_T", "", 800, 600 );
             
      TLegend *leg_T   = new TLegend( 0.12, 0.58, 0.48, 0.88 );
      leg_T->SetBorderSize(0);

      std::vector< TH1D* > h_1D;

      for( unsigned int k = 0; k < vect_ddxsec.size(); ++k ){

          std::stringstream ss;
          ss << "h_ddxsec_T_" << k;

          TH1D *h_ddxsec_T = new TH1D( ss.str().c_str(), "", x_bins, -1, 1 ); 
          h_1D.push_back( h_ddxsec_T);
          leg_T->AddEntry( h_ddxsec_T, names[k].c_str(), "l" );

      }

      for ( int i = 1; i <= y_bins; ++i ){

          // Define the histograms
          // Get the lower and upper bin edges of the y axis
          double low_edge_T;
          double up_edge_T;

          low_edge_T = vect_ddxsec[0]->GetYaxis()->GetBinLowEdge(i);
          up_edge_T  = vect_ddxsec[0]->GetYaxis()->GetBinLowEdge(i + 1);
     
          // Make the title for the current histogram and the file name
          // Clear the title for the new loop
          std::stringstream conv;
          conv.clear();
      
          std::string title;
          title.clear();
      
          char file_name[1024];
      
          conv << std::setprecision(4) << file_path << "signal_comparison_T_slice_" << low_edge_T << ";" << up_edge_T << ".png";
          title = conv.str();
              
          strcpy( file_name, title.c_str() );

          // For the title of the histogram
          std::stringstream hist;
          hist.clear();
      
          char hist_name[1024];
          std::string temp1;
      
          hist << std::setprecision(4) << "T_{#mu} in [" << low_edge_T << "," << up_edge_T << "], GeV";
          temp1 = hist.str();
       
          strcpy( hist_name, temp1.c_str() );
     
          // Fill the histogram
          for ( int j = 1; j <= x_bins; ++j ){
   
              for( unsigned int k = 0; k < vect_ddxsec.size(); ++k ){
              
                  h_1D[k]->SetBinContent( j, vect_ddxsec[k]->GetBinContent(j, i) );
                  h_1D[k]->SetBinError( j,   vect_ddxsec[k]->GetBinError(j, i) );
                  
              }
          }

          double m = -std::numeric_limits< double >::max();

          for( unsigned int k = 0; k < vect_ddxsec.size(); ++k ){
                  
              h_1D[k]->SetLineColor( pal[k] );
              
              if( h_1D[k]->GetBinContent(h_1D[k]->GetMaximumBin()) > m ){
                  m = h_1D[k]->GetBinContent(h_1D[k]->GetMaximumBin());
              }
          }
          
          double max = 1.2 * m; 

          for( unsigned int k = 0; k < vect_ddxsec.size(); ++k ){
              
              if( k == 0 ){
               
                  h_1D[k]->SetTitle(hist_name);
                  h_1D[k]->GetYaxis()->SetRangeUser(0,max);
                  h_1D[k]->GetXaxis()->SetTitle("cos#theta_{#mu}");   
                  h_1D[k]->GetYaxis()->SetTitle("CC0#pi, d^{2}#sigma / dcos#theta_{#mu}dT_{#mu} [ 10^{-38} cm^{2} / GeV / n ]");   
                  h_1D[k]->SetTitleOffset(1.4, "Y");
                  h_1D[k]->SetStats(kFALSE);
                  h_1D[k]->Draw("e1x0");
                  h_1D[k]->Draw("hist same");

              }
              else{

                  h_1D[k]->Draw("e1x0 same");
                  h_1D[k]->Draw("hist same");
              }
          }

          leg_T->Draw(); 
          c_T->SaveAs(file_name);

      } 
     
      for( unsigned int k = 0; k < vect_ddxsec.size(); ++k ){
          delete h_1D[k];
      }
      
      delete c_T;
      delete leg_T;

      // ------------------------------------------------------------------------------
      //                              Cos slices
      // ------------------------------------------------------------------------------

      TCanvas *c_cos   = new TCanvas ( "c_cos", "", 800, 600 );
     
      TLegend *leg_cos = new TLegend( 0.62, 0.56, 0.86, 0.88 );
      leg_cos->SetBorderSize(0);

      std::vector< TH1D* > h_1D_c;

      for( unsigned int k = 0; k < vect_ddxsec.size(); ++k ){

          std::stringstream ss;
          ss << "h_ddxsec_cos_" << k;

          TH1D *h_ddxsec_cos = new TH1D( ss.str().c_str(), "", y_bins, 0.2, 2 ); 
          h_1D_c.push_back( h_ddxsec_cos);
          leg_cos->AddEntry( h_ddxsec_cos, names[k].c_str(), "l" );

      }

      for ( int i = 1; i <= x_bins; ++i ){

          // Define the histograms
          // Get the lower and upper bin edges of the y axis
          double low_edge_cos;
          double up_edge_cos;

          low_edge_cos = vect_ddxsec[0]->GetXaxis()->GetBinLowEdge(i);
          up_edge_cos  = vect_ddxsec[0]->GetXaxis()->GetBinLowEdge(i + 1);
     
          // Make the title for the current histogram and the file name
          // Clear the title for the new loop
          std::stringstream conv;
          conv.clear();
      
          std::string title;
          title.clear();
          
          char file_name1[1024];
      
          conv << std::setprecision(4) << file_path << "signal_comparison_cos_slice_" << low_edge_cos << ";" << up_edge_cos << ".png";
          title = conv.str();
              
          strcpy( file_name1, title.c_str() );

          // For the title of the histogram
          std::stringstream hist;
          hist.clear();
      
          std::string temp1;
          temp1.clear();
          
          char hist_name1[1024];
      
          hist << std::setprecision(4) << "cos#theta_{#mu} in [" << low_edge_cos << "," << up_edge_cos << "], GeV";
          temp1 = hist.str();
       
          strcpy( hist_name1, temp1.c_str() );
      
          // Fill the histogram
          for ( int j = 1; j <= y_bins; ++j ){
   
              for( unsigned int k = 0; k < vect_ddxsec.size(); ++k ){
              
                  h_1D_c[k]->SetBinContent( j, vect_ddxsec[k]->GetBinContent(i, j) );
                  h_1D_c[k]->SetBinError( j,   vect_ddxsec[k]->GetBinError(i, j) );
                  
              }
          }

          double m_c = -std::numeric_limits< double >::max();

          for( unsigned int k = 0; k < vect_ddxsec.size(); ++k ){
                  
              h_1D_c[k]->SetLineColor( pal[k] );
              
              if( h_1D_c[k]->GetBinContent(h_1D_c[k]->GetMaximumBin()) > m_c ){
                  m_c = h_1D_c[k]->GetBinContent(h_1D_c[k]->GetMaximumBin());
              }
          }
          
          double max_c = 1.2 * m_c; 

          for( unsigned int k = 0; k < vect_ddxsec.size(); ++k ){
              
              if( k == 0 ){
               
                  h_1D_c[k]->SetTitle(hist_name1);
                  h_1D_c[k]->GetYaxis()->SetRangeUser(0,max_c);
                  h_1D_c[k]->GetXaxis()->SetTitle("T_{#mu}");   
                  h_1D_c[k]->GetYaxis()->SetTitle("CC0#pi, d^{2}#sigma / dcos#theta_{#mu}dT_{#mu} [ 10^{-38} cm^{2} / GeV / n ]");   
                  h_1D_c[k]->SetTitleOffset(1.4, "Y");
                  h_1D_c[k]->SetStats(kFALSE);
                  h_1D_c[k]->Draw("e1x0");
                  h_1D_c[k]->Draw("hist same");

              }
              else{

                  h_1D_c[k]->Draw("e1x0 same");
                  h_1D_c[k]->Draw("hist same");
              }
          }

          leg_cos->Draw(); 
          c_cos->SaveAs(file_name1);

      } 
     
      for( unsigned int k = 0; k < vect_ddxsec.size(); ++k ){
          delete h_1D_c[k];
      }
      
      delete c_cos;
      delete leg_cos;

  }
} // ana
