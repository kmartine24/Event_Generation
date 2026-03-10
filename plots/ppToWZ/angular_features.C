#include <TClonesArray.h>
#include "classes/DelphesClasses.h"
// Mass Reconstruction Header Files
#include <Math/Vector4D.h>
#include <Math/LorentzVector.h>
#include <Math/PtEtaPhiM4D.h>
// Canvas/Histogram Header Files
#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TPaveText.h>
#include <TCut.h>
#include <TH2.h>
#include <TLine.h>
//C++ 
#include <algorithm>
#include <iostream>

/* Susmita's cosTheta code: 
double costheta(const TLorentzVector& z1P4_input, const TLorentzVector& z2P4_input, const TLorentzVector& leptonP4_input) {
    TLorentzVector z1P4 = z1P4_input; // Z1 boson
    TLorentzVector z2P4 = z2P4_input; // Z2 boson
    TLorentzVector leptonP4 = leptonP4_input; // Lepton from Z1
    
    TLorentzVector zzP4 = z1P4 + z2P4; // ZZ diboson pair
    leptonP4.Boost(-z1P4.BoostVector());  // Boost lepton to Z1 rest frame
    z1P4.Boost(-zzP4.BoostVector());      // Boost Z1 to ZZ rest frame
    
    double cosTheta = leptonP4.Vect().Dot(z1P4.Vect()) /
                      (leptonP4.Vect().Mag() * z1P4.Vect().Mag());

    return cosTheta;
}
*/
// My cosTheta code:
double costheta(const TLorentzVector& z1P4_input, const TLorentzVector& lepton1P4_input, const TLorentzVector& lepton2P4_input) {
    TLorentzVector lepton1P4 = lepton1P4_input; // Lepton1
    TLorentzVector lepton2P4 = lepton2P4_input; // Lepton2

    TLorentzVector zP4 = lepton1P4 + lepton2P4; // Z boson recreated from leptons

    lepton1P4.Boost(-zP4.BoostVector()); // Boost lepton1 to Z rest frame

    double cosTheta = lepton1P4.Vect().Dot(zP4.Vect()) /
                      (lepton1P4.Vect().Mag() * zP4.Vect().Mag());
    return cosTheta;  // So cosTheta is calculated in the Z rest frame?
}


int main() {

    //Load the file and get the tree
    TFile *hfile = new TFile("/afs/hep.wisc.edu/home/kmartine/Event_Generation/MG5_aMC_v3_6_7/ppToWZ/Events/run_02/tag_1_delphes_events.root");
    TTree *tree = (TTree*)hfile->Get("Delphes");
    std::cout << "1) File was loaded & Tree made" << std::endl;
    // tree->Print();

    //TTrees need to have a reference variable to put the data into
    std::cout << "2) Branches found" << std::endl;
    TClonesArray *branchMuon = 0;
    tree->SetBranchAddress("Muon", &branchMuon);

    //Create a canvas to put plots onto
    TCanvas *c1 = new TCanvas("c1", "Canvas", 1200, 1000);
    TCanvas *c2 = new TCanvas("c3", "Canvas", 1200, 1000);
    std::cout << "3) Canvas made" << std::endl;

    //Create some histograms to fill with the branch in a loop over entries (Option 1)
    TH1F *hist_Z = new TH1F("Z Invariant Mass", "Z Invariant Mass", 50, 50, 200);
    TH1F *hist_cosTheta = new TH1F("cos theta", "cos Theta", 100, -1, 1);
    std::cout << "4) Making Histograms" << std::endl;

    int nEntries = tree->GetEntries();
    std::cout << "nEntries = " << nEntries << std::endl;
    for (int i=0; i<nEntries; i++){
        tree->GetEntry(i);
        int nMuons = branchMuon->GetEntries();

	if (nMuons >= 2) {
	    for (int j = 0; j < nMuons; j++) {
                for (int k = j+1; k < nMuons; k++) {
                    Muon *mu1 = (Muon*) branchMuon->At(j);
		    Muon *mu2 = (Muon*) branchMuon->At(k);
	            
		    // Opposite charges: 
		    if (mu1->Charge * mu2->Charge >= 0) continue;

                    // The two leptons that the Z boson decayed into:	    
		    ROOT::Math::PtEtaPhiMVector v1(mu1->PT, mu1->Eta, mu1->Phi, 0.105);
		    ROOT::Math::PtEtaPhiMVector v2(mu2->PT, mu2->Eta, mu2->Phi, 0.105);
		    
		    auto Z = v1 + v2;
		    hist_Z->Fill(Z.M());

                    double cosTheta = costheta(Z, v1, v2);
		    hist_cosTheta->Fill(cosTheta);

		}
            }
	}
    }

    // Drawing the Z mass Histogram
    hist_Z->Draw();
    //Save Histogram
    c1->SaveAs("Z_mass.pdf");

    c2->cd();
    hist_cosTheta->Draw();
    c2->SaveAs("cosTheta.pdf");

    std::cout << "Histogram saved" << std::endl;

    return 0;
}
