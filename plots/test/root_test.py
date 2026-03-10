import ROOT

# A: Get Files
file = ROOT.TFile.Open('/afs/hep.wisc.edu/home/kmartine/Event_Generation/MG5_aMC_v3_6_7/ppToZZ/Events/run_01/tag_1_delphes_events.root')
tree = file.Get("Delphes")

tree.Print()

# B: Get Particle Info
# i: Get pT Info
h_ept = ROOT.TH1F("h_ept", "Electron p_{T};p_{T} [GeV];Events", 50, 0, 200)
h_mupt = ROOT.TH1F("h_mupt", "Muon p_{T};p_{T} [GeV], Events", 50, 0, 200)

for event in tree: 
    for el in event.Electron.PT:
        h_ept.Fill(el)
    for mu in event.Muon.PT:
        h_mupt.Fill(mu)

# Note to self: I need to calculate mass using pT now (but that requires math)

# C: Get Plots
# i: Start with pT plots 
c1 = ROOT.TCanvas("c1", "Canvas", 800, 600)
h_ept.SetLineColor(ROOT.kBlue)
h_mupt.SetLineColor(ROOT.kRed)

h_ept.Draw()
h_mupt.Draw("SAME")

leg = ROOT.TLegend(0.65, 0.75, 0.88, 0.88)
leg.AddEntry(h_ept, "Z → e+e-", "l")
leg.AddEntry(h_mupt, "Z → mu+mu-", "l")
leg.Draw()

c1.SaveAs("pT_test.png")

print("Good so far")


