#pragma once

#ifdef KL2EDK_INCLUDE_MESSAGES
  #pragma message ( "Including 'Mat44.h'" )
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
#include "Vec4.h"

namespace Fabric {
namespace EDK {
namespace KL {


// KL struct 'Mat44'
// Defined at Mat44.kl:50:1

struct Mat44
{
  typedef Mat44 &Result;
  typedef Mat44 const &INParam;
  typedef Mat44 &IOParam;
  typedef Mat44 &OUTParam;
  
  ::Fabric::EDK::KL::Vec4 row0;
  ::Fabric::EDK::KL::Vec4 row1;
  ::Fabric::EDK::KL::Vec4 row2;
  ::Fabric::EDK::KL::Vec4 row3;
};

inline void Traits<Mat44>::ConstructEmpty( Mat44 &val )
{
  Traits< ::Fabric::EDK::KL::Vec4 >::ConstructEmpty( val.row0 );
  Traits< ::Fabric::EDK::KL::Vec4 >::ConstructEmpty( val.row1 );
  Traits< ::Fabric::EDK::KL::Vec4 >::ConstructEmpty( val.row2 );
  Traits< ::Fabric::EDK::KL::Vec4 >::ConstructEmpty( val.row3 );
}
inline void Traits<Mat44>::ConstructCopy( Mat44 &lhs, Mat44 const &rhs )
{
  Traits< ::Fabric::EDK::KL::Vec4 >::ConstructCopy( lhs.row0, rhs.row0 );
  Traits< ::Fabric::EDK::KL::Vec4 >::ConstructCopy( lhs.row1, rhs.row1 );
  Traits< ::Fabric::EDK::KL::Vec4 >::ConstructCopy( lhs.row2, rhs.row2 );
  Traits< ::Fabric::EDK::KL::Vec4 >::ConstructCopy( lhs.row3, rhs.row3 );
}
inline void Traits<Mat44>::AssignCopy( Mat44 &lhs, Mat44 const &rhs )
{
  Traits< ::Fabric::EDK::KL::Vec4 >::AssignCopy( lhs.row0, rhs.row0 );
  Traits< ::Fabric::EDK::KL::Vec4 >::AssignCopy( lhs.row1, rhs.row1 );
  Traits< ::Fabric::EDK::KL::Vec4 >::AssignCopy( lhs.row2, rhs.row2 );
  Traits< ::Fabric::EDK::KL::Vec4 >::AssignCopy( lhs.row3, rhs.row3 );
}
inline void Traits<Mat44>::Destruct( Mat44 &val )
{
  Traits< ::Fabric::EDK::KL::Vec4 >::Destruct( val.row3 );
  Traits< ::Fabric::EDK::KL::Vec4 >::Destruct( val.row2 );
  Traits< ::Fabric::EDK::KL::Vec4 >::Destruct( val.row1 );
  Traits< ::Fabric::EDK::KL::Vec4 >::Destruct( val.row0 );
}
} // namespace KL
} // namespace EDK
} // namespace Fabric


