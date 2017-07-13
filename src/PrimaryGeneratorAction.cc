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
#include "G4ios.hh"


PrimaryGeneratorAction::PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction()
{
    particle_gun = new G4ParticleGun();

    G4ParticleTable *particle_table = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle = particle_table->FindParticle("gamma");

    
    particle_gun->SetParticleDefinition(particle);
    
    particle_gun->SetParticleEnergy(100. * MeV);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete particle_gun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *event)
{
    double xdir = .25*G4UniformRand()*(G4UniformRand()-.5);
    double ydir = .25*G4UniformRand()*(G4UniformRand()-.5);
    //double zdir = .25*G4UniformRand()*(G4UniformRand()-.5);
    
    particle_gun->SetParticleMomentumDirection(G4ThreeVector
            (xdir, ydir, -1));
    particle_gun->SetParticlePosition(G4ThreeVector
                                      (1,1, 6 * cm));
    particle_gun->GeneratePrimaryVertex(event);
}
