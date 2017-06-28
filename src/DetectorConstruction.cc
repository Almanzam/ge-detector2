#include "DetectorConstruction.hh"

// CADMESH //
//#include "CADMesh.hh"

// GEANT4 //
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4AssemblyVolume.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh"


DetectorConstruction::DetectorConstruction()
{
    filename = "";
    filetype = "";
}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
    G4NistManager *nist_manager = G4NistManager::Instance();
    G4Material *air = nist_manager->FindOrBuildMaterial("G4_AIR");
    G4Material *Ge = nist_manager->FindOrBuildMaterial("G4_Ge");
    G4Material *Cu = nist_manager->FindOrBuildMaterial("G4_Cu");
    G4Material *Mg = nist_manager->FindOrBuildMaterial("G4_Mg");
    G4Material *Al = nist_manager->FindOrBuildMaterial("G4_Al");
    G4Material *mylar = nist_manager->FindOrBuildMaterial("G4_MYLAR");

    world_solid = new G4Box("world_solid", 50 * cm, 50 * cm, 50 * cm);
    world_logical =
        new G4LogicalVolume(world_solid, air, "world_logical", 0, 0, 0);
    world_physical =
        new G4PVPlacement(0, G4ThreeVector(), world_logical,
                          "world_physical", 0, false, 0);
    world_logical->SetVisAttributes(G4VisAttributes::Invisible);

    // CAD model rotation.
    G4RotationMatrix *rot = new G4RotationMatrix();
    rot->rotateX(90 * deg);

    // Load CAD file as tessellated solid //
    //offset = G4ThreeVector(-20*cm, 0, 0);

    // Note that offset is applied to the points in mesh directly before placement.
//     CADMesh *Ge_Crystal_mesh =
//         new CADMesh((char*)"/home/daq/projects/HPGe_Import/CAD/Ge_Crystal.stl");
//     CADMesh *Copper_Cup_mesh =
//         new CADMesh((char*)"/home/daq/projects/HPGe_Import/CAD/Copper_Cup.stl");
//     CADMesh *Shell_mesh =
//         new CADMesh((char*)"/home/daq/projects/HPGe_Import/CAD/Shell.stl");
//     CADMesh *Mylar_Foil_mesh =
//         new CADMesh((char*)"/home/daq/projects/HPGe_Import/CAD/Mylar_Foil.stl");
//     CADMesh *Al_Foil_mesh =
//         new CADMesh((char*)"/home/daq/projects/HPGe_Import/CAD/Al_Foil.stl");
//     CADMesh *Ge_Li_Layer_mesh =
//         new CADMesh((char*)"/home/daq/projects/HPGe_Import/CAD/Ge_Li_Layer.stl");
//     CADMesh *Ge_B_Layer_mesh =
//         new CADMesh((char*)"/home/daq/projects/HPGe_Import/CAD/Ge_B_Layer.stl");
//     Ge_Crystal_mesh->SetScale(mm);
//     Ge_Crystal_mesh->SetOffset(G4ThreeVector());
//     Ge_Crystal_mesh->SetReverse(false);
// 
//     Copper_Cup_mesh->SetScale(mm);
//     Copper_Cup_mesh->SetOffset(G4ThreeVector());
//     Copper_Cup_mesh->SetReverse(false);
//     cuvec = G4ThreeVector(0,-18.34*mm,0);
// 
//     Shell_mesh->SetScale(mm);
//     Shell_mesh->SetOffset(G4ThreeVector());
//     Shell_mesh->SetReverse(false);
//     shellvec = G4ThreeVector(0,-69*mm,0);
// 
//     Mylar_Foil_mesh->SetScale(mm);
//     Mylar_Foil_mesh->SetOffset(G4ThreeVector());
//     Mylar_Foil_mesh->SetReverse(false);
//     my_Foilvec = G4ThreeVector(0,75.7*mm,0);
// 
//     Al_Foil_mesh->SetScale(mm);
//     Al_Foil_mesh->SetOffset(G4ThreeVector());
//     Al_Foil_mesh->SetReverse(false);
//     al_foilvec = G4ThreeVector(0,75.73*mm,0);
// 
//     Ge_Li_Layer_mesh->SetScale(mm);
//     Ge_Li_Layer_mesh->SetOffset(G4ThreeVector());
//     Ge_Li_Layer_mesh->SetReverse(false);
// 
//     Ge_B_Layer_mesh->SetScale(mm);
//     Ge_B_Layer_mesh->SetOffset(G4ThreeVector());
//     Ge_B_Layer_mesh->SetReverse(false);
// 
//     G4VSolid *Ge_Crystal_solid = Ge_Crystal_mesh->TessellatedMesh();
//     G4LogicalVolume *Ge_Crystal_logical =
//         new G4LogicalVolume(Ge_Crystal_solid, Ge, "Ge_Crystal_logical", 0,
//                             0, 0);
//     G4PVPlacement *Ge_Crystal_physical =
//         new G4PVPlacement(rot, G4ThreeVector(), Ge_Crystal_logical,
//                           "Ge_Crystal_physical", world_logical, false, 0);
//     Ge_Crystal_logical->SetVisAttributes(G4Color(0, 1, 0, .45));
// 
//     G4VSolid *Copper_Cup_Solid = Copper_Cup_mesh->TessellatedMesh();
//     G4LogicalVolume *Copper_Cup_logical =
//         new G4LogicalVolume(Copper_Cup_Solid, Cu, "Copper_Cup_logical", 0,
//                             0, 0);
//     G4PVPlacement *Copper_Cup_physical =
//         new G4PVPlacement(rot, cuvec, Copper_Cup_logical,
//                           "Copper_Cup_physical", world_logical, false ,0);
//     Copper_Cup_logical->SetVisAttributes(G4Color(1,0,0,.45));
//     G4VSolid *Shell_solid = Shell_mesh->TessellatedMesh();
//     G4LogicalVolume *Shell_logical =
//         new G4LogicalVolume(Shell_solid, Mg, "Shell_logical", 0,
//                             0, 0);
//     G4PVPlacement *Shell_physical =
//         new G4PVPlacement(rot, shellvec, Shell_logical,
//                           "Shell_physical", world_logical, false, 0);
//     Shell_logical->SetVisAttributes(G4Color(1,1,1,.45));
//     G4VSolid *Mylar_Foil_solid = Mylar_Foil_mesh->TessellatedMesh();
//     G4LogicalVolume *Mylar_Foil_logical =
//         new G4LogicalVolume(Mylar_Foil_solid, mylar, "Mylar_Foil_logical", 0,
//                             0, 0);
//     G4PVPlacement *Mylar_Foil_physical = 
//         new G4PVPlacement(rot, my_Foilvec, Mylar_Foil_logical,
//                           "Mylar_Foil_physical", world_logical, false, 0);
//     Mylar_Foil_logical->SetVisAttributes(G4Color(0,0,1,.45));
//     G4VSolid *Al_Foil_solid = Al_Foil_mesh->TessellatedMesh();
//     G4LogicalVolume *Al_Foil_logical =
//         new G4LogicalVolume(Al_Foil_solid, Al, "Al_Foil_logical", 0,
//                             0, 0);
//     G4PVPlacement *Al_Foil_physical =
//         new G4PVPlacement(rot, al_foilvec, Al_Foil_logical,
//                           "Al_Foil_physical", world_logical, false,0);
//     Al_Foil_logical->SetVisAttributes(G4Color(1,1,0,.45));
//     G4VSolid *Ge_Li_Layer_solid = Ge_Li_Layer_mesh->TessellatedMesh();
//     G4LogicalVolume *Ge_Li_Layer_logical =
//         new G4LogicalVolume(Ge_Li_Layer_solid, Ge, "Ge_Li_Layer_logical", 0,
//                             0, 0);
//     G4PVPlacement *Ge_Li_Layer_physical =
//         new G4PVPlacement(rot, G4ThreeVector(), Ge_Li_Layer_logical,
//                           "Ge_Li_Layer_physical", world_logical, false, 0);
//     Ge_Li_Layer_logical->SetVisAttributes(G4Color(1,0,1,.45));
//     G4VSolid *Ge_B_Layer_solid = Ge_B_Layer_mesh->TessellatedMesh();
//     G4LogicalVolume *Ge_B_Layer_logical =
//         new G4LogicalVolume(Ge_B_Layer_solid, Ge, "Ge_B_Layer_logical", 0,
//                             0, 0);
//     G4PVPlacement *Ge_B_Layer_physical =
//         new G4PVPlacement(rot, G4ThreeVector(), Ge_B_Layer_logical,
//                           "Ge_B_Layer_physical", world_logical, false, 0);
//     Ge_B_Layer_logical->SetVisAttributes(G4Color(.5,.5,.2,.45));
    return world_physical;
}
