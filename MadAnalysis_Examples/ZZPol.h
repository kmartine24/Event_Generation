#ifndef analysis_ZZPol_h
#define analysis_ZZPol_h

#include "SampleAnalyzer/Process/Analyzer/AnalyzerBase.h"
// The following line was added for my analysis
#include "SampleAnalyzer/Interfaces/root/RootMainHeaders.h"


namespace MA5
{
class ZZPol: public AnalyzerBase
{
  INIT_ANALYSIS(ZZPol,"ZZPol")

 public:
  virtual bool Initialize(const MA5::Configuration& cfg, const std::map<std::string,std::string>& parameters);
  virtual void Finalize(const SampleFormat& summary, const std::vector<SampleFormat>& files);
  virtual bool Execute(SampleFormat& sample, const EventFormat& event);

 private:
  // The following line is required for a root histogram output. The name of the histogram (myHisto) must match the name of the histogram declared in the .cpp file
  TH1F* myHisto;
};
}

#endif
