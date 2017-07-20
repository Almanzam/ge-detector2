#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

// STL //
#include <string>

// GEANT4 //
//class G4VSolid;
//class G4LogicalVolume;
//class G4VPhysicalVolume;

//#include "G4ThreeVector.hh"
#include "G4VUserDetectorConstruction.hh"

class G4GDMLParser;

class DetectorConstruction: public G4VUserDetectorConstruction
{
public:

    DetectorConstruction(const G4GDMLParser& parser);
    virtual G4VPhysicalVolume *Construct();
    virtual void ConstructSDandField();
    G4LogicalVolume* GetSensDet() {return myvol;};

private:
    const G4GDMLParser& fParser;
    G4LogicalVolume* myvol; 
};
#endif
