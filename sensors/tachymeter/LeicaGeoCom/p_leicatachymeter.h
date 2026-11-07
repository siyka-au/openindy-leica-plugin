#ifndef P_LEICATACHYMETER_H
#define P_LEICATACHYMETER_H
#include <QDateTime>
#include <QDebug>
#include <QObject>
#include <QThread>
#include <QtGlobal>
#include <QtSerialPort/QSerialPort>
#include <map>
#include <vector>

#include "totalstation.h"

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

  bool doSelfDefinedAction(const QString& action) override;

  bool abortAction() override;

  bool connectSensor() override;
  bool disconnectSensor() override;

  std::vector<oi::Guarded<Reading> > measure(
      const MeasurementConfig& mConfig) override;
  std::map<QString, QVariant> readingStream(
      const ReadingTypes& streamFormat) override;

  bool getConnectionState() override;
  bool getIsReadyForMeasurement() override;
  std::map<QString, QString> getSensorStatus() override;
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

  std::vector<oi::Guarded<Reading> > measurePolar(
      const MeasurementConfig& mConfig);
  std::vector<oi::Guarded<Reading> > measureDistance(
      const MeasurementConfig& mConfig);
  std::vector<oi::Guarded<Reading> > measureDirection(
      const MeasurementConfig& mConfig);
  std::vector<oi::Guarded<Reading> > measureCartesian(
      const MeasurementConfig& mConfig);

  QSerialPort::BaudRate myBaudRate;
  QSerialPort::DataBits myDataBits;
  QSerialPort::Parity myParity;
  QSerialPort::StopBits myStopBits;
  QSerialPort::FlowControl myFlowControl;

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

  oi::Guarded<Reading> getStreamValues();
};

#endif  // P_LEICATACHYMETER_H
