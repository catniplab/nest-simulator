#include "connection.h"
#include "static_connection.h"

#include "curious_connection.h"

mynest::CuriousConnection (nest::Node target,
                           double weight,
                           nest::delay delay,
                           nest::rport port,
                           double curiosity = 0.0,
                           double rate = 0.01)
  {
    target_ = target;
    weight_ = weight;
    weight0_ = weight;
    weight1_ = weight;
    curiosity_ = curiosity;
    eligibility_ = 0.0;
    rate_ = rate;
    reward_ = 0.0;
  }

void mynest::CuriousConnection< targetidentifierT >::set_reward (double reward)
{
  reward_ = reward;
}

template <typename targetidentifierT>
void mynest::CuriousConnection< targetidentifierT >::update_dynamics ()
{
  double helper = weight_;
  weight_ += rate_*(reward_ + curiosity_*abs(weight0_ - weight1_))*eligibility_;
  weight1_ = weight0_;
  weight0_ = helper;
}