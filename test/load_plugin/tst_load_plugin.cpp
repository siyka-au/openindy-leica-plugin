#include <QPointer>
#include <QString>
#include <QtTest>
#include <vector>

#include "plugin.h"
#include "plugin_loader.h"
#include "sensor_type.h"

using namespace oi;

/*!
 * Stage 5's acceptance criterion: "the Leica plugin builds and loads from
 * its own repo" - this loads the actual built .so through core's
 * oi::PluginLoader, the same mechanism the app uses at startup, rather
 * than just linking against the driver class directly. A driver that only
 * compiles but never actually resolves as a plugin (missing
 * OI_DECLARE_PLUGIN entry points, ABI mismatch, meta_info.json mismatch)
 * would pass every other test in this repo and still fail to load in the
 * real app.
 */
class LoadPluginTest : public QObject {
  Q_OBJECT

 private Q_SLOTS:
  void testLoadPlugin();
};

void LoadPluginTest::testLoadPlugin() {
  QString pluginPath = PLUGIN_PATH;

  QVERIFY2(QFile::exists(pluginPath), pluginPath.toLatin1().data());
  oi::PluginLoadResult loaded =
      oi::PluginLoader::load(pluginPath.toStdString());
  QVERIFY2(loaded, loaded.error.c_str());

  Plugin* oiPlugin = loaded.plugin.get();
  QVERIFY2(
      loaded.plugin.metadataJson().find("\"isOiPlugin\"") != std::string::npos,
      "plugin metadata missing");

  // this plugin is Leica-only: no functions, no bundle adjustments, no
  // simulations, no tools, no exchanges - just the sensor it exists for
  QVERIFY2(oiPlugin->createFunctions().empty(),
           "expected no functions from a sensor-only plugin");

  std::vector<std::unique_ptr<Sensor>> sensors = oiPlugin->createSensors();
  QCOMPARE(sensors.size(), 1);

  std::unique_ptr<Sensor> sensor = oiPlugin->createSensor("LeicaTachymeter");
  QVERIFY2(sensor != nullptr,
           "createSensor(\"LeicaTachymeter\") returned null");

  sensor->init();

  // same derivation PluginRepository itself applies at scan time (Stage 1's
  // open SensorType, resolved from plugin metadata rather than a core enum)
  const SensorType type =
      SensorType::fromInterfaceId(sensor->getMetaData().iid);
  QVERIFY2(type.isValid(),
           "LeicaTachymeter's IID must resolve to a valid SensorType");

  QVERIFY2(!sensor->getSupportedMeasurementConfigs().empty(),
           "LeicaTachymeter must publish its own measurement configs");
}

QTEST_APPLESS_MAIN(LoadPluginTest)

#include "tst_load_plugin.moc"
