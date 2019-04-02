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
// $Id: B2EventAction.cc 75214 2013-10-29 16:04:42Z gcosmo $
//
/// \file B2EventAction.cc
/// \brief Implementation of the B2EventAction class

#include "geEventAction.hh"
#include "geTrackerHit.hh"
#include "geRunAction.hh"
#include "HistoManager.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "G4SDManager.hh"
#include "G4UnitsTable.hh"
#include "HistoManager.hh"
#include <vector>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


geEventAction::geEventAction()
: G4UserEventAction()//,
// fhisto(histo)

{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

geEventAction::~geEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void geEventAction::BeginOfEventAction(const G4Event*)
{
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void geEventAction::EndOfEventAction(const G4Event* event)
{
  // get number of stored trajectories
  auto analysisManager = G4AnalysisManager::Instance();
  G4TrajectoryContainer* trajectoryContainer = event->GetTrajectoryContainer();
  G4int n_trajectories = 0;
  if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();

  // periodic printing

  G4int eventID = event->GetEventID();
  //if ( eventID < 100 || eventID % 100 == 0) {
    G4cout << ">>> Event: " << eventID  << G4endl;
    if ( trajectoryContainer ) {
      G4cout << "    " << n_trajectories
             << " trajectories stored in this event." << G4endl;
    }
    G4VHitsCollection* hc = event->GetHCofThisEvent()->GetHC(0);
    
    G4HCofThisEvent* HCE = event->GetHCofThisEvent();
    
    geTrackerHitsCollection* HPGeHC = 0;
    G4int n_hit = 0;
    G4double totEnergy=0.;// energyD=0.;
    G4ThreeVector pos;
    
    G4SDManager * SDman = G4SDManager::GetSDMpointer();
    HPGeCollID = SDman->GetCollectionID("TrackerHitsCollectionName");
//     HistoManager* histo = new HistoManager();
    
    if (HCE) HPGeHC = 
      (geTrackerHitsCollection*)(HCE->GetHC(HPGeCollID));

    if(HPGeHC)            
      {
        n_hit = HPGeHC->entries();
    
        for (G4int i=0;i<n_hit;i++)
          {
            totEnergy += (*HPGeHC)[i]->GetEdepTot(); 
            pos = (*HPGeHC)[i]->GetPos();
            analysisManager->FillNtupleIColumn(1,0,eventID);
            analysisManager->FillNtupleDColumn(1,1,(*HPGeHC)[i]->GetEdepTot());
            std::vector<double> pos_vec = {pos[0],pos[1],pos[2]};
            analysisManager->FillNtupleDColumn(1,2,pos_vec);
            analysisManager->AddNtupleRow(1);
//             energyD = detectorType->ResponseFunction(totEnergy);            
//             XrayFluoAnalysisManager* analysis = XrayFluoAnalysisManager::getInstance();
//             analysis->analyseEnergyDep(energyD);
//             totEnergyDetect += energyD;             
          }
	  if(totEnergy > 0){
		analysisManager->FillH1(0,totEnergy);
    analysisManager->FillNtupleDColumn(0,0, totEnergy);
    analysisManager->AddNtupleRow(0);
      }
    G4cout << "    "  
           << hc->GetSize() << " hits stored in this event" << G4endl;
    G4cout << "    Total energy deposited:  "  
    <<  G4BestUnit(totEnergy, "Energy") << G4endl;
  }
  
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
