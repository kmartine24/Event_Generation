#include <TClonesArray.h>
#include "classes/DelphesClasses.h"
// Mass Reconstruction Header Files
#include <Math/VectorUtil.h>
#include <Math/Vector4D.h>
#include <Math/LorentzVector.h>
#include <Math/PtEtaPhiM4D.h>
#include <Math/Boost.h>
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
#include <cmath>

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
double costheta(const ROOT::Math::PtEtaPhiMVector& w1P4_input, const ROOT::Math::PtEtaPhiMVector& lepton1P4_input, const ROOT::Math::PtEtaPhiMVector& lepton2P4_input) {
    ROOT::Math::PtEtaPhiMVector lepton1P4 = lepton1P4_input; // Lepton1 from Z
    ROOT::Math::PtEtaPhiMVector lepton2P4 = lepton2P4_input; // Lepton2 from Z

    ROOT::Math::PtEtaPhiMVector zP4 = lepton1P4 + lepton2P4; // Z boson recreated from leptons

    ROOT::Math::Boost boostToZRestFrame(-zP4.BoostToCM()); // .BoostToCM() appears to be standard practice?
    auto lepton1_zframe = boostToZRestFrame(lepton1P4);

    ROOT::Math::PtEtaPhiMVector wzP4 = zP4 + w1P4_input;
    ROOT::Math::Boost boostToWZFrame(-wzP4.BoostToCM());
    auto z_dibosonFrame = boostToWZFrame(zP4);
    // Based on Susmita's code, I need to include the W boson, and then boost the Z lepton to the WZ rest frame

    double cosTheta = ROOT::Math::VectorUtil::CosTheta(lepton1_zframe, z_dibosonFrame);
    return cosTheta;  // cosTheta is calculated in the WZ rest frame
}

double calculateW_MT (double lepton_phi, double lepton_pt, double met, double metphi) {
    double dphi = std::abs(lepton_phi - metphi);
    // Check dphi is in the range [0, pi]
    if (dphi > M_PI) dphi = 2*M_PI - dphi;

    // Transverse mass equation: sqrt(2* lepton_pt * MET * (1- cos dphi)
    double W_mt = std::sqrt(2.0*lepton_pt * met * (1.0 - std::cos(dphi)));

    return W_mt;
}

bool checkMother(GenParticle * p, int motherPID, TClonesArray *branchParticle) {
    int motherIndex = p->M1;
    while (motherIndex > 0) {
        GenParticle *mother = (GenParticle*) branchParticle->At(motherIndex);
        if (abs(mother->PID) == motherPID) return true; 
	motherIndex = mother->M1;
    }
    return false;
}

int main() {

    bool _long = true; 
    bool _trans = false;
    TFile *hfile = nullptr;
    /* Files: 
    longitudinal polarized: /afs/hep.wisc.edu/home/kmartine/Event_Generation/MG5_aMC_v3_6_7/ppToWZ_long/Events/run_01/tag_1_delphes_events.root 
    transverse polarized: /afs/hep.wisc.edu/home/kmartine/Event_Generation/MG5_aMC_v3_6_7/ppToWZ/Events/run_02/tag_1_delphes_events.root
    */
    //Load the file and get the tree
    if (_trans == true) {
        hfile = new TFile("/afs/hep.wisc.edu/home/kmartine/Event_Generation/MG5_aMC_v3_6_7/ppToWZ/Events/run_02/tag_1_delphes_events.root");
    }
    else if (_long == true) {
        hfile = new TFile("/afs/hep.wisc.edu/home/kmartine/Event_Generation/MG5_aMC_v3_6_7/ppToWZ_long/Events/run_01/tag_1_delphes_events.root"); 
    }
    else { std::cout << "Pick a ROOT File" << std::endl; }
    TTree *tree = (TTree*)hfile->Get("Delphes");
    std::cout << "1) File was loaded & Tree made" << std::endl;
    // tree->Print();

    //TTrees need to have a reference variable to put the data into
    std::cout << "2) Branches found" << std::endl;
    TClonesArray *branchMuon = 0;
    tree->SetBranchAddress("Muon", &branchMuon);
    TClonesArray *branchElectron = 0;
    tree->SetBranchAddress("Electron", &branchElectron);
    TClonesArray *branchMissingET = 0;
    tree->SetBranchAddress("MissingET", &branchMissingET);
    TClonesArray *branchParticle = 0;
    tree->SetBranchAddress("Particle", &branchParticle);

    //Create a canvas to put plots onto
    TCanvas *c1 = new TCanvas("c1", "Canvas", 1200, 1000);
    TCanvas *c2 = new TCanvas("c2", "Canvas", 1200, 1000);
    TCanvas *c3 = new TCanvas("c3", "Canvas", 1200, 1000);
    std::cout << "3) Canvas made" << std::endl;

    //Create some histograms to fill with the branch in a loop over entries (Option 1)
    TH1F *hist_Z = new TH1F("Z Invariant Mass", "Z Invariant Mass", 50, 50, 200);
    TH1F *hist_cosTheta = new TH1F("cos Theta", "cos Theta", 100, -1, 1);
    TH1F *hist_W = new TH1F("W Transverse Mass", "W Transverse Mass", 50, 50, 150);
    std::cout << "4) Making Histograms" << std::endl;

    int nEntries = tree->GetEntries();
    std::cout << "nEntries = " << nEntries << std::endl;
    for (int i=0; i<nEntries; i++){
        tree->GetEntry(i);

        //////////////////
        // Z boson Info //
        //////////////////
        int nMuons = branchMuon->GetEntries();

	for (int j = 0; j < nMuons; j++) {
            for (int k = j+1; k < nMuons; k++) {
                Muon *mu1 = (Muon*) branchMuon->At(j);
                Muon *mu2 = (Muon*) branchMuon->At(k);
		    
                // Opposite charges: 
                if (mu1->Charge * mu2->Charge >= 0) continue;
		
                // Perform Gen level checking:
                GenParticle *gen1 = (GenParticle*) mu1->Particle.GetObject(); // Getting the gen level info (particle) associated with mu1/mu2
                GenParticle *gen2 = (GenParticle*) mu2->Particle.GetObject();

                if (!gen1 || !gen2) continue; // make sure gen1 or gen2 is not a nullptr

                // Check mother info with checkMother()
                if (!checkMother(gen1, 23, branchParticle)) continue;
                if (!checkMother(gen2, 23, branchParticle)) continue;

                // The two leptons that the Z boson decayed into:	    
                ROOT::Math::PtEtaPhiMVector v1(mu1->PT, mu1->Eta, mu1->Phi, 0.105);
                ROOT::Math::PtEtaPhiMVector v2(mu2->PT, mu2->Eta, mu2->Phi, 0.105);
		    
                auto Z = v1 + v2;
                hist_Z->Fill(Z.M());

                //////////////////
                // W Boson Info //
                //////////////////
                int nElectrons = branchElectron->GetEntries();
                for (int l = 0; l < nElectrons; l++) {
                
                    Electron *el = (Electron*) branchElectron->At(l);

                    GenParticle *genEl = (GenParticle*) el->Particle.GetObject(); // Get gen level data associated with el
                    if (!genEl) continue; // make sure not a nullptr

                    if (!checkMother(genEl, 24, branchParticle)) continue;

                    // Reconstruct the W mass:
                    // if (branchMissingET->GetEntries() == 0) continue; // Make sure the event had a neutrino

                    MissingET *missingET = (MissingET*) branchMissingET->At(0);
     
                    double w_mass = calculateW_MT(el->Phi, el->PT, missingET->MET, missingET->Phi);
                    hist_W->Fill(w_mass);

                    // I also need to create the 4-vector of the W boson
                    ROOT::Math::PtEtaPhiMVector lep1(el->PT, el->Eta, el->Phi, 0);
                    ROOT::Math::PtEtaPhiMVector nu2(missingET->MET, 0.0, missingET->Phi, 0);
                    auto W = lep1 + nu2;

                    // Get cosTheta		    
                    double cosTheta = costheta(W, v1, v2);
                    hist_cosTheta->Fill(cosTheta);
                }
            }
        }
    }
    std::cout << "5) Event Loop Done" << std::endl;

    // Drawing the Z mass Histogram
    c1->cd();
    hist_Z->Draw();
    hist_Z->GetXaxis()->SetTitle("Mass (GeV)");
    //Save Histogram
    if (_trans == true) c1->SaveAs("Z_mass_trans.pdf");
    if (_long == true) c1->SaveAs("Z_mass_long.pdf");

    c2->cd();
    hist_cosTheta->Draw();
    hist_cosTheta->SetTitle("In Diboson Frame");
    if (_trans == true) c2->SaveAs("cosTheta_trans.pdf");
    if (_long == true) c2->SaveAs("cosTheta_long.pdf");

    c3->cd();
    hist_W->Draw();
    hist_W->GetXaxis()->SetTitle("Mass (GeV)");
    if (_trans == true) c3->SaveAs("W_mass_trans.pdf");
    if (_long == true) c3->SaveAs("W_mass_long.pdf");
    std::cout << "Histogram saved" << std::endl;

    return 0;
}




