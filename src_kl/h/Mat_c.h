#pragma once

#ifdef KL2EDK_INCLUDE_MESSAGES
  #pragma message ( "Including 'Mat_c.h'" )
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
#include "Complex.h"

namespace Fabric {
namespace EDK {
namespace KL {


// KL struct 'Mat_c'
// Defined at Mat_c.kl:19:1

struct Mat_c
{
  typedef Mat_c &Result;
  typedef Mat_c const &INParam;
  typedef Mat_c &IOParam;
  typedef Mat_c &OUTParam;
  
  ::Fabric::EDK::KL::SInt32 rows;
  ::Fabric::EDK::KL::SInt32 cols;
  ::Fabric::EDK::KL::VariableArray< ::Fabric::EDK::KL::Complex > vals;
};

inline void Traits<Mat_c>::ConstructEmpty( Mat_c &val )
{
  Traits< ::Fabric::EDK::KL::SInt32 >::ConstructEmpty( val.rows );
  Traits< ::Fabric::EDK::KL::SInt32 >::ConstructEmpty( val.cols );
  Traits< ::Fabric::EDK::KL::VariableArray< ::Fabric::EDK::KL::Complex > >::ConstructEmpty( val.vals );
}
inline void Traits<Mat_c>::ConstructCopy( Mat_c &lhs, Mat_c const &rhs )
{
  Traits< ::Fabric::EDK::KL::SInt32 >::ConstructCopy( lhs.rows, rhs.rows );
  Traits< ::Fabric::EDK::KL::SInt32 >::ConstructCopy( lhs.cols, rhs.cols );
  Traits< ::Fabric::EDK::KL::VariableArray< ::Fabric::EDK::KL::Complex > >::ConstructCopy( lhs.vals, rhs.vals );
}
inline void Traits<Mat_c>::AssignCopy( Mat_c &lhs, Mat_c const &rhs )
{
  Traits< ::Fabric::EDK::KL::SInt32 >::AssignCopy( lhs.rows, rhs.rows );
  Traits< ::Fabric::EDK::KL::SInt32 >::AssignCopy( lhs.cols, rhs.cols );
  Traits< ::Fabric::EDK::KL::VariableArray< ::Fabric::EDK::KL::Complex > >::AssignCopy( lhs.vals, rhs.vals );
}
inline void Traits<Mat_c>::Destruct( Mat_c &val )
{
  Traits< ::Fabric::EDK::KL::VariableArray< ::Fabric::EDK::KL::Complex > >::Destruct( val.vals );
  Traits< ::Fabric::EDK::KL::SInt32 >::Destruct( val.cols );
  Traits< ::Fabric::EDK::KL::SInt32 >::Destruct( val.rows );
}
} // namespace KL
} // namespace EDK
} // namespace Fabric


