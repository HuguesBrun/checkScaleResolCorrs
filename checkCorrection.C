#include "MuonPogTree.h"
#include <rochcor2015.h>
#include <RoccoR.h>
//##include "KaMuCa/Calibration/interface/KalmanMuonCalibrator.h"

float deltaR(float eta1, float eta2, float phi1, float phi2){
  float deltaR = sqrt(pow(eta2-eta1,2)+ pow(acos(cos(phi2-phi1)),2)) ;
  return deltaR;
}

std::vector<muon_pog::Muon> getThe2HighestPtMuon(std::vector<muon_pog::Muon> allMuons){
  int nbOfMuons = allMuons.size();
  int indexMax = -1;
  int indexSec = -1;
  float valueMax = 0;
  float valueSec = 0;

  for (int i=0 ; i<nbOfMuons ; i++){
    muon_pog::Muon theMuon = allMuons.at(i);
    if (theMuon.pt>valueMax){
      valueSec = valueMax;
      indexSec = indexMax;
      valueMax = theMuon.pt;
      indexMax = i;
    }
  }
  if (indexSec==-1){
    for (int i=0 ; i<nbOfMuons ; i++){
      muon_pog::Muon theMuon = allMuons.at(i);
      if (i==indexMax) continue;
      if (theMuon.pt>valueSec){;
        valueSec = theMuon.pt;
        indexSec = i;
      }
    }
  }
  std::vector<muon_pog::Muon> the2firstMuons;
  the2firstMuons.push_back(allMuons.at(indexMax));
  the2firstMuons.push_back(allMuons.at(indexSec));
  return the2firstMuons;
}

float genPt(muon_pog::Muon theMuon, std::vector<muon_pog::GenParticle> theGenParticles){
  int iteMinDeltaR = -1;
  float minDeltaR = 100;
  int nbOfGenParticles = theGenParticles.size();
  for (int i=0 ; i<nbOfGenParticles ; i++){
    muon_pog::GenParticle theGenMuon = theGenParticles.at(i);
    if (fabs(theGenMuon.pdgId)!=13) continue;
    float theLocalDeltaR = deltaR(theMuon.eta, theGenMuon.eta, theMuon.phi, theGenMuon.phi);
    if (theLocalDeltaR>0.3) continue;
    if (theLocalDeltaR<minDeltaR){
      minDeltaR = theLocalDeltaR;
      iteMinDeltaR = i;
    }
  }
  if (iteMinDeltaR==-1) return -1;
  else return (theGenParticles.at(iteMinDeltaR)).pt;
}

void checkCorrection(){
  //TFile* inputFile = TFile::Open("muonPOGNtuple_8_0_3_RelValZMM_13.root","READONLY");
  TFile* inputFile = TFile::Open("/tmp/hbrun/theMergedTree.root","READONLY");
  TTree* tree = (TTree*)inputFile->Get("MuonPogTree/MUONPOGTREE");
   if (!tree) cout << "oupssss" << endl;
   KalmanMuonCalibrator *kalman = new KalmanMuonCalibrator("MC_76X_13TeV");
   KalmanMuonCalibrator *kalmanData = new KalmanMuonCalibrator("DATA_76X_13TeV");
   rochcor2015 *rmcor = new rochcor2015();
   TFile *outputFile = new TFile("/tmp/hbrun/theNewMuonTree.root","RECREATE");
   TTree *mytreeEvent_ = new TTree("eventTree","");
   muon_pog::Muon theCorrectedMuons;
   TTree *mytree_ = new TTree("theCorrectedMuons","");
   mytree_->Branch("theCorrectedMuons", &theCorrectedMuons, 64000 ,2);

   muon_pog::Event* ev = new muon_pog::Event();


   TBranch *evBranch = tree->GetBranch("event");
   evBranch->SetAddress(&ev);
   int nEvents = evBranch->GetEntries();
   cout << "nEvents=" << nEvents << endl;
   int nbEventPassing = 0;
   float qter=0;
   for (int i = 0 ; i<nEvents ; i++){
     if (i%1000==0) cout << "i=" << i << endl;
     evBranch->GetEntry(i);
     std::vector<muon_pog::Muon> allMuons = ev->muons;
     std::vector<muon_pog::GenParticle> theGenParticles = ev->genParticles;
     if (allMuons.size()<2) continue;
     std::vector<muon_pog::Muon> the2firstMuons = getThe2HighestPtMuon(allMuons);
     for (int m=0 ; m<2 ; m++){
       float theGenPt = genPt(the2firstMuons.at(m), theGenParticles);
       theCorrectedMuons = the2firstMuons.at(m);
       theCorrectedMuons.pt_genMuon = theGenPt;
       TLorentzVector theMuonQuadri;
       theMuonQuadri.SetPtEtaPhiM((the2firstMuons.at(m)).pt,(the2firstMuons.at(m)).eta,(the2firstMuons.at(m)).phi,.10565);
       TLorentzVector theMuonQuadriToSmear = theMuonQuadri;
       rmcor->momcor_mc(theMuonQuadri, (the2firstMuons.at(m)).charge, (the2firstMuons.at(m)).trkPixelLayersWithMeas, qter, false);
       float pTafterMC = theMuonQuadri.Pt();
       theCorrectedMuons.pt_RocAfterMCscale = pTafterMC;
       rmcor->momcor_mc(theMuonQuadriToSmear, (the2firstMuons.at(m)).charge, (the2firstMuons.at(m)).trkPixelLayersWithMeas, qter, true);
       float pTafterMCres = theMuonQuadriToSmear.Pt();
       theCorrectedMuons.pt_RocAfterMCsmear = pTafterMCres;
       rmcor->momcor_dataInv(theMuonQuadriToSmear, (the2firstMuons.at(m)).charge, 0, qter);
       float pTbeforeData = theMuonQuadriToSmear.Pt();
       theCorrectedMuons.pt_RocBeforeDataScale = pTbeforeData;
       rmcor->momcor_data(theMuonQuadriToSmear, (the2firstMuons.at(m)).charge, 0, qter);
       float pTcheckReverse =  theMuonQuadriToSmear.Pt();
       theCorrectedMuons.pt_RocDataReversed = pTcheckReverse;
       //cout << "init=" << (the2firstMuons.at(m)).pt  << " afterMC=" << pTafterMC << " afterMCplusSmearing=" << pTafterMCres << " beforeData=" << pTbeforeData << " rever=" << pTcheckReverse << endl;

       float pTafterMCK = kalman->getCorrectedPt((the2firstMuons.at(m)).pt, (the2firstMuons.at(m)).eta, (the2firstMuons.at(m)).phi, (the2firstMuons.at(m)).charge);
       theCorrectedMuons.pt_KalAfterMCscale = pTafterMCK;
       float pTafterMCsmearedK = kalman->smear(pTafterMCK, (the2firstMuons.at(m)).eta);
       theCorrectedMuons.pt_KalAfterMCsmear = pTafterMCsmearedK;
       float pTbeforeDataK = (pTafterMCsmearedK*pTafterMCsmearedK)/kalmanData->getCorrectedPt(pTafterMCsmearedK, (the2firstMuons.at(m)).eta, (the2firstMuons.at(m)).phi, (the2firstMuons.at(m)).charge);
       theCorrectedMuons.pt_KalBeforeDataScale = pTbeforeDataK;
       float pTcheckReverseK = kalmanData->getCorrectedPt(pTbeforeDataK, (the2firstMuons.at(m)).eta, (the2firstMuons.at(m)).phi, (the2firstMuons.at(m)).charge);
       theCorrectedMuons.pt_KalDataReversed = pTcheckReverseK;
       mytree_->Fill();
       //cout << "init=" << (the2firstMuons.at(m)).pt  << " afterMC=" << pTafterMCK << " afterMCplusSmearing=" << pTafterMCsmearedK << " pTbeforeDataK=" << pTbeforeDataK << " pTcheckReverseK=" << pTcheckReverseK << endl;
     }
     /*TLorentzVector muon1quadri;
     muon1quadri.SetPtEtaPhiM((the2firstMuons.at(0)).pt,(the2firstMuons.at(0)).eta,(the2firstMuons.at(0)).phi,.10565);
     TLorentzVector muon2quadri;
     muon2quadri.SetPtEtaPhiM((the2firstMuons.at(1)).pt,(the2firstMuons.at(1)).eta,(the2firstMuons.at(1)).phi,.10565);*/
     /*cout << "befpre" << muon2quadri.Pt() << endl;
     rmcor->momcor_data(muon2quadri, 1, 0, qter);
     cout << "after" << muon2quadri.Pt() << endl;
     cout << "kalman=" << kalman->getCorrectedPt(40,0.0,0.0,-1) << endl;
     float mass = (muon1quadri+muon2quadri).M();

     if ((fabs((the2firstMuons.at(0).eta))<0.9)&&(fabs((the2firstMuons.at(1).eta))<0.9)){
       glbMassBB->Fill(mass);
     }
     else {
       glbMassBE->Fill(mass);
     }*/

   }
   outputFile->cd();
   mytree_->Write();
   //glbMassBE->Write();
   //glbMassBB->Write();
   outputFile->Close();

}
