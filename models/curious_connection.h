#ifndef CURIOUS_CONNECTION
#define CURIOUS_CONNECTION

#include "connection.h"
#include "static_connection.h"

namespace nest
{
  template <typename targetidentifierT>
  class CuriousConnection : public StaticConnection< targetidentifierT >
  {

    Node &target_;
    double weight_;
    double delay_;
    rport rport_;

    double weight0_;
    double weight1_;
    double curiosity_;
    double eligibility_;
    double rate_;
    double reward_;

    public:

      CuriousConnection (Node &target,
                    double weight,
                    double delay,
                    rport port,
                    double curiosity = 0.0,
                    double rate = 0.01)
      {
        &target_ = &target;
        weight_ = weight;
        weight0_ = weight;
        weight1_ = weight;
        curiosity_ = curiosity;
        eligibility_ = 0.0;
        rate_ = rate;
        reward = 0.0;
      }

      void set_reward (double reward)
      {
        reward_ = reward;
      }

      void set_eligibility (double eligibility)
      {
        eligibility_ = eligibility;
      }

      void update_dynamics ();

      void send (Event & e, double_t t_lastspike, const CommonSynapseProperties & cp);
  };
  template <typename targetidentifierT>
  void CuriousConnection< targetidentifierT >::send (Event & e,
                              double_t t_lastspike,
                              const CommonSynapseProperties &cp)
  {
    update_dynamics();
    e.set_receiver(target_);
    e.set_weight(weight_);
    e.set_delay(delay_);
    e.set_rport(rport_);
    e();
  }
}

#endif