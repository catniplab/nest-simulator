#include "curious_connection.h"

template <typename targetidentifierT>
void nest::CuriousConnection< targetidentifierT >::update_dynamics ()
{
  double helper = weight_;
  weight_ += rate_*(reward_ + curiosity_*abs(weight0_ - weight1_))*eligibility_;
  weight1_ = weight0_;
  weight0_ = helper;
}