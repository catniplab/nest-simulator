#ifndef CURIOUSMODULE_H
#define CURIOUSMODULE_H

// Includes from sli:
#include "slifunction.h"
#include "slimodule.h"

// Namespace for the curiousmodule.
namespace curiousnest
{

class CuriousModule : public SLIModule
{
public:
  // Interface functions ------------------------------------------

  /**
   * @note The constructor registers the module with the dynamic loader.
   *       Initialization proper is performed by the init() method.
   */
  CuriousModule();

  /**
   * @note The destructor does not do much in modules.
   */
  ~CuriousModule();

  /**
   * Initialize module.
   * @param SLIInterpreter* SLI interpreter
   */
  void init( SLIInterpreter* );

  /**
   * Return the name of your model.
   */
  const std::string name( void ) const;

  /**
   * Return the name of a sli file to execute when CuriousModule is loaded.
   * This mechanism can be used to define SLI commands associated with the
   * module, in particular, set up type tries for functions you have defined.
   */
  const std::string commandstring( void ) const;
};
} // namespace curiousnest

#endif
