#include "PrimaryGeneratorAction.hh"

// GEANT4 //
#include "globals.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4ios.hh"


PrimaryGeneratorAction::PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction()
{
    //particle_gun = new G4ParticleGun();
    particle_source = new G4GeneralParticleSource();
    G4ParticleTable *particle_table = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle = particle_table->FindParticle("gamma");

    
    particle_source->SetParticleDefinition(particle);
    
    
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete particle_source;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *event)
{
    //double xdir = 0;//.25*G4UniformRand()*(G4UniformRand()-.5);
    //double ydir = 0;//.25*G4UniformRand()*(G4UniformRand()-.5);
    //double engvar = 0;//.25*G4UniformRand()*(G4UniformRand()-.5);
    //particle_gun->SetParticleEnergy((1.332+engvar) * MeV);
    //particle_gun->SetParticleMomentumDirection(G4ThreeVector
    //        (xdir, ydir, -1));
    //particle_gun->SetParticlePosition(G4ThreeVector
    //                                  (1*cm,1*cm, 6 * cm));
    particle_gun->GeneratePrimaryVertex(event);
}
