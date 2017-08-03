#include "PhysicsList.hh"

// GEANT4 //
#include "G4EmStandardPhysics_option4.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"

#include "G4ParticleTypes.hh"
#include "G4IonConstructor.hh"
#include "G4PhysicsListHelper.hh"
#include "G4NuclideTable.hh"
#include "G4LossTableManager.hh"
#include "G4UAtomicDeexcitation.hh"
#include "G4NuclearLevelData.hh"
#include "G4DeexPrecoParameters.hh"

// Bosons
#include "G4ChargedGeantino.hh"
#include "G4Geantino.hh"
#include "G4Gamma.hh"
#include "G4OpticalPhoton.hh"

// leptons
#include "G4MuonPlus.hh"
#include "G4MuonMinus.hh"
#include "G4NeutrinoMu.hh"
#include "G4AntiNeutrinoMu.hh"

#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4NeutrinoE.hh"
#include "G4AntiNeutrinoE.hh"

// Hadrons
#include "G4Proton.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4RadioactiveDecay.hh"

PhysicsList::PhysicsList()
{
    RegisterPhysics(new G4EmStandardPhysics_option4());
}

PhysicsList::~PhysicsList()
{
    ;
}

void PhysicsList::ConstructParticle()
{
    // pseudo-particles
    G4Geantino::GeantinoDefinition();
    G4ChargedGeantino::ChargedGeantinoDefinition();

    // gamma
    G4Gamma::GammaDefinition();

    // leptons
    G4Electron::ElectronDefinition();
    G4Positron::PositronDefinition();
    G4MuonPlus::MuonPlusDefinition();
    G4MuonMinus::MuonMinusDefinition();

    G4NeutrinoE::NeutrinoEDefinition();
    G4AntiNeutrinoE::AntiNeutrinoEDefinition();
    G4NeutrinoMu::NeutrinoMuDefinition();
    G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();

    // mesons
    G4MesonConstructor mConstructor;
    mConstructor.ConstructParticle();

    // barions
    G4BaryonConstructor bConstructor;
    bConstructor.ConstructParticle();

    // ions
    G4IonConstructor iConstructor;
    iConstructor.ConstructParticle();
}

void PhysicsList::ConstructProcess()
{
    G4VModularPhysicsList::ConstructProcess();
	AddTransportation();

  G4RadioactiveDecay* radioactiveDecay = new G4RadioactiveDecay();

  radioactiveDecay->SetARM(false);               //Atomic Rearangement
  
  G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();  
  ph->RegisterProcess(radioactiveDecay, G4GenericIon::GenericIon());

  // Need to initialize atomic deexcitation outside of radioactive decay
  G4LossTableManager* theManager = G4LossTableManager::Instance();
  G4VAtomDeexcitation* p = theManager->AtomDeexcitation();
  if (!p) {
     G4UAtomicDeexcitation* atomDeex = new G4UAtomicDeexcitation();
     theManager->SetAtomDeexcitation(atomDeex);
     atomDeex->InitialiseAtomicDeexcitation();
  }
  //
  // mandatory for G4NuclideTable
  //
  G4NuclideTable::GetInstance()->SetThresholdOfHalfLife(0.1*picosecond);
  G4NuclideTable::GetInstance()->SetLevelTolerance(1.0*eV);  
}


void PhysicsList::SetCuts()
{
    SetCutValue(defaultCutValue, "gamma");
    SetCutValue(defaultCutValue, "e-");
    SetCutValue(defaultCutValue, "e+");
}
