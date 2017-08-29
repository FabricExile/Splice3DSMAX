#pragma once

#ifdef KL2EDK_INCLUDE_MESSAGES
  #pragma message ( "Including 'RGBA.h'" )
#endif

////////////////////////////////////////////////////////////////
// THIS FILE IS AUTOMATICALLY GENERATED -- DO NOT MODIFY!!
////////////////////////////////////////////////////////////////
// Generated by kl2edk version 2.7.0
////////////////////////////////////////////////////////////////

#include <FabricEDK.h>
#if FABRIC_EDK_VERSION_MAJ != 2 || FABRIC_EDK_VERSION_MIN != 7
# error "This file needs to be rebuilt for the current EDK version!"
#endif

// Core\Clients\CAPI\KL2EDK.cpp:812
#include "global.h"

namespace Fabric {
namespace EDK {
namespace KL {


// KL struct 'RGBA'
// Defined at RGB.kl:18:1

struct RGBA
{
  typedef RGBA &Result;
  typedef RGBA const &INParam;
  typedef RGBA &IOParam;
  typedef RGBA &OUTParam;
  
  ::Fabric::EDK::KL::UInt8 r;
  ::Fabric::EDK::KL::UInt8 g;
  ::Fabric::EDK::KL::UInt8 b;
  ::Fabric::EDK::KL::UInt8 a;
};

inline void Traits<RGBA>::ConstructEmpty( RGBA &val )
{
  Traits< ::Fabric::EDK::KL::UInt8 >::ConstructEmpty( val.r );
  Traits< ::Fabric::EDK::KL::UInt8 >::ConstructEmpty( val.g );
  Traits< ::Fabric::EDK::KL::UInt8 >::ConstructEmpty( val.b );
  Traits< ::Fabric::EDK::KL::UInt8 >::ConstructEmpty( val.a );
}
inline void Traits<RGBA>::ConstructCopy( RGBA &lhs, RGBA const &rhs )
{
  Traits< ::Fabric::EDK::KL::UInt8 >::ConstructCopy( lhs.r, rhs.r );
  Traits< ::Fabric::EDK::KL::UInt8 >::ConstructCopy( lhs.g, rhs.g );
  Traits< ::Fabric::EDK::KL::UInt8 >::ConstructCopy( lhs.b, rhs.b );
  Traits< ::Fabric::EDK::KL::UInt8 >::ConstructCopy( lhs.a, rhs.a );
}
inline void Traits<RGBA>::AssignCopy( RGBA &lhs, RGBA const &rhs )
{
  Traits< ::Fabric::EDK::KL::UInt8 >::AssignCopy( lhs.r, rhs.r );
  Traits< ::Fabric::EDK::KL::UInt8 >::AssignCopy( lhs.g, rhs.g );
  Traits< ::Fabric::EDK::KL::UInt8 >::AssignCopy( lhs.b, rhs.b );
  Traits< ::Fabric::EDK::KL::UInt8 >::AssignCopy( lhs.a, rhs.a );
}
inline void Traits<RGBA>::Destruct( RGBA &val )
{
  Traits< ::Fabric::EDK::KL::UInt8 >::Destruct( val.a );
  Traits< ::Fabric::EDK::KL::UInt8 >::Destruct( val.b );
  Traits< ::Fabric::EDK::KL::UInt8 >::Destruct( val.g );
  Traits< ::Fabric::EDK::KL::UInt8 >::Destruct( val.r );
}
} // namespace KL
} // namespace EDK
} // namespace Fabric


