#pragma once

#ifdef KL2EDK_INCLUDE_MESSAGES
  #pragma message ( "Including 'Vec_c.h'" )
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
#include "Complex.h"

namespace Fabric {
namespace EDK {
namespace KL {


// KL struct 'Vec_c'
// Defined at Vec_c.kl:19:1

struct Vec_c
{
  typedef Vec_c &Result;
  typedef Vec_c const &INParam;
  typedef Vec_c &IOParam;
  typedef Vec_c &OUTParam;
  
  ::Fabric::EDK::KL::VariableArray< ::Fabric::EDK::KL::Complex > vals;
};

inline void Traits<Vec_c>::ConstructEmpty( Vec_c &val )
{
  Traits< ::Fabric::EDK::KL::VariableArray< ::Fabric::EDK::KL::Complex > >::ConstructEmpty( val.vals );
}
inline void Traits<Vec_c>::ConstructCopy( Vec_c &lhs, Vec_c const &rhs )
{
  Traits< ::Fabric::EDK::KL::VariableArray< ::Fabric::EDK::KL::Complex > >::ConstructCopy( lhs.vals, rhs.vals );
}
inline void Traits<Vec_c>::AssignCopy( Vec_c &lhs, Vec_c const &rhs )
{
  Traits< ::Fabric::EDK::KL::VariableArray< ::Fabric::EDK::KL::Complex > >::AssignCopy( lhs.vals, rhs.vals );
}
inline void Traits<Vec_c>::Destruct( Vec_c &val )
{
  Traits< ::Fabric::EDK::KL::VariableArray< ::Fabric::EDK::KL::Complex > >::Destruct( val.vals );
}
} // namespace KL
} // namespace EDK
} // namespace Fabric


