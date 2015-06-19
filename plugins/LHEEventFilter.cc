// -*- C++ -*-
//
// Package:    MyAnalysis/LHEEventFilter
// Class:      LHEEventFilter
// 
/**\class LHEEventFilter LHEEventFilter.cc MyAnalysis/LHEEventFilter/plugins/LHEEventFilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Dinko Ferencek
//         Created:  Fri, 19 Jun 2015 23:15:13 GMT
//
//


// system include files
#include <memory>
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"

//
// class declaration
//

class LHEEventFilter : public edm::EDFilter {
   public:
      explicit LHEEventFilter(const edm::ParameterSet&);
      ~LHEEventFilter();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() override;
      virtual bool filter(edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      
      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
      const edm::InputTag  src_;
      const std::string    model_;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
LHEEventFilter::LHEEventFilter(const edm::ParameterSet& iConfig) :

  src_(iConfig.getParameter<edm::InputTag>("src")),
  model_(iConfig.getParameter<std::string> ("model"))

{
   //now do what ever initialization is needed

}


LHEEventFilter::~LHEEventFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
LHEEventFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  bool foundModel = false;

  edm::Handle<LHEEventProduct> product;
  iEvent.getByLabel(src_, product);

  for( LHEEventProduct::comments_const_iterator cit=product->comments_begin(); cit!=product->comments_end(); ++cit)
  {
    if( cit->find(model_.c_str()) != std::string::npos )
    {
      foundModel = true;
      break;
    }
  }

  return foundModel;
}

// ------------ method called once each job just before starting event loop  ------------
void 
LHEEventFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
LHEEventFilter::endJob() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
LHEEventFilter::beginRun(edm::Run const&, edm::EventSetup const&)
{ 
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
LHEEventFilter::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
LHEEventFilter::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
LHEEventFilter::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
LHEEventFilter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(LHEEventFilter);
