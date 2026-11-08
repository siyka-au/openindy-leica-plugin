#include "p_factory.h"

#include <memory>
#include <vector>

#include "meta_info.h"

using namespace oi;

LeicaPlugin::LeicaPlugin() {}

std::vector<std::unique_ptr<Sensor>> LeicaPlugin::createSensors() {
  std::vector<std::unique_ptr<Sensor>> resultSet;
  resultSet.push_back(std::make_unique<LeicaTachymeter>());
  return resultSet;
}

std::vector<std::unique_ptr<Function>> LeicaPlugin::createFunctions() {
  return {};
}

std::vector<std::unique_ptr<BundleAdjustment>>
LeicaPlugin::createBundleAdjustments() {
  return {};
}

std::vector<std::unique_ptr<SimulationModel>> LeicaPlugin::createSimulations() {
  return {};
}

std::vector<std::unique_ptr<ExchangeSimpleAscii>>
LeicaPlugin::createSimpleAsciiExchanges() {
  return {};
}

std::vector<std::unique_ptr<ExchangeDefinedFormat>>
LeicaPlugin::createDefinedFormatExchanges() {
  return {};
}

std::unique_ptr<Sensor> LeicaPlugin::createSensor(const std::string& name) {
  if (name.compare("LeicaTachymeter") == 0) {
    return std::make_unique<LeicaTachymeter>();
  }
  return nullptr;
}

std::unique_ptr<Function> LeicaPlugin::createFunction(
    const std::string& /*name*/) {
  return nullptr;
}

std::unique_ptr<BundleAdjustment> LeicaPlugin::createBundleAdjustment(
    const std::string& /*name*/) {
  return nullptr;
}

std::unique_ptr<SimulationModel> LeicaPlugin::createSimulation(
    const std::string& /*name*/) {
  return nullptr;
}

std::unique_ptr<ExchangeSimpleAscii> LeicaPlugin::createSimpleAsciiExchange(
    const std::string& /*name*/) {
  return nullptr;
}

std::unique_ptr<ExchangeDefinedFormat> LeicaPlugin::createDefinedFormatExchange(
    const std::string& /*name*/) {
  return nullptr;
}

OI_DECLARE_PLUGIN_WITH_METADATA(LeicaPlugin, kOiPluginMetadataJson)
