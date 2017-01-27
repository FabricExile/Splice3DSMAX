#pragma once

#ifdef KL2EDK_INCLUDE_MESSAGES
  #pragma message ( "Including 'Ray.h'" )
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
#include "Vec3.h"

namespace Fabric {
namespace EDK {
namespace KL {


// KL struct 'Ray'
// Defined at Ray.kl:17:1

struct Ray
{
  typedef Ray &Result;
  typedef Ray const &INParam;
  typedef Ray &IOParam;
  typedef Ray &OUTParam;
  
  ::Fabric::EDK::KL::Vec3 start;
  ::Fabric::EDK::KL::Vec3 direction;
};

inline void Traits<Ray>::ConstructEmpty( Ray &val )
{
  Traits< ::Fabric::EDK::KL::Vec3 >::ConstructEmpty( val.start );
  Traits< ::Fabric::EDK::KL::Vec3 >::ConstructEmpty( val.direction );
}
inline void Traits<Ray>::ConstructCopy( Ray &lhs, Ray const &rhs )
{
  Traits< ::Fabric::EDK::KL::Vec3 >::ConstructCopy( lhs.start, rhs.start );
  Traits< ::Fabric::EDK::KL::Vec3 >::ConstructCopy( lhs.direction, rhs.direction );
}
inline void Traits<Ray>::AssignCopy( Ray &lhs, Ray const &rhs )
{
  Traits< ::Fabric::EDK::KL::Vec3 >::AssignCopy( lhs.start, rhs.start );
  Traits< ::Fabric::EDK::KL::Vec3 >::AssignCopy( lhs.direction, rhs.direction );
}
inline void Traits<Ray>::Destruct( Ray &val )
{
  Traits< ::Fabric::EDK::KL::Vec3 >::Destruct( val.direction );
  Traits< ::Fabric::EDK::KL::Vec3 >::Destruct( val.start );
}
} // namespace KL
} // namespace EDK
} // namespace Fabric


