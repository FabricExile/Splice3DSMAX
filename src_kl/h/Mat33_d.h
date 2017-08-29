#pragma once

#ifdef KL2EDK_INCLUDE_MESSAGES
  #pragma message ( "Including 'Mat33_d.h'" )
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
#include "Vec3_d.h"

namespace Fabric {
namespace EDK {
namespace KL {


// KL struct 'Mat33_d'
// Defined at Mat33_d.kl:54:1

struct Mat33_d
{
  typedef Mat33_d &Result;
  typedef Mat33_d const &INParam;
  typedef Mat33_d &IOParam;
  typedef Mat33_d &OUTParam;
  
  ::Fabric::EDK::KL::Vec3_d row0;
  ::Fabric::EDK::KL::Vec3_d row1;
  ::Fabric::EDK::KL::Vec3_d row2;
};

inline void Traits<Mat33_d>::ConstructEmpty( Mat33_d &val )
{
  Traits< ::Fabric::EDK::KL::Vec3_d >::ConstructEmpty( val.row0 );
  Traits< ::Fabric::EDK::KL::Vec3_d >::ConstructEmpty( val.row1 );
  Traits< ::Fabric::EDK::KL::Vec3_d >::ConstructEmpty( val.row2 );
}
inline void Traits<Mat33_d>::ConstructCopy( Mat33_d &lhs, Mat33_d const &rhs )
{
  Traits< ::Fabric::EDK::KL::Vec3_d >::ConstructCopy( lhs.row0, rhs.row0 );
  Traits< ::Fabric::EDK::KL::Vec3_d >::ConstructCopy( lhs.row1, rhs.row1 );
  Traits< ::Fabric::EDK::KL::Vec3_d >::ConstructCopy( lhs.row2, rhs.row2 );
}
inline void Traits<Mat33_d>::AssignCopy( Mat33_d &lhs, Mat33_d const &rhs )
{
  Traits< ::Fabric::EDK::KL::Vec3_d >::AssignCopy( lhs.row0, rhs.row0 );
  Traits< ::Fabric::EDK::KL::Vec3_d >::AssignCopy( lhs.row1, rhs.row1 );
  Traits< ::Fabric::EDK::KL::Vec3_d >::AssignCopy( lhs.row2, rhs.row2 );
}
inline void Traits<Mat33_d>::Destruct( Mat33_d &val )
{
  Traits< ::Fabric::EDK::KL::Vec3_d >::Destruct( val.row2 );
  Traits< ::Fabric::EDK::KL::Vec3_d >::Destruct( val.row1 );
  Traits< ::Fabric::EDK::KL::Vec3_d >::Destruct( val.row0 );
}
} // namespace KL
} // namespace EDK
} // namespace Fabric


