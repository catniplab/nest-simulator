#include <cmath>

#include "connection.h"
#include "static_connection.h"

#include "curious_synapse.h"

using namespace std;

template <typename targetidentifierT>
curiousnest::CuriousSynapse< targetidentifierT >::CuriousSynapse(map<string, double> cp)
{
  curious_properties_ = cp;

  if (curious_properties_.count("curiosity") == 0)
  {
    curious_properties_["curiosity"] = 0.0;
  }
  if (curious_properties_.count("learning_rate") == 0)
  {
    curious_properties_["learning_rate"] = 0.01;
  }
  if (curious_properties_.count("max_weight") == 0)
  {
    curious_properties_["max_weight"] = 1.0;
  }
  if (curious_properties_["min_weight"] == 0)
  {
    curious_properties_["min_weight"] == 0.0;
  }
  if (curious_properties_.count("reward") == 0)
  {
    curious_properties_["reward"] = 0.0;
  }
  if (curious_properties_.count("eligibility_slope") == 0)
  {
    curious_properties_["eligibility_slope"] = 1.0;
  }
  if (curious_properties_.count("eligibility_decay") == 0)
  {
    curious_properties_["eligibility_decay"] = 1.0;
  }
  if (curious_properties_.count("a_plus") == 0)
  {
    curious_properties_["a_plus"] = 1.0;
  }
  if (curious_properties_.count("a_minus") == 0)
  {
    curious_properties_["a_minus"] = 1.0;
  }
  if (curious_properties_.count("tau_plus") == 0)
  {
    curious_properties_["tau_plus"] = 1.0;
  }
  if (curious_properties_.count("tau_minus") == 0)
  {
    curious_properties_["tau_minus"] = 1.0;
  }
}

double eligibility_fcn (double t, double slope, double decay)
{
  //decay is assumed to be positive
  return slope*t*exp(-decay*t);
}

double learning_curve (double dt, double a_plus, double a_minus, double tau_plus, double tau_minus)
{
  if (dt < 0.0)
  {
    return -a_minus*exp(dt/tau_minus);
  }
  else
  {
    return a_plus*exp(-dt/tau_plus);
  }
}

double compute_eligibility(const vector< nest::spikecounter > &spikes, map< string, double > cur_p)
{
  return 1.0;
}

template <typename targetidentifierT>
void curiousnest::CuriousSynapse< targetidentifierT >::update_weight
( const nest::thread tr,
  const CommonProperties& cp
)
{
  double eligibility = compute_eligibility(spikes, curious_properties_);

  double w = weight_;
  double lr = curious_properties_["learning_rate"];
  double r = curious_properties_["reward"];
  double c = curious_properties_["curiosity"];
  double w0 = curious_properties["weight0"];
  double w1 = curious_properties["weight1"];
  double maw = curious_properties["max_weight"];
  double miw = curious_properties["min_weight"];

  //where the magic happens
  weight_ = max(miw, min(maw, w + eligibility*lr*(r + c*fabs(w0 - w1))));

  curious_properties_["weight0"] = w;
  curious_properties_["weight1"] = w0;
}