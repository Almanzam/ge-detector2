{ 
  TFile *f = new TFile("tot.root");
  TH1D * h1 = (TH1D*)f->Get("EAbs"); 
  h1->Draw(); 
}
