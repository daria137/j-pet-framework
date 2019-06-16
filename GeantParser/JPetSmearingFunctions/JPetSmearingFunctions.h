/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  @file JPetSmearingFunctions.h
 */

#ifndef JPETSMEARINGFUNCTIONS_H
#define JPETSMEARINGFUNCTIONS_H

#include <TF1.h>


#ifdef __CINT__
//when cint is used instead of compiler, override word is not recognized
//nevertheless it's needed for checking if the structure of project is correct
#   define override
#endif

/**
 * @brief stores smearing functions that should be applied to generated computer simulations in
 * order to reproduce collected data 
 */

class JPetSmearingFunctions
{
  public:
    static double addEnergySmearing(double zIn, double eneIn);
    static double addZHitSmearing(double zIn, double eneIn);
    static const double addTimeSmearing(double zIn, double eneIn, double timeIn);

  private:
    static const float kEnergyThreshold;
    static const float kReferenceEnergy;
    static const float kTimeResolutionConstant;

    static std::string fFunEnergySmearing;
    static std::string fFunZHitSmearing;
    static std::string fFunTimeHitSmearing;

    static std::vector<double> fParamEnergySmearing;
    static std::vector<double> fParamZHitSmearing;
    static std::vector<double> fParamTimeHitSmearing;

};

#endif
