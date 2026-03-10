namespace std {}
using namespace std;
#include "libDirProjectHeaders.h"

#include "libDirLinkDef.h"

#include "libDirProjectDict.cxx"

struct DeleteObjectFunctor {
   template <typename T>
   void operator()(const T *ptr) const {
      delete ptr;
   }
   template <typename T, typename Q>
   void operator()(const std::pair<T,Q> &) const {
      // Do nothing
   }
   template <typename T, typename Q>
   void operator()(const std::pair<T,Q*> &ptr) const {
      delete ptr.second;
   }
   template <typename T, typename Q>
   void operator()(const std::pair<T*,Q> &ptr) const {
      delete ptr.first;
   }
   template <typename T, typename Q>
   void operator()(const std::pair<T*,Q*> &ptr) const {
      delete ptr.first;
      delete ptr.second;
   }
};

#ifndef HepMCEvent_cxx
#define HepMCEvent_cxx
HepMCEvent::HepMCEvent() {
}
HepMCEvent &HepMCEvent::operator=(const HepMCEvent & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   Event::operator=(const_cast<HepMCEvent &>( rhs ));
   ProcessID = (const_cast<HepMCEvent &>( rhs ).ProcessID);
   MPI = (const_cast<HepMCEvent &>( rhs ).MPI);
   Weight = (const_cast<HepMCEvent &>( rhs ).Weight);
   CrossSection = (const_cast<HepMCEvent &>( rhs ).CrossSection);
   CrossSectionError = (const_cast<HepMCEvent &>( rhs ).CrossSectionError);
   Scale = (const_cast<HepMCEvent &>( rhs ).Scale);
   AlphaQED = (const_cast<HepMCEvent &>( rhs ).AlphaQED);
   AlphaQCD = (const_cast<HepMCEvent &>( rhs ).AlphaQCD);
   ID1 = (const_cast<HepMCEvent &>( rhs ).ID1);
   ID2 = (const_cast<HepMCEvent &>( rhs ).ID2);
   X1 = (const_cast<HepMCEvent &>( rhs ).X1);
   X2 = (const_cast<HepMCEvent &>( rhs ).X2);
   ScalePDF = (const_cast<HepMCEvent &>( rhs ).ScalePDF);
   PDF1 = (const_cast<HepMCEvent &>( rhs ).PDF1);
   PDF2 = (const_cast<HepMCEvent &>( rhs ).PDF2);
   return *this;
}
HepMCEvent::HepMCEvent(const HepMCEvent & rhs)
   : Event(const_cast<HepMCEvent &>( rhs ))
   , ProcessID(const_cast<HepMCEvent &>( rhs ).ProcessID)
   , MPI(const_cast<HepMCEvent &>( rhs ).MPI)
   , Weight(const_cast<HepMCEvent &>( rhs ).Weight)
   , CrossSection(const_cast<HepMCEvent &>( rhs ).CrossSection)
   , CrossSectionError(const_cast<HepMCEvent &>( rhs ).CrossSectionError)
   , Scale(const_cast<HepMCEvent &>( rhs ).Scale)
   , AlphaQED(const_cast<HepMCEvent &>( rhs ).AlphaQED)
   , AlphaQCD(const_cast<HepMCEvent &>( rhs ).AlphaQCD)
   , ID1(const_cast<HepMCEvent &>( rhs ).ID1)
   , ID2(const_cast<HepMCEvent &>( rhs ).ID2)
   , X1(const_cast<HepMCEvent &>( rhs ).X1)
   , X2(const_cast<HepMCEvent &>( rhs ).X2)
   , ScalePDF(const_cast<HepMCEvent &>( rhs ).ScalePDF)
   , PDF1(const_cast<HepMCEvent &>( rhs ).PDF1)
   , PDF2(const_cast<HepMCEvent &>( rhs ).PDF2)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
}
HepMCEvent::~HepMCEvent() {
}
#endif // HepMCEvent_cxx

#ifndef Event_cxx
#define Event_cxx
Event::Event() {
}
Event &Event::operator=(const Event & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   TObject::operator=(const_cast<Event &>( rhs ));
   Number = (const_cast<Event &>( rhs ).Number);
   ReadTime = (const_cast<Event &>( rhs ).ReadTime);
   ProcTime = (const_cast<Event &>( rhs ).ProcTime);
   return *this;
}
Event::Event(const Event & rhs)
   : TObject(const_cast<Event &>( rhs ))
   , Number(const_cast<Event &>( rhs ).Number)
   , ReadTime(const_cast<Event &>( rhs ).ReadTime)
   , ProcTime(const_cast<Event &>( rhs ).ProcTime)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
}
Event::~Event() {
}
#endif // Event_cxx

#ifndef Weight_cxx
#define Weight_cxx
Weight::Weight() {
}
Weight &Weight::operator=(const Weight & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   TObject::operator=(const_cast<Weight &>( rhs ));
   Weight = (const_cast<Weight &>( rhs ).Weight);
   return *this;
}
Weight::Weight(const Weight & rhs)
   : TObject(const_cast<Weight &>( rhs ))
   , Weight(const_cast<Weight &>( rhs ).Weight)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
}
Weight::~Weight() {
}
#endif // Weight_cxx

#ifndef GenParticle_cxx
#define GenParticle_cxx
GenParticle::GenParticle() {
}
GenParticle &GenParticle::operator=(const GenParticle & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   SortableObject::operator=(const_cast<GenParticle &>( rhs ));
   PID = (const_cast<GenParticle &>( rhs ).PID);
   Status = (const_cast<GenParticle &>( rhs ).Status);
   IsPU = (const_cast<GenParticle &>( rhs ).IsPU);
   M1 = (const_cast<GenParticle &>( rhs ).M1);
   M2 = (const_cast<GenParticle &>( rhs ).M2);
   D1 = (const_cast<GenParticle &>( rhs ).D1);
   D2 = (const_cast<GenParticle &>( rhs ).D2);
   Charge = (const_cast<GenParticle &>( rhs ).Charge);
   Mass = (const_cast<GenParticle &>( rhs ).Mass);
   E = (const_cast<GenParticle &>( rhs ).E);
   Px = (const_cast<GenParticle &>( rhs ).Px);
   Py = (const_cast<GenParticle &>( rhs ).Py);
   Pz = (const_cast<GenParticle &>( rhs ).Pz);
   P = (const_cast<GenParticle &>( rhs ).P);
   PT = (const_cast<GenParticle &>( rhs ).PT);
   Eta = (const_cast<GenParticle &>( rhs ).Eta);
   Phi = (const_cast<GenParticle &>( rhs ).Phi);
   Rapidity = (const_cast<GenParticle &>( rhs ).Rapidity);
   T = (const_cast<GenParticle &>( rhs ).T);
   X = (const_cast<GenParticle &>( rhs ).X);
   Y = (const_cast<GenParticle &>( rhs ).Y);
   Z = (const_cast<GenParticle &>( rhs ).Z);
   return *this;
}
GenParticle::GenParticle(const GenParticle & rhs)
   : SortableObject(const_cast<GenParticle &>( rhs ))
   , PID(const_cast<GenParticle &>( rhs ).PID)
   , Status(const_cast<GenParticle &>( rhs ).Status)
   , IsPU(const_cast<GenParticle &>( rhs ).IsPU)
   , M1(const_cast<GenParticle &>( rhs ).M1)
   , M2(const_cast<GenParticle &>( rhs ).M2)
   , D1(const_cast<GenParticle &>( rhs ).D1)
   , D2(const_cast<GenParticle &>( rhs ).D2)
   , Charge(const_cast<GenParticle &>( rhs ).Charge)
   , Mass(const_cast<GenParticle &>( rhs ).Mass)
   , E(const_cast<GenParticle &>( rhs ).E)
   , Px(const_cast<GenParticle &>( rhs ).Px)
   , Py(const_cast<GenParticle &>( rhs ).Py)
   , Pz(const_cast<GenParticle &>( rhs ).Pz)
   , P(const_cast<GenParticle &>( rhs ).P)
   , PT(const_cast<GenParticle &>( rhs ).PT)
   , Eta(const_cast<GenParticle &>( rhs ).Eta)
   , Phi(const_cast<GenParticle &>( rhs ).Phi)
   , Rapidity(const_cast<GenParticle &>( rhs ).Rapidity)
   , T(const_cast<GenParticle &>( rhs ).T)
   , X(const_cast<GenParticle &>( rhs ).X)
   , Y(const_cast<GenParticle &>( rhs ).Y)
   , Z(const_cast<GenParticle &>( rhs ).Z)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
}
GenParticle::~GenParticle() {
}
#endif // GenParticle_cxx

#ifndef SortableObject_cxx
#define SortableObject_cxx
SortableObject::SortableObject() {
}
SortableObject &SortableObject::operator=(const SortableObject & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   TObject::operator=(const_cast<SortableObject &>( rhs ));
   return *this;
}
SortableObject::SortableObject(const SortableObject & rhs)
   : TObject(const_cast<SortableObject &>( rhs ))
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
}
SortableObject::~SortableObject() {
}
#endif // SortableObject_cxx

#ifndef Track_cxx
#define Track_cxx
Track::Track() {
}
Track &Track::operator=(const Track & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   SortableObject::operator=(const_cast<Track &>( rhs ));
   PID = (const_cast<Track &>( rhs ).PID);
   Charge = (const_cast<Track &>( rhs ).Charge);
   IsPU = (const_cast<Track &>( rhs ).IsPU);
   IsRecoPU = (const_cast<Track &>( rhs ).IsRecoPU);
   HardEnergyFraction = (const_cast<Track &>( rhs ).HardEnergyFraction);
   P = (const_cast<Track &>( rhs ).P);
   PT = (const_cast<Track &>( rhs ).PT);
   Eta = (const_cast<Track &>( rhs ).Eta);
   Phi = (const_cast<Track &>( rhs ).Phi);
   CtgTheta = (const_cast<Track &>( rhs ).CtgTheta);
   C = (const_cast<Track &>( rhs ).C);
   Mass = (const_cast<Track &>( rhs ).Mass);
   EtaOuter = (const_cast<Track &>( rhs ).EtaOuter);
   PhiOuter = (const_cast<Track &>( rhs ).PhiOuter);
   T = (const_cast<Track &>( rhs ).T);
   X = (const_cast<Track &>( rhs ).X);
   Y = (const_cast<Track &>( rhs ).Y);
   Z = (const_cast<Track &>( rhs ).Z);
   TOuter = (const_cast<Track &>( rhs ).TOuter);
   XOuter = (const_cast<Track &>( rhs ).XOuter);
   YOuter = (const_cast<Track &>( rhs ).YOuter);
   ZOuter = (const_cast<Track &>( rhs ).ZOuter);
   Xd = (const_cast<Track &>( rhs ).Xd);
   Yd = (const_cast<Track &>( rhs ).Yd);
   Zd = (const_cast<Track &>( rhs ).Zd);
   XFirstHit = (const_cast<Track &>( rhs ).XFirstHit);
   YFirstHit = (const_cast<Track &>( rhs ).YFirstHit);
   ZFirstHit = (const_cast<Track &>( rhs ).ZFirstHit);
   L = (const_cast<Track &>( rhs ).L);
   D0 = (const_cast<Track &>( rhs ).D0);
   DZ = (const_cast<Track &>( rhs ).DZ);
   Nclusters = (const_cast<Track &>( rhs ).Nclusters);
   dNdx = (const_cast<Track &>( rhs ).dNdx);
   ErrorP = (const_cast<Track &>( rhs ).ErrorP);
   ErrorPT = (const_cast<Track &>( rhs ).ErrorPT);
   ErrorPhi = (const_cast<Track &>( rhs ).ErrorPhi);
   ErrorCtgTheta = (const_cast<Track &>( rhs ).ErrorCtgTheta);
   ErrorT = (const_cast<Track &>( rhs ).ErrorT);
   ErrorD0 = (const_cast<Track &>( rhs ).ErrorD0);
   ErrorDZ = (const_cast<Track &>( rhs ).ErrorDZ);
   ErrorC = (const_cast<Track &>( rhs ).ErrorC);
   ErrorD0Phi = (const_cast<Track &>( rhs ).ErrorD0Phi);
   ErrorD0C = (const_cast<Track &>( rhs ).ErrorD0C);
   ErrorD0DZ = (const_cast<Track &>( rhs ).ErrorD0DZ);
   ErrorD0CtgTheta = (const_cast<Track &>( rhs ).ErrorD0CtgTheta);
   ErrorPhiC = (const_cast<Track &>( rhs ).ErrorPhiC);
   ErrorPhiDZ = (const_cast<Track &>( rhs ).ErrorPhiDZ);
   ErrorPhiCtgTheta = (const_cast<Track &>( rhs ).ErrorPhiCtgTheta);
   ErrorCDZ = (const_cast<Track &>( rhs ).ErrorCDZ);
   ErrorCCtgTheta = (const_cast<Track &>( rhs ).ErrorCCtgTheta);
   ErrorDZCtgTheta = (const_cast<Track &>( rhs ).ErrorDZCtgTheta);
   Particle = (const_cast<Track &>( rhs ).Particle);
   VertexIndex = (const_cast<Track &>( rhs ).VertexIndex);
   return *this;
}
Track::Track(const Track & rhs)
   : SortableObject(const_cast<Track &>( rhs ))
   , PID(const_cast<Track &>( rhs ).PID)
   , Charge(const_cast<Track &>( rhs ).Charge)
   , IsPU(const_cast<Track &>( rhs ).IsPU)
   , IsRecoPU(const_cast<Track &>( rhs ).IsRecoPU)
   , HardEnergyFraction(const_cast<Track &>( rhs ).HardEnergyFraction)
   , P(const_cast<Track &>( rhs ).P)
   , PT(const_cast<Track &>( rhs ).PT)
   , Eta(const_cast<Track &>( rhs ).Eta)
   , Phi(const_cast<Track &>( rhs ).Phi)
   , CtgTheta(const_cast<Track &>( rhs ).CtgTheta)
   , C(const_cast<Track &>( rhs ).C)
   , Mass(const_cast<Track &>( rhs ).Mass)
   , EtaOuter(const_cast<Track &>( rhs ).EtaOuter)
   , PhiOuter(const_cast<Track &>( rhs ).PhiOuter)
   , T(const_cast<Track &>( rhs ).T)
   , X(const_cast<Track &>( rhs ).X)
   , Y(const_cast<Track &>( rhs ).Y)
   , Z(const_cast<Track &>( rhs ).Z)
   , TOuter(const_cast<Track &>( rhs ).TOuter)
   , XOuter(const_cast<Track &>( rhs ).XOuter)
   , YOuter(const_cast<Track &>( rhs ).YOuter)
   , ZOuter(const_cast<Track &>( rhs ).ZOuter)
   , Xd(const_cast<Track &>( rhs ).Xd)
   , Yd(const_cast<Track &>( rhs ).Yd)
   , Zd(const_cast<Track &>( rhs ).Zd)
   , XFirstHit(const_cast<Track &>( rhs ).XFirstHit)
   , YFirstHit(const_cast<Track &>( rhs ).YFirstHit)
   , ZFirstHit(const_cast<Track &>( rhs ).ZFirstHit)
   , L(const_cast<Track &>( rhs ).L)
   , D0(const_cast<Track &>( rhs ).D0)
   , DZ(const_cast<Track &>( rhs ).DZ)
   , Nclusters(const_cast<Track &>( rhs ).Nclusters)
   , dNdx(const_cast<Track &>( rhs ).dNdx)
   , ErrorP(const_cast<Track &>( rhs ).ErrorP)
   , ErrorPT(const_cast<Track &>( rhs ).ErrorPT)
   , ErrorPhi(const_cast<Track &>( rhs ).ErrorPhi)
   , ErrorCtgTheta(const_cast<Track &>( rhs ).ErrorCtgTheta)
   , ErrorT(const_cast<Track &>( rhs ).ErrorT)
   , ErrorD0(const_cast<Track &>( rhs ).ErrorD0)
   , ErrorDZ(const_cast<Track &>( rhs ).ErrorDZ)
   , ErrorC(const_cast<Track &>( rhs ).ErrorC)
   , ErrorD0Phi(const_cast<Track &>( rhs ).ErrorD0Phi)
   , ErrorD0C(const_cast<Track &>( rhs ).ErrorD0C)
   , ErrorD0DZ(const_cast<Track &>( rhs ).ErrorD0DZ)
   , ErrorD0CtgTheta(const_cast<Track &>( rhs ).ErrorD0CtgTheta)
   , ErrorPhiC(const_cast<Track &>( rhs ).ErrorPhiC)
   , ErrorPhiDZ(const_cast<Track &>( rhs ).ErrorPhiDZ)
   , ErrorPhiCtgTheta(const_cast<Track &>( rhs ).ErrorPhiCtgTheta)
   , ErrorCDZ(const_cast<Track &>( rhs ).ErrorCDZ)
   , ErrorCCtgTheta(const_cast<Track &>( rhs ).ErrorCCtgTheta)
   , ErrorDZCtgTheta(const_cast<Track &>( rhs ).ErrorDZCtgTheta)
   , Particle(const_cast<Track &>( rhs ).Particle)
   , VertexIndex(const_cast<Track &>( rhs ).VertexIndex)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
}
Track::~Track() {
}
#endif // Track_cxx

#ifndef Tower_cxx
#define Tower_cxx
Tower::Tower() {
}
Tower &Tower::operator=(const Tower & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   SortableObject::operator=(const_cast<Tower &>( rhs ));
   ET = (const_cast<Tower &>( rhs ).ET);
   Eta = (const_cast<Tower &>( rhs ).Eta);
   Phi = (const_cast<Tower &>( rhs ).Phi);
   E = (const_cast<Tower &>( rhs ).E);
   T = (const_cast<Tower &>( rhs ).T);
   X = (const_cast<Tower &>( rhs ).X);
   Y = (const_cast<Tower &>( rhs ).Y);
   Z = (const_cast<Tower &>( rhs ).Z);
   NTimeHits = (const_cast<Tower &>( rhs ).NTimeHits);
   Eem = (const_cast<Tower &>( rhs ).Eem);
   Ehad = (const_cast<Tower &>( rhs ).Ehad);
   Etrk = (const_cast<Tower &>( rhs ).Etrk);
   IsPU = (const_cast<Tower &>( rhs ).IsPU);
   IsRecoPU = (const_cast<Tower &>( rhs ).IsRecoPU);
   HardEnergyFraction = (const_cast<Tower &>( rhs ).HardEnergyFraction);
   Particles = (const_cast<Tower &>( rhs ).Particles);
   for (Int_t i=0;i<4;i++) Edges[i] = rhs.Edges[i];
   return *this;
}
Tower::Tower(const Tower & rhs)
   : SortableObject(const_cast<Tower &>( rhs ))
   , ET(const_cast<Tower &>( rhs ).ET)
   , Eta(const_cast<Tower &>( rhs ).Eta)
   , Phi(const_cast<Tower &>( rhs ).Phi)
   , E(const_cast<Tower &>( rhs ).E)
   , T(const_cast<Tower &>( rhs ).T)
   , X(const_cast<Tower &>( rhs ).X)
   , Y(const_cast<Tower &>( rhs ).Y)
   , Z(const_cast<Tower &>( rhs ).Z)
   , NTimeHits(const_cast<Tower &>( rhs ).NTimeHits)
   , Eem(const_cast<Tower &>( rhs ).Eem)
   , Ehad(const_cast<Tower &>( rhs ).Ehad)
   , Etrk(const_cast<Tower &>( rhs ).Etrk)
   , IsPU(const_cast<Tower &>( rhs ).IsPU)
   , IsRecoPU(const_cast<Tower &>( rhs ).IsRecoPU)
   , HardEnergyFraction(const_cast<Tower &>( rhs ).HardEnergyFraction)
   , Particles(const_cast<Tower &>( rhs ).Particles)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   for (Int_t i=0;i<4;i++) Edges[i] = rhs.Edges[i];
}
Tower::~Tower() {
}
#endif // Tower_cxx

#ifndef Jet_cxx
#define Jet_cxx
Jet::Jet() {
}
Jet &Jet::operator=(const Jet & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   SortableObject::operator=(const_cast<Jet &>( rhs ));
   PT = (const_cast<Jet &>( rhs ).PT);
   Eta = (const_cast<Jet &>( rhs ).Eta);
   Phi = (const_cast<Jet &>( rhs ).Phi);
   T = (const_cast<Jet &>( rhs ).T);
   Mass = (const_cast<Jet &>( rhs ).Mass);
   DeltaEta = (const_cast<Jet &>( rhs ).DeltaEta);
   DeltaPhi = (const_cast<Jet &>( rhs ).DeltaPhi);
   Flavor = (const_cast<Jet &>( rhs ).Flavor);
   FlavorAlgo = (const_cast<Jet &>( rhs ).FlavorAlgo);
   FlavorPhys = (const_cast<Jet &>( rhs ).FlavorPhys);
   TauFlavor = (const_cast<Jet &>( rhs ).TauFlavor);
   BTag = (const_cast<Jet &>( rhs ).BTag);
   BTagAlgo = (const_cast<Jet &>( rhs ).BTagAlgo);
   BTagPhys = (const_cast<Jet &>( rhs ).BTagPhys);
   TauTag = (const_cast<Jet &>( rhs ).TauTag);
   TauWeight = (const_cast<Jet &>( rhs ).TauWeight);
   Charge = (const_cast<Jet &>( rhs ).Charge);
   EhadOverEem = (const_cast<Jet &>( rhs ).EhadOverEem);
   NCharged = (const_cast<Jet &>( rhs ).NCharged);
   NNeutrals = (const_cast<Jet &>( rhs ).NNeutrals);
   NeutralEnergyFraction = (const_cast<Jet &>( rhs ).NeutralEnergyFraction);
   ChargedEnergyFraction = (const_cast<Jet &>( rhs ).ChargedEnergyFraction);
   Beta = (const_cast<Jet &>( rhs ).Beta);
   BetaStar = (const_cast<Jet &>( rhs ).BetaStar);
   MeanSqDeltaR = (const_cast<Jet &>( rhs ).MeanSqDeltaR);
   PTD = (const_cast<Jet &>( rhs ).PTD);
   SoftDroppedJet = (const_cast<Jet &>( rhs ).SoftDroppedJet);
   SoftDroppedSubJet1 = (const_cast<Jet &>( rhs ).SoftDroppedSubJet1);
   SoftDroppedSubJet2 = (const_cast<Jet &>( rhs ).SoftDroppedSubJet2);
   NSubJetsTrimmed = (const_cast<Jet &>( rhs ).NSubJetsTrimmed);
   NSubJetsPruned = (const_cast<Jet &>( rhs ).NSubJetsPruned);
   NSubJetsSoftDropped = (const_cast<Jet &>( rhs ).NSubJetsSoftDropped);
   ExclYmerge12 = (const_cast<Jet &>( rhs ).ExclYmerge12);
   ExclYmerge23 = (const_cast<Jet &>( rhs ).ExclYmerge23);
   ExclYmerge34 = (const_cast<Jet &>( rhs ).ExclYmerge34);
   ExclYmerge45 = (const_cast<Jet &>( rhs ).ExclYmerge45);
   ExclYmerge56 = (const_cast<Jet &>( rhs ).ExclYmerge56);
   Constituents = (const_cast<Jet &>( rhs ).Constituents);
   Particles = (const_cast<Jet &>( rhs ).Particles);
   Area = (const_cast<Jet &>( rhs ).Area);
   for (Int_t i=0;i<5;i++) FracPt[i] = rhs.FracPt[i];
   for (Int_t i=0;i<5;i++) Tau[i] = rhs.Tau[i];
   for (Int_t i=0;i<5;i++) TrimmedP4[i] = rhs.TrimmedP4[i];
   for (Int_t i=0;i<5;i++) PrunedP4[i] = rhs.PrunedP4[i];
   for (Int_t i=0;i<5;i++) SoftDroppedP4[i] = rhs.SoftDroppedP4[i];
   return *this;
}
Jet::Jet(const Jet & rhs)
   : SortableObject(const_cast<Jet &>( rhs ))
   , PT(const_cast<Jet &>( rhs ).PT)
   , Eta(const_cast<Jet &>( rhs ).Eta)
   , Phi(const_cast<Jet &>( rhs ).Phi)
   , T(const_cast<Jet &>( rhs ).T)
   , Mass(const_cast<Jet &>( rhs ).Mass)
   , DeltaEta(const_cast<Jet &>( rhs ).DeltaEta)
   , DeltaPhi(const_cast<Jet &>( rhs ).DeltaPhi)
   , Flavor(const_cast<Jet &>( rhs ).Flavor)
   , FlavorAlgo(const_cast<Jet &>( rhs ).FlavorAlgo)
   , FlavorPhys(const_cast<Jet &>( rhs ).FlavorPhys)
   , TauFlavor(const_cast<Jet &>( rhs ).TauFlavor)
   , BTag(const_cast<Jet &>( rhs ).BTag)
   , BTagAlgo(const_cast<Jet &>( rhs ).BTagAlgo)
   , BTagPhys(const_cast<Jet &>( rhs ).BTagPhys)
   , TauTag(const_cast<Jet &>( rhs ).TauTag)
   , TauWeight(const_cast<Jet &>( rhs ).TauWeight)
   , Charge(const_cast<Jet &>( rhs ).Charge)
   , EhadOverEem(const_cast<Jet &>( rhs ).EhadOverEem)
   , NCharged(const_cast<Jet &>( rhs ).NCharged)
   , NNeutrals(const_cast<Jet &>( rhs ).NNeutrals)
   , NeutralEnergyFraction(const_cast<Jet &>( rhs ).NeutralEnergyFraction)
   , ChargedEnergyFraction(const_cast<Jet &>( rhs ).ChargedEnergyFraction)
   , Beta(const_cast<Jet &>( rhs ).Beta)
   , BetaStar(const_cast<Jet &>( rhs ).BetaStar)
   , MeanSqDeltaR(const_cast<Jet &>( rhs ).MeanSqDeltaR)
   , PTD(const_cast<Jet &>( rhs ).PTD)
   , SoftDroppedJet(const_cast<Jet &>( rhs ).SoftDroppedJet)
   , SoftDroppedSubJet1(const_cast<Jet &>( rhs ).SoftDroppedSubJet1)
   , SoftDroppedSubJet2(const_cast<Jet &>( rhs ).SoftDroppedSubJet2)
   , NSubJetsTrimmed(const_cast<Jet &>( rhs ).NSubJetsTrimmed)
   , NSubJetsPruned(const_cast<Jet &>( rhs ).NSubJetsPruned)
   , NSubJetsSoftDropped(const_cast<Jet &>( rhs ).NSubJetsSoftDropped)
   , ExclYmerge12(const_cast<Jet &>( rhs ).ExclYmerge12)
   , ExclYmerge23(const_cast<Jet &>( rhs ).ExclYmerge23)
   , ExclYmerge34(const_cast<Jet &>( rhs ).ExclYmerge34)
   , ExclYmerge45(const_cast<Jet &>( rhs ).ExclYmerge45)
   , ExclYmerge56(const_cast<Jet &>( rhs ).ExclYmerge56)
   , Constituents(const_cast<Jet &>( rhs ).Constituents)
   , Particles(const_cast<Jet &>( rhs ).Particles)
   , Area(const_cast<Jet &>( rhs ).Area)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   for (Int_t i=0;i<5;i++) FracPt[i] = rhs.FracPt[i];
   for (Int_t i=0;i<5;i++) Tau[i] = rhs.Tau[i];
   for (Int_t i=0;i<5;i++) TrimmedP4[i] = rhs.TrimmedP4[i];
   for (Int_t i=0;i<5;i++) PrunedP4[i] = rhs.PrunedP4[i];
   for (Int_t i=0;i<5;i++) SoftDroppedP4[i] = rhs.SoftDroppedP4[i];
}
Jet::~Jet() {
}
#endif // Jet_cxx

#ifndef MissingET_cxx
#define MissingET_cxx
MissingET::MissingET() {
}
MissingET &MissingET::operator=(const MissingET & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   TObject::operator=(const_cast<MissingET &>( rhs ));
   MET = (const_cast<MissingET &>( rhs ).MET);
   Eta = (const_cast<MissingET &>( rhs ).Eta);
   Phi = (const_cast<MissingET &>( rhs ).Phi);
   return *this;
}
MissingET::MissingET(const MissingET & rhs)
   : TObject(const_cast<MissingET &>( rhs ))
   , MET(const_cast<MissingET &>( rhs ).MET)
   , Eta(const_cast<MissingET &>( rhs ).Eta)
   , Phi(const_cast<MissingET &>( rhs ).Phi)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
}
MissingET::~MissingET() {
}
#endif // MissingET_cxx

#ifndef Electron_cxx
#define Electron_cxx
Electron::Electron() {
}
Electron &Electron::operator=(const Electron & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   SortableObject::operator=(const_cast<Electron &>( rhs ));
   PT = (const_cast<Electron &>( rhs ).PT);
   Eta = (const_cast<Electron &>( rhs ).Eta);
   Phi = (const_cast<Electron &>( rhs ).Phi);
   T = (const_cast<Electron &>( rhs ).T);
   Charge = (const_cast<Electron &>( rhs ).Charge);
   EhadOverEem = (const_cast<Electron &>( rhs ).EhadOverEem);
   Particle = (const_cast<Electron &>( rhs ).Particle);
   IsolationVar = (const_cast<Electron &>( rhs ).IsolationVar);
   IsolationVarRhoCorr = (const_cast<Electron &>( rhs ).IsolationVarRhoCorr);
   SumPtCharged = (const_cast<Electron &>( rhs ).SumPtCharged);
   SumPtNeutral = (const_cast<Electron &>( rhs ).SumPtNeutral);
   SumPtChargedPU = (const_cast<Electron &>( rhs ).SumPtChargedPU);
   SumPt = (const_cast<Electron &>( rhs ).SumPt);
   D0 = (const_cast<Electron &>( rhs ).D0);
   DZ = (const_cast<Electron &>( rhs ).DZ);
   ErrorD0 = (const_cast<Electron &>( rhs ).ErrorD0);
   ErrorDZ = (const_cast<Electron &>( rhs ).ErrorDZ);
   return *this;
}
Electron::Electron(const Electron & rhs)
   : SortableObject(const_cast<Electron &>( rhs ))
   , PT(const_cast<Electron &>( rhs ).PT)
   , Eta(const_cast<Electron &>( rhs ).Eta)
   , Phi(const_cast<Electron &>( rhs ).Phi)
   , T(const_cast<Electron &>( rhs ).T)
   , Charge(const_cast<Electron &>( rhs ).Charge)
   , EhadOverEem(const_cast<Electron &>( rhs ).EhadOverEem)
   , Particle(const_cast<Electron &>( rhs ).Particle)
   , IsolationVar(const_cast<Electron &>( rhs ).IsolationVar)
   , IsolationVarRhoCorr(const_cast<Electron &>( rhs ).IsolationVarRhoCorr)
   , SumPtCharged(const_cast<Electron &>( rhs ).SumPtCharged)
   , SumPtNeutral(const_cast<Electron &>( rhs ).SumPtNeutral)
   , SumPtChargedPU(const_cast<Electron &>( rhs ).SumPtChargedPU)
   , SumPt(const_cast<Electron &>( rhs ).SumPt)
   , D0(const_cast<Electron &>( rhs ).D0)
   , DZ(const_cast<Electron &>( rhs ).DZ)
   , ErrorD0(const_cast<Electron &>( rhs ).ErrorD0)
   , ErrorDZ(const_cast<Electron &>( rhs ).ErrorDZ)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
}
Electron::~Electron() {
}
#endif // Electron_cxx

#ifndef Photon_cxx
#define Photon_cxx
Photon::Photon() {
}
Photon &Photon::operator=(const Photon & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   SortableObject::operator=(const_cast<Photon &>( rhs ));
   PT = (const_cast<Photon &>( rhs ).PT);
   Eta = (const_cast<Photon &>( rhs ).Eta);
   Phi = (const_cast<Photon &>( rhs ).Phi);
   E = (const_cast<Photon &>( rhs ).E);
   T = (const_cast<Photon &>( rhs ).T);
   EhadOverEem = (const_cast<Photon &>( rhs ).EhadOverEem);
   Particles = (const_cast<Photon &>( rhs ).Particles);
   IsolationVar = (const_cast<Photon &>( rhs ).IsolationVar);
   IsolationVarRhoCorr = (const_cast<Photon &>( rhs ).IsolationVarRhoCorr);
   SumPtCharged = (const_cast<Photon &>( rhs ).SumPtCharged);
   SumPtNeutral = (const_cast<Photon &>( rhs ).SumPtNeutral);
   SumPtChargedPU = (const_cast<Photon &>( rhs ).SumPtChargedPU);
   SumPt = (const_cast<Photon &>( rhs ).SumPt);
   Status = (const_cast<Photon &>( rhs ).Status);
   return *this;
}
Photon::Photon(const Photon & rhs)
   : SortableObject(const_cast<Photon &>( rhs ))
   , PT(const_cast<Photon &>( rhs ).PT)
   , Eta(const_cast<Photon &>( rhs ).Eta)
   , Phi(const_cast<Photon &>( rhs ).Phi)
   , E(const_cast<Photon &>( rhs ).E)
   , T(const_cast<Photon &>( rhs ).T)
   , EhadOverEem(const_cast<Photon &>( rhs ).EhadOverEem)
   , Particles(const_cast<Photon &>( rhs ).Particles)
   , IsolationVar(const_cast<Photon &>( rhs ).IsolationVar)
   , IsolationVarRhoCorr(const_cast<Photon &>( rhs ).IsolationVarRhoCorr)
   , SumPtCharged(const_cast<Photon &>( rhs ).SumPtCharged)
   , SumPtNeutral(const_cast<Photon &>( rhs ).SumPtNeutral)
   , SumPtChargedPU(const_cast<Photon &>( rhs ).SumPtChargedPU)
   , SumPt(const_cast<Photon &>( rhs ).SumPt)
   , Status(const_cast<Photon &>( rhs ).Status)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
}
Photon::~Photon() {
}
#endif // Photon_cxx

#ifndef Muon_cxx
#define Muon_cxx
Muon::Muon() {
}
Muon &Muon::operator=(const Muon & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   SortableObject::operator=(const_cast<Muon &>( rhs ));
   PT = (const_cast<Muon &>( rhs ).PT);
   Eta = (const_cast<Muon &>( rhs ).Eta);
   Phi = (const_cast<Muon &>( rhs ).Phi);
   T = (const_cast<Muon &>( rhs ).T);
   Charge = (const_cast<Muon &>( rhs ).Charge);
   Particle = (const_cast<Muon &>( rhs ).Particle);
   IsolationVar = (const_cast<Muon &>( rhs ).IsolationVar);
   IsolationVarRhoCorr = (const_cast<Muon &>( rhs ).IsolationVarRhoCorr);
   SumPtCharged = (const_cast<Muon &>( rhs ).SumPtCharged);
   SumPtNeutral = (const_cast<Muon &>( rhs ).SumPtNeutral);
   SumPtChargedPU = (const_cast<Muon &>( rhs ).SumPtChargedPU);
   SumPt = (const_cast<Muon &>( rhs ).SumPt);
   D0 = (const_cast<Muon &>( rhs ).D0);
   DZ = (const_cast<Muon &>( rhs ).DZ);
   ErrorD0 = (const_cast<Muon &>( rhs ).ErrorD0);
   ErrorDZ = (const_cast<Muon &>( rhs ).ErrorDZ);
   return *this;
}
Muon::Muon(const Muon & rhs)
   : SortableObject(const_cast<Muon &>( rhs ))
   , PT(const_cast<Muon &>( rhs ).PT)
   , Eta(const_cast<Muon &>( rhs ).Eta)
   , Phi(const_cast<Muon &>( rhs ).Phi)
   , T(const_cast<Muon &>( rhs ).T)
   , Charge(const_cast<Muon &>( rhs ).Charge)
   , Particle(const_cast<Muon &>( rhs ).Particle)
   , IsolationVar(const_cast<Muon &>( rhs ).IsolationVar)
   , IsolationVarRhoCorr(const_cast<Muon &>( rhs ).IsolationVarRhoCorr)
   , SumPtCharged(const_cast<Muon &>( rhs ).SumPtCharged)
   , SumPtNeutral(const_cast<Muon &>( rhs ).SumPtNeutral)
   , SumPtChargedPU(const_cast<Muon &>( rhs ).SumPtChargedPU)
   , SumPt(const_cast<Muon &>( rhs ).SumPt)
   , D0(const_cast<Muon &>( rhs ).D0)
   , DZ(const_cast<Muon &>( rhs ).DZ)
   , ErrorD0(const_cast<Muon &>( rhs ).ErrorD0)
   , ErrorDZ(const_cast<Muon &>( rhs ).ErrorDZ)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
}
Muon::~Muon() {
}
#endif // Muon_cxx

#ifndef ScalarHT_cxx
#define ScalarHT_cxx
ScalarHT::ScalarHT() {
}
ScalarHT &ScalarHT::operator=(const ScalarHT & rhs)
{
   // This is NOT a copy operator=. This is actually a move operator= (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
   TObject::operator=(const_cast<ScalarHT &>( rhs ));
   HT = (const_cast<ScalarHT &>( rhs ).HT);
   return *this;
}
ScalarHT::ScalarHT(const ScalarHT & rhs)
   : TObject(const_cast<ScalarHT &>( rhs ))
   , HT(const_cast<ScalarHT &>( rhs ).HT)
{
   // This is NOT a copy constructor. This is actually a move constructor (for stl container's sake).
   // Use at your own risk!
   (void)rhs; // avoid warning about unused parameter
}
ScalarHT::~ScalarHT() {
}
#endif // ScalarHT_cxx

