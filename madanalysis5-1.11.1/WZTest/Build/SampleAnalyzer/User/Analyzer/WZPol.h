#ifndef ANALYSIS_WZPOL_H
#define ANALYSIS_WZPOL_H

#include "SampleAnalyzer/Process/Analyzer/AnalyzerBase.h"
#include "SampleAnalyzer/Interfaces/root/RootMainHeaders.h"

namespace MA5
{
    class WZPol : public AnalyzerBase
    {
        INIT_ANALYSIS(WZPol, "WZPol")

        public:
            bool Initialize(const MA5::Configuration& cfg,
                            const std::map<std::string,std::string>& parameters);
            void Finalize(const SampleFormat& summary, const std::vector<SampleFormat>& files);
            bool Execute(SampleFormat& sample, const EventFormat& event);

        private:
	    TH1F* hist_cosThetaW;
	    TH1F* hist_cosThetaZ;
    };
}

#endif // ANALYSIS_WZPOL_H
