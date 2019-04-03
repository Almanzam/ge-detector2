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
// $Id: geRunAction.cc 75214 2013-10-29 16:04:42Z gcosmo $
//
/// \file geRunAction.cc
/// \brief Implementation of the geRunAction class

#include "geRunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4ios.hh"
#include "HistoManager.hh"
#include <chrono>
#include <ctime>
#include "G4UnitsTable.hh"
//#include "G4Threading.hh"
//#include "TThread.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

geRunAction::geRunAction()
//  fHistomanager(histo)
{
  // set printing event number per each 100 events
  G4RunManager::GetRunManager()->SetPrintProgress(1000);
  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  // Create directories 
  //analysisManager->SetHistoDirectoryName("histograms");
  //analysisManager->SetNtupleDirectoryName("ntuple");
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);
    // Note: merging ntuples is available only with Root output

  // Book histograms, ntuple
  //
  
  // Creating histograms
  analysisManager->CreateH1("Eabs","Edep in absorber", 8192, 0*CLHEP::keV, 3000*CLHEP::keV);

  // Creating ntuple
  //
  analysisManager->CreateNtuple("Event list","Eabs for each event");  
  analysisManager->CreateNtupleDColumn(0,"Eabs");
  analysisManager->FinishNtuple(0);

  analysisManager->CreateNtuple("Position List","unique event id with positions for each hit");
  analysisManager->CreateNtupleIColumn(1,"EventID");
  analysisManager->CreateNtupleDColumn(1,"Energy_Deposited");
  analysisManager->CreateNtupleDColumn(1,"Hit_x");
  analysisManager->CreateNtupleDColumn(1,"Hit_y");
  analysisManager->CreateNtupleDColumn(1,"Hit_z");
  analysisManager->FinishNtuple(1);


  
  
  
  G4cout << "geAI runaction" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

geRunAction::~geRunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void geRunAction::BeginOfRunAction(const G4Run*)
{ 
  //inform the runManager to save random number seed
//   TThread::Initialize();
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
//   if(G4Threading::IsWorkerThread()){
//   G4int id = G4Threading::G4GetThreadId();
//   fHistomanager->Book(0);
  auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  //
  std::time_t rawtime;
  std::tm* timeinfo;
  char buffer [80];

  std::time(&rawtime);
  timeinfo = std::localtime(&rawtime);

  std::strftime(buffer,80,"%Y-%m-%d-%H-%M",timeinfo);
  std::puts(buffer);  
  std::string date = buffer;
  G4String fileName = "ge-detector"+date+".root";
  analysisManager->OpenFile(fileName);
//   G4cout << "geRA begin" << id << G4endl;
//   }
  G4cout << "geRA begin" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void geRunAction::EndOfRunAction(const G4Run* )
{
//     fHistomanager->Save();
  auto analysisManager = G4AnalysisManager::Instance();
  if ( analysisManager->GetH1(0) ) {
    G4cout << G4endl << " ----> print histograms statistic ";
    if(isMaster) {
      G4cout << "for the entire run " << G4endl << G4endl; 
    }
    else {
      G4cout << "for the local thread " << G4endl << G4endl; 
    }
    
    G4cout << " EAbs : mean = " 
       << G4BestUnit(analysisManager->GetH1(0)->mean(), "Energy") 
       << " rms = " 
       << G4BestUnit(analysisManager->GetH1(0)->rms(),  "Energy") << G4endl;
    
    
  }

  // save histograms & ntuple
  //
  analysisManager->Write();
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
