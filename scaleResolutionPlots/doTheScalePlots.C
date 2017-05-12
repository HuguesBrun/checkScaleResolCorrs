TChain *chain;
TFile *outputFile;

void doTheScalePlots(){
  outputFile = new TFile("theScaleAndResolutionPlots.root", "RECREATE");
  chain = new TChain("theCorrectedMuons");
  chain->Add("theNewMuonTree.root");

    TString baseCut = "theCorrectedMuons.pt>20&&abs(theCorrectedMuons.eta)<2.4&&theCorrectedMuons.isTight==1";

    TString correctionType[2] = {"Roc","Kal"};
    TString etaBins[3] = {"negEndcaps","barrel","posEndcaps"};
    TString etaBinsCuts[3] = {"theCorrectedMuons.eta<-0.9","abs(theCorrectedMuons.eta)<0.9","theCorrectedMuons.eta>0.9"};

    TH1F *theScaleRoc = new TH1F("theScaleRoc","",100,-0.1,0.1);
    chain->Draw("(theCorrectedMuons.pt_RocAfterMCscale- theCorrectedMuons.pt_RocBeforeDataScale)/theCorrectedMuons.pt_RocBeforeDataScale>>theScaleRoc",baseCut);

    TH1F *theScaleKal = new TH1F("theScaleKal","",100,-0.1,0.1);
    chain->Draw("(theCorrectedMuons.pt_KalAfterMCscale- theCorrectedMuons.pt_KalBeforeDataScale)/theCorrectedMuons.pt_KalBeforeDataScale>>theScaleKal",baseCut);


    TH1F *theResolutionNoCor = new TH1F("theResolutionNoCor","",100,-0.1,0.1);
    chain->Draw("(theCorrectedMuons.pt-theCorrectedMuons.pt_genMuon)/theCorrectedMuons.pt_genMuon>>theResolutionNoCor",baseCut);


    TH1F *theResolutionRocScaleMC = new TH1F("theResolutionRocScaleMC","",100,-0.1,0.1);
    chain->Draw("(theCorrectedMuons.pt_RocAfterMCscale-theCorrectedMuons.pt_genMuon)/theCorrectedMuons.pt_genMuon>>theResolutionRocScaleMC",baseCut);
    TH1F *theResolutionRocScaleResoMC = new TH1F("theResolutionRocScaleResoMC","",100,-0.1,0.1);
    chain->Draw("(theCorrectedMuons.pt_RocAfterMCsmear-theCorrectedMuons.pt_genMuon)/theCorrectedMuons.pt_genMuon>>theResolutionRocScaleResoMC",baseCut);
    TH1F *theResolutionRocData = new TH1F("theResolutionData","",100,-0.1,0.1);
    chain->Draw("(theCorrectedMuons.pt_RocBeforeDataScale-theCorrectedMuons.pt_genMuon)/theCorrectedMuons.pt_genMuon>>theResolutionData",baseCut);



    TH1F *theResolutionKalScaleMC = new TH1F("theResolutionKalScaleMC","",100,-0.1,0.1);
    chain->Draw("(theCorrectedMuons.pt_KalAfterMCscale-theCorrectedMuons.pt_genMuon)/theCorrectedMuons.pt_genMuon>>theResolutionKalScaleMC",baseCut);
    TH1F *theResolutionKalScaleResoMC = new TH1F("theResolutionKalScaleResoMC","",100,-0.1,0.1);
    chain->Draw("(theCorrectedMuons.pt_KalAfterMCsmear-theCorrectedMuons.pt_genMuon)/theCorrectedMuons.pt_genMuon>>theResolutionKalScaleResoMC",baseCut);
    TH1F *theResolutionKalData = new TH1F("theResolutionKalData","",100,-0.1,0.1);
    chain->Draw("(theCorrectedMuons.pt_KalAfterMCsmear-theCorrectedMuons.pt_genMuon)/theCorrectedMuons.pt_genMuon>>theResolutionKalData",baseCut);


    TH1F *theScaleRocEtaBins[3];
    TH1F *theScaleKalEtaBins[3];
    TH1F *theResolutionNoCorEtaBins[3];

    TH1F *theResolutionRocScaleMCEtaBins[3];
    TH1F *theResolutionRocScaleResoMCEtaBins[3];
    TH1F *theResolutionRocDataEtaBins[3];

    TH1F *theResolutionKalScaleMCEtaBins[3];
    TH1F *theResolutionKalScaleResoMCEtaBins[3];
    TH1F *theResolutionKalDataEtaBins[3];


    for (int m=0; m<3 ; m++){
      theScaleRocEtaBins[m] = new TH1F("theScaleRoc"+etaBins[m],"",100,-0.1,0.1);
      chain->Draw("(theCorrectedMuons.pt_RocAfterMCscale- theCorrectedMuons.pt_RocBeforeDataScale)/theCorrectedMuons.pt_RocBeforeDataScale>>theScaleRoc"+etaBins[m],baseCut+"&&"+etaBinsCuts[m]);

      theScaleKalEtaBins[m] = new TH1F("theScaleKal"+etaBins[m],"",100,-0.1,0.1);
      chain->Draw("(theCorrectedMuons.pt_KalAfterMCscale-theCorrectedMuons.pt_KalBeforeDataScale)/theCorrectedMuons.pt_KalBeforeDataScale>>theScaleKal"+etaBins[m],baseCut+"&&"+etaBinsCuts[m]);


      theResolutionNoCorEtaBins[m] = new TH1F("theResolutionNoCor"+etaBins[m],"",100,-0.1,0.1);
      chain->Draw("(theCorrectedMuons.pt-theCorrectedMuons.pt_genMuon)/theCorrectedMuons.pt_genMuon>>theResolutionNoCor"+etaBins[m],baseCut+"&&"+etaBinsCuts[m]);

      theResolutionRocScaleMCEtaBins[m] = new TH1F("theResolutionRocScaleMC"+etaBins[m],"",100,-0.1,0.1);
      chain->Draw("(theCorrectedMuons.pt_RocAfterMCscale-theCorrectedMuons.pt_genMuon)/theCorrectedMuons.pt_genMuon>>theResolutionRocScaleMC"+etaBins[m],baseCut+"&&"+etaBinsCuts[m]);
      theResolutionRocScaleResoMCEtaBins[m] = new TH1F("theResolutionRocScaleResoMC"+etaBins[m],"",100,-0.1,0.1);
      chain->Draw("(theCorrectedMuons.pt_RocAfterMCsmear-theCorrectedMuons.pt_genMuon)/theCorrectedMuons.pt_genMuon>>theResolutionRocScaleResoMC"+etaBins[m],baseCut+"&&"+etaBinsCuts[m]);
      theResolutionRocDataEtaBins[m] = new TH1F("theResolutionRocData"+etaBins[m],"",100,-0.1,0.1);
      chain->Draw("(theCorrectedMuons.pt_RocBeforeDataScale-theCorrectedMuons.pt_genMuon)/theCorrectedMuons.pt_genMuon>>theResolutionRocData"+etaBins[m],baseCut+"&&"+etaBinsCuts[m]);

      theResolutionKalScaleMCEtaBins[m] = new TH1F("theResolutionKalScaleMC"+etaBins[m],"",100,-0.1,0.1);
      chain->Draw("(theCorrectedMuons.pt_KalAfterMCscale-theCorrectedMuons.pt_genMuon)/theCorrectedMuons.pt_genMuon>>theResolutionKalScaleMC"+etaBins[m],baseCut+"&&"+etaBinsCuts[m]);
      theResolutionKalScaleResoMCEtaBins[m] = new TH1F("theResolutionKalScaleResoMC"+etaBins[m],"",100,-0.1,0.1);
      chain->Draw("(theCorrectedMuons.pt_KalAfterMCsmear-theCorrectedMuons.pt_genMuon)/theCorrectedMuons.pt_genMuon>>theResolutionKalScaleResoMC"+etaBins[m],baseCut+"&&"+etaBinsCuts[m]);
      theResolutionKalDataEtaBins[m] = new TH1F("theResolutionKalData"+etaBins[m],"",100,-0.1,0.1);
      chain->Draw("(theCorrectedMuons.pt_KalBeforeDataScale-theCorrectedMuons.pt_genMuon)/theCorrectedMuons.pt_genMuon>>theResolutionKalData"+etaBins[m],baseCut+"&&"+etaBinsCuts[m]);

    }

    TString etaSmallBinsCuts[8] = {"theCorrectedMuons.eta<-2.1",
                              "theCorrectedMuons.eta>-2.1&&theCorrectedMuons.eta<-1.2",
                              "theCorrectedMuons.eta>-1.2&&theCorrectedMuons.eta<-0.9",
                              "theCorrectedMuons.eta>-0.9&&theCorrectedMuons.eta<0",
                              "theCorrectedMuons.eta>0&&theCorrectedMuons.eta<0.9",
                              "theCorrectedMuons.eta>0.0&&theCorrectedMuons.eta<1.2",
                              "theCorrectedMuons.eta>1.2&&theCorrectedMuons.eta<2.1",
                              "theCorrectedMuons.eta<2.4"};

    TH1F *theScaleRocSmallEtaBins[8];
    TH1F *theScaleKalSmallEtaBins[8];
    TH1F *theResolutionNoCorSmallEtaBins[8];

    TH1F *theResolutionRocScaleMCSmallEtaBins[8];
    TH1F *theResolutionRocScaleResoMCSmallEtaBins[8];
    TH1F *theResolutionRocDataSmallEtaBins[8];

    TH1F *theResolutionKalScaleMCSmallEtaBins[8];
    TH1F *theResolutionKalScaleResoMCSmallEtaBins[8];
    TH1F *theResolutionKalDataSmallEtaBins[8];

    for (int n=0 ; n<8 ; n++){
      cout << "n=" << n << endl;
      theScaleRocSmallEtaBins[n] = new TH1F(Form("theScaleRoc_bin%i",n),"",100,-0.1,0.1);
      chain->Draw(Form("(theCorrectedMuons.pt_RocAfterMCscale- theCorrectedMuons.pt_RocBeforeDataScale)/theCorrectedMuons.pt_RocBeforeDataScale>>theScaleRoc_bin%i",n),baseCut+"&&"+etaSmallBinsCuts[n]);

      theScaleKalSmallEtaBins[n] = new TH1F(Form("theScaleKal_bin%i",n),"",100,-0.1,0.1);
      chain->Draw(Form("(theCorrectedMuons.pt_KalAfterMCscale-theCorrectedMuons.pt_KalBeforeDataScale)/theCorrectedMuons.pt_KalBeforeDataScale>>theScaleKal_bin%i",n),baseCut+"&&"+etaSmallBinsCuts[n]);


      theResolutionNoCorSmallEtaBins[n] = new TH1F(Form("theResolutionNoCor_bin%i",n),"",100,-0.1,0.1);
      chain->Draw(Form("(theCorrectedMuons.pt-theCorrectedMuons.pt_genMuon)/theCorrectedMuons.pt_genMuon>>theResolutionNoCor_bin%i",n),baseCut+"&&"+etaSmallBinsCuts[n]);

      theResolutionRocScaleMCSmallEtaBins[n] = new TH1F(Form("theResolutionRocScaleMC_bin%i",n),"",100,-0.1,0.1);
      chain->Draw(Form("(theCorrectedMuons.pt_RocAfterMCscale-theCorrectedMuons.pt_genMuon)/theCorrectedMuons.pt_genMuon>>theResolutionRocScaleMC_bin%i",n),baseCut+"&&"+etaSmallBinsCuts[n]);
      theResolutionRocScaleResoMCSmallEtaBins[n] = new TH1F(Form("theResolutionRocScaleResoMC_bin%i",n),"",100,-0.1,0.1);
      chain->Draw(Form("(theCorrectedMuons.pt_RocAfterMCsmear-theCorrectedMuons.pt_genMuon)/theCorrectedMuons.pt_genMuon>>theResolutionRocScaleResoMC_bin%i",n),baseCut+"&&"+etaSmallBinsCuts[n]);
      theResolutionRocDataSmallEtaBins[n] = new TH1F(Form("theResolutionRocData_bin%i",n),"",100,-0.1,0.1);
      chain->Draw(Form("(theCorrectedMuons.pt_RocBeforeDataScale-theCorrectedMuons.pt_genMuon)/theCorrectedMuons.pt_genMuon>>theResolutionRocData_bin%i",n),baseCut+"&&"+etaSmallBinsCuts[n]);

      theResolutionKalScaleMCSmallEtaBins[n] = new TH1F(Form("theResolutionKalScaleMC_bin%i",n),"",100,-0.1,0.1);
      chain->Draw(Form("(theCorrectedMuons.pt_KalAfterMCscale-theCorrectedMuons.pt_genMuon)/theCorrectedMuons.pt_genMuon>>theResolutionKalScaleMC_bin%i",n),baseCut+"&&"+etaSmallBinsCuts[n]);
      theResolutionKalScaleResoMCSmallEtaBins[n] = new TH1F(Form("theResolutionKalScaleResoMC_bin%i",n),"",100,-0.1,0.1);
      chain->Draw(Form("(theCorrectedMuons.pt_KalAfterMCsmear-theCorrectedMuons.pt_genMuon)/theCorrectedMuons.pt_genMuon>>theResolutionKalScaleResoMC_bin%i",n),baseCut+"&&"+etaSmallBinsCuts[n]);
      theResolutionKalDataSmallEtaBins[n] = new TH1F(Form("theResolutionKalData_bin%i",n),"",100,-0.1,0.1);
      chain->Draw(Form("(theCorrectedMuons.pt_KalBeforeDataScale-theCorrectedMuons.pt_genMuon)/theCorrectedMuons.pt_genMuon>>theResolutionKalData_bin%i",n),baseCut+"&&"+etaSmallBinsCuts[n]);
    }


    outputFile->cd();
    theScaleRoc->Write();
    theScaleKal->Write();

    theResolutionNoCor->Write();
    theResolutionRocScaleMC->Write();
    theResolutionRocScaleResoMC->Write();
    theResolutionKalScaleMC->Write();
    theResolutionKalScaleResoMC->Write();
    theResolutionRocData->Write();
    theResolutionKalData->Write();


    for (int m=0 ; m<3; m++){
      theScaleRocEtaBins[m]->Write();
      theScaleKalEtaBins[m]->Write();

      theResolutionNoCorEtaBins[m]->Write();

      theResolutionRocScaleMCEtaBins[m]->Write();
      theResolutionRocScaleResoMCEtaBins[m]->Write();
      theResolutionRocDataEtaBins[m]->Write();

      theResolutionKalScaleMCEtaBins[m]->Write();
      theResolutionKalScaleResoMCEtaBins[m]->Write();
      theResolutionKalDataEtaBins[m]->Write();
    }

    for (int m=0 ; m<8; m++){
      cout << "m=" << m << endl;
      theScaleRocSmallEtaBins[m]->Write();
      theScaleKalSmallEtaBins[m]->Write();

      theResolutionNoCorSmallEtaBins[m]->Write();

      theResolutionRocScaleMCSmallEtaBins[m]->Write();
      theResolutionRocScaleResoMCSmallEtaBins[m]->Write();
      theResolutionRocDataSmallEtaBins[m]->Write();

      theResolutionKalScaleMCSmallEtaBins[m]->Write();
      theResolutionKalScaleResoMCSmallEtaBins[m]->Write();
      theResolutionKalDataSmallEtaBins[m]->Write();
    }

    outputFile->Close();



}
