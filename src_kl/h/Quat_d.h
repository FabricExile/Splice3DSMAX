#pragma once

#ifdef KL2EDK_INCLUDE_MESSAGES
  #pragma message ( "Including 'Quat_d.h'" )
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
#include "Vec3_d.h"

namespace Fabric {
namespace EDK {
namespace KL {


// KL struct 'Quat_d'
// Defined at Mat33_d.kl:52:1

struct Quat_d
{
  typedef Quat_d &Result;
  typedef Quat_d const &INParam;
  typedef Quat_d &IOParam;
  typedef Quat_d &OUTParam;
  
  ::Fabric::EDK::KL::Vec3_d v;
  ::Fabric::EDK::KL::Float64 w;
};

inline void Traits<Quat_d>::ConstructEmpty( Quat_d &val )
{
  Traits< ::Fabric::EDK::KL::Vec3_d >::ConstructEmpty( val.v );
  Traits< ::Fabric::EDK::KL::Float64 >::ConstructEmpty( val.w );
}
inline void Traits<Quat_d>::ConstructCopy( Quat_d &lhs, Quat_d const &rhs )
{
  Traits< ::Fabric::EDK::KL::Vec3_d >::ConstructCopy( lhs.v, rhs.v );
  Traits< ::Fabric::EDK::KL::Float64 >::ConstructCopy( lhs.w, rhs.w );
}
inline void Traits<Quat_d>::AssignCopy( Quat_d &lhs, Quat_d const &rhs )
{
  Traits< ::Fabric::EDK::KL::Vec3_d >::AssignCopy( lhs.v, rhs.v );
  Traits< ::Fabric::EDK::KL::Float64 >::AssignCopy( lhs.w, rhs.w );
}
inline void Traits<Quat_d>::Destruct( Quat_d &val )
{
  Traits< ::Fabric::EDK::KL::Float64 >::Destruct( val.w );
  Traits< ::Fabric::EDK::KL::Vec3_d >::Destruct( val.v );
}
} // namespace KL
} // namespace EDK
} // namespace Fabric


