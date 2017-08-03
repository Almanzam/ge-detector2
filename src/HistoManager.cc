//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file analysis/AnaEx02/src/HistoManager.cc
/// \brief Implementation of the HistoManager class
//
// $Id: HistoManager.cc 98060 2016-07-01 16:24:08Z gcosmo $
// GEANT4 tag $Name: geant4-09-04 $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// #include </home/almanzam/root/root-build/include/TH1D.h>
// #include </home/almanzam/root/root-build/include/TFile.h>
// #include </home/almanzam/root/root-build/include/TTree.h>
#include <TH1D.h>
#include <TFile.h>
#include <TTree.h>
#include <CLHEP/Units/SystemOfUnits.h>

#include "HistoManager.hh"
#include "G4UnitsTable.hh"
#include "G4UIcommand.hh"
#include <chrono>
#include <ctime>
//#include "G4Threading.hh"
//#include "G4Version.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager()
:fRootFile(0), 
 fNtuple1(0), fNtuple2(0), 
 fEabs(0.), fEgap(0.) ,fLabs(0.), fLgap(0.)
{
      
  // histograms
  for (G4int k=0; k<kMaxHisto; k++) fHisto[k] = 0;
    
  // ntuple
  fNtuple1 = 0;
  fNtuple2 = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{
  if (fRootFile) delete fRootFile;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Book(G4int thread)
{ 
  // Creating a tree container to handle histograms and ntuples.
  // This tree is associated to an output file.
  //
  std::chrono::time_point<std::chrono::system_clock> time;
  time = std::chrono::system_clock::now();
  std::time_t s_time = std::chrono::system_clock::to_time_t(time);
  std::string date = std::string(std::ctime(&s_time));
  date.erase(std::remove(date.begin(), date.end(), ' '), date.end());
  str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
  G4String fileName = "ge-detector"+date+".root";
  //G4String fileName = "ge-detector.root";
  fRootFile = new TFile(fileName,"UPDATE");
  if (! fRootFile) {
    G4cout << " HistoManager::Book :" 
           << " problem creating the ROOT TFile "
           << G4endl;
    return;
  }
  
  // id = 0

  fHisto[0] = new TH1D("EAbs", "Edep in detector (MeV)", 8192, 20*CLHEP::keV, 3000*CLHEP::keV);

  

  for ( G4int i=0; i<kMaxHisto; ++i ) {
    if (! fHisto[i]) G4cout << "\n can't create histo " << i << G4endl;
  }  

  // create 1st ntuple
  fNtuple1 = new TTree("Ntuple1", "Edep");
  fNtuple1->Branch("Eabs", &fEabs, "Eabs/D");
  fNtuple1->Branch("Egap", &fEgap, "Egap/D");


  // create 2nd ntuple 
  fNtuple2 = new TTree("Ntuple2", "TrackL");
  fNtuple2->Branch("Labs", &fLabs, "Labs/D");
  fNtuple2->Branch("Lgap", &fLgap, "Lgap/D");

 
  G4cout << "\n----> Output file is open in " << fileName << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Save()
{ 
//   G4int numCPU = sysconf(_SC_NPROCESSORS_ONLN);
//   if(numCPU>10){
//       if (! fRootFile) return;
//         G4cout << "\n---->Saving\n" << G4endl;
//         if(!G4Threading::IsWorkerThread()){
//             fRootFile->Write();       // Writing the histograms to the file
//         }
//         
//         G4cout << "\n----> Written \n" << G4endl;
//         if(!G4Threading::IsWorkerThread()){
//             fRootFile->Close();       // and closing the tree (and the file)
//   }
//  }else{
     if (! fRootFile) return;
       G4cout << "\n---->Saving\n" << G4endl;
//        if(G4Threading::IsMasterThread()){
           fRootFile->Write();       // Writing the histograms to the file
//        }
        
        G4cout << "\n----> Written \n" << G4endl;
//         if(G4Threading::IsMasterThread()){
            fRootFile->Close();       // and closing the tree (and the file)
//         }
//   }
  
  G4cout << "\n----> Histograms and ntuples are saved\n" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::FillHisto(G4int ih, G4double xbin, G4double weight)
{
  if (ih >= kMaxHisto) {
    G4cerr << "---> warning from HistoManager::FillHisto() : histo " << ih
           << " does not exist. (xbin=" << xbin << " weight=" << weight << ")"
           << G4endl;
    return;
  }
  if  (fHisto[ih]) { fHisto[ih]->Fill(xbin, weight); }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Normalize(G4int ih, G4double fac)
{
  if (ih >= kMaxHisto) {
    G4cout << "---> warning from HistoManager::Normalize() : histo " << ih
           << " does not exist. (fac=" << fac << ")" << G4endl;
    return;
  }
  if (fHisto[ih]) fHisto[ih]->Scale(fac);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::FillNtuple(G4double energyAbs, G4double energyGap,
                              G4double trackLAbs , G4double trackLGap )
{
  fEabs = energyAbs;
  fEgap = energyGap;
  fLabs = trackLAbs;
  fLgap = trackLGap;

  if (fNtuple1) fNtuple1->Fill();
  if (fNtuple2) fNtuple2->Fill();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::PrintStatistic()
{
  G4cout << "\n ----> print histograms statistic \n" << G4endl;
  for ( G4int i=0; i<kMaxHisto; ++i ) {
    TH1D* h1 = fHisto[i];
    const G4String name = h1->GetName();  

    G4String unitCategory;
    if (name[0] == 'E' ) unitCategory = "Energy"; 
    if (name[0] == 'L' ) unitCategory = "Length";

    G4cout << name
           << ": mean = " << G4BestUnit(h1->GetMean(), unitCategory) 
           << " rms = " << G4BestUnit(h1->GetRMS(), unitCategory ) 
           << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


