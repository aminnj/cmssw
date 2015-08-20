#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/METReco/interface/BeamHaloSummary.h"

class HcalHaloFilter : public edm::EDFilter {

  public:

    explicit HcalHaloFilter(const edm::ParameterSet & iConfig);
    ~HcalHaloFilter() {}

  private:

    virtual bool filter(edm::Event & iEvent, const edm::EventSetup & iSetup) override;

    const bool taggingMode_;
    const int maxStripLength_;
    edm::EDGetTokenT<reco::BeamHaloSummary> beamHaloSummaryToken_;
};

HcalHaloFilter::HcalHaloFilter(const edm::ParameterSet & iConfig)
  : taggingMode_     (iConfig.getParameter<bool> ("taggingMode"))
  , maxStripLength_   (iConfig.getParameter<int>("maxStripLength"))
  , beamHaloSummaryToken_(consumes<reco::BeamHaloSummary>(edm::InputTag("BeamHaloSummary")))
{
  produces<bool>();
}

bool HcalHaloFilter::filter(edm::Event & iEvent, const edm::EventSetup & iSetup) {

  edm::Handle<reco::BeamHaloSummary> beamHaloSummary;
  iEvent.getByToken(beamHaloSummaryToken_ , beamHaloSummary);

  // DEBUG XXX
  std::vector<std::vector<std::pair<int, CaloTowerDetId> > > probStrips = beamHaloSummary->GetProblematicStrips();
  for (unsigned int iStrip = 0; iStrip < probStrips.size(); iStrip++) {
    int numContiguousCells = 0;
    std::vector<std::pair<int,CaloTowerDetId> > probStrip = probStrips.at(iStrip);
    for (unsigned int iTower = 0; iTower < probStrip.size(); iTower++) {
      numContiguousCells += probStrip.at(iTower).first;
    }
    std::cout << "nCells: " << numContiguousCells << std::endl;
  }
  // DEBUG XXX

  bool pass = true;
  std::vector<std::vector<std::pair<int, CaloTowerDetId> > > problematicStrips = beamHaloSummary->GetProblematicStrips();
  for (unsigned int iStrip = 0; iStrip < problematicStrips.size(); iStrip++) {
    int numContiguousCells = 0;
    std::vector<std::pair<int,CaloTowerDetId> > problematicStrip = problematicStrips.at(iStrip);
    for (unsigned int iTower = 0; iTower < problematicStrip.size(); iTower++) {
      numContiguousCells += problematicStrip.at(iTower).first;
    }
    if(numContiguousCells > maxStripLength_) {
      pass = false;
      break;
    }
  }

  iEvent.put( std::auto_ptr<bool>(new bool(pass)) );

  return taggingMode_ || pass;  // return false if it is a beamhalo event
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(HcalHaloFilter);
