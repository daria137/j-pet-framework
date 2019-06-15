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
 *  @file JPetSmearingFunctions.cpp
 */

#include <JPetSmearingFunctions/JPetSmearingFunctions.h>
#include <TMath.h>

const float JPetSmearingFunctions::kEnergyThreshold = 200.; ///< see Eur. Phys. J. C (2016) 76:445  equation 4 and 5 
const float JPetSmearingFunctions::kReferenceEnergy = 270.; ///< see Eur. Phys. J. C (2016) 76:445  equation 4 and 5
const float JPetSmearingFunctions::kTimeResolutionConstant = 80.; ///< see Eur. Phys. J. C (2016) 76:445  equation 3

CachedFunction2D JPetSmearingFunctions::fFunTimeSmearing(fParamTimeSmearing,Range(10000, 0., 100.),Range(10000, 0., 100.));
CachedFunction1D JPetSmearingFunctions::fFunEnergySmearing(fParamEnergySmearing,Range(10000, 0., 100.));

// z: zIn, EneIn
// e: eneIn
// t: t, eneIn
double JPetSmearingFunctions::addZHitSmearing(double zIn, double eneIn)
{

  Params JPetSmearingFunctions::fParamZHitSmearing("exp(-0.5*((x-[0])/[1])**2)/(sqrt(2*pi)*[1]))", {zIn,eneIn});

  CachedFunction2D JPetSmearingFunctions::FunZHitSmearing(fParamZHitSmearing,Range(10000, 0., 100.),Range(10000, 0., 100.));
  //return fRandomGenerator->Gaus(zIn, z_res);
  return FunZHitSmearing->GetRandom();
}

double JPetSmearingFunctions::addEnergySmearing(double eneIn)
{
  /// @param eneIn in keV
  //float alpha = 0.044 / sqrt(eneIn / 1000.);
  //return eneIn + alpha * eneIn * fRandomGenerator->Gaus(0., 1.);
  return fFunEnergySmearing(eneIn);
}

const double JPetSmearingFunctions::addTimeSmearing(float timeIn, float eneIn)
{
  /// @param eneIn in keV
  /// @param timeIn in ps
//  float time;
//
//  if ( eneIn > kEnergyThreshold ) {
//    time = timeIn + kTimeResolutionConstant * fRandomGenerator->Gaus(0., 1.);
//  } else {
//    time = timeIn + kTimeResolutionConstant * fRandomGenerator->Gaus(0., 1.) / sqrt(eneIn / kReferenceEnergy);
//  }

   double ene = 4.0;
  return  fFunTimeSmearing(timeIn,ene);
}


//void JPetSmearingFunctions::SetFunTimeSmearing(const Params &params, Range range) 
//{
//   fFunTimeSmearing(params,range);
//}
//
//void JPetSmearingFunctions::SetStandardSmearing()
//{
//  Params params("pol1", { -91958., 19341.});
//  SetFunTimeSmearing(params,Range(100,0.,100.));
//
//}
