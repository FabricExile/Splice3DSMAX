#pragma once

#ifdef KL2EDK_INCLUDE_MESSAGES
  #pragma message ( "Including 'Xfo.h'" )
#endif

////////////////////////////////////////////////////////////////
// THIS FILE IS AUTOMATICALLY GENERATED -- DO NOT MODIFY!!
////////////////////////////////////////////////////////////////
// Generated by kl2edk version 2.5.0
////////////////////////////////////////////////////////////////

#include <FabricEDK.h>
#if FABRIC_EDK_VERSION_MAJ != 2 || FABRIC_EDK_VERSION_MIN != 5
# error "This file needs to be rebuilt for the current EDK version!"
#endif

// Core\Clients\CAPI\KL2EDK.cpp:803
#include "global.h"
// Core\Clients\CAPI\KL2EDK.cpp:855
#include "Quat.h"
// Core\Clients\CAPI\KL2EDK.cpp:855
#include "Vec3.h"

namespace Fabric {
namespace EDK {
namespace KL {


// KL struct 'Xfo'
// Defined at Xfo.kl:29:1

struct Xfo
{
  typedef Xfo &Result;
  typedef Xfo const &INParam;
  typedef Xfo &IOParam;
  typedef Xfo &OUTParam;
  
  ::Fabric::EDK::KL::Quat ori;
  ::Fabric::EDK::KL::Vec3 tr;
  ::Fabric::EDK::KL::Vec3 sc;
};

inline void Traits<Xfo>::ConstructEmpty( Xfo &val )
{
  Traits< ::Fabric::EDK::KL::Quat >::ConstructEmpty( val.ori );
  Traits< ::Fabric::EDK::KL::Vec3 >::ConstructEmpty( val.tr );
  Traits< ::Fabric::EDK::KL::Vec3 >::ConstructEmpty( val.sc );
}
inline void Traits<Xfo>::ConstructCopy( Xfo &lhs, Xfo const &rhs )
{
  Traits< ::Fabric::EDK::KL::Quat >::ConstructCopy( lhs.ori, rhs.ori );
  Traits< ::Fabric::EDK::KL::Vec3 >::ConstructCopy( lhs.tr, rhs.tr );
  Traits< ::Fabric::EDK::KL::Vec3 >::ConstructCopy( lhs.sc, rhs.sc );
}
inline void Traits<Xfo>::AssignCopy( Xfo &lhs, Xfo const &rhs )
{
  Traits< ::Fabric::EDK::KL::Quat >::AssignCopy( lhs.ori, rhs.ori );
  Traits< ::Fabric::EDK::KL::Vec3 >::AssignCopy( lhs.tr, rhs.tr );
  Traits< ::Fabric::EDK::KL::Vec3 >::AssignCopy( lhs.sc, rhs.sc );
}
inline void Traits<Xfo>::Destruct( Xfo &val )
{
  Traits< ::Fabric::EDK::KL::Vec3 >::Destruct( val.sc );
  Traits< ::Fabric::EDK::KL::Vec3 >::Destruct( val.tr );
  Traits< ::Fabric::EDK::KL::Quat >::Destruct( val.ori );
}
} // namespace KL
} // namespace EDK
} // namespace Fabric


