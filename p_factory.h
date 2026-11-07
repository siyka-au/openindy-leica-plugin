#ifndef P_FACTORY_H
#define P_FACTORY_H
#include <memory>
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

  std::vector<std::unique_ptr<Sensor>> createSensors();
  std::vector<std::unique_ptr<Function>> createFunctions();
  std::vector<std::unique_ptr<BundleAdjustment>> createBundleAdjustments();
  std::vector<std::unique_ptr<SimulationModel>> createSimulations();
  std::vector<std::unique_ptr<ExchangeSimpleAscii>>
  createSimpleAsciiExchanges();
  std::vector<std::unique_ptr<ExchangeDefinedFormat>>
  createDefinedFormatExchanges();

  std::unique_ptr<Sensor> createSensor(const std::string& name);
  std::unique_ptr<Function> createFunction(const std::string& name);
  std::unique_ptr<BundleAdjustment> createBundleAdjustment(
      const std::string& name);
  std::unique_ptr<SimulationModel> createSimulation(const std::string& name);
  std::unique_ptr<ExchangeSimpleAscii> createSimpleAsciiExchange(
      const std::string& name);
  std::unique_ptr<ExchangeDefinedFormat> createDefinedFormatExchange(
      const std::string& name);
};

#endif  // P_FACTORY_H
