/*********************************************************************
 * z60
 *
 * Copyright (C) 2022 Marcel Maage
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * LICENSE file for more details.
 */

#include "z60.h"

z60::z60(uint16_t hash, uint32_t serialNumber, HwType hwType, uint32_t swVersion, bool debugZ60, bool debugZ21, bool debugTrainbox)
    : MaerklinCanInterfaceObserver(hash, debugTrainbox),
      z21InterfaceObserver(hwType, swVersion, debugZ21),
      m_serialNumber(serialNumber),
      m_programmingActiv(false),
      m_directProgramming(false),
      m_debug(debugZ60)
{
}

z60::~z60()
{
}

void z60::begin()
{

  if (!m_preferences.begin(m_namespaceZ21, true))
  {
    Serial.println(F("Access preferences failed"));
  }
  else
  {
    ConfigLoco buffer[256];
    size_t sizeLocoMode = m_preferences.getBytesLength(m_keyLocoMode);
    size_t readSize = 0;
    Serial.print(F("sizeLocoMode "));
    Serial.println(sizeLocoMode);
    if (0 != sizeLocoMode)
    {
      readSize = m_preferences.getBytes(m_keyLocoMode, buffer, sizeLocoMode);
      if (readSize != sizeLocoMode)
      {
        Serial.println(F(" Failed to read locoMode"));
      }
    }
    Serial.print(F("readSize "));
    Serial.println(readSize);
    readSize /= sizeof(ConfigLoco);
    for (size_t i = 0; i < readSize; i++)
    {

      m_locos.emplace_back(DataLoco{buffer[i].adrZ21, fromZ21AdrToTrainboxAdr(buffer[i].adrZ21, buffer[i].mode), buffer[i].mode, false, 0, true, {buffer[i].steps, 0, 0, 0, 0, 0}});
    }

    // if (preferences.getBytes(keyTurnOutMode, turnOutMode, sizeof(turnOutMode)) != sizeof(turnOutMode))
    // {
    //   Serial.println(F(" Failed to read turnOutMode"));
    // }
    m_preferences.end();

    if (nullptr != m_configDataStream)
    {
      m_configDataStream->setHash(m_hash);
    }
  }

  MaerklinCanInterfaceObserver::begin();
  z21InterfaceObserver::begin();

  delay(1000);
  m_trainboxIdList.clear();
  m_stationList.clear();
  // check for train box or mobile station
  for (uint8_t i = 0; i < 5; i++)
  {
    sendPing();
    delay(500);
    if (m_trainboxIdList.size() != 0)
    {
      break;
    }
  }

  // Disable track voltage
  // z21InterfaceObserver::setPower(EnergyState::csTrackVoltageOff);
  // MaerklinCanInterfaceEsp32::sendSystemStop();

  // if (m_trainboxIdList.size() > 0)
  // {
  //   Serial.println("Found Trainbox");
  //   if (0 == m_stationList.size())
  //   {
  //     sendSetTrackProtocol(5, m_trainboxIdList.at(0)); // no mfx
  //     sendSetTrackProtocol(5, 0);                      // no mfx
  //     Serial.println("No Mobile Station");
  //   }
  //   sendSetMfxCounter(0, m_trainboxIdList.at(0));
  //   // sendSystemStatus(static_cast<uint8_t>(ValueChannel::current), m_trainboxIdList.at(0)); // current
  //   // sendSystemStatus(static_cast<uint8_t>(ValueChannel::voltage), m_trainboxIdList.at(0)); // voltage
  //   // sendSystemStatus(static_cast<uint8_t>(ValueChannel::temp), m_trainboxIdList.at(0));    // temp
  // }
}

void z60::cyclic()
{
  uint32_t currentTimeINms = millis();
  if (m_programmingCmdActive)
  {
    if ((m_lastProgrammingCmdSentTimeINms + m_currentProgrammingCmd.timeoutINms) < currentTimeINms)
    {
      if(m_debug)
      {
      Serial.println("Timeout ProgrammingCmd");
      }
      sendNextProgrammingCmd();
    }
  }

  // if(MfxDetectionState::Idle == m_mfxDetectionState)
  // {
  //   requestLocoDiscovery(ProgrammingProtocol::MfxProgramDetection);
  //   m_mfxDetectionState = MfxDetectionState::Detection;
  // }
  // if (Serial.available())
  // {
  //   char zeichen = Serial.read();

  //   if ('a' == zeichen)
  //   {
  //     // requestLocoDiscovery(ProgrammingProtocol::MfxProgramDetection);
  //     requestLocoDiscovery(ProgrammingProtocol::Mm2_20Khz);
  //   }
  //   else if ('b' == zeichen)
  //   {
  //     // verifyMfxUid(0x44abc, 5);
  //     requestLocoDiscovery(ProgrammingProtocol::DccLong);
  //   }
  //   else if ('c' == zeichen)
  //   {
  //     // bindMfxUid(0x44abc, 5);
  //     requestLocoDiscovery(ProgrammingProtocol::DccShort);
  //   }
  // }
}

void z60::saveLocoConfig()
{
  ConfigLoco buffer[256];

  size_t index = 0;
  for (DataLoco n : m_locos)
  {
    // only locos where trainbox adress is determent by mode are saved
    if (n.adrZ21 < m_startAdressDcc14)
    {
      buffer[index].adrZ21 = n.adrZ21;
      buffer[index].mode = n.mode;
      buffer[index].steps = n.data[0] & 0x07;
      index++;
    }
  }

  if (!m_preferences.begin(m_namespaceZ21, false))
  {
    Serial.println(F("Access preferences failed"));
  }
  else
  {
    if (m_preferences.putBytes(m_keyLocoMode, buffer, m_locos.size() * sizeof(ConfigLoco)) != m_locos.size() * sizeof(ConfigLoco))
    {
      Serial.println(F(" Failed to write locoMode"));
    }
    m_preferences.end();
  }
}

void z60::deleteLocoConfig()
{
  if (!m_preferences.begin(m_namespaceZ21, false))
  {
    Serial.println(F("Access preferences failed"));
  }
  else
  {
    if (!m_preferences.remove(m_keyLocoMode))
    {
      Serial.println(F(" Failed to delete locoMode"));
    }
    else
    {
      // delete all locos currently in memory to prevent writing again
      m_locos.clear();
    }
    m_preferences.end();
  }
}

bool z60::calcSpeedZ21toTrainbox(uint8_t data, uint8_t speedConfig, uint8_t &speed)
{
  bool emergencyStop = false;
  if (0 == data)
  {
    speed = 0;
  }
  else if (1 == data)
  {
    emergencyStop = true;
  }
  else
  {
    if (static_cast<uint8_t>(StepConfig::Step28) == speedConfig)
    {
      speed = (((data & 0x0F) << 1) | ((data & 0x10) >> 4)) - 3;
    }
    else
    {
      speed = data - 1;
    }
  }
  return emergencyStop;
}

void z60::calcSpeedTrainboxToZ21(uint8_t speed, uint8_t speedConfig, uint8_t &data)
{
  if (0 == speed)
  {
    data = 0;
  }
  else
  {
    if (static_cast<uint8_t>(StepConfig::Step28) == speedConfig)
    {
      uint8_t buf = speed + 3;
      data = ((buf & 0x1E) >> 1) | ((buf & 0x01) << 4);
    }
    else
    {
      data = speed + 1;
    }
  }
}

bool z60::getConfig1(std::array<uint8_t, 10> &config)
{
  bool success{false};
  memset(&config[0], 0, config.size());
  success = true;
  // if (!m_preferences.begin(m_namespaceZ21, false))
  // {
  //   Serial.println(F("Access preferences failed"));
  // }
  // else
  // {
  //   if (m_preferences.getBytes(m_keyConfig2, &config[0], config.size()) != config.size())
  //   {
  //     Serial.println(F(" Failed to read config1"));
  //   }
  //   else
  //   {
  //     success = true;
  //   }
  //   m_preferences.end();
  // }
  return success;
}

void z60::setConfig1(std::array<uint8_t, 10> &config)
{
  // if (!m_preferences.begin(m_namespaceZ21, false))
  // {
  //   Serial.println(F("Access preferences failed"));
  // }
  // else
  // {
  //   if (m_preferences.putBytes(m_keyConfig1, &config[0], config.size()) != config.size())
  //   {
  //     Serial.println(F(" Failed to write config1"));
  //   }
  //   m_preferences.end();
  // }
}

bool z60::getConfig2(std::array<uint8_t, 16> &config)
{
  bool success{false};
  memset(&config[0], 0, config.size());
  success = true;
  // if (!m_preferences.begin(m_namespaceZ21, false))
  // {
  //   Serial.println(F("Access preferences failed"));
  // }
  // else
  // {
  //   if (m_preferences.getBytes(m_keyConfig2, &config[0], config.size()) != config.size())
  //   {
  //     Serial.println(F(" Failed to read config2"));
  //   }
  //   else
  //   {
  //     success = true;
  //   }
  //   m_preferences.end();
  // }
  return success;
}

void z60::setConfig2(std::array<uint8_t, 16> &config)
{
  // if (!m_preferences.begin(m_namespaceZ21, false))
  // {
  //   Serial.println(F("Access preferences failed"));
  // }
  // else
  // {
  //   if (m_preferences.putBytes(m_keyConfig2, &config[0], config.size()) != config.size())
  //   {
  //     Serial.println(F(" Failed to write config2"));
  //   }
  //   m_preferences.end();
  // }
}

uint16_t z60::getSerialNumber()
{
  return m_serialNumber;
}

void z60::notifyProgrammingCmdSent()
{
  m_lastProgrammingCmdSentTimeINms = millis();
}

void z60::setLocoManagment(MaerklinConfigDataStream *configDataStream)
{
  m_configDataStream = configDataStream;
}

void z60::update(Observable<Can::Message> &observable, Can::Message *data)
{
  MaerklinCanInterfaceObserver::update(observable, data);
}

void z60::update(Observable<Udp::Message> &observable, Udp::Message *data)
{
  z21InterfaceObserver::update(observable, data);
}

void z60::searchLoco(ProgrammingProtocol protocol)
{
  m_foundLocoString = "Searching";
  requestLocoDiscovery(protocol);
}

// onCallback
bool z60::onSystemStop(uint32_t id)
{
  Serial.printf("onSystemStop %x\n", id);
  uint8_t data[16];
  data[0] = static_cast<uint8_t>(z21Interface::XHeader::LAN_X_BC_TRACK_POWER);
  data[1] = 0x00; // Power OFF
  EthSend(0, 0x07, z21Interface::Header::LAN_X_HEADER, data, true, (static_cast<uint16_t>(BcFlagShort::Z21bcAll) | static_cast<uint16_t>(BcFlagShort::Z21bcNetAll)));
  // data[0] = static_cast<uint8_t>(z21Interface::XHeader::LAN_X_GET_SETTING);
  // data[1] = 0x80; // Power OFF
  // EthSend(0, 0x07, z21Interface::Header::LAN_X_HEADER, data, true, 0);
  return true;
}

bool z60::onSystemGo(uint32_t id)
{
  Serial.printf("onSystemGo %x\n", id);
  uint8_t data[16]; // z21Interface send storage
  data[0] = static_cast<uint8_t>(z21Interface::XHeader::LAN_X_BC_TRACK_POWER);
  data[1] = 0x01;
  EthSend(0x00, 0x07, z21Interface::Header::LAN_X_HEADER, data, true, (static_cast<uint16_t>(BcFlagShort::Z21bcAll) | static_cast<uint16_t>(BcFlagShort::Z21bcNetAll)));
  // data[0] = static_cast<uint8_t>(z21Interface::XHeader::LAN_X_GET_SETTING);
  // data[1] = 0x81; // Power ON
  // EthSend(0, 0x07, z21Interface::Header::LAN_X_HEADER, data, true, 0);
  return true;
}

bool z60::onSystemHalt(uint32_t id)
{
  Serial.printf("onSystemHalt %x\n", id);
  uint8_t data[16]; // z21Interface send storage
  data[0] = static_cast<uint8_t>(z21Interface::XHeader::LAN_X_BC_STOPPED);
  data[1] = 0x00;
  // EthSend(0x00, 0x07, z21Interface::Header::LAN_X_HEADER, data, true, 0);
  EthSend(0x00, 0x07, z21Interface::Header::LAN_X_HEADER, data, true, (static_cast<uint16_t>(BcFlagShort::Z21bcAll) | static_cast<uint16_t>(BcFlagShort::Z21bcNetAll)));
  return true;
}

bool z60::onLocoStop(uint32_t id)
{
  if(m_debug)
  {
  Serial.print("onLocoStop:");
  Serial.println(id, HEX);
  }
  // uint8_t data[16]; // z21Interface send storage
  //  data[0] = static_cast<uint8_t>(z21Interface::XHeader::LAN_X_BC_TRACK_POWER);
  //  data[1] = 0x00;
  //  EthSend(0x00, 0x07, z21Interface::Header::LAN_X_HEADER, data, true, 0);

  for (auto finding = m_locos.begin(); finding != m_locos.end(); ++finding)
  // for (dataLoco finding : locos)
  {
    if (finding->adrTrainbox == id)
    {
      uint8_t emergencyStop = 0x01;
      finding->data[1] = emergencyStop + (finding->data[1] & 0x80);
      notifyLocoState(0, finding->adrZ21, finding->data);
    }
  }
  return true;
}

bool z60::onLocoRemoveCycle(uint32_t id)
{
  return false;
}

bool z60::onLocoDataProtocol(uint32_t id, ProtocolLoco protocol)
{
  return false;
}

bool z60::onAccTime(uint32_t id, uint16_t accTimeIN10ms)
{
  return false;
}

bool z60::onFastReadMfx(uint32_t id, uint16_t mfxSid)
{
  return false;
}

bool z60::onTrackProtocol(uint32_t id, uint8_t param)
{
  return true;
}

bool z60::onMfxCounter(uint32_t id, uint16_t counter)
{
  return false;
}

bool z60::onSystemOverLoad(uint32_t id, uint8_t channel)
{
  Serial.print("onSystemOverLoad:");
  Serial.println(channel);
  uint8_t data[16];
  data[0] = static_cast<uint8_t>(z21Interface::XHeader::LAN_X_BC_TRACK_POWER);
  data[1] = 0x08; // Shortcut
  EthSend(0, 0x07, z21Interface::Header::LAN_X_HEADER, data, true, (static_cast<uint16_t>(BcFlagShort::Z21bcAll) | static_cast<uint16_t>(BcFlagShort::Z21bcNetAll)));
  return true;
}

bool z60::onSystemStatus(uint32_t id, uint8_t channel, bool valid)
{
  Serial.print("onSystemStatus C ");
  Serial.print(channel);
  Serial.print(" : ");
  Serial.println(valid);
  return false;
}

bool z60::onSystemStatus(uint32_t id, uint8_t channel, uint16_t value)
{
  Serial.print("C ");
  Serial.print(channel);
  Serial.print(" : ");
  Serial.printf("%d\n", value);

  if (static_cast<uint8_t>(ValueChannel::current) == channel)
  {
    m_currentINmA = (value - 0x0F) * 10;
    // sendSystemStatus(static_cast<uint8_t>(ValueChannel::voltage), id); // voltage
  }
  else if (static_cast<uint8_t>(ValueChannel::voltage) == channel)
  {
    m_voltageINmV = value * 10;
    // sendSystemStatus(static_cast<uint8_t>(ValueChannel::temp), id); // temp
  }
  else if (static_cast<uint8_t>(ValueChannel::temp) == channel)
  {
    m_tempIN10_2deg = value;
    sendSystemInfo(0, m_currentINmA, m_voltageINmV, m_tempIN10_2deg / 10); // report System State to z21Interface clients
  }
  return true;
}

bool z60::onSystemIdent(uint32_t id, uint16_t feedbackId)
{
  return false;
}

bool z60::onSystemReset(uint32_t id, uint8_t target)
{
  Serial.println("onSystemReset");
  return true;
}
///////////////////////////

bool z60::onLocoDiscovery()
{
  Serial.printf("onLocoDiscovery\n");
  m_foundLocoString = "Found Nothing";
  // requestLocoDiscovery(ProgrammingProtocol::MfxProgramDetection);
  return false;
}

bool z60::onLocoDiscovery(uint32_t uid, uint8_t protocol)
{
  Serial.printf("Found 0x%X\n", uid);
  if (0xFFFF > uid)
  {
    m_foundLocoString = "Found ";
    m_foundLocoString += std::to_string(uid);
  }
  // if (0 != uid)
  // {
  //   auto found = m_mfxLocoData.find(uid);
  //   if (found != m_mfxLocoData.end())
  //   {
  //     verifyMfxUid(found->first, found->second);
  //   }
  //   else
  //   {
  //     verifyMfxUid(uid, 5);
  //   }
  // }
  return true;
}

bool z60::onLocoDiscovery(uint32_t uid, uint8_t protocol, uint8_t ask)
{
  Serial.printf("Found 0x%X with %d\n", uid, ask);
  if (0xFFFF > uid)
  {
    m_foundLocoString = "Found ";
    m_foundLocoString += std::to_string(uid);
  }
  // if (0 != uid)
  // {
  //   auto found = m_mfxLocoData.find(uid);
  //   if (found != m_mfxLocoData.end())
  //   {
  //     verifyMfxUid(found->first, found->second);
  //   }
  //   else
  //   {
  //     verifyMfxUid(uid, 5);
  //   }
  // }
  return true;
}

bool z60::onMfxBind(uint32_t uid, uint16_t sid)
{
  Serial.printf("Bound %X with %X\n", uid, sid);
  // auto found = m_mfxLocoData.find(uid);
  // if (found == m_mfxLocoData.end())
  // {
  //   m_mfxLocoData.emplace(uid, sid);
  // }
  // m_locoDiscoveryStartINms = millis();
  // requestLocoDiscovery(ProgrammingProtocol::MfxProgramDetection);
  return true;
}

bool z60::onMfxVerify(uint32_t uid, uint16_t sid)
{
  Serial.printf("Verified %X with %X\n", uid, sid);
  // if (0 != sid)
  // {
  //   auto found = m_mfxLocoData.find(uid);
  //   if (found == m_mfxLocoData.end())
  //   {
  //     bindMfxUid(found->first, found->second);
  //     m_locoDiscoveryStartINms = millis();
  //     requestLocoDiscovery(ProgrammingProtocol::MfxProgramDetection);
  //   }
  // }
  // else
  // {
  //   // add element to map
  //   // m_mfxLocoData.emplace(uid)
  //   bindMfxUid(uid, 5);
  // }
  return true;
}

bool z60::onMfxVerify(uint32_t uid, uint16_t sid, uint8_t ask)
{
  Serial.printf("Verified %X with %X and %d\n", uid, sid, ask);
  // if (0 != sid)
  // {
  //   auto found = m_mfxLocoData.find(uid);
  //   if (found == m_mfxLocoData.end())
  //   {
  //     bindMfxUid(found->first, found->second);
  //     m_locoDiscoveryStartINms = millis();
  //     requestLocoDiscovery(ProgrammingProtocol::MfxProgramDetection);
  //   }
  // }
  // else
  // {
  //   // add element to map
  //   // m_mfxLocoData.emplace(uid)
  //   bindMfxUid(uid, 5);
  // }
  return true;
}

///////////////////////////
bool z60::onLocoSpeed(uint32_t id)
{
  // reading was not possible
  Serial.println(F("onLocoSpeed"));
  return true;
}

bool z60::onLocoSpeed(uint32_t id, uint16_t speed)
{
  for (auto finding = m_locos.begin(); finding != m_locos.end(); ++finding)
  // for (dataLoco finding : locos)
  {
    if (finding->adrTrainbox == id)
    {
      finding->speedResponseReceived = true;
      uint8_t divider = 71; // 14 steps
      uint8_t stepConfig = (finding->data[0] & 0x03);
      if (stepConfig == static_cast<uint8_t>(StepConfig::Step128))
      {
        divider = 8;
      }
      else if (stepConfig == static_cast<uint8_t>(StepConfig::Step28))
      {
        divider = 35;
      }
      if (m_debug)
      {
        Serial.print(F("Id:"));
        Serial.print(finding->adrZ21);
        Serial.print(F(" onLS:"));
        Serial.println(speed);
      }

      uint8_t locoSpeed = static_cast<uint8_t>(speed / divider);
      uint8_t locoSpeedDcc = 0;
      calcSpeedTrainboxToZ21(locoSpeed, stepConfig, locoSpeedDcc);
      finding->data[1] = locoSpeedDcc | (finding->data[1] & 0x80);
      notifyLocoState(0, finding->adrZ21, finding->data);
    }
  }
  return true;
}

// 0 = Fahrtrichtung bleibt
// 1 = Fahrtrichtung vorwärts
// 2 = Fahrtrichtung rückwärts
// 3 = Fahrtrichtung umschalten
bool z60::onLocoDir(uint32_t id, uint8_t dir)
{

  // Serial.print("Id:");
  // Serial.print(id);
  // Serial.print(" onLocoDir:");
  // Serial.println(dir);

  for (auto finding = m_locos.begin(); finding != m_locos.end(); ++finding)
  {
    if (finding->adrTrainbox == id)
    {
      finding->data[1] = (finding->data[1] & 0x7F) + (2 == dir ? 0x00 : 0x80);
      // notifyLocoState(0, static_cast<uint16_t>(id), finding->second);
    }
  }
  return true;
}

bool z60::onLocoFunc(uint32_t id, uint8_t function, uint8_t value)
{
  if (m_debug)
  {
    Serial.print(F("Id:"));
    Serial.print(id, HEX);
    Serial.print(F(" onLocoFunc:"));
    Serial.print(function);
    Serial.print(F(" value:"));
    Serial.println(value);
  }

  for (auto finding = m_locos.begin(); finding != m_locos.end(); ++finding)
  {
    if (finding->adrTrainbox == id)
    {
      if (0 == function)
      {
        bitWrite(finding->data[2], 4, 0 == value ? 0 : 1);
      }
      else if (function < 5)
      {
        bitWrite(finding->data[2], function - 1, 0 == value ? 0 : 1);
      }
      else if (function < 13)
      {
        bitWrite(finding->data[3], function - 5, 0 == value ? 0 : 1);
      }
      else if (function < 21)
      {
        bitWrite(finding->data[4], function - 13, 0 == value ? 0 : 1);
      }
      else if (function < 29)
      {
        bitWrite(finding->data[5], function - 21, 0 == value ? 0 : 1);
      }
      else if (function < 32)
      {
        bitWrite(finding->data[6], function - 29, 0 == value ? 0 : 1);
      }
      else
      {
        Serial.println(F("### ERROR: Function number to big"));
      }
      notifyLocoState(0, finding->adrZ21, finding->data);
    }
  }
  return true;
}

bool z60::onReadConfig(uint32_t id, uint16_t cvAdr, uint8_t value, bool readSuccessful)
{
  if (m_debug)
  {
    Serial.print("RC:");
    Serial.print(id);
    Serial.print(" cvAdr:");
    Serial.print(cvAdr);
    Serial.print(" value:");
    Serial.print(value);
    Serial.print(" :");
    Serial.print(readSuccessful);
  }
  if (readSuccessful)
  {
    setCVReturn(cvAdr - 1, value);
  }
  else
  {
    setCVNack();
  }
  return true;
}

bool z60::onWriteConfig(uint32_t id, uint16_t cvAdr, uint8_t value, bool writeSuccessful, bool verified)
{
  if (m_debug)
  {
    Serial.print(F("WC:"));
    Serial.print(id);
    Serial.print(F(" cvAdr:"));
    Serial.print(cvAdr);
    Serial.print(F(" value:"));
    Serial.print(value);
    Serial.print(F(" :"));
    Serial.print(writeSuccessful);
    Serial.println(verified);
  }
  if (writeSuccessful)
  {
    setCVReturn(cvAdr - 1, value);
    // if (directProgramming)
    // {
    //   // sending report in case that direct programming
    // }
  }
  else
  {
    setCVNack();
  }
  return true;
}

///////////////////////////
bool z60::onAccSwitch(uint32_t id, uint8_t position, uint8_t current)
{
  if (m_debug)
  {
    Serial.print(F("onAccSwitch:"));
    Serial.print(id);
    Serial.print(F(" position:"));
    Serial.print(position);
    Serial.print(F(" current:"));
    Serial.println(current);
  }
  uint8_t data[16];
  if (static_cast<uint32_t>(AddrOffset::DCCAcc) <= id)
  {
    id -= static_cast<uint32_t>(AddrOffset::DCCAcc);
    id += m_startAdressAccDCC;
  }
  else if (static_cast<uint32_t>(AddrOffset::MM2Acc) <= id)
  {
    id -= static_cast<uint32_t>(AddrOffset::MM2Acc);
  }

  auto finding = m_turnouts.find(id);
  if (finding == m_turnouts.end())
  {
    // delete all if buffer is to big
    if (m_maxNumberOfTurnout < m_turnouts.size())
    {
      Serial.println(F("clear turnoutlist"));
      m_turnouts.clear();
    }
    m_turnouts.insert({id, position ? 0x02 : 0x01});
    Serial.print(F("Turnout not found:"));
    Serial.println(id);
  }
  else
  {
    finding->second = position ? 0x02 : 0x01;
  }
  Serial.println(id);
  data[0] = static_cast<uint8_t>(z21Interface::XHeader::LAN_X_GET_TURNOUT_INFO);
  data[1] = highByte(static_cast<uint16_t>(id));
  data[2] = lowByte(static_cast<uint16_t>(id));
  data[3] = position ? 0x02 : 0x01;
  EthSend(0x00, 0x09, z21Interface::Header::LAN_X_HEADER, data, true, static_cast<uint16_t>(BcFlagShort::Z21bcAll) | static_cast<uint16_t>(BcFlagShort::Z21bcNetAll)); // BC new 23.04. !!!(old = 0)
  return true;
}

bool z60::onPing(uint16_t hash, uint32_t id, uint16_t swVersion, uint16_t hwIdent)
{
  Serial.println("Ping received");

  if (0x0010 == (hwIdent & 0xFFF0))
  {
    // Trainbox
    auto finding = std::find(m_trainboxIdList.begin(), m_trainboxIdList.end(), id);
    if (finding == m_trainboxIdList.end())
    {
      m_trainboxIdList.emplace_back(id);
      Serial.print("Adding Trainbox: Uid:");
      Serial.print(id, HEX);
      Serial.print(" HW:");
      Serial.print(hwIdent, HEX);
      Serial.print(" SW:");
      Serial.println(swVersion, HEX);
      if (0 == m_stationList.size())
      {
        sendSetTrackProtocol(0b101, id); // no mfx
        sendSetTrackProtocol(0b101, 0); // no mfx
      }
    }
  }
  else if (0x0030 == (hwIdent & 0xFFF0))
  {
    // Mobile Station
    auto finding = std::find_if(m_stationList.begin(), m_stationList.end(), [&id](MaerklinStationConfig cfg)
                                { return cfg.id == id; });
    if (finding == m_stationList.end())
    {
      m_stationList.emplace_back(MaerklinStationConfig{hash, id, swVersion, hwIdent});
      Serial.print("Adding MobileStation: Hash:");
      Serial.print(hash, HEX);
      Serial.print(" Uid:");
      Serial.print(id, HEX);
      Serial.print(" HW:");
      Serial.print(hwIdent, HEX);
      Serial.print(" SW:");
      Serial.println(swVersion, HEX);
      if (0 != m_trainboxIdList.size())
      {
        sendSetTrackProtocol(0b111, m_trainboxIdList.at(0)); // dcc, mfx, motorola
        sendSetTrackProtocol(0b111, 0); // dcc, mfx, motorola
      }
    }
  }
  return true;
}

bool z60::onStatusDataConfig(uint16_t hash, std::array<uint8_t, 8> &data)
{
  return true;
}

bool z60::onStatusDataConfig(uint16_t hash, uint32_t uid, uint8_t index, uint8_t length)
{
  return true;
}

bool z60::onConfigData(uint16_t hash, std::array<uint8_t, 8> data)
{
  if (nullptr != m_configDataStream)
  {
    return m_configDataStream->onConfigData(hash, data);
  }
  return false;
}

bool z60::onConfigDataStream(uint16_t hash, uint32_t streamlength, uint16_t crc)
{
  if (nullptr != m_configDataStream)
  {
    return m_configDataStream->onConfigDataStream(hash, streamlength, crc);
  }
  return false;
}

bool z60::onConfigDataStream(uint16_t hash, uint32_t streamlength, uint16_t crc, uint8_t res)
{
  if (nullptr != m_configDataStream)
  {
    return m_configDataStream->onConfigDataStream(hash, streamlength, crc, res);
  }
  return false;
}

bool z60::onConfigDataStream(uint16_t hash, std::array<uint8_t, 8> &data)
{
  if (nullptr != m_configDataStream)
  {
    return m_configDataStream->onConfigDataStream(hash, data);
  }
  return false;
}

bool z60::onConfigDataSteamError(uint16_t hash)
{
  if (nullptr != m_configDataStream)
  {
    return m_configDataStream->onConfigDataSteamError(hash);
  }
  return false;
}

void z60::notifyLocoState(uint8_t client, uint16_t Adr, std::array<uint8_t, 7> &locoData)
{

  uint8_t data[10];
  data[0] = static_cast<uint8_t>(z21Interface::XHeader::LAN_X_LOCO_INFO); // 0xEF X-HEADER
  data[1] = (Adr >> 8) & 0x3F;
  data[2] = Adr & 0xFF;
  // Fahrstufeninformation: 0=14, 2=28, 4=128
  if ((locoData[0] & 0x03) == static_cast<uint8_t>(StepConfig::Step14))
    data[3] = 1; // 14 steps
  if ((locoData[0] & 0x03) == static_cast<uint8_t>(StepConfig::Step28))
    data[3] = 2; // 28 steps
  if ((locoData[0] & 0x03) == static_cast<uint8_t>(StepConfig::Step128))
    data[3] = 4; // 128 steps
  // data[3] = data[3] | 0x08; //BUSY!

  data[4] = (char)locoData[1]; // DSSS SSSS
  data[5] = (char)locoData[2]; // F0, F4, F3, F2, F1
  data[6] = (char)locoData[3]; // F5 - F12; Funktion F5 ist bit0 (LSB)
  data[7] = (char)locoData[4]; // F13-F20
  data[8] = (char)locoData[5]; // F21-F28
  data[9] = (char)locoData[6]; // F29-F31

  EthSend(0, 15, z21Interface::Header::LAN_X_HEADER, data, true, (static_cast<uint16_t>(BcFlagShort::Z21bcAll) | static_cast<uint16_t>(BcFlagShort::Z21bcNetAll)));
}

// Z21

void z60::addToLocoList(uint16_t adrZ21, uint8_t mode, uint8_t steps)
{
  if (adrZ21 > m_startAdressDcc14)
  {
    if (adrZ21 > m_startAdressDcc128) // DCC 128 steps
    {
      // mode = 0 = DCC
      m_locos.push_front(DataLoco{adrZ21, fromZ21AdrToTrainboxAdr(adrZ21, static_cast<uint8_t>(AdrMode::Dcc)), static_cast<uint8_t>(AdrMode::Dcc), true, 0, true, {static_cast<uint8_t>(StepConfig::Step128), 0, 0, 0, 0, 0}});
    }
    else if (adrZ21 > m_startAdressDcc28) // DCC 28 steps
    {
      // mode = 0 = DCC
      m_locos.push_front(DataLoco{adrZ21, fromZ21AdrToTrainboxAdr(adrZ21, static_cast<uint8_t>(AdrMode::Dcc)), static_cast<uint8_t>(AdrMode::Dcc), true, 0, true, {static_cast<uint8_t>(StepConfig::Step28), 0, 0, 0, 0, 0}});
    }
    else if (adrZ21 > m_startAdressMfx) // MFX (handled like 128 steps DCC)
    {
      // mode = 0 = DCC
      m_locos.push_front(DataLoco{adrZ21, fromZ21AdrToTrainboxAdr(adrZ21, static_cast<uint8_t>(AdrMode::Dcc)), static_cast<uint8_t>(AdrMode::Dcc), true, 0, true, {static_cast<uint8_t>(StepConfig::Step128), 0, 0, 0, 0, 0}});
    }
    else if (adrZ21 > m_startAdressMoto) // Motorola
    {
      // mode = 1 = Motorola
      m_locos.push_front(DataLoco{adrZ21, fromZ21AdrToTrainboxAdr(adrZ21, static_cast<uint8_t>(AdrMode::Motorola)), static_cast<uint8_t>(AdrMode::Motorola), true, 0, true, {static_cast<uint8_t>(StepConfig::Step128), 0, 0, 0, 0, 0}});
    }
    else // DCC 14 steps
    {
      // mode = 0 = DCC
      m_locos.push_front(DataLoco{adrZ21, fromZ21AdrToTrainboxAdr(adrZ21, static_cast<uint8_t>(AdrMode::Dcc)), static_cast<uint8_t>(AdrMode::Dcc), true, 0, true, {static_cast<uint8_t>(StepConfig::Step14), 0, 0, 0, 0, 0}});
    }
  }
  else
  {
    // adressing is based on z21 managment
    m_locos.push_front(DataLoco{adrZ21, fromZ21AdrToTrainboxAdr(adrZ21, mode), mode, false, 0, true, {static_cast<uint8_t>(steps), 0, 0, 0, 0, 0}});
  }
}

uint16_t z60::fromZ21AdrToTrainboxAdr(uint16_t adr, uint8_t mode)
{
  uint16_t trainboxAdr = adr;
  if (adr > m_startAdressDcc14)
  {
    if (adr > m_startAdressDcc128) // DCC 128 steps
    {
      trainboxAdr -= m_startAdressDcc128;
      trainboxAdr += static_cast<uint16_t>(AddrOffset::DCC);
    }
    else if (adr > m_startAdressDcc28) // DCC 28 steps
    {
      trainboxAdr -= m_startAdressDcc28;
      trainboxAdr += static_cast<uint16_t>(AddrOffset::DCC);
    }
    else if (adr > m_startAdressMfx) // MFX (handled like 128 steps DCC)
    {
      trainboxAdr -= m_startAdressMfx;
      trainboxAdr += static_cast<uint16_t>(AddrOffset::MFX);
    }
    else if (adr > m_startAdressMoto) // Motorola
    {
      trainboxAdr -= m_startAdressMoto;
    }
    else // DCC 14 steps
    {
      trainboxAdr -= m_startAdressDcc14;
    }
  }
  else
  {
    // adressing is based on z21 managment
    trainboxAdr += (static_cast<uint8_t>(AdrMode::Motorola) == mode ? 0 : static_cast<uint32_t>(AddrOffset::DCC));
  }
  return trainboxAdr;
}

void z60::handleGetLocoMode(uint16_t adr, uint8_t &mode)
{
  mode = 0;
  for (auto finding = m_locos.begin(); finding != m_locos.end(); ++finding)
  {
    if (finding->adrZ21 == adr)
    {
      mode = finding->mode;
      return;
    }
  }
  if (m_debug)
  {
    Serial.print("handleGetLocoMode");
    Serial.println(adr);
  }
}

void z60::handleSetLocoMode(uint16_t adr, uint8_t mode)
{
  for (auto finding = m_locos.begin(); finding != m_locos.end(); ++finding)
  {
    if (finding->adrZ21 == adr)
    {
      if (finding->mode != mode)
      {
        finding->mode = mode;
        finding->adrTrainbox = fromZ21AdrToTrainboxAdr(adr, mode);
        // Write to flash
        saveLocoConfig();
        // speed is send again in next cycle
        finding->isActive = false;
      }
      return;
    }
  }
  if (m_debug)
  {
    Serial.printf("handleSetLocoMode: %d, %d\n", adr, mode);
  }
  if (m_locos.size() >= m_maxNumberOfLoco)
  {
    m_locos.pop_back();
  }
  addToLocoList(adr, mode, static_cast<uint8_t>(StepConfig::Step128));
  saveLocoConfig();
}

void z60::handleGetTurnOutMode(uint16_t adr, uint8_t &mode)
{
  if (adr >= m_startAdressAccDCC)
  {
    mode = 0;
  }
  else
  {
    mode = 1;
  }
}

void z60::handleSetTurnOutMode(uint16_t adr, uint8_t mode)
{
}

//--------------------------------------------------------------------------------------------
void z60::notifyz21InterfaceRailPower(EnergyState State)
{
  Serial.print("Power: ");
  Serial.println(static_cast<uint8_t>(State), HEX);

  if (EnergyState::csNormal == State)
  {
    MaerklinCanInterfaceObserver::sendSystemGo(0); // trainBoxUid);
    // TrackMessage out, in;
    // messageSystemGo(out);
    // exchangeMessage(out, in, 1000)
  }
  else if (EnergyState::csEmergencyStop == State)
  {
    MaerklinCanInterfaceObserver::sendSystemHalt(0); // trainBoxUid);
    // TrainBoxMaerklinEsp32::sendSystemStop();
  }
  else if (EnergyState::csTrackVoltageOff == State)
  {
    MaerklinCanInterfaceObserver::sendSystemStop(0); // trainBoxUid);
  }
  z21InterfaceObserver::setPower(State);
}

//--------------------------------------------------------------------------------------------
void z60::notifyz21InterfaceS88Data(uint8_t gIndex)
{
  // z21Interface.setS88Data (datasend);  //Send back state of S88 Feedback
  Serial.println("S88Data");
}

void z60::notifyz21InterfaceLocoState(uint16_t Adr, uint8_t data[])
{
  for (auto finding = m_locos.begin(); finding != m_locos.end(); ++finding)
  {
    if (finding->adrZ21 == Adr)
    {
      uint8_t index = 0;
      for (auto i : finding->data)
      {
        data[index++] = i;
      }
      // if (finding->data[0] == static_cast<uint8_t>(StepConfig::Step128))
      // {
      //   data[0] = 4;
      // }
      return;
    }
  }
  if (m_debug)
  {
    Serial.print("notifyz21InterfaceLocoState:");
    Serial.println(Adr);
  }
  if (m_locos.size() >= m_maxNumberOfLoco)
  {
    m_locos.pop_back();
  }
  addToLocoList(Adr, static_cast<uint8_t>(AdrMode::Motorola), static_cast<uint8_t>(StepConfig::Step128));
  saveLocoConfig();
  data[0] = static_cast<uint8_t>(StepConfig::Step128);
  memset(&data[1], 0, 5);
  // before state was requested her, which is not possible if mode of loco is not known
}

void z60::notifyz21InterfaceLocoFkt(uint16_t Adr, uint8_t type, uint8_t fkt)
{
  for (auto finding = m_locos.begin(); finding != m_locos.end(); ++finding)
  {
    if (finding->adrZ21 == Adr)
    {
      setLocoFunc(finding->adrTrainbox, fkt, type);
      return;
    }
  }
  if (m_locos.size() >= m_maxNumberOfLoco)
  {
    m_locos.pop_back();
  }
  if (m_debug)
  {
    Serial.print("Loco not found:");
    Serial.println(Adr);
  }
  addToLocoList(Adr, static_cast<uint8_t>(AdrMode::Motorola), static_cast<uint8_t>(StepConfig::Step128));
  saveLocoConfig();
}

//--------------------------------------------------------------------------------------------
void z60::notifyz21InterfaceLocoSpeed(uint16_t Adr, uint8_t speed, uint8_t stepConfig)
{
  for (auto finding = m_locos.begin(); finding != m_locos.end(); ++finding)
  {
    if (finding->adrZ21 == Adr)
    {
      // adapt adress for trainbox
      uint32_t id = finding->adrTrainbox;

      if (finding->data[0] != stepConfig)
      {
        finding->data[0] = stepConfig;
        // safe config to flash
        saveLocoConfig();
        finding->isActive = true;
      }
      if (!finding->isActive)
      {
        // set data protocol
        if (0 == finding->mode) // DCC
        {
          switch (stepConfig)
          {
          case static_cast<uint8_t>(StepConfig::Step14):
            sendLocoDataProtocol(id, ProtocolLoco::DCC_SHORT_14);
            break;
          case static_cast<uint8_t>(StepConfig::Step28):
            if (m_longDccAddressStart > (Adr & 0x0FFF))
            {
              sendLocoDataProtocol(id, ProtocolLoco::DCC_SHORT_28);
            }
            else
            {
              sendLocoDataProtocol(id, ProtocolLoco::DCC_LONG_28);
            }
            break;
          case static_cast<uint8_t>(StepConfig::Step128):
            if (m_longDccAddressStart > (Adr & 0x0FFF))
            {
              sendLocoDataProtocol(id, ProtocolLoco::DCC_SHORT_128);
            }
            else
            {
              sendLocoDataProtocol(id, ProtocolLoco::DCC_LONG_128);
            }
            break;
          default:
            sendLocoDataProtocol(id, ProtocolLoco::DCC_SHORT_28);
            break;
          }
        }
        finding->isActive = true;
      }

      uint8_t locoSpeedAdapted = 0;
      if (calcSpeedZ21toTrainbox(speed & 0x7F, stepConfig, locoSpeedAdapted))
      {
        // emergency break
        if (m_debug)
        {
          Serial.print("Emergency Break:");
          Serial.println(id);
        }
        sendLocoStop(id);
      }
      else
      {
        unsigned long currentTimeINms = millis();
        // we are sending speed in case that we already received an answer for the last command or the time is up
        if (((finding->lastSpeedCmdTimeINms + minimumCmdIntervalINms) < currentTimeINms) || (finding->speedResponseReceived))
        {
          finding->lastSpeedCmdTimeINms = currentTimeINms;
          uint8_t steps = 1;
          if (static_cast<uint8_t>(StepConfig::Step14) == stepConfig)
          {
            steps = 14;
          }
          else if (static_cast<uint8_t>(StepConfig::Step28) == stepConfig)
          {
            steps = 28;
          }
          else
          {
            steps = 128;
          }
          uint16_t locoSpeedTrainBox = static_cast<uint16_t>(static_cast<uint32_t>(locoSpeedAdapted) * 1000 / static_cast<uint32_t>(steps));
          if (m_debug)
          {
            Serial.print(F("SetV:"));
            Serial.print(locoSpeedTrainBox);
            Serial.print(F(" D:"));
            Serial.println(speed & 0x80 ? 1 : 2);
          }
          setLocoDir(id, speed & 0x80 ? 1 : 2);
          setLocoSpeed(id, locoSpeedTrainBox);
          finding->speedResponseReceived = false;
        }
      }
      return;
    }
  }
  if (m_debug)
  {
    Serial.print(F("Loco not found:"));
    Serial.println(Adr);
  }
  if (m_locos.size() >= m_maxNumberOfLoco)
  {
    m_locos.pop_back();
  }
  addToLocoList(Adr, static_cast<uint8_t>(AdrMode::Motorola), stepConfig);
  saveLocoConfig();
}

//--------------------------------------------------------------------------------------------
void z60::notifyz21InterfaceAccessory(uint16_t Adr, bool state, bool active)
{
  if (m_debug)
  {
    Serial.print("setAccSwitch:");
    Serial.print(Adr);
    Serial.print(" state:");
    Serial.print(state);
    Serial.print(" active:");
    Serial.println(active);
  }
  auto finding = m_turnouts.find(Adr);
  if (finding == m_turnouts.end())
  {
    // delete all if buffer is to big
    if (m_maxNumberOfTurnout < m_turnouts.size())
    {
      if (m_debug)
      {
        Serial.println(F("clear turnoutlist"));
      }
      m_turnouts.clear();
    }
    m_turnouts.insert({Adr, state ? 0x02 : 0x01});
    if (m_debug)
    {
      Serial.print(F("Turnout not found:"));
      Serial.println(Adr);
    }
  }
  else
  {
    finding->second = state ? 0x02 : 0x01;
  }

  uint32_t adrTurnOut = static_cast<uint32_t>(Adr);

  // if (adrTurnOut < 256)
  // {
  //   adrTurnOut += bitRead(turnOutMode[(Adr + 1) / 8], (Adr + 1) % 8) ? static_cast<uint32_t>(AddrOffset::MM2Acc) : static_cast<uint32_t>(AddrOffset::DCCAcc);
  // }
  // else
  // {
  //   adrTurnOut += static_cast<uint32_t>(AddrOffset::DCCAcc);
  // }
  if (adrTurnOut >= m_startAdressAccDCC)
  {
    adrTurnOut -= m_startAdressAccDCC;
    adrTurnOut += static_cast<uint32_t>(AddrOffset::DCCAcc);
  }
  else
  {
    adrTurnOut += static_cast<uint32_t>(AddrOffset::MM2Acc);
  }
  Serial.println(adrTurnOut);
  setAccSwitch(adrTurnOut, state ? 0x01 : 0x00, active ? 0x00 : 0x01, 0); // only execute command, no deactivation
}

//--------------------------------------------------------------------------------------------
void z60::notifyz21InterfaceAccessoryInfo(uint16_t Adr, uint8_t &position)
{
  auto finding = m_turnouts.find(Adr);
  position = finding != m_turnouts.end() ? finding->second : 0;
}

//--------------------------------------------------------------------------------------------
uint8_t z60::notifyz21InterfaceLNdispatch(uint16_t Adr)
// return the Slot that was dispatched, 0xFF at error!
{
  Serial.println("LNdispatch");
  return 0xFF;
}

//--------------------------------------------------------------------------------------------
void z60::notifyz21InterfaceLNSendPacket(uint8_t *data, uint8_t length)
{
  Serial.println("LNSendPacket");
}

//--------------------------------------------------------------------------------------------
void z60::notifyz21InterfaceCVREAD(uint8_t cvAdrMSB, uint8_t cvAdrLSB)
{
  Serial.println("CVREAD");
  if (m_programmingActiv)
  {
    m_directProgramming = true;
  }
  else
  {
    setCVNack();
  }
}

//--------------------------------------------------------------------------------------------
void z60::notifyz21InterfaceCVWRITE(uint8_t cvAdrMSB, uint8_t cvAdrLSB, uint8_t value)
{
  if (m_debug)
  {
    Serial.print("CVWRITE");

    Serial.print(cvAdrMSB);
    Serial.print(":");
    Serial.print(cvAdrLSB);
    Serial.print(":");
    Serial.println(value);
  }
  uint16_t cvAdr = (cvAdrMSB << 8) + cvAdrLSB + 1;
  if (m_programmingActiv)
  {
    m_directProgramming = true;
    // Directprogramming
    // sendWriteConfig(static_cast<uint32_t>(AddrOffset::MM2) + 80, cvAdr, value, true, false);//MM
    sendWriteConfig(static_cast<uint32_t>(AddrOffset::DCC) + 1, cvAdr, value, true, false); // DCC
  }
  else
  {
    setCVReturn(cvAdr, value);
  }
}

//--------------------------------------------------------------------------------------------
void z60::notifyz21InterfaceMMWRITE(uint8_t regAdr, uint8_t value)
{
  if (m_debug)
  {
    Serial.println("MMWRITE");
  }
  if (m_programmingActiv)
  {
    m_directProgramming = true;
    sendWriteConfig(80, static_cast<uint8_t>(regAdr) + 1, value, true, false);
  }
  else
  {
    setCVReturn(regAdr, value);
  }
}

//--------------------------------------------------------------------------------------------
void z60::notifyz21InterfaceDCCWRITE(uint8_t regAdr, uint8_t value)
{
  if (m_debug)
  {
    Serial.println("DCCWRITE");
  }
  if (m_programmingActiv)
  {
    m_directProgramming = true;
    sendWriteConfig(0xC001, static_cast<uint8_t>(regAdr) + 1, value, true, false);
  }
  else
  {
    setCVReturn(regAdr, value);
  }
}

//--------------------------------------------------------------------------------------------
void z60::notifyz21InterfaceDCCREAD(uint8_t regAdr)
{
  if (m_debug)
  {
    Serial.println("DCCREAD");
  }
  setCVNack();
}

//--------------------------------------------------------------------------------------------
void z60::notifyz21InterfaceCVPOMWRITEBYTE(uint16_t Adr, uint16_t cvAdr, uint8_t value)
{
  if (m_debug)
  {
    Serial.println("CVPOMWRITEBYTE");
  }
  if (m_programmingActiv)
  {
    m_directProgramming = false;
    for (auto finding = m_locos.begin(); finding != m_locos.end(); ++finding)
    {
      if (finding->adrZ21 == Adr)
      {
        sendWriteConfig(finding->adrTrainbox, cvAdr + 1, value, false, true);
        return;
      }
    }
    setCVNack();
  }
  else
  {
    setCVReturn(cvAdr, value);
  }
}

//--------------------------------------------------------------------------------------------
void z60::notifyz21InterfaceCVPOMWRITEBIT(uint16_t Adr, uint16_t cvAdr, uint8_t value)
{
  if (m_debug)
  {
    Serial.println("CVPOMWRITEBIT");
  }
  if (m_programmingActiv)
  {
    // directProgramming = false;
    // sendWriteConfig(static_cast<uint16_t>(Adr), cvAdr + 1, value, false, false);
  }
  else
  {
    setCVReturn(cvAdr, value);
  }
}

//--------------------------------------------------------------------------------------------
void z60::notifyz21InterfaceCVPOMREADBYTE(uint16_t Adr, uint16_t cvAdr)
{
  if (m_debug)
  {
    Serial.println("CVPOMREADBYTE");
  }
  if (m_programmingActiv)
  {
    /*
    directProgramming = false;
    for (auto finding = m_locos.begin(); finding != m_locos.end(); ++finding)
    {
      if (finding->adr == Adr)
      {
        // adapt adress for trainbox
        uint32_t id = static_cast<uint32_t>(Adr) + (finding->mode ? 0 : static_cast<uint32_t>(AddrOffset::DCC));
        sendReadConfig(id, cvAdr + 1, 1);
        return;
      }
    }
    setCVNack();
    */
  }
  else
  {
    setCVReturn(cvAdr, 1);
  }
}

//--------------------------------------------------------------------------------------------
void z60::notifyz21InterfacegetSystemInfo(uint8_t client)
{
  // uint16_t inAm = 0;
  // uint16_t temp = 1600;
  // uint16_t volt = 0x4650; // 18V

  if (m_trainboxIdList.size() > 0)
  {
    sendSystemStatus(static_cast<uint8_t>(ValueChannel::current), m_trainboxIdList.at(0)); // current
    sendSystemStatus(static_cast<uint8_t>(ValueChannel::voltage), m_trainboxIdList.at(0)); // voltage
    sendSystemStatus(static_cast<uint8_t>(ValueChannel::temp), m_trainboxIdList.at(0));    // temp
  }
  else
  {
    sendSystemInfo(client, 0, 50000, 0); // report System State to z21Interface clients
  }
  // sendSystemStatus(static_cast<uint8_t>(valueChannel::voltage), m_trainBoxUid); // voltage
  // sendSystemStatus(static_cast<uint8_t>(valueChannel::temp), m_trainBoxUid);    // temp
  // sendSystemInfo(client, 1000, 18000, 1600); // report System State to z21Interface clients
  //(12-22V): 20V=0x4e20, 21V=0x5208, 22V=0x55F0
}