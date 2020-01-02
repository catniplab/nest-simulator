#include "curiousmodule.h"
#include "curious_syn.h"

// Generated includes:
#include "config.h"

// include headers with your own stuff
#include "drop_odd_spike_connection.h"
#include "pif_psc_alpha.h"
#include "step_pattern_builder.h"

// Includes from nestkernel:
#include "connection_manager_impl.h"
#include "connector_model_impl.h"
#include "dynamicloader.h"
#include "exceptions.h"
#include "genericmodel.h"
#include "genericmodel_impl.h"
#include "kernel_manager.h"
#include "model.h"
#include "model_manager_impl.h"
#include "nestmodule.h"
#include "target_identifier.h"

// Includes from sli:
#include "booldatum.h"
#include "integerdatum.h"
#include "sliexceptions.h"
#include "tokenarray.h"

// -- Interface to dynamic module loader ---------------------------------------

#if defined( LTX_MODULE ) | defined( LINKED_MODULE )
curiousnest::CuriousModule curiousmodule_LTX_mod;
#endif

// -- DynModule functions ------------------------------------------------------

curiousnest::CuriousModule::CuriousModule()
{
#ifdef LINKED_MODULE
  // register this module at the dynamic loader
  // this is needed to allow for linking in this module at compile time
  // all registered modules will be initialized by the main app's dynamic loader
  nest::DynamicLoaderModule::registerLinkedModule( this );
#endif
}

curiousnest::CuriousModule::~CuriousModule()
{
}

const std::string
curiousnest::CuriousModule::name( void ) const
{
  return std::string( "curiousmodule" );
}

const std::string
curiousnest::CuriousModule::commandstring( void ) const
{
  // Instruct the interpreter to load curiousmodule-init.sli
  return std::string( "(curiousmodule-init) run" );
}

//-------------------------------------------------------------------------------------

void curiousnest::CuriousModule::init( SLIInterpreter* i )
{
  /* Register the synapse type.
     Give synapse type as template argument and the name as second argument.

     There are two choices for the template argument:
         - nest::TargetIdentifierPtrRport
         - nest::TargetIdentifierIndex
     The first is the standard and you should usually stick to it.
     nest::TargetIdentifierIndex reduces the memory requirement of synapses
     even further, but limits the number of available rports. Please see
     Kunkel et al, Front Neurofinfom 8:78 (2014), Sec 3.3.2, for details.
  */
  nest::kernel().model_manager.register_connection_model< CuriousSyn< nest::TargetIdentifierPtrRport > >( "curious_syn" );
}

//CuriousModule::init()
