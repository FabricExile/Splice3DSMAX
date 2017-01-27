#pragma once

#ifdef KL2EDK_INCLUDE_MESSAGES
  #pragma message ( "Including 'Vec4_cd.h'" )
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
#include "Complex_d.h"

namespace Fabric {
namespace EDK {
namespace KL {


// KL struct 'Vec4_cd'
// Defined at Vec4_cd.kl:19:1

struct Vec4_cd
{
  typedef Vec4_cd &Result;
  typedef Vec4_cd const &INParam;
  typedef Vec4_cd &IOParam;
  typedef Vec4_cd &OUTParam;
  
  ::Fabric::EDK::KL::Complex_d x;
  ::Fabric::EDK::KL::Complex_d y;
  ::Fabric::EDK::KL::Complex_d z;
  ::Fabric::EDK::KL::Complex_d t;
};

inline void Traits<Vec4_cd>::ConstructEmpty( Vec4_cd &val )
{
  Traits< ::Fabric::EDK::KL::Complex_d >::ConstructEmpty( val.x );
  Traits< ::Fabric::EDK::KL::Complex_d >::ConstructEmpty( val.y );
  Traits< ::Fabric::EDK::KL::Complex_d >::ConstructEmpty( val.z );
  Traits< ::Fabric::EDK::KL::Complex_d >::ConstructEmpty( val.t );
}
inline void Traits<Vec4_cd>::ConstructCopy( Vec4_cd &lhs, Vec4_cd const &rhs )
{
  Traits< ::Fabric::EDK::KL::Complex_d >::ConstructCopy( lhs.x, rhs.x );
  Traits< ::Fabric::EDK::KL::Complex_d >::ConstructCopy( lhs.y, rhs.y );
  Traits< ::Fabric::EDK::KL::Complex_d >::ConstructCopy( lhs.z, rhs.z );
  Traits< ::Fabric::EDK::KL::Complex_d >::ConstructCopy( lhs.t, rhs.t );
}
inline void Traits<Vec4_cd>::AssignCopy( Vec4_cd &lhs, Vec4_cd const &rhs )
{
  Traits< ::Fabric::EDK::KL::Complex_d >::AssignCopy( lhs.x, rhs.x );
  Traits< ::Fabric::EDK::KL::Complex_d >::AssignCopy( lhs.y, rhs.y );
  Traits< ::Fabric::EDK::KL::Complex_d >::AssignCopy( lhs.z, rhs.z );
  Traits< ::Fabric::EDK::KL::Complex_d >::AssignCopy( lhs.t, rhs.t );
}
inline void Traits<Vec4_cd>::Destruct( Vec4_cd &val )
{
  Traits< ::Fabric::EDK::KL::Complex_d >::Destruct( val.t );
  Traits< ::Fabric::EDK::KL::Complex_d >::Destruct( val.z );
  Traits< ::Fabric::EDK::KL::Complex_d >::Destruct( val.y );
  Traits< ::Fabric::EDK::KL::Complex_d >::Destruct( val.x );
}
} // namespace KL
} // namespace EDK
} // namespace Fabric


