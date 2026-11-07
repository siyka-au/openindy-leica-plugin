#include "p_factory.h"

#include <vector>

#include "metaInfo.h"

using namespace oi;

LeicaPlugin::LeicaPlugin() {}

std::vector<oi::Guarded<Sensor> > LeicaPlugin::createSensors() {
  std::vector<oi::Guarded<Sensor> > resultSet;
  resultSet.push_back(new LeicaTachymeter());
  return resultSet;
}

std::vector<oi::Guarded<Function> > LeicaPlugin::createFunctions() {
  return std::vector<oi::Guarded<Function> >();
}

std::vector<oi::Guarded<BundleAdjustment> >
LeicaPlugin::createBundleAdjustments() {
  return std::vector<oi::Guarded<BundleAdjustment> >();
}

std::vector<oi::Guarded<SimulationModel> > LeicaPlugin::createSimulations() {
  return std::vector<oi::Guarded<SimulationModel> >();
}

std::vector<oi::Guarded<ExchangeSimpleAscii> >
LeicaPlugin::createSimpleAsciiExchanges() {
  return std::vector<oi::Guarded<ExchangeSimpleAscii> >();
}

std::vector<oi::Guarded<ExchangeDefinedFormat> >
LeicaPlugin::createDefinedFormatExchanges() {
  return std::vector<oi::Guarded<ExchangeDefinedFormat> >();
}

oi::Guarded<Sensor> LeicaPlugin::createSensor(const std::string& name) {
  if (name.compare("LeicaTachymeter") == 0) {
    return new LeicaTachymeter();
  }
  return oi::Guarded<Sensor>(nullptr);
}

oi::Guarded<Function> LeicaPlugin::createFunction(const std::string& /*name*/) {
  return oi::Guarded<Function>(nullptr);
}

oi::Guarded<BundleAdjustment> LeicaPlugin::createBundleAdjustment(
    const std::string& /*name*/) {
  return oi::Guarded<BundleAdjustment>(nullptr);
}

oi::Guarded<SimulationModel> LeicaPlugin::createSimulation(
    const std::string& /*name*/) {
  return oi::Guarded<SimulationModel>(nullptr);
}

oi::Guarded<ExchangeSimpleAscii> LeicaPlugin::createSimpleAsciiExchange(
    const std::string& /*name*/) {
  return oi::Guarded<ExchangeSimpleAscii>(nullptr);
}

oi::Guarded<ExchangeDefinedFormat> LeicaPlugin::createDefinedFormatExchange(
    const std::string& /*name*/) {
  return oi::Guarded<ExchangeDefinedFormat>(nullptr);
}

OI_DECLARE_PLUGIN_WITH_METADATA(LeicaPlugin, kOiPluginMetadataJson)
