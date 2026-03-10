#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TPaveText.h>
#include <TCut.h>
#include <TH2.h>
#include <algorithm>
#include <iostream>

void open_root_file() {

    //Load the file and get the tree
    TFile *hfile = new TFile("/afs/hep.wisc.edu/home/kmartine/Event_Generation/MG5_aMC_v3_6_7/ppToWZ/Events/run_02/tag_1_delphes_events.root");
    TTree *tree = (TTree*)hfile->Get("Delphes");
    std::cout << "1) File was loaded & Tree made" << std::endl;
    tree->Print();

    //TTrees need to have a reference variable to put the data into
    float electron;
    tree->SetBranchAddress("Electron.PT", &electron);
    float muon; 
    tree->SetBranchAddress("Muon.PT", &muon);
    std::cout << "2) Electron branch found" << std::endl;

    //Create a canvas to put plots onto
    TCanvas *c1 = new TCanvas("c1", "Canvas", 1200, 1000);

    std::cout << "3) Canvas made" << std::endl;

    //Create some histograms to fill with the branch in a loop over entries (Option 1)
    TH1F *hist_el = new TH1F("Electron Data", "Electron Data", 50, 0, 200);
    TH1F *hist_mu = new TH1F("Muon Data", "Muon Data", 50, 0, 200);
    std::cout << "4) Making Histograms" << std::endl;

    int nEntries = tree->GetEntries();
    std::cout << "nEntries = " << nEntries << std::endl;
    std::cout << "5) Getting Entries" << std::endl;
    for (int i=0; i<1000; i++){
        tree->GetEntry(i);

        hist_el->Fill(electron);
	hist_mu->Fill(muon);
        //std::cout << "5a) Entries loading " << i << "/" << nEntries << std::endl;
    }
    hist_el->Draw();
    hist_mu->Draw();
    hist_el->GetXaxis()->SetTitle("p_{T} (GeV)");

    c1->SaveAs("electron_muon_test.pdf");
    std::cout << "Histogram saved" << std::endl;
}

int main() {
    open_root_file();

    return 0;
}
