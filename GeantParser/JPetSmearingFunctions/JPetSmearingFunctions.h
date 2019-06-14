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

#include <JPetCachedFunction/JPetCachedFunction.h>

#ifdef __CINT__
//when cint is used instead of compiler, override word is not recognized
//nevertheless it's needed for checking if the structure of project is correct
#   define override
#endif

using Params = jpet_common_tools::JPetCachedFunctionParams;
using Range = jpet_common_tools::Range;
using CachedFunction1D = jpet_common_tools::JPetCachedFunction1D;
using CachedFunction2D = jpet_common_tools::JPetCachedFunction2D;

/**
 * @brief stores smearing functions that should be applied to generated computer simulations in
 * order to reproduce collected data 
 */

const Params fParamTimeSmearing("pol0", {-1});  
const Params fParamEnergySmearing("pol0", {-1});  
const Params fParamZHitSmearing("pol0", {-1});  

class JPetSmearingFunctions
{
  public:
    static float addEnergySmearing(float);
    static float addZHitSmearing(float, float);
    static const double addTimeSmearing(float, float);

    static void SetFunTimeSmearing(const Params &params, const Range range); 

    static void SetStandardSmearing();

  private:
    static const float kEnergyThreshold;
    static const float kReferenceEnergy;
    static const float kTimeResolutionConstant;

    static CachedFunction1D fFunEnergySmearing;
    static CachedFunction2D fFunZHitSmearing;
    static CachedFunction2D fFunTimeSmearing;


};

#endif
