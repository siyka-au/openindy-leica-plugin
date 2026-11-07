#ifndef P_FACTORY_H
#define P_FACTORY_H

#include <QObject>
#include <QString>
#include <QtGlobal>

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
class LeicaPlugin : public QObject, Plugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID Plugin_iidd FILE "metaInfo.json")
  Q_INTERFACES(Plugin)

 public:
  explicit LeicaPlugin(QObject* parent = 0);

  QList<oi::Guarded<Sensor> > createSensors();
  QList<oi::Guarded<Function> > createFunctions();
  QList<oi::Guarded<BundleAdjustment> > createBundleAdjustments();
  QList<oi::Guarded<SimulationModel> > createSimulations();
  QList<oi::Guarded<ExchangeSimpleAscii> > createSimpleAsciiExchanges();
  QList<oi::Guarded<ExchangeDefinedFormat> > createDefinedFormatExchanges();

  oi::Guarded<Sensor> createSensor(const QString& name);
  oi::Guarded<Function> createFunction(const QString& name);
  oi::Guarded<BundleAdjustment> createBundleAdjustment(const QString& name);
  oi::Guarded<SimulationModel> createSimulation(const QString& name);
  oi::Guarded<ExchangeSimpleAscii> createSimpleAsciiExchange(
      const QString& name);
  oi::Guarded<ExchangeDefinedFormat> createDefinedFormatExchange(
      const QString& name);
};

#endif  // P_FACTORY_H
