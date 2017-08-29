#pragma once

#ifdef KL2EDK_INCLUDE_MESSAGES
  #pragma message ( "Including 'Mat44_c.h'" )
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
#include "Vec4_c.h"
// Core\Clients\CAPI\KL2EDK.cpp:864
#include "Complex.h"

namespace Fabric {
namespace EDK {
namespace KL {


// KL struct 'Mat44_c'
// Defined at Mat44_c.kl:50:1

struct Mat44_c
{
  typedef Mat44_c &Result;
  typedef Mat44_c const &INParam;
  typedef Mat44_c &IOParam;
  typedef Mat44_c &OUTParam;
  
  ::Fabric::EDK::KL::Vec4_c row0;
  ::Fabric::EDK::KL::Vec4_c row1;
  ::Fabric::EDK::KL::Vec4_c row2;
  ::Fabric::EDK::KL::Vec4_c row3;
};

inline void Traits<Mat44_c>::ConstructEmpty( Mat44_c &val )
{
  Traits< ::Fabric::EDK::KL::Vec4_c >::ConstructEmpty( val.row0 );
  Traits< ::Fabric::EDK::KL::Vec4_c >::ConstructEmpty( val.row1 );
  Traits< ::Fabric::EDK::KL::Vec4_c >::ConstructEmpty( val.row2 );
  Traits< ::Fabric::EDK::KL::Vec4_c >::ConstructEmpty( val.row3 );
}
inline void Traits<Mat44_c>::ConstructCopy( Mat44_c &lhs, Mat44_c const &rhs )
{
  Traits< ::Fabric::EDK::KL::Vec4_c >::ConstructCopy( lhs.row0, rhs.row0 );
  Traits< ::Fabric::EDK::KL::Vec4_c >::ConstructCopy( lhs.row1, rhs.row1 );
  Traits< ::Fabric::EDK::KL::Vec4_c >::ConstructCopy( lhs.row2, rhs.row2 );
  Traits< ::Fabric::EDK::KL::Vec4_c >::ConstructCopy( lhs.row3, rhs.row3 );
}
inline void Traits<Mat44_c>::AssignCopy( Mat44_c &lhs, Mat44_c const &rhs )
{
  Traits< ::Fabric::EDK::KL::Vec4_c >::AssignCopy( lhs.row0, rhs.row0 );
  Traits< ::Fabric::EDK::KL::Vec4_c >::AssignCopy( lhs.row1, rhs.row1 );
  Traits< ::Fabric::EDK::KL::Vec4_c >::AssignCopy( lhs.row2, rhs.row2 );
  Traits< ::Fabric::EDK::KL::Vec4_c >::AssignCopy( lhs.row3, rhs.row3 );
}
inline void Traits<Mat44_c>::Destruct( Mat44_c &val )
{
  Traits< ::Fabric::EDK::KL::Vec4_c >::Destruct( val.row3 );
  Traits< ::Fabric::EDK::KL::Vec4_c >::Destruct( val.row2 );
  Traits< ::Fabric::EDK::KL::Vec4_c >::Destruct( val.row1 );
  Traits< ::Fabric::EDK::KL::Vec4_c >::Destruct( val.row0 );
}
} // namespace KL
} // namespace EDK
} // namespace Fabric


