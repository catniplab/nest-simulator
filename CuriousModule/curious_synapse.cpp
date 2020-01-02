#include <cmath>

#include "connection.h"
#include "static_connection.h"

#include "curious_synapse.h"

template <typename targetidentifierT>
curiousnest::CuriousSynapse< targetidentifierT >::CuriousSynapse(map<std::string, double> cp)
{
  curious_properties_ = cp;
}

double eligibility_fcn (double t, double slope, double decay)
{
  //decay is assumed to be positive
  return slope*t*exp(-decay*t);
}

double learning_curve (double dt, double a_plus, double a_minus, double tau_plus, double tau_minus)
{
  if (t < 0.0)
  {
    return -a_minus*exp(dt/tau_minus);
  }
  else
  {
    return a_plus*exp(-dt/tau_plus);
  }
}

double compute_eligibility(const std::vector< nest::spikecounter > &spikes, const double t_trig)
{
  return 1.0;
}

template <typename targetidentifierT>
void curiousnest::CuriousSynapse< targetidentifierT >::trigger_update_weight
( const nest::thread tr,
  const std::vector< nest::spikecounter > &spikes,
  const double t_trig,
  const nest::CommonSynapseProperties &cp
)
{
  double eligibility = compute_eligibility(&spikes, t_trig);

  double helper = weight_;
  weight_ += learning_rate_*(reward_ + curiosity_*fabs(weight0_ - weight1_))*eligibility_;
  weight_ = min(max_weight_, weight_);
  weight1_ = weight0_;
  weight0_ = helper;
}