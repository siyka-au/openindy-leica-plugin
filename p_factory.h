#ifndef P_FACTORY_H
#define P_FACTORY_H

#include <QtGlobal>
#include <QObject>
#include <QString>

#include "plugin.h"

#include "sensor.h"
#include "totalstation.h"

#include "p_leicatachymeter.h"

using namespace oi;

/*!
 * \brief The LeicaPlugin class
 * A first-class instrument family living entirely outside the core repos:
 * everything else in the Plugin interface (functions, bundle adjustments,
 * simulations, tools, exchanges) is out of scope for this plugin, so those
 * factory methods just return empty lists - PseudoTracker and every fit/
 * construct/transform function still live in OpenIndyDefaultPlugin.
 */
class LeicaPlugin : public QObject, Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID Plugin_iidd FILE "metaInfo.json")
    Q_INTERFACES(Plugin)

public:
    explicit LeicaPlugin(QObject *parent = 0);

    QList<QPointer<Sensor> > createSensors();
    QList<QPointer<Function> > createFunctions();
    QList<QPointer<BundleAdjustment> > createBundleAdjustments();
    QList<QPointer<SimulationModel> > createSimulations();
    QList<QPointer<Tool> > createTools();
    QList<QPointer<ExchangeSimpleAscii> > createSimpleAsciiExchanges();
    QList<QPointer<ExchangeDefinedFormat> > createDefinedFormatExchanges();

    QPointer<Sensor> createSensor(const QString &name);
    QPointer<Function> createFunction(const QString &name);
    QPointer<BundleAdjustment> createBundleAdjustment(const QString &name);
    QPointer<SimulationModel> createSimulation(const QString &name);
    QPointer<Tool> createTool(const QString &name);
    QPointer<ExchangeSimpleAscii> createSimpleAsciiExchange(const QString &name);
    QPointer<ExchangeDefinedFormat> createDefinedFormatExchange(const QString &name);

};

#endif // P_FACTORY_H
