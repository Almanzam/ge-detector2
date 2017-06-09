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

class DetectorConstruction: public G4VUserDetectorConstruction
{
public:

    DetectorConstruction(G4VPhysicalVolume *setWorld = 0){
        fWorld = setWorld;
    }
    virtual G4VPhysicalVolume *Construct()
    {
      return fWorld;
    }
    //~DetectorConstruction();

    //G4VPhysicalVolume *Construct();

//     void SetCADFilename(std::string name) {
//         filename = name;
//     };
// 
//     void SetCADFiletype(std::string type) {
//         filetype = type;
//     };


private:
//     G4VSolid *world_solid;
//     G4LogicalVolume *world_logical;
//     G4VPhysicalVolume *world_physical;
    G4VPhysicalVolume *fWorld;
//     G4ThreeVector offset;
//     G4ThreeVector cuvec;
//     G4ThreeVector my_Foilvec;
//     G4ThreeVector shellvec;
//     G4ThreeVector al_foilvec;
//     
//     G4VSolid *cad_solid;
//     G4LogicalVolume *cad_logical;
//     G4VPhysicalVolume *cad_physical;
// 
//     std::string filename;
//     std::string filetype;
};

#endif
