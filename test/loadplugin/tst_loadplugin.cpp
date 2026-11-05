#include <QList>
#include <QPointer>
#include <QString>
#include <QtTest>

#include "plugin.h"
#include "sensortype.h"

using namespace oi;

/*!
 * Stage 5's acceptance criterion: "the Leica plugin builds and loads from
 * its own repo" - this loads the actual built .so through QPluginLoader,
 * the same mechanism PluginRepository uses at real app startup, rather
 * than just linking against the driver class directly. A driver that only
 * compiles but never actually resolves as a Qt plugin (wrong IID, missing
 * Q_PLUGIN_METADATA, metaInfo.json mismatch) would pass every other test
 * in this repo and still fail to load in the real app.
 */
class LoadPluginTest : public QObject {
  Q_OBJECT

 private Q_SLOTS:
  void testLoadPlugin();
};

void LoadPluginTest::testLoadPlugin() {
  QString pluginPath = PLUGIN_PATH;

  QVERIFY2(QFile::exists(pluginPath), pluginPath.toLatin1().data());
  QPluginLoader pluginLoader(pluginPath);

  QObject* plugin = pluginLoader.instance();
  QVERIFY2(plugin, pluginLoader.errorString().toLatin1().data());

  Plugin* oiPlugin = qobject_cast<Plugin*>(plugin);
  QVERIFY2(oiPlugin, "qobject_cast");

  // this plugin is Leica-only: no functions, no bundle adjustments, no
  // simulations, no tools, no exchanges - just the sensor it exists for
  QVERIFY2(oiPlugin->createFunctions().isEmpty(),
           "expected no functions from a sensor-only plugin");

  QList<QPointer<Sensor> > sensors = oiPlugin->createSensors();
  QCOMPARE(sensors.size(), 1);

  QPointer<Sensor> sensor = oiPlugin->createSensor("LeicaTachymeter");
  QVERIFY2(!sensor.isNull(), "createSensor(\"LeicaTachymeter\") returned null");

  sensor->init();

  // same derivation PluginRepository itself applies at scan time (Stage 1's
  // open SensorType, resolved from plugin metadata rather than a core enum)
  const SensorType type =
      SensorType::fromInterfaceId(sensor->getMetaData().iid);
  QVERIFY2(type.isValid(),
           "LeicaTachymeter's IID must resolve to a valid SensorType");

  QVERIFY2(!sensor->getSupportedMeasurementConfigs().isEmpty(),
           "LeicaTachymeter must publish its own measurement configs");
}

QTEST_APPLESS_MAIN(LoadPluginTest)

#include "tst_loadplugin.moc"
