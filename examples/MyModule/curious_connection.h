#ifndef CURIOUS_CONNECTION
#define CURIOUS_CONNECTION

#include "slifunction.h"
#include "slimodule.h"

#include "connection.h"
#include "static_connection.h"

namespace mynest
{
  template <typename targetidentifierT>
  class CuriousConnection : public SLIModule
  {

    targetidentifierT target_;
    double weight_;
    nest::delay delay_;
    nest::rport rport_;

    double weight0_;
    double weight1_;
    double curiosity_;
    double eligibility_;
    double rate_;
    double reward_;

    public:

      CuriousConnection () {}

      void set_reward (double reward) {}

      void update_dynamics ();

      void send (nest::Event & e,
                 double_t t_lastspike,
                 const nest::CommonSynapseProperties &cp);
  };

  template <typename targetidentifierT>
  void mynest::CuriousConnection< targetidentifierT >::send (nest::Event &e,
                              double_t t_lastspike,
                              const nest::CommonSynapseProperties &cp)
  {
    update_dynamics();
    e.set_receiver(target_);
    e.set_weight(weight_);
    e.set_delay_steps(delay_);
    e.set_rport(rport_);
    e();
  }
}

#endif