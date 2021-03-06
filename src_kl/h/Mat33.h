#pragma once

#ifdef KL2EDK_INCLUDE_MESSAGES
  #pragma message ( "Including 'Mat33.h'" )
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
// Core\Clients\CAPI\KL2EDK.cpp:864
#include "Vec3.h"

namespace Fabric {
namespace EDK {
namespace KL {


// KL struct 'Mat33'
// Defined at Mat33.kl:54:1

struct Mat33
{
  typedef Mat33 &Result;
  typedef Mat33 const &INParam;
  typedef Mat33 &IOParam;
  typedef Mat33 &OUTParam;
  
  ::Fabric::EDK::KL::Vec3 row0;
  ::Fabric::EDK::KL::Vec3 row1;
  ::Fabric::EDK::KL::Vec3 row2;
};

inline void Traits<Mat33>::ConstructEmpty( Mat33 &val )
{
  Traits< ::Fabric::EDK::KL::Vec3 >::ConstructEmpty( val.row0 );
  Traits< ::Fabric::EDK::KL::Vec3 >::ConstructEmpty( val.row1 );
  Traits< ::Fabric::EDK::KL::Vec3 >::ConstructEmpty( val.row2 );
}
inline void Traits<Mat33>::ConstructCopy( Mat33 &lhs, Mat33 const &rhs )
{
  Traits< ::Fabric::EDK::KL::Vec3 >::ConstructCopy( lhs.row0, rhs.row0 );
  Traits< ::Fabric::EDK::KL::Vec3 >::ConstructCopy( lhs.row1, rhs.row1 );
  Traits< ::Fabric::EDK::KL::Vec3 >::ConstructCopy( lhs.row2, rhs.row2 );
}
inline void Traits<Mat33>::AssignCopy( Mat33 &lhs, Mat33 const &rhs )
{
  Traits< ::Fabric::EDK::KL::Vec3 >::AssignCopy( lhs.row0, rhs.row0 );
  Traits< ::Fabric::EDK::KL::Vec3 >::AssignCopy( lhs.row1, rhs.row1 );
  Traits< ::Fabric::EDK::KL::Vec3 >::AssignCopy( lhs.row2, rhs.row2 );
}
inline void Traits<Mat33>::Destruct( Mat33 &val )
{
  Traits< ::Fabric::EDK::KL::Vec3 >::Destruct( val.row2 );
  Traits< ::Fabric::EDK::KL::Vec3 >::Destruct( val.row1 );
  Traits< ::Fabric::EDK::KL::Vec3 >::Destruct( val.row0 );
}
} // namespace KL
} // namespace EDK
} // namespace Fabric


