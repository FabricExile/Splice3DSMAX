#pragma once

#ifdef KL2EDK_INCLUDE_MESSAGES
  #pragma message ( "Including 'Vec3.h'" )
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

namespace Fabric {
namespace EDK {
namespace KL {


// KL struct 'Vec3'
// Defined at Vec3.kl:25:1

struct Vec3
{
  typedef Vec3 &Result;
  typedef Vec3 const &INParam;
  typedef Vec3 &IOParam;
  typedef Vec3 &OUTParam;
  
  ::Fabric::EDK::KL::Float32 x;
  ::Fabric::EDK::KL::Float32 y;
  ::Fabric::EDK::KL::Float32 z;
};

inline void Traits<Vec3>::ConstructEmpty( Vec3 &val )
{
  Traits< ::Fabric::EDK::KL::Float32 >::ConstructEmpty( val.x );
  Traits< ::Fabric::EDK::KL::Float32 >::ConstructEmpty( val.y );
  Traits< ::Fabric::EDK::KL::Float32 >::ConstructEmpty( val.z );
}
inline void Traits<Vec3>::ConstructCopy( Vec3 &lhs, Vec3 const &rhs )
{
  Traits< ::Fabric::EDK::KL::Float32 >::ConstructCopy( lhs.x, rhs.x );
  Traits< ::Fabric::EDK::KL::Float32 >::ConstructCopy( lhs.y, rhs.y );
  Traits< ::Fabric::EDK::KL::Float32 >::ConstructCopy( lhs.z, rhs.z );
}
inline void Traits<Vec3>::AssignCopy( Vec3 &lhs, Vec3 const &rhs )
{
  Traits< ::Fabric::EDK::KL::Float32 >::AssignCopy( lhs.x, rhs.x );
  Traits< ::Fabric::EDK::KL::Float32 >::AssignCopy( lhs.y, rhs.y );
  Traits< ::Fabric::EDK::KL::Float32 >::AssignCopy( lhs.z, rhs.z );
}
inline void Traits<Vec3>::Destruct( Vec3 &val )
{
  Traits< ::Fabric::EDK::KL::Float32 >::Destruct( val.z );
  Traits< ::Fabric::EDK::KL::Float32 >::Destruct( val.y );
  Traits< ::Fabric::EDK::KL::Float32 >::Destruct( val.x );
}
} // namespace KL
} // namespace EDK
} // namespace Fabric


