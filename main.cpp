#include <iostream>
#include "DetectorConstruction.hh"
//#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "geActionInitialization.hh"


#include "G4RunManager.hh"

#include "G4UImanager.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4GDMLParser.hh"
#include "geColorReader.hh"

#include "geEventAction.hh"
#include "Randomize.hh"
#include "time.h"
#include "Shielding.hh"

int main(int argc, char **argv)
{
    
    //choose the Random engine
    CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());
    //set random seed with system time
    G4long seed = time(NULL);
    CLHEP::HepRandom::setTheSeed(seed);
    //create gdml reader object with support for colors
    G4GDMLReadStructure* fReader;
    fReader = new geColorReader();
    //create gdml parser to process gdml file
    G4GDMLParser parser(fReader);
    parser.SetStripFlag(false);
    parser.SetAddPointerToName(false);
    //read file
    parser.Read("/home/almanzam/projects/ge-detector2/CAD/HPGe.gdml");
    //create run manager
    G4RunManager* run_manager = new G4RunManager;
    //use shielding physics list
    run_manager->SetUserInitialization(new Shielding); 

    //create new detector geometry using our gdml file
    DetectorConstruction* detector = new DetectorConstruction(parser);
    //add geometry to run
    run_manager->SetUserInitialization(detector);
    //create actionInitialization using geometry
    geActionInitialization *ge_action = new geActionInitialization(detector);
    //tell run manager to use new actionInitialization
    run_manager->SetUserInitialization(ge_action);
    //start
    run_manager->Initialize();
    //initialize visualization manager
    G4VisManager *vis_manager = new G4VisExecutive;
    vis_manager->Initialize();
    //initialize UI
    G4UImanager *ui_manager = G4UImanager::GetUIpointer();
    G4UIExecutive* ui = 0;
    if ( argc == 1 ) {
        ui = new G4UIExecutive(argc, argv);
    }
    if ( ! ui ) { 
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    ui_manager->ApplyCommand(G4String("/control/execute ") +
                             G4String(argv[1]));
    }else { 
    // interactive mode
    
    ui->SessionStart();
    delete ui;
  }

    delete vis_manager;
    delete run_manager;
    return 0;
}
