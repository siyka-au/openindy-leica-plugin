#include "p_factory.h"

using namespace oi;

LeicaPlugin::LeicaPlugin(QObject* parent) : QObject(parent) {}

QList<oi::Guarded<Sensor> > LeicaPlugin::createSensors() {
  QList<oi::Guarded<Sensor> > resultSet;
  resultSet.append(new LeicaTachymeter());
  return resultSet;
}

QList<oi::Guarded<Function> > LeicaPlugin::createFunctions() {
  return QList<oi::Guarded<Function> >();
}

QList<oi::Guarded<BundleAdjustment> > LeicaPlugin::createBundleAdjustments() {
  return QList<oi::Guarded<BundleAdjustment> >();
}

QList<oi::Guarded<SimulationModel> > LeicaPlugin::createSimulations() {
  return QList<oi::Guarded<SimulationModel> >();
}

QList<oi::Guarded<ExchangeSimpleAscii> >
LeicaPlugin::createSimpleAsciiExchanges() {
  return QList<oi::Guarded<ExchangeSimpleAscii> >();
}

QList<oi::Guarded<ExchangeDefinedFormat> >
LeicaPlugin::createDefinedFormatExchanges() {
  return QList<oi::Guarded<ExchangeDefinedFormat> >();
}

oi::Guarded<Sensor> LeicaPlugin::createSensor(const QString& name) {
  if (name.compare("LeicaTachymeter") == 0) {
    return new LeicaTachymeter();
  }
  return oi::Guarded<Sensor>(nullptr);
}

oi::Guarded<Function> LeicaPlugin::createFunction(const QString& /*name*/) {
  return oi::Guarded<Function>(nullptr);
}

oi::Guarded<BundleAdjustment> LeicaPlugin::createBundleAdjustment(
    const QString& /*name*/) {
  return oi::Guarded<BundleAdjustment>(nullptr);
}

oi::Guarded<SimulationModel> LeicaPlugin::createSimulation(
    const QString& /*name*/) {
  return oi::Guarded<SimulationModel>(nullptr);
}

oi::Guarded<ExchangeSimpleAscii> LeicaPlugin::createSimpleAsciiExchange(
    const QString& /*name*/) {
  return oi::Guarded<ExchangeSimpleAscii>(nullptr);
}

oi::Guarded<ExchangeDefinedFormat> LeicaPlugin::createDefinedFormatExchange(
    const QString& /*name*/) {
  return oi::Guarded<ExchangeDefinedFormat>(nullptr);
}
