/*********************************************************************
 * TrainBox Maerklin Loco Managment
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

#include "trainBoxMaerklin/MaerklinLocoManagment.h"
#include "Cs2DataParser.h"

MaerklinLocoManagment::MaerklinLocoManagment(uint32_t uid, MaerklinCanInterface &interface,
                                             std::vector<MaerklinStationConfig> &stationList, unsigned long messageTimeout,
                                             uint8_t maxCmdRepeat, bool debug)
    : MaerklinConfigDataStream(interface, stationList),
      m_uid(uid), m_cmdTimeoutINms(messageTimeout),
      m_maxCmdRepeat(maxCmdRepeat),
      m_debug(debug)
{
    m_lastCmdTimeINms = millis();
}

MaerklinLocoManagment::~MaerklinLocoManagment()
{
}

uint32_t MaerklinLocoManagment::getUid()
{
    return m_uid;
}

void MaerklinLocoManagment::getLokomotiveConfig(void (*writeFileCallback)(std::string *data), void (*resultCallback)(bool success))
{
    m_resultCallback = resultCallback;
    m_writeFileCallback = writeFileCallback;
    m_state = LocoManagmentState::WaitingForLocoList;
    m_currentInfo.clear();
    m_currentType = DataType::Lokliste;
    startConfigDataRequest(m_currentType, &m_currentInfo, &m_buffer, 1);
    // m_state = LocoManagmentState::WaitingForLocoNamen;
    // m_currentInfo = "0 2";
    // m_currentType = DataType::Loknamen;
    // startConfigDataRequest(m_currentType, &m_currentInfo, &m_buffer, 1);
}

bool MaerklinLocoManagment::startConfigDataRequest(DataType type, std::string *info, std::string *buffer)
{
    if (nullptr != buffer)
    {
        buffer->clear();
    }
    if (requestConfigData(type, info, buffer))
    {
        m_transmissionStarted = true;
        m_lastCmdTimeINms = millis();
        return true;
    }
    return false;
}

bool MaerklinLocoManagment::startConfigDataRequest(DataType type, std::string *info, std::string *buffer, uint8_t cmdRepeat)
{
    if (startConfigDataRequest(type, info, buffer))
    {
        m_cmdRepeat = cmdRepeat;
        return true;
    }
    return false;
}

bool MaerklinLocoManagment::Ms2LocoToCs2Loco(std::string &locoName, std::string *ms2Data, std::string *cs2Data)
{
    if ((nullptr == ms2Data) || (nullptr == cs2Data))
    {
        return false;
    }
    uint8_t functionNumber = 0;
    size_t strLenFkt = strlen(".fkt\n") - 2;
    size_t index = ms2Data->find("lok\n");
    *cs2Data = "";
    if (std::string::npos != index)
    {
        *cs2Data = "lokomotive\n .name=" + locoName + "\n .icon=loco\n ";
        size_t indexEndOfFile = ms2Data->find_last_of('\n');
        bool newLine = true;
        for (index += 4; index < ms2Data->size(); index++)
        {
            char character = ms2Data->at(index);
            if (' ' == character)
            {
                if (newLine)
                {
                    continue;
                }
                else
                {
                    *cs2Data += character;
                }
            }
            else if (indexEndOfFile == index)
            {
                *cs2Data += "\n";
                break;
            }
            else if ('\r' == character)
            {
                continue;
            }
            else if ('\n' == character)
            {
                newLine = true;
                *cs2Data += "\n ";
            }
            else if ('.' == character)
            {
                newLine = false;
                if (ms2Data->find(".fkt\n", index) == index)
                {
                    *cs2Data += ".funktionen\n ..nr=";
                    char intBuffer[4];
                    sprintf(intBuffer, "%u", functionNumber);
                    *cs2Data += intBuffer;
                    functionNumber++;
                    index += strLenFkt;
                }
                else if (ms2Data->find(".fkt2\n", index) == index)
                {
                    *cs2Data += ".funktionen_2\n ..nr=";
                    char intBuffer[4];
                    sprintf(intBuffer, "%u", functionNumber);
                    *cs2Data += intBuffer;
                    functionNumber++;
                    index += (strLenFkt + 1);
                }
                else if (ms2Data->find(".typ2", index) == index)
                {
                    *cs2Data += ".typ";
                    index += 4;
                }
                else if (ms2Data->find(".dauer2", index) == index)
                {
                    *cs2Data += ".dauer";
                    index += 6;
                }
                else if (ms2Data->find(".wert2", index) == index)
                {
                    *cs2Data += ".wert";
                    index += 5;
                }
                else if ((ms2Data->find(".name=", index) == index) && (ms2Data->at(index - 1) != '.'))
                {
                    while (ms2Data->at(index) != '\n')
                    {
                        index++;
                    }
                    index++;
                    newLine = true;
                }
                else
                {
                    *cs2Data += character;
                }
            }
            else
            {
                newLine = false;
                *cs2Data += character;
            }
        }
        return true;
    }
    return false;
}

void MaerklinLocoManagment::handleConfigDataStreamFeedback(std::string *data, uint16_t hash, bool success)
{
    if (m_transmissionStarted) // message expected
    {
        if (success)
        {
            m_lastCmdTimeINms = millis();
            m_transmissionStarted = false;
            // analyze buffer depending on current state
            if (nullptr != data)
            {
                if (m_debug)
                {
                    for (auto i : (*data))
                    {
                        Serial.print((char)i);
                    }
                    Serial.print("\n");
                }
                switch (m_state)
                {
                case LocoManagmentState::WaitingForLocoList:
                {
                    if (m_debug)
                    {
                        Serial.println("Received Lokliste");
                    }
                    // extract all loconames and switch to lokinfo for getting data
                    size_t nameStringSize = strlen(".name=");
                    m_locoList.clear();
                    for (size_t index = 0, nameEnd = 0; (index = data->find(".name=", index)) != std::string::npos; index = nameEnd)
                    {
                        index += nameStringSize;
                        nameEnd = data->find('\n', index);
                        std::string locoName = data->substr(index, nameEnd - index);
                        if (!locoName.empty())
                        {
                            m_locoList.emplace_back(move(locoName));
                        }
                        // Serial.print("Found loco:");
                        // Serial.print(m_locos->back()->name.c_str());
                        // Serial.print(" with size ");
                        // Serial.println(m_buffer->substr(index, nameEnd - index).size());
                    }
                    m_numberOfLoco = m_locoList.size();
                    m_currentLocoNum = 0;
                    if (m_debug)
                    {
                        Serial.println("locos:");
                        for (auto lok : m_locoList)
                        {
                            Serial.println(lok.c_str());
                        }
                    }
                    if (m_numberOfLoco > 0)
                    {
                        if (nullptr != m_writeFileCallback)
                        {
                            std::string baseString{"[lokomotive]\n"
                                                   "version\n"
                                                   " .minor=3\n"
                                                   "session\n"
                                                   " .id=1\n"};
                            m_writeFileCallback(&baseString);
                        }

                        if (m_debug)
                        {
                            Serial.print("Found ");
                            Serial.print(m_numberOfLoco);
                            Serial.println(" locos");
                        }
                        m_state = LocoManagmentState::WaitingForLocoInfo;
                        m_currentType = DataType::Lokinfo;
                        m_currentInfo = m_locoList.at(m_currentLocoNum);
                        startConfigDataRequest(m_currentType, &m_currentInfo, &m_buffer, 1);
                    }
                    else
                    {
                        Serial.println("No locos could be read");
                    }
                }
                break;
                case LocoManagmentState::WaitingForLocoInfo:
                {
                    if (nullptr != m_writeFileCallback)
                    {
                        // transform loco string into new string
                        std::string cs2LocoString;
                        // Serial.print(data->c_str());
                        Ms2LocoToCs2Loco(m_locoList.at(m_currentLocoNum), data, &cs2LocoString);
                        m_writeFileCallback(&cs2LocoString);
                    }
                    m_currentLocoNum++;
                    if (m_currentLocoNum < m_locoList.size())
                    {
                        m_state = LocoManagmentState::WaitingForLocoInfo;
                        m_currentType = DataType::Lokinfo;
                        m_currentInfo = m_locoList.at(m_currentLocoNum);
                        startConfigDataRequest(m_currentType, &m_currentInfo, &m_buffer, 1);
                    }
                    else
                    {
                        // all loco received
                        if (nullptr != m_resultCallback)
                        {
                            m_resultCallback(true);
                        }
                    }
                }
                break;
                case LocoManagmentState::WaitingForLocoNamen:
                {
                    if (0 == m_locoList.size())
                    {
                        // read maximum number of locomotives
                        if (std::string::npos == Cs2DataParser::getParameter(data, ".wert=", m_numberOfLoco, 0))
                        {
                            if (nullptr != m_resultCallback)
                            {
                                m_resultCallback(true);
                            }
                            return;
                        }
                    }
                    // get first loco
                    std::string locoName;
                    std::string::size_type pos = Cs2DataParser::getParameter(data, ".name=", locoName, 0);
                    if (std::string::npos != pos)
                    {
                        m_locoList.emplace_back(move(locoName));
                    }
                    // get second loco if diff is high enough
                    if (m_locoList.size() < m_numberOfLoco)
                    {
                        pos = Cs2DataParser::getParameter(data, ".name=", locoName, 0);
                        if (std::string::npos != pos)
                        {
                            m_locoList.emplace_back(move(locoName));
                        }
                    }
                    // check if all locos where received
                    if (m_locoList.size() < m_numberOfLoco)
                    {
                        m_state = LocoManagmentState::WaitingForLocoNamen;
                        m_currentInfo = std::to_string(m_locoList.size()) + " 2";
                        m_currentType = DataType::Loknamen;
                        startConfigDataRequest(m_currentType, &m_currentInfo, &m_buffer, 1);
                    }
                    else
                    {
                        // request first locoinfo
                        m_currentLocoNum = 0;
                        m_state = LocoManagmentState::WaitingForLocoInfo;
                        m_currentType = DataType::Lokinfo;
                        m_currentInfo = m_locoList.at(m_currentLocoNum);
                        startConfigDataRequest(m_currentType, &m_currentInfo, &m_buffer, 1);
                    }
                    // Serial.printf("LocoNamen:%s", data);
                    if (nullptr != m_resultCallback)
                    {
                        m_resultCallback(true);
                    }
                }
                break;
                default:
                    break;
                }
                // if(nullptr != m_callbackFunc)
                // {
                //     m_callbackFunc(true);
                // }
            }
        }
        else
        {
            m_transmissionStarted = false;
            switch (m_state)
            {
            case LocoManagmentState::WaitingForLocoList:
                // Does not seem to work
                // Switch to old version
                m_locoList.clear();
                m_state = LocoManagmentState::WaitingForLocoNamen;
                m_currentInfo = "0 2";
                m_currentType = DataType::Loknamen;
                startConfigDataRequest(m_currentType, &m_currentInfo, &m_buffer, 1);
                break;

            case LocoManagmentState::WaitingForLocoInfo:
            {
                Serial.print("Could not get loco:");
                Serial.println(m_locoList.at(m_currentLocoNum).c_str());
                m_currentLocoNum++;
                if (m_currentLocoNum < m_locoList.size())
                {
                    m_state = LocoManagmentState::WaitingForLocoInfo;
                    m_currentType = DataType::Lokinfo;
                    m_currentInfo = m_locoList.at(m_currentLocoNum);
                    startConfigDataRequest(m_currentType, &m_currentInfo, &m_buffer, 1);
                }
            }
            break;
            case LocoManagmentState::WaitingForLocoNamen:
            {
                // all loco received
                if (nullptr != m_resultCallback)
                {
                    m_resultCallback(false);
                }
            }
            break;
            default:
                break;
            }
        }
    }
    else
    {
        // message not expected. Only [lokliste] is handled, if transmission was successful
        if (success)
        {
            Serial.println("Unexpected data received");
            if (nullptr != data)
            {
                for (auto i : (*data))
                {
                    Serial.print((char)i);
                }
                Serial.print("\n");
            }
        }
    }
}

void MaerklinLocoManagment::cyclic()
{
    if (m_transmissionStarted)
    {
        unsigned long currentTimeINms = millis();
        if ((m_lastCmdTimeINms + m_cmdTimeoutINms) < currentTimeINms)
        {
            Serial.print("Timeout:");
            Serial.print((uint8_t)m_currentType);
            Serial.print(" ");
            Serial.println(m_currentInfo.c_str());
            if (m_cmdRepeat < m_maxCmdRepeat)
            {
                Serial.println("Repeat");
                m_cmdRepeat++;
                startConfigDataRequest(m_currentType, &m_currentInfo, &m_buffer);
            }
            else
            {
                handleConfigDataStreamFeedback(nullptr, 0, false);
            }
        }
    }
}
