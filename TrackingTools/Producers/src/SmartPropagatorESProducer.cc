/** \class SmartPropagatorESProducer
 *  ES producer needed to put the SmartPropagator inside the EventSetup
 *
 *  \author R. Bellan - INFN Torino <riccardo.bellan@cern.ch>
 */

#include "FWCore/Framework/interface/ESProducer.h"

#include "TrackingTools/GeomPropagators/interface/SmartPropagator.h"
#include "DataFormats/TrajectorySeed/interface/PropagationDirection.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ModuleFactory.h"
#include "FWCore/Utilities/interface/Exception.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "TrackingTools/Records/interface/TrackingComponentsRecord.h"

#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"

#include <memory>

class SmartPropagatorESProducer : public edm::ESProducer {
public:
  /// Constructor
  SmartPropagatorESProducer(const edm::ParameterSet &);

  /// Destructor
  ~SmartPropagatorESProducer() override;

  // Operations
  std::unique_ptr<Propagator> produce(const TrackingComponentsRecord &);

private:
  PropagationDirection thePropagationDirection;
  std::string theTrackerPropagatorName;
  std::string theMuonPropagatorName;
  double theEpsilon;
};

using namespace edm;
using namespace std;

SmartPropagatorESProducer::SmartPropagatorESProducer(const ParameterSet& parameterSet) {
  string myname = parameterSet.getParameter<string>("ComponentName");

  string propDir = parameterSet.getParameter<string>("PropagationDirection");

  if (propDir == "oppositeToMomentum")
    thePropagationDirection = oppositeToMomentum;
  else if (propDir == "alongMomentum")
    thePropagationDirection = alongMomentum;
  else if (propDir == "anyDirection")
    thePropagationDirection = anyDirection;
  else
    throw cms::Exception("SmartPropagatorESProducer") << "Wrong fit direction chosen in SmartPropagatorESProducer";

  theEpsilon = parameterSet.getParameter<double>("Epsilon");

  theTrackerPropagatorName = parameterSet.getParameter<string>("TrackerPropagator");
  theMuonPropagatorName = parameterSet.getParameter<string>("MuonPropagator");

  setWhatProduced(this, myname);
}

SmartPropagatorESProducer::~SmartPropagatorESProducer() {}

std::unique_ptr<Propagator> SmartPropagatorESProducer::produce(const TrackingComponentsRecord& iRecord) {
  ESHandle<MagneticField> magField;
  iRecord.getRecord<IdealMagneticFieldRecord>().get(magField);

  ESHandle<Propagator> trackerPropagator;
  iRecord.get(theTrackerPropagatorName, trackerPropagator);

  ESHandle<Propagator> muonPropagator;
  iRecord.get(theMuonPropagatorName, muonPropagator);

  return std::make_unique<SmartPropagator>(
      *trackerPropagator, *muonPropagator, &*magField, thePropagationDirection, theEpsilon);
}

DEFINE_FWK_EVENTSETUP_MODULE(SmartPropagatorESProducer);
