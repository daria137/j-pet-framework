/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @file JPetTaskIO.h
 */

#ifndef JPETTASKIO_H
#define JPETTASKIO_H

#include "./JPetProgressBarManager/JPetProgressBarManager.h"
#include "./JPetTaskInterface/JPetTaskInterface.h"
#include "./JPetParamManager/JPetParamManager.h"
#include "./JPetStatistics/JPetStatistics.h"
#include "./JPetParams/JPetParams.h"
#include "./JPetTask/JPetTask.h"
#include <memory>
#include <string>

class JPetTreeHeader;
class JPetStatistics;
class JPetWriter;
class JPetReader;

/**
 * @brief Computing task with input/output operations.
 *
 * Class representing computing task with input/output operations.
 * In the current implementation the single entry that is read by the reader
 * corresponds to a JPetTimeWindow object.
 * TODO Add tests for this class
 */
class JPetTaskIO: public JPetTask
{
public:
  JPetTaskIO(const char* name = "", const char* in_file_type = "", const char* out_file_type = "");
  virtual ~JPetTaskIO();
  virtual bool init(const JPetParamsInterface& inOptions) override;
  virtual bool run(const JPetDataInterface& inData) override;
  virtual bool terminate(JPetParamsInterface& outOptions) override;
  virtual void addSubTask(std::unique_ptr<JPetTaskInterface> subTask) override;
  void displayProgressBar(int currentEventNumber, int numberOfEvents) const;
  void setOptions(const JPetParams& opts);
  inline JPetParams getOptions() const { return fParams; }

protected:
  virtual std::tuple<bool, std::string, std::string, bool> setInputAndOutputFile(
    const jpet_options_tools::OptsStrAny options) const;
  virtual bool createInputObjects(const char* inputFilename);
  virtual bool createOutputObjects(const char* outputFilename);
  bool setUserLimits(const jpet_options_tools::OptsStrAny& opts,
    const long long kTotEventsFromReader,
    long long& first, long long& last) const;
  const JPetParamBank& getParamBank();
  JPetParamManager& getParamManager();
  std::map<std::string, std::unique_ptr<JPetStatistics>> fSubTasksStatistics;
  std::unique_ptr<JPetStatistics> fStatistics = 0;
  JPetProgressBarManager fProgressBar;
  JPetReaderInterface* fReader = 0;
  std::string fOutFileFullPath;
  JPetTreeHeader* fHeader = 0;
  std::string fOutFileType;
  std::string fInFileType;
  JPetWriter* fWriter = 0;
  bool fResetOutputPath;
  JPetParams fParams;
  int fEventNb = -1;
};

#endif /* !JPETTASKIO_H */
