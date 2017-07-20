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
// $Id: B2ActionInitialization.cc 68058 2013-03-13 14:47:43Z gcosmo $
//
/// \file B2ActionInitialization.cc
/// \brief Implementation of the B2ActionInitialization class

#include "geActionInitialization.hh"
#include "HistoManager.hh"
#include "PrimaryGeneratorAction.hh"
#include "geRunAction.hh"
#include "geEventAction.hh"
//#include "SteppingAction.hh"
#include "G4ios.hh"
#include "HistoManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

geActionInitialization::geActionInitialization(DetectorConstruction* detector,HistoManager* histo)
 : G4VUserActionInitialization(),
   fDetector(detector),
   fhisto(histo)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

geActionInitialization::~geActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void geActionInitialization::BuildForMaster() const
{ 
  //HistoManager* histo = new HistoManager();
  SetUserAction(new geRunAction());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void geActionInitialization::Build() const
{

//   HistoManager* histo = new HistoManager();
  SetUserAction(new PrimaryGeneratorAction);
  SetUserAction(new geRunAction);
  SetUserAction(new geEventAction(fhisto));

  G4cout << "geAI Build" << G4endl;
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
