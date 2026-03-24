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
    ROOT::Math::PtEtaPhiMVector lepton1P4 = lepton1P4_input; // Lepton1
    ROOT::Math::PtEtaPhiMVector lepton2P4 = lepton2P4_input; // Lepton2

    ROOT::Math::PtEtaPhiMVector zP4 = lepton1P4 + lepton2P4; // Z boson recreated from leptons

    ROOT::Math::Boost boostToZRestFrame(-zP4.BoostToCM());
    auto lepton1_zframe = boostToZRestFrame(lepton1P4);

    ROOT::Math::PtEtaPhiMVector wzP4 = zP4 + w1P4_input;
    ROOT::Math::Boost boostToWZFrame(-wzP4.BoostToCM());
    auto z_dibosonFrame = boostToWZFrame(zP4);
    // Based on Susmita's code, I need to include the W boson, and then boost the Z lepton to the WZ rest frame

    double cosTheta = ROOT::Math::VectorUtil::CosTheta(lepton1_zframe, z_dibosonFrame);
    /* Trying the cosTheta function in ROOT
    double cosTheta = lepton1_restcom.Vect().Dot(zP4.Vect()) /
                      (lepton1_restcom.Vect().R() * zP4.Vect().R()); // No more .Mag(); use .R()
    */
    return cosTheta;  // cosTheta is calculated in the Z rest frame
}

double calculateW_MT (double lepton_phi, double lepton_pt, double met, double metphi) {
    double dphi = std::abs(lepton_phi - metphi);
    // Check dphi is in the range [0, pi]
    if (dphi > M_PI) dphi = 2*M_PI - dphi;

    // Transverse mass equation: sqrt(2* lepton_pt * MET * (1- cos dphi)
    double W_mt = std::sqrt(2.0*lepton_pt * met * (1.0 - std::cos(dphi)));

    return W_mt;
}

int main() {

    /* The polarization files: 
    long_pol_diboson.root
    trans_pol_diboson.root
    */

    //Load the file and get the tree
    TFile *hfile = new TFile("trans_pol_diboson.root");
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
        /////////////////////////////////
        // GEN PARTICLE RECONSTRUCTION //
        /////////////////////////////////
        int nParticle = branchParticle->GetEntries(); // number of events to loop through

        bool elFromW = false; // checks to make sure I use the correct electrons/muons
        bool muFromZ = false;

        for (int n = 0; n < nParticle; n++) { // Looping through each event,
            GenParticle *p = (GenParticle*) branchParticle->At(n); // p is the particle we're using to see it's mother
            int motherIndex = p->M1; // M1 is the mother particle as a characteristic of p
	                             // motherIndex clarifies which particle in the event we're looking at
            if (motherIndex < 0) continue; // if motherindex == 0, then no mother assigned so we skip

            GenParticle *mother = (GenParticle*) branchParticle->At(motherIndex); // We label the mother as the particle at the motherIndex

            if (abs(p->PID) == 11 && abs(mother->PID) == 24) { // knowing the particle and mother, we can check the particle ID
                elFromW = true; // flag is true
            }
            if (abs(p->PID) == 13 && abs(mother->PID) == 23) {
                muFromZ = true;
            }
        }

        //////////////////////////////////
        // RECO PARTICLE RECONSTRUCTION //
        //////////////////////////////////
        int nMuons = branchMuon->GetEntries();

        if (muFromZ == true && nMuons >= 2) {
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

                    if (elFromW == true && branchElectron->GetEntries() > 0 && branchMissingET->GetEntries() >0) {
                        // I need to check if this electron came from the W boson and not some other showering event
                        // I should use it to see if the mother particle it came from was a W boson; maybe check with the Electron->Particle branch
                        Electron *el = (Electron*) branchElectron->At(0);
                        MissingET *missingET = (MissingET*) branchMissingET->At(0);
     
                        double w_mass = calculateW_MT(el->Phi, el->PT, missingET->MET, missingET->Phi);
                        hist_W->Fill(w_mass);

                        // I also need to create the 4-vector of the W boson
                        ROOT::Math::PtEtaPhiMVector lep1(el->PT, el->Eta, el->Phi, 0);
                        ROOT::Math::PtEtaPhiMVector nu2(missingET->MET, missingET->Eta, missingET->Phi, 0);
                        auto W = lep1 + nu2;

                        // Get cosTheta		    
                        double cosTheta = costheta(W, v1, v2);
                        hist_cosTheta->Fill(cosTheta);
                    }
                }
            }
        }
    }

    // Drawing the Z mass Histogram
    c1->cd();
    hist_Z->Draw();
    hist_Z->GetXaxis()->SetTitle("Mass (GeV)");
    //Save Histogram
    c1->SaveAs("Z_mass.pdf");

    c2->cd();
    hist_cosTheta->Draw();
    hist_cosTheta->SetTitle("In Diboson Frame");
    c2->SaveAs("cosTheta.pdf");

    c3->cd();
    hist_W->Draw();
    c3->SaveAs("W_mass.pdf");
    std::cout << "Histogram saved" << std::endl;

    return 0;
}




