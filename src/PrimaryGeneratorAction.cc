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
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"


PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    particle_gun = new G4ParticleGun();

    G4ParticleTable *particle_table = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle = particle_table->FindParticle("gamma");

    
    particle_gun->SetParticleDefinition(particle);
    
    particle_gun->SetParticleEnergy(1. * MeV);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete particle_gun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *event)
{
    double xdir = .75*G4UniformRand()*(G4UniformRand()-.5);
    double ydir = .75*G4UniformRand()*(G4UniformRand()-.5);
    
    particle_gun->SetParticleMomentumDirection(G4ThreeVector
            (xdir, ydir, -.5));
    particle_gun->SetParticlePosition(G4ThreeVector
                                      (0,0, 20 * cm));
    particle_gun->GeneratePrimaryVertex(event);
}
