#include <TClonesArray.h>
#include "classes/DelphesClasses.h"
#include "ExRootAnalysis/ExRootTreeReader.h"
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
#include <TLegend.h>
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
double costheta(const ROOT::Math::PtEtaPhiMVector& w1P4_input, const ROOT::Math::PtEtaPhiMVector& lepton1P4_input, const ROOT::Math::PtEtaPhiMVector& lepton2P4_input, const ROOT::Math::PtEtaPhiMVector& lepton3P4_input, bool fromW, bool fromZ) {
    ROOT::Math::PtEtaPhiMVector lepton1P4 = lepton1P4_input; // Lepton1 from Z is the particle
    ROOT::Math::PtEtaPhiMVector lepton2P4 = lepton2P4_input; // Lepton2 from Z is the anti-particle
    ROOT::Math::PtEtaPhiMVector lepton3P4 = lepton3P4_input; // Lepton from W boson

    ROOT::Math::PtEtaPhiMVector zP4 = lepton1P4 + lepton2P4; // Z boson recreated from leptons
    ROOT::Math::PtEtaPhiMVector wzP4 = zP4 + w1P4_input; // Diboson from W and Z bosons

    // Boost to W or Z Frame
    ROOT::Math::Boost boostToZRestFrame(-zP4.BoostToCM()); // Boost to Z restframe
    ROOT::Math::Boost boostToWRestFrame(-w1P4_input.BoostToCM()); // Boost to W restframe 
    ROOT::Math::Boost boostToWZFrame(-wzP4.BoostToCM()); // Boost to diboson rest frame
    ROOT::Math::PtEtaPhiMVector lepton_BosonFrame(0,0,0,0); // make variable for lepton in boson frame 
    double cosTheta = 0;
    if (fromW == false && fromZ == true) { // in the Z boson frame:
        lepton_BosonFrame = boostToZRestFrame(lepton1P4);
        auto z_dibosonFrame = boostToWZFrame(zP4);
	ROOT::Math::DisplacementVector3D z_dir = z_dibosonFrame.Vect().Unit();
	auto z_dir_Zframe = boostToZRestFrame(ROOT::Math::PxPyPzMVector(z_dir.X(), z_dir.Y(), z_dir.Z(), 0.0));
	cosTheta = ROOT::Math::VectorUtil::CosTheta(lepton_BosonFrame.Vect(), z_dir_Zframe.Vect());
    }
    else if (fromW == true && fromZ == false) { // in the W boson frame:
        lepton_BosonFrame = boostToWRestFrame(lepton3P4);
        auto w_dibosonFrame = boostToWZFrame(w1P4_input);
	ROOT::Math::DisplacementVector3D w_dir = w_dibosonFrame.Vect().Unit();
	auto w_dir_Wframe = boostToWRestFrame(ROOT::Math::PxPyPzMVector(w_dir.X(), w_dir.Y(), w_dir.Z(), 0.0));
	cosTheta = ROOT::Math::VectorUtil::CosTheta(lepton_BosonFrame.Vect(), w_dir_Wframe.Vect());
    }
    else {std::cout << "Something went wrong" << std::endl;}

    // auto z_dibosonFrame = boostToWZFrame(zP4);
    // auto w_dibosonFrame = boostToWZFrame(w1P4_input);

    // double cosTheta = ROOT::Math::VectorUtil::CosTheta(lepton3_wframe, w_dibosonFrame);
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

    bool _long = false; 
    bool _trans = true;
    TFile *hfile = nullptr;
    /* Files: 
    longitudinal polarized: /afs/hep.wisc.edu/home/kmartine/Event_Generation/MG5_aMC_v3_6_7/ppToWZ_long/Events/run_01/tag_1_delphes_events.root 
    transverse polarized: /afs/hep.wisc.edu/home/kmartine/Event_Generation/MG5_aMC_v3_6_7/ppToWZ/Events/run_02/tag_1_delphes_events.root
    */
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
    TCanvas *c4 = new TCanvas("c4", "Canvas", 1200, 1000);
    TCanvas *c5 = new TCanvas("c5", "Canvas", 1200, 1000);
    std::cout << "3) Canvas made" << std::endl;

    //Create some histograms to fill with the branch in a loop over entries
    TH1F *hist_Z = new TH1F("Z Invariant Mass", "Z Invariant Mass", 50, 50, 200);
    TH1F *hist_cosThetaW = new TH1F("cos ThetaW", "cos ThetaW", 100, -1, 1);
    TH1F *hist_cosThetaZ = new TH1F("cos ThetaZ", "cos ThetaZ", 100, -1, 1);
    TH1F *hist_W = new TH1F("W Transverse Mass", "W Transverse Mass", 50, 50, 150);
    TH1F *hist_Zpt = new TH1F("Z Transverse Momentum", "Z Transverse Momentum", 50, 0, 250); 
    TH1F *hist_Zlep1_pt = new TH1F("Muon pT", "Muon Transverse Momentum", 50, 0, 250);
    TH1F *hist_Zlep2_pt = new TH1F("Muon pT", "Muon Transverse Momentum", 50, 0, 250);
    std::cout << "4) Making Histograms" << std::endl;

    int nEntries = tree->GetEntries();
    std::cout << "nEntries = " << nEntries << std::endl;
    for (int i=0; i<nEntries; i++){
        tree->GetEntry(i);
        std::cout << std::endl;
	std::cout << "nEntry = " << i << std::endl;
	bool foundZ = false; 
	bool foundW = false; 
        //////////////////
        // Z boson Info //
        //////////////////
        int nMuons = branchMuon->GetEntries();

        ROOT::Math::PtEtaPhiMVector v1(0, 0, 0, 0);
        ROOT::Math::PtEtaPhiMVector v2(0, 0, 0, 0);
        ROOT::Math::PtEtaPhiMVector Z(0, 0, 0, 0);
        std::cout << "Inside Muon loop: " << std::endl;
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

                // The two leptons that the Z boson decayed into: v1 is the lepton, v2 is the anti-lepton
		if (gen1->Charge < 0 && gen2->Charge > 0) {
                    v1 = ROOT::Math::PtEtaPhiMVector(mu1->PT, mu1->Eta, mu1->Phi, 0.105); // Muon
		    v2 = ROOT::Math::PtEtaPhiMVector(mu2->PT, mu2->Eta, mu2->Phi, 0.105); // Anti-Muon
                } 
		else if (gen1->Charge > 0 && gen2->Charge < 0) {
                    v1 = ROOT::Math::PtEtaPhiMVector(mu2->PT, mu2->Eta, mu2->Phi, 0.105); // Muon
		    v2 = ROOT::Math::PtEtaPhiMVector(mu1->PT, mu1->Eta, mu1->Phi, 0.105); // Anti-Muon
                }
                else {std::cout << "Something went wrong" << std::endl;}

                /*
                ROOT::Math::PtEtaPhiMVector v1(mu1->PT, mu1->Eta, mu1->Phi, 0.105);
                ROOT::Math::PtEtaPhiMVector v2(mu2->PT, mu2->Eta, mu2->Phi, 0.105);
                */

                Z = v1 + v2;
                foundZ = true;
            }
            if (foundZ) break;
        }

        std::cout << "Outside Muon Loop" << std::endl;
        //////////////////
        // W Boson Info //
        //////////////////
        int nElectrons = branchElectron->GetEntries();
	ROOT::Math::PtEtaPhiMVector lep1(0, 0, 0, 0);
	ROOT::Math::PtEtaPhiMVector nu2(0, 0, 0, 0);
	ROOT::Math::PtEtaPhiMVector W(0, 0, 0, 0);
        double w_mass = 0.0;
	std::cout << "Starting Electron Loop" << std::endl;
        for (int l = 0; l < nElectrons; l++) {
                
            Electron *el = (Electron*) branchElectron->At(l);
            GenParticle *genEl = (GenParticle*) el->Particle.GetObject(); // Get gen level data associated with el
            if (!genEl) continue; // make sure not a nullptr

            if (!checkMother(genEl, 24, branchParticle)) continue;

            // Reconstruct the W mass:
            // if (branchMissingET->GetEntries() == 0) continue; // Make sure the event had a neutrino

            MissingET *missingET = (MissingET*) branchMissingET->At(0);
     
            /*
            double w_mass = calculateW_MT(el->Phi, el->PT, missingET->MET, missingET->Phi);
            hist_W->Fill(w_mass);
            */

            w_mass = calculateW_MT(el->Phi, el->PT, missingET->MET, missingET->Phi);
            // I also need to create the 4-vector of the W boson
            lep1 = ROOT::Math::PtEtaPhiMVector(el->PT, el->Eta, el->Phi, 0);
            nu2 = ROOT::Math::PtEtaPhiMVector(missingET->MET, 0.0, missingET->Phi, 0);
            W = lep1 + nu2;
	    foundW = true;
            break;
	}
        ///////////////////////////////////////
        // Continue if W and Z were produced //
        ///////////////////////////////////////
	if (!foundZ || !foundW) continue; 
        std::cout << "Outside Electron Loop" << std::endl;

        /////////////////////
        // Fill Histograms //
        /////////////////////
        // (A) W Boson
	hist_W->Fill(w_mass);
	// (B) Z Boson
	hist_Z->Fill(Z.M());
	hist_Zpt->Fill(Z.Pt());
	hist_Zlep1_pt->Fill(v1.Pt());
	hist_Zlep2_pt->Fill(v2.Pt());
        // (C) cosTheta
	std::cout << "Starting cosTheta calculation" << std::endl;
	std::cout << "W = " << W << ", v1 = " << v1 << ", v2 = " << v2 << ", lep1 = " << lep1 << std::endl;
        double cosThetaW = costheta(W, v1, v2, lep1, true, false);
	std::cout << "cosTheta = " << cosThetaW << std::endl;
        hist_cosThetaW->Fill(cosThetaW);
	std::cout << "Z = " << Z << ", v1 = " << v1 << ", v2 = " << v2 << ", lep1 = " << lep1 << std::endl;
	double cosThetaZ = costheta(Z, v1, v2, lep1, false, true);
	std::cout << "cosTheta = " << cosThetaZ << std::endl;
        hist_cosThetaZ->Fill(cosThetaZ);
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
    hist_cosThetaW->Draw();
    hist_cosThetaZ->Draw("SAME");
    hist_cosThetaW->SetLineColor(kRed);
    hist_cosThetaW->SetTitle("In Diboson Frame");
    hist_cosThetaW->GetXaxis()->SetTitle("cos #theta (l,W)");
    hist_cosThetaZ->SetLineColor(kBlue);
    TLegend *leg1 = new TLegend(0.5, 0.8, 0.7, 0.9);
    leg1->AddEntry(hist_cosThetaW, "W Boson", "l");
    leg1->AddEntry(hist_cosThetaZ, "Z Boson", "l");
    leg1->Draw();
    if (_trans == true) c2->SaveAs("cosTheta_trans.pdf");
    if (_long == true) c2->SaveAs("cosTheta_long.pdf");

    c3->cd();
    hist_W->Draw();
    hist_W->GetXaxis()->SetTitle("Mass (GeV)");
    if (_trans == true) c3->SaveAs("W_mass_trans.pdf");
    if (_long == true) c3->SaveAs("W_mass_long.pdf");

    c4->cd();
    hist_Zpt->Draw();
    hist_Zpt->GetXaxis()->SetTitle("pT");
    if (_trans == true) c4->SaveAs("Z_pt_trans.pdf");
    if (_long == true) c4->SaveAs("Z_pt_long.pdf");

    c5->cd();
    hist_Zlep1_pt->Draw();
    hist_Zlep2_pt->Draw("SAME");
    hist_Zlep1_pt->SetLineColor(kRed);
    hist_Zlep2_pt->SetLineColor(kBlue);
    TLegend *leg2 = new TLegend(0.5, 0.8, 0.7, 0.9);
    leg2->AddEntry(hist_Zlep1_pt, "Muon", "l");
    leg2->AddEntry(hist_Zlep2_pt, "Anti-Muon", "l");
    leg2->Draw();
    hist_Zlep2_pt->GetXaxis()->SetTitle("p_T");
    if (_trans == true) c5->SaveAs("Z_lep_pt_trans.pdf");
    if (_long == true) c5->SaveAs("Z_lep_pt_long.pdf");

    std::cout << "Histogram saved" << std::endl;

    return 0;
}




