#pragma once

#ifdef KL2EDK_INCLUDE_MESSAGES
  #pragma message ( "Including 'RotationOrder.h'" )
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


// KL struct 'RotationOrder'
// Defined at RotationOrder.kl:21:1

struct RotationOrder
{
  typedef RotationOrder &Result;
  typedef RotationOrder const &INParam;
  typedef RotationOrder &IOParam;
  typedef RotationOrder &OUTParam;
  
  ::Fabric::EDK::KL::SInt32 order;
};

inline void Traits<RotationOrder>::ConstructEmpty( RotationOrder &val )
{
  Traits< ::Fabric::EDK::KL::SInt32 >::ConstructEmpty( val.order );
}
inline void Traits<RotationOrder>::ConstructCopy( RotationOrder &lhs, RotationOrder const &rhs )
{
  Traits< ::Fabric::EDK::KL::SInt32 >::ConstructCopy( lhs.order, rhs.order );
}
inline void Traits<RotationOrder>::AssignCopy( RotationOrder &lhs, RotationOrder const &rhs )
{
  Traits< ::Fabric::EDK::KL::SInt32 >::AssignCopy( lhs.order, rhs.order );
}
inline void Traits<RotationOrder>::Destruct( RotationOrder &val )
{
  Traits< ::Fabric::EDK::KL::SInt32 >::Destruct( val.order );
}
} // namespace KL
} // namespace EDK
} // namespace Fabric


