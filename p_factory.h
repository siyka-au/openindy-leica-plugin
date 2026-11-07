#ifndef P_FACTORY_H
#define P_FACTORY_H
#include <string>
#include <vector>

#include "p_leicatachymeter.h"
#include "plugin.h"
#include "sensor.h"
#include "totalstation.h"

using namespace oi;

/*!
 * \brief The LeicaPlugin class
 * A first-class instrument family living entirely outside the core repos:
 * everything else in the Plugin interface (functions, bundle adjustments,
 * simulations, tools, exchanges) is out of scope for this plugin, so those
 * factory methods just return empty lists - PseudoTracker and every fit/
 * construct/transform function still live in OpenIndyDefaultPlugin.
 */
class LeicaPlugin : public Plugin {
 public:
  LeicaPlugin();

  std::vector<oi::Guarded<Sensor> > createSensors();
  std::vector<oi::Guarded<Function> > createFunctions();
  std::vector<oi::Guarded<BundleAdjustment> > createBundleAdjustments();
  std::vector<oi::Guarded<SimulationModel> > createSimulations();
  std::vector<oi::Guarded<ExchangeSimpleAscii> > createSimpleAsciiExchanges();
  std::vector<oi::Guarded<ExchangeDefinedFormat> >
  createDefinedFormatExchanges();

  oi::Guarded<Sensor> createSensor(const std::string& name);
  oi::Guarded<Function> createFunction(const std::string& name);
  oi::Guarded<BundleAdjustment> createBundleAdjustment(const std::string& name);
  oi::Guarded<SimulationModel> createSimulation(const std::string& name);
  oi::Guarded<ExchangeSimpleAscii> createSimpleAsciiExchange(
      const std::string& name);
  oi::Guarded<ExchangeDefinedFormat> createDefinedFormatExchange(
      const std::string& name);
};

#endif  // P_FACTORY_H
