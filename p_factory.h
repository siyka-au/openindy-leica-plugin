#ifndef OI_LEICA_PLUGIN_P_FACTORY_H_
#define OI_LEICA_PLUGIN_P_FACTORY_H_
#include <memory>
#include <string>
#include <vector>

#include "p_leica_tachymeter.h"
#include "plugin.h"
#include "sensor.h"
#include "total_station.h"

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

  std::vector<std::unique_ptr<Sensor>> createSensors() override;
  std::vector<std::unique_ptr<Function>> createFunctions() override;
  std::vector<std::unique_ptr<BundleAdjustment>> createBundleAdjustments()
      override;
  std::vector<std::unique_ptr<SimulationModel>> createSimulations() override;
  std::vector<std::unique_ptr<ExchangeSimpleAscii>> createSimpleAsciiExchanges()
      override;
  std::vector<std::unique_ptr<ExchangeDefinedFormat>>
  createDefinedFormatExchanges() override;

  std::unique_ptr<Sensor> createSensor(const std::string& name) override;
  std::unique_ptr<Function> createFunction(const std::string& name) override;
  std::unique_ptr<BundleAdjustment> createBundleAdjustment(
      const std::string& name) override;
  std::unique_ptr<SimulationModel> createSimulation(
      const std::string& name) override;
  std::unique_ptr<ExchangeSimpleAscii> createSimpleAsciiExchange(
      const std::string& name) override;
  std::unique_ptr<ExchangeDefinedFormat> createDefinedFormatExchange(
      const std::string& name) override;
};

#endif  // OI_LEICA_PLUGIN_P_FACTORY_H_
