//
/// \file geHit.hh
/// \brief Definition of the geHit class

#ifndef geHit_h
#define geHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"


class geHit : public G4VHit{
public:
    geHit();
    geHit(const geHit&);
    virtual ~geHit();
    
    //operators
    const geHit& operator=(const geHit&);
    G4int operator==(const geHit&) const;
    
    inline void* operator new(size_t);
    inline void operator delete(void*);
    
    // methods from base class
    virtual void Draw();
    virtual void Print();
    
    // set methods
    
    void SetTrackId  (G4int track)      { fTrackID = track; };
    void SetChamberNb(G4int chamb)      { fChamberNb = chamb; };
    void SetEdep     (G4double de)      { fEdep = de;   };
    void SetPos      (G4ThreeVector xyz){ fPos = xyz;   };
    
    // get methods
    G4int GetTrackID() const     { return fTrackID; };
    G4int GetChamberNb() const   { return fChamberNb; };
    G4double GetEdep() const     { return fEdep; };
    G4ThreeVector GetPos() const { return fPos; };

  private:

      G4int         fTrackID;
      G4int         fChamberNb;
      G4double      fEdep;
      G4ThreeVector fPos;
};

typedef G4THitsCollection<geHit> geHitsCollection;

extern G4ThreadLocal G4Allocator<geHit>* geHitAllocator;

inline void* geHit::operator new(size_t)
{
    if(!geHitAllocator)
        geHitAllocator = new G4Allocator<geHit>;
    return (void *) geHitAllocator->MallocSingle();
}

inline void geHit::operator delete(void *hit)
{
    geHitAllocator->FreeSingle((geHit*) hit);
}
#endif
