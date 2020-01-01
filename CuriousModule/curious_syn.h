#ifndef CURIOUS_SYN
#define CURIOUS_SYN

#include "slifunction.h"
#include "slimodule.h"

#include "connection.h"
#include "static_connection.h"

namespace curiousnest
{
  template <typename targetidentifierT>
  class CuriousSyn : public StaticConnection
  {

    private:

      double curiosity_;
      double learning_rate_;
      double weight_
      double weight0_;
      double weight1_;
      double reward_;

    public:
      //! Type to use for representing common synapse properties
      typedef nest::CommonSynapseProperties CommonPropertiesType;

      //! Shortcut for base class
      typedef nest::Connection< targetidentifierT > ConnectionBase;

      CuriousSyn () : ConnectionBase(), weight(1.0) {}
      ~CuriousSyn () {}

      void trigger_update_weight( const thread tr,
                                  const std::vector< spikecounter > &spikes,
                                  const double t_trig,
                                  const CommonSynapseProperties &cp);

      void send (nest::Event &e,
                 double_t t_lastspike,
                 const nest::CommonSynapseProperties &cp
                 const nest::thread tr,
                 const std:vector< nest::spikecounter > &spikes);

      //! Store connection status information in dictionary
      void get_status( DictionaryDatum& d ) const;

      /**
       * Set connection status.
       *
       * @param d Dictionary with new parameter values
       * @param cm ConnectorModel is passed along to validate new delay values
       */
      void set_status( const DictionaryDatum& d, nest::ConnectorModel& cm );

      void set_reward (double reward)
      {
        reward_ = reward;
      }
  };

  template <typename targetidentifierT>
  inline void curiousnest::CuriousSyn< targetidentifierT >::send
  ( nest::Event &e,
    double_t t_lastspike,
    const nest::CommonSynapseProperties &cp,
    const nest::thread tr,
    const std::vector< nest::spikecounter > &spikes )
  {
    trigger_update_weight(tr, &spikes, t_lastspike, &cp);

    e.set_receiver(target_);
    e.set_weight(weight_);
    e.set_delay_steps(delay_);
    e.set_rport(rport_);
    e();
  }

  template <typename targetidentifierT>
  void CuriousSyn< targetidentifierT >::get_status( DictionaryDatum& d ) const
  {
    ConnectionBase::get_status(d);
    def< double >(d, nest::names::weight, weight_);
    def< long >(d, nest::names::size_of, sizeof(*this));
  }

  template < typename targetidentifierT >
  void CuriousSyn< targetidentifierT >::set_status
  (const DictionaryDatum& d,   nest::ConnectorModel& cm)
  {
    ConnectionBase::set_status( d, cm );
    updateValue< double >( d, nest::names::weight, weight_ );
  }
}

#endif