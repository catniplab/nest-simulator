/*
 *  curiousmodule.cpp
 *
 *  This file is part of NEST.
 *
 *  Copyright (C) 2004 The NEST Initiative
 *
 *  NEST is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  NEST is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with NEST.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "curiousmodule.h"

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
  return std::string( "My NEST Module" ); // Return name of the module
}

const std::string
curiousnest::CuriousModule::commandstring( void ) const
{
  // Instruct the interpreter to load curiousmodule-init.sli
  return std::string( "(curiousmodule-init) run" );
}

//-------------------------------------------------------------------------------------

void
curiousnest::CuriousModule::init( SLIInterpreter* i )
{
  /* Register a neuron or device model.
     Give node type as template argument and the name as second argument.
  */
  nest::kernel().model_manager.register_node_model< pif_psc_alpha >( "pif_psc_alpha" );

  /* Register a synapse type.
     Give synapse type as template argument and the name as second argument.

     There are two choices for the template argument:
         - nest::TargetIdentifierPtrRport
         - nest::TargetIdentifierIndex
     The first is the standard and you should usually stick to it.
     nest::TargetIdentifierIndex reduces the memory requirement of synapses
     even further, but limits the number of available rports. Please see
     Kunkel et al, Front Neurofinfom 8:78 (2014), Sec 3.3.2, for details.
  */
  nest::kernel().model_manager.register_connection_model< DropOddSpikeConnection< nest::TargetIdentifierPtrRport > >(
    "drop_odd_synapse" );

  // Register connection rule.
  nest::kernel().connection_manager.register_conn_builder< StepPatternBuilder >( "step_pattern" );

} // CuriousModule::init()
