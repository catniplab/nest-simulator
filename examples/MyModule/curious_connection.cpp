#include <cmath>

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
    rate_ = rate;
    reward_ = 0.0;
  }

double compute_eligibility(const std::vector< spikecounter > &spikes, const double t_trig)
{
  return 1.0;
}

template <typename targetidentifierT>
void mynest::CuriousConnection< targetidentifierT >::trigger_update_weight
( const thread tr,
  const std::vector< spikecounter > &spikes,
  const double t_trig,
  const nest::CommonSynapseProperties &cp)
{

  double eligibility = compute_eligibility(&spikes, t_trig);

  double helper = weight_;
  weight_ += learning_rate_*(reward_ + curiosity_*fabs(weight0_ - weight1_))*eligibility_;
  weight1_ = weight0_;
  weight0_ = helper;
}