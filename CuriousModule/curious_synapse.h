#ifndef CURIOUS_SYNAPSE
#define CURIOUS_SYNAPSE

#include "connection.h"

using namespace std;

namespace curiousnest
{

  typedef nest::CommonSynapseProperties CommonProperties;

  template <typename targetidentifierT>
  class CuriousSynapse : public nest::Connection< targetidentifierT >
  {
    private:
      map< string, double > curious_properties_;
      list< double > pre_syn_spikes_;
      list< double > post_syn_spikes_;

    public:

      CuriousSynapse (map<string, double> curious_properties) {}
      ~CuriousSynapse () {}

      void update_weight ( const nest::thread tr,
                           const CommonProperties& cp );

      void send ( nest::Event& e,
                  double_t t_lastspike,
                  const CommonProperties& cp,
                  const nest::thread thr );
      /*
      //! Store connection status information in dictionary
      void get_status (DictionaryDatum& d) const;

      /**
       * Set connection status.
       *
       * @param d Dictionary with new parameter values
       * @param cm ConnectorModel is passed along to validate new delay values

      void set_status (const DictionaryDatum& d, nest::ConnectorModel& cm);
      */
      void get_pre_syn_spikes ()
      {
        return pre_syn_spikes_;
      }

      void get_post_syn_spikes ()
      {
        return post_syn_spikes_;
      }

      void get_curious_properties ()
      {
        return curious_properties_;
      }

      void set_curious_properties (map<string, double> curious_properties)
      {
        if (curious_properties.count("curiosity") > 0)
        {
          curious_properties_["curiosity"] = curious_properties["curiosity"];
        }
        if (curious_properties.count("learning_rate") > 0)
        {
          curious_properties_["learning_rate"] = curious_properties["learning_rate"];
        }
        if (curious_properties.count("max_weight") > 0)
        {
          curious_properties_["max_weight"] = curious_properties["max_weight"];
        }
        if (curious_properties.count("min_weight") > 0)
        {
          curious_properties_["min_weight"] = curious_properties["min_weight"];
        }
        if (curious_properties.count("reward") > 0)
        {
          curious_properties_["reward"] = curious_properties["reward"];
        }
        if (curious_properties.count("eligibility_slope") > 0)
        {
          curious_properties_["eligibility_slope"] = curious_properties["eligibility_slope"];
        }
        if (curious_properties.count("eligibility_decay") > 0)
        {
          curious_properties_["eligibility_decay"] = curious_properties["eligibility_decay"];
        }
        if (curious_properties.count("a_plus") > 0)
        {
          curious_properties_["a_plus"] = curious_properties["a_plus"];
        }
        if (curious_properties.count("a_minus") > 0)
        {
          curious_properties_["a_minus"] = curious_properties["a_minus"];
        }
        if (curious_properties.count("tau_plus") > 0)
        {
          curious_properties_["tau_plus"] = curious_properties["tau_plus"];
        }
        if (curious_properties.count("tau_minus") > 0)
        {
          curious_properties_["tau_minus"] = curious_properties["tau_minus"];
        }
      }

  };

  template <typename targetidentifierT>
  inline void curiousnest::CuriousSynapse< targetidentifierT >::send ( nest::Event& e,
                                                                       double_t t_lastspike,
                                                                       const CommonProperties& cp,
                                                                       const nest::thread thr )
  {
    pres_syn_spikes_.push_front(t_lastspike);
    update_weight(thr, pres_syn_spikes_, &cp);

    e.set_weight(weight_);
    e.set_delay_steps(Connection::get_delay_steps());
    e.set_receiver(*nest::Connection< targetIdentifierT >::get_target(thr));
    e.set_rport(Connection::get_rport());
    e();
  }

/*
  template <typename targetidentifierT>
  void CuriousSynapse< targetidentifierT >::get_status(DictionaryDatum& d) const
  {
    ConnectionBase::get_status(d);
    def< double >(d, nest::names::weight, weight_);
    def< long >(d, nest::names::size_of, sizeof(*this));
  }

  template < typename targetidentifierT >
  void CuriousSynapse< targetidentifierT >::set_status
  (const DictionaryDatum& d, nest::ConnectorModel& cm)
  {
    ConnectionBase::set_status(d, cm);
    updateValue< double >(d, nest::names::weight, weight_);
  }
*/
}

#endif