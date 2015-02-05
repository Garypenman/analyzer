#ifndef GenScaler_
#define GenScaler_

/////////////////////////////////////////////////////////////////////
//
//   GenScaler
//   Generic scaler.  
//
/////////////////////////////////////////////////////////////////////

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include "Rtypes.h"
#include "VmeModule.h"
#include "Decoder.h"

const int DEFAULT_DELTAT = 4;

class Decoder::GenScaler : public VmeModule {

public:

   GenScaler() {};  
   GenScaler(Int_t crate, Int_t slot);  
   virtual ~GenScaler();  

   virtual void Init() { return; };  // derived classes should implement
   void GenInit();
   Int_t SetClock(Double_t deltaT, Int_t clockchan=0, Double_t clockrate=0);
   using Module::Decode;
   Int_t Decode(const Int_t *evbuffer);
   using Module::GetData;
   Int_t GetData(Int_t chan);   // Raw scaler counts
   Double_t GetRate(Int_t chan);  // Scaler rate
   Double_t GetTimeSincePrev();  // returns deltaT since last reading
   void Clear(const Option_t *opt) { fIsDecoded=kFALSE; };
   Bool_t IsDecoded() { return fIsDecoded; };
   using VmeModule::IsSlot;
   Bool_t IsSlot(Int_t rdata);
   void LoadNormScaler(GenScaler *scal);  // loads pointer to norm. scaler
   void DoPrint();
   void DebugPrint(ofstream *file=0);

// Loads sldat 
  virtual Int_t LoadSlot(THaSlotData *sldat,  const UInt_t *evbuffer, const UInt_t *pstop );  

protected:

   void LoadRates();
   Bool_t checkchan(Int_t chan) { return (chan >=0 && chan < fWordsExpect); }
   static TypeIter_t fgThisType;
   Bool_t fIsDecoded, fFirstTime, fDeltaT;
   Int_t *fDataArray, *fPrevData;
   Double_t *fRate;
   Int_t fNumChan, fClockChan, fNumChanMask;
   Bool_t fHasClock;
   Double_t fClockRate;
   GenScaler *fNormScaler;
 
   ClassDef(Decoder::GenScaler,0)  //   A generic scaler.  Abstract class.

};

#endif
