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

#include "DetectorConstruction.hh"
#include "geTrackerSD.hh"
#include "G4SDManager.hh"
#include "G4GDMLParser.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4Types.hh"
#include "G4UnitsTable.hh"
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction(const G4GDMLParser& parser)
 : G4VUserDetectorConstruction(),
   fParser(parser)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return fParser.GetWorldVolume();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{
  //------------------------------------------------ 
  // Sensitive detectors
  //------------------------------------------------ 

  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  
  G4String trackerChamberSDname = "Tracker";
  geTrackerSD* aTrackerSD = 
    new geTrackerSD(trackerChamberSDname,
                    "TrackerHitsCollectionName",
                    this
                   );
  SDman->AddNewDetector( aTrackerSD );
   
  ///////////////////////////////////////////////////////////////////////
  //
  // Example how to retrieve Auxiliary Information for sensitive detector
  //
  const G4GDMLAuxMapType* auxmap = fParser.GetAuxMap();
  G4cout << "Found " << auxmap->size()
            << " volume(s) with auxiliary information."
            << G4endl << G4endl;
  for(G4GDMLAuxMapType::const_iterator iter=auxmap->begin();
      iter!=auxmap->end(); iter++) 
  {
    G4cout << "Volume " << ((*iter).first)->GetName()
           << " has the following list of auxiliary information: "
           << G4endl << G4endl;
    for (G4GDMLAuxListType::const_iterator vit=(*iter).second.begin();
         vit!=(*iter).second.end(); vit++)
    {
      G4cout << "--> Type: " << (*vit).type
                << " Value: " << (*vit).value << G4endl;
    }
  }
  G4cout << G4endl;

  // The same as above, but now we are looking for
  // sensitive detectors setting them for the volumes

  for(G4GDMLAuxMapType::const_iterator iter=auxmap->begin();
      iter!=auxmap->end(); iter++) 
  {
    G4cout << "Volume " << ((*iter).first)->GetName()
           << " has the following list of auxiliary information: "
           << G4endl << G4endl;
    for (G4GDMLAuxListType::const_iterator vit=(*iter).second.begin();
         vit!=(*iter).second.end();vit++)
    {
        G4cout << (*iter).first->GetName() << ":  "<<
            G4BestUnit((*iter).first->GetMass(),"Mass") << G4endl;
      if ((*vit).type=="SensDet")
      {
        G4cout << "Attaching sensitive detector " << (*vit).value
               << " to volume " << ((*iter).first)->GetName()
               <<  G4endl << G4endl;

        G4VSensitiveDetector* mydet = 
          SDman->FindSensitiveDetector((*vit).value);
        if(mydet) 
        {
          /*G4LogicalVolume*/ myvol = (*iter).first;
          myvol->SetSensitiveDetector(mydet);
        }
        else
        {
          G4cout << (*vit).value << " detector not found" << G4endl;
        }
      }
// 	  if ((*vit).type=="Target")
//       {
//             shell = (*iter).first;
//             G4cout << shell->GetMaterial()->GetName() << G4endl;
//             G4VPhysicalVolume* cup = shell->GetDaughter(1);
//             G4cout << cup->GetName()<<"======"<<cup->GetLogicalVolume()->GetName() << G4endl;
//             cup->SetName("Copper_phys");
//             G4cout << cup->GetName() << G4endl;
//             G4PhysicalVolumeStore* PVS = G4PhysicalVolumeStore::GetInstance();
//             for(G4int i = 0; i < G4int(PVS->size());i++){
//                 G4String t = (*PVS)[i]->GetName();
//                 kh = (t == "Copper_phys");
//                 G4cout << G4UIcommand::ConvertToString(kh) << G4endl;
//             }
//       }
    }
  }
}
