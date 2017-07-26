{ 
  TFile *f = new TFile("ge-detector.root");
  TH1D * h1 = (TH1D*)f->Get("EAbs"); 
  h1->Draw(); 
}
