#ifndef OI_LEICA_PLUGIN_SENSORS_TACHYMETER_LEICA_GEO_COM_P_LEICA_TACHYMETER_H_
#define OI_LEICA_PLUGIN_SENSORS_TACHYMETER_LEICA_GEO_COM_P_LEICA_TACHYMETER_H_
#include <QDateTime>
#include <QDebug>
#include <QObject>
#include <QPointer>
#include <QThread>
#include <QtGlobal>
#include <QtSerialPort/QSerialPort>
#include <map>
#include <memory>
#include <vector>

#include "total_station.h"

using namespace oi;

/*!
 * \brief The LeicaTachymeter class
 */
class LeicaTachymeter : public TotalStation {
 public:
  // ############################
  // sensor initialization method
  // ############################

  void init() override;

  // ########################
  // sensor state and actions
  // ########################

  bool doSelfDefinedAction(const std::string& action) override;

  bool abortAction() override;

  bool connectSensor() override;
  bool disconnectSensor() override;

  std::vector<std::unique_ptr<Reading>> measure(
      const MeasurementConfig& mConfig) override;
  oi::ValueMap readingStream(const ReadingTypes& streamFormat) override;

  bool getConnectionState() override;
  bool getIsReadyForMeasurement() override;
  std::map<std::string, std::string> getSensorStatus() override;
  bool getIsBusy() override;

 protected:
  // ############################
  // special totalstation methods
  // ############################

  bool move(const double& azimuth, const double& zenith, const double& distance,
            const bool& isRelative) override;
  bool move(const double& x, const double& y, const double& z) override;

  bool toggleSightOrientation() override;

  // #########################
  // Leica tachymeter specific
  // #########################

  // bool getLOCKState();
  // void deactiveLockState();
  // bool setLOCKState(QString currentState);
  // bool startTargetTracking();
  // bool fineAdjust();

 private:
  QPointer<QSerialPort> serial;

  std::vector<std::unique_ptr<Reading>> measurePolar(
      const MeasurementConfig& mConfig);
  std::vector<std::unique_ptr<Reading>> measureDistance(
      const MeasurementConfig& mConfig);
  std::vector<std::unique_ptr<Reading>> measureDirection(
      const MeasurementConfig& mConfig);
  std::vector<std::unique_ptr<Reading>> measureCartesian(
      const MeasurementConfig& mConfig);

  QString receive();
  // void getError(QSerialPort::SerialPortError);
  bool executeEDM();
  bool executeCommand(QString);

  bool checkCommandRC(QString command);

  SensorFaces getCurrentFace(double zenith);

  bool setTargetTypeMeasure();
  bool setTargetTypeStream();
  // bool setAdjustMode();

  // void stopTrackingAfterMeasure();

  // bool laserOn;
  // bool fineAdjusted;

  // bool measureWatchWindow;
  // bool watchWindowOpen;
  // ReadingTypes currentStreamFormat;
  // void stopWatchWindowForMeasurement();
  // void restartWatchWindowAfterMeasurement();

  // oi::Guarded<Reading> getQuickMeasReading(QString receive);

  // void activateLaserPointer();
  // void deactivateLaserPointer();

  // void stopTrackingMode();

  std::unique_ptr<Reading> getStreamValues();
};

#endif  // OI_LEICA_PLUGIN_SENSORS_TACHYMETER_LEICA_GEO_COM_P_LEICA_TACHYMETER_H_
