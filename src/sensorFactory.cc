#include "sensorFactory.hh"
#include <iostream>
#include <cassert>
#include "object_cc.hh"
#include "Sensor.hh"
#include "PointListSensor.hh"
#include "ActivationTimeSensor.hh"

using namespace std;

namespace
{
   Sensor* scanPointListSensor(OBJECT* obj, const SensorParms& sp, const Anatomy& anatomy);
   Sensor* scanActivationTimeSensor(OBJECT* obj, const SensorParms& sp, const Anatomy& anatomy);
}


Sensor* sensorFactory(const std::string& name, const Anatomy& anatomy)
{
  OBJECT* obj = objectFind(name, "SENSOR");
  string method;
  objectGet(obj, "method", method, "undefined");
  SensorParms sp;
  objectGet(obj, "printRate", sp.printRate, "1");
  objectGet(obj, "evalRate",  sp.evalRate,  "1");


  if (method == "undefined")
    assert(false);
  else if (method == "pointlist")
     return scanPointListSensor(obj, sp, anatomy);
  else if (method == "activationTime")
     return scanActivationTimeSensor(obj, sp, anatomy);

  assert(false); // reachable only due to bad input
}


namespace
{
   Sensor* scanPointListSensor(OBJECT* obj, const SensorParms& sp, const Anatomy& anatomy)
   {
      PointListSensorParms p;
      objectGet(obj, "pointlist",   p.pointlist);
      objectGet(obj, "startTime",   p.startTime,   "0.0");
      objectGet(obj, "endTime",     p.endTime,     "-1.0");
      objectGet(obj, "printDerivs", p.printDerivs, "0");
      objectGet(obj, "filebase",    p.filebase,    "sensor.pointlist");
      return new PointListSensor(sp, p, anatomy);
   }
}

namespace
{
   Sensor* scanActivationTimeSensor(OBJECT* obj, const SensorParms& sp, const Anatomy& anatomy)
   {
      ActivationTimeSensorParms p;
      objectGet(obj, "filename",  p.filename,  "activationTime");
      return new ActivationTimeSensor(sp, p, anatomy);
   }
}