#include "p_factory.h"

using namespace oi;

LeicaPlugin::LeicaPlugin(QObject *parent) : QObject(parent){

}

QList<QPointer<Sensor> > LeicaPlugin::createSensors(){
    QList<QPointer<Sensor> > resultSet;
    resultSet.append(new LeicaTachymeter());
    return resultSet;
}

QList<QPointer<Function> > LeicaPlugin::createFunctions(){
    return QList<QPointer<Function> >();
}

QList<QPointer<BundleAdjustment> > LeicaPlugin::createBundleAdjustments(){
    return QList<QPointer<BundleAdjustment> >();
}

QList<QPointer<SimulationModel> > LeicaPlugin::createSimulations(){
    return QList<QPointer<SimulationModel> >();
}

QList<QPointer<Tool> > LeicaPlugin::createTools(){
    return QList<QPointer<Tool> >();
}

QList<QPointer<ExchangeSimpleAscii> > LeicaPlugin::createSimpleAsciiExchanges(){
    return QList<QPointer<ExchangeSimpleAscii> >();
}

QList<QPointer<ExchangeDefinedFormat> > LeicaPlugin::createDefinedFormatExchanges(){
    return QList<QPointer<ExchangeDefinedFormat> >();
}

QPointer<Sensor> LeicaPlugin::createSensor(const QString &name){
    if(name.compare("LeicaTachymeter") == 0){
        return new LeicaTachymeter();
    }
    return QPointer<Sensor>(NULL);
}

QPointer<Function> LeicaPlugin::createFunction(const QString &/*name*/){
    return QPointer<Function>(NULL);
}

QPointer<BundleAdjustment> LeicaPlugin::createBundleAdjustment(const QString &/*name*/){
    return QPointer<BundleAdjustment>(NULL);
}

QPointer<SimulationModel> LeicaPlugin::createSimulation(const QString &/*name*/){
    return QPointer<SimulationModel>(NULL);
}

QPointer<Tool> LeicaPlugin::createTool(const QString &/*name*/){
    return QPointer<Tool>(NULL);
}

QPointer<ExchangeSimpleAscii> LeicaPlugin::createSimpleAsciiExchange(const QString &/*name*/){
    return QPointer<ExchangeSimpleAscii>(NULL);
}

QPointer<ExchangeDefinedFormat> LeicaPlugin::createDefinedFormatExchange(const QString &/*name*/){
    return QPointer<ExchangeDefinedFormat>(NULL);
}
