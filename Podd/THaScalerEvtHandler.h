#ifndef Podd_THaScalerEvtHandler_h_
#define Podd_THaScalerEvtHandler_h_

/////////////////////////////////////////////////////////////////////
//
//   THaScalerEvtHandler
//   Class to handle Hall A scaler events (type 140)
//   author  Robert Michaels (rom@jlab.org)
//
/////////////////////////////////////////////////////////////////////

#include "THaEvtTypeHandler.h"
#include "Decoder.h"
#include "TString.h"
#include <vector>

class TTree;

static const UInt_t ICOUNT    = 1;
static const UInt_t IRATE     = 2;
static const UInt_t MAXCHAN   = 32;
static const UInt_t MAXTEVT   = 5000;
static const UInt_t defaultDT = 4;

class ScalerLoc { // Utility class used by THaScalerEvtHandler
 public:
  ScalerLoc( TString nm, TString desc, Int_t idx, Int_t sl,
             Int_t ich, Int_t iki) :
    name(std::move(nm)), description(std::move(desc)), index(idx), islot(sl),
    ichan(ich),  ikind(iki) {};
  ~ScalerLoc() = default;
  TString name, description;
  Int_t index, islot, ichan, ikind;
};

class THaScalerEvtHandler : public THaEvtTypeHandler {

public:

  THaScalerEvtHandler(const char* name, const char* description);
  THaScalerEvtHandler(const THaScalerEvtHandler& fh) = delete;
  THaScalerEvtHandler& operator=(const THaScalerEvtHandler& fh) = delete;
  virtual ~THaScalerEvtHandler();

   virtual Int_t Analyze(THaEvData *evdata);
   virtual EStatus Init( const TDatime& run_time);
   virtual Int_t End( THaRunBase* r=0 );


protected:

   void AddVars(const TString& name, const TString& desc, Int_t iscal,
       Int_t ichan, Int_t ikind);
   void DefVars();

   std::vector<Decoder::GenScaler*> scalers;
   std::vector<ScalerLoc*> scalerloc;
   Double_t evcount;
   Int_t fNormIdx, fNormSlot;
   Double_t *dvars;
   TTree *fScalerTree;

   ClassDef(THaScalerEvtHandler,0)  // Scaler Event handler

};

#endif
