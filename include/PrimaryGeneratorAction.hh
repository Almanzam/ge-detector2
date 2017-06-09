#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

class G4ParticleGun;
class G4Event;
// class G4Double;

class PrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction
{
public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction();

public:
    void GeneratePrimaries(G4Event *event);
    const G4ParticleGun *GetParticleGun() const {
        return particle_gun;
    } private:
    G4ParticleGun *particle_gun;
//     G4Double *xdir;
//     G4Double *zdir;
};

#endif
