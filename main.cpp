#include <iostream>
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "geActionInitialization.hh"

// GEANT4 //
// #ifdef G4MULTITHREADED
// #include "G4MTRunManager.hh"
// #else
#include "G4RunManager.hh"
// #endif
#include "G4UImanager.hh"
//#include "G4UIterminal.hh"
//#include "G4UItcsh.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4GDMLParser.hh"
#include "geColorReader.hh"
#include "HistoManager.hh"
#include "geEventAction.hh"


int main(int argc, char **argv)
{
    

    //DetectorConstruction *detector_construction = new DetectorConstruction;
    G4GDMLReadStructure* fReader;
    fReader = new geColorReader();
    G4GDMLParser parser(fReader);
    parser.SetStripFlag(false);
	parser->SetAddPointerToName(false);
    parser.Read("../CAD/HPGe.gdml");
	//parser.StripNamePointers();
//     G4int numCPU = sysconf(_SC_NPROCESSORS_ONLN);
//     #ifdef G4MULTITHREADED  
//     G4MTRunManager* run_manager = new G4MTRunManager;
//     if(numCPU > 10){
//         run_manager->SetNumberOfThreads(10);
//     }else{
//         run_manager->SetNumberOfThreads(4);
//     }
//     #else
    G4RunManager* run_manager = new G4RunManager;
//     #endif
//     if (argc == 3) {
//      detector_construction->SetCADFilename(argv[2]);
//     } else if (argc == 4) {
//      // We must specify the file type for tetrahedral meshes.
//      detector_construction->SetCADFilename(argv[2]);
//      detector_construction->SetCADFiletype(argv[3]);
//     } else {
//      G4cout << "Usage:" << G4endl;
//      G4cout <<
//          "    cadmesh_example <macro> <cad file name> <cad file type, optional>"
//          << G4endl;
//      return 0;
//     }

    DetectorConstruction* detector = new DetectorConstruction(parser);
    run_manager->SetUserInitialization(detector);
    HistoManager* histo = new HistoManager();

    PhysicsList *physics_list = new PhysicsList;
    run_manager->SetUserInitialization(physics_list);
    
    
    
    

    //PrimaryGeneratorAction *primary_generator = new PrimaryGeneratorAction;
    geActionInitialization *ge_action = new geActionInitialization(detector,histo);
    run_manager->SetUserInitialization(ge_action);
//     PrimaryGeneratorAction* gen_action = 
//                           new PrimaryGeneratorAction();
//     run_manager->SetUserAction(gen_action);
//     
    
    //
//     geEventAction* event_action = new geEventAction(histo);
//     run_manager->SetUserAction(event_action);
    
    run_manager->Initialize();

    G4VisManager *vis_manager = new G4VisExecutive;
    vis_manager->Initialize();

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

        
    //histo->Book();
    
    
    delete vis_manager;
    delete run_manager;
    return 0;
}
