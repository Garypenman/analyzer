#ifndef Podd_DynamicTriggerTime_h_
#define Podd_DynamicTriggerTime_h_

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// Podd::DynamicTriggerTime                                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#include "THaTriggerTime.h"
#include "THaFormula.h"
#include "THaCut.h"
#include "TString.h"
#include <set>

namespace Podd {

class DynamicTriggerTime : public THaTriggerTime {
public:
  DynamicTriggerTime( const char* name, const char* description,
                      THaApparatus* a = NULL );
  DynamicTriggerTime( const char* name, const char* description,
                      const char* expr, const char* cond = "",
                      THaApparatus* a = NULL );

  virtual Int_t Decode( const THaEvData& );
  virtual Int_t CoarseProcess( TClonesArray& tracks );
  virtual Int_t FineProcess( TClonesArray& tracks );
  virtual void  Clear( Option_t *opt = "" );
  virtual Int_t DefineVariables( EMode mode = kDefine );

protected:

  virtual Int_t ReadDatabase( const TDatime &date );
  Int_t InitDefs();
  Int_t Process();

  struct TimeCorrDef {
    explicit TimeCorrDef( const char* expr, const char* cond = "",
                          UInt_t prio = 0 ) :
      fFormStr(expr), fCondStr(cond), fPrio(prio), fFromDB(true),
      fForm(nullptr), fCond(nullptr) {}
    ~TimeCorrDef() { delete fForm; delete fCond; }
    bool operator<(const TimeCorrDef& rhs) const { return fPrio < rhs.fPrio; }
    TString  fFormStr; // Formula string
    TString  fCondStr; // Condition string
    UInt_t   fPrio;    // Priority of this correction (0=highest)
    Bool_t   fFromDB;  // True if read from database (not in constructor)
    mutable THaFormula* fForm;    // Formula for calculating time correction
    mutable THaCut*     fCond;    // Condition to pass for this correction to apply (optional)
  };
  std::set<TimeCorrDef> fDefs;

  TString fTestBlockName;

  ClassDef( DynamicTriggerTime, 0 )  // Trigger time correction based on formula(s)
};

} // namespace Podd

#endif  /*  Podd_DynamicTriggerTime_h_  */
