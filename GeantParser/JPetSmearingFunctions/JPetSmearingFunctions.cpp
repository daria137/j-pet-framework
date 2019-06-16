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

std::string JPetSmearingFunctions::fFunEnergySmearing = "[&](double *x,double *p){ return p[2]*(1+p[0]*exp(-0.5*(pow(x[0],2)))/(sqrt(2*M_PI)*p[2]/1000.));}"; ///< 0:0.044 1:zIn 2:eneIn 
std::string JPetSmearingFunctions::fFunZHitSmearing = "[&](double *x, double *p){return exp(-0.5*(pow(x[0]-p[1]/p[0],2)))/(sqrt(2*M_PI)*p[0]);}"; ///< 0:sigma:0.976 1:zIn 2:eneIn
std::string JPetSmearingFunctions::fFunTimeHitSmearing = "[&](double *x,double *p){ if(p[4]>p[0]) {  return p[5]+p[1]*exp(-0.5*pow(x[0],2))/(sqrt(2*M_PI)); } else {  return p[5]+p[1]*exp(-0.5*pow(x[0],2))/(sqrt(2*M_PI*p[4]/p[2])); };} "; ///< 0:EneThr 1:resolution 2:refEne 3:zIn 4:eneIn 5:timeIn 

std::vector<double> JPetSmearingFunctions::fParamEnergySmearing = {0.044};
std::vector<double> JPetSmearingFunctions::fParamZHitSmearing = {0.976};
std::vector<double> JPetSmearingFunctions::fParamTimeHitSmearing = {kEnergyThreshold,kTimeResolutionConstant,kReferenceEnergy };


double JPetSmearingFunctions::addZHitSmearing(double zIn, double eneIn)
{
  
  auto fParam  = fParamZHitSmearing;
  fParam.push_back(zIn);
  fParam.push_back(eneIn);
  TF1 func("funZHitSmearing", fFunZHitSmearing.c_str(), -120., 120.,fParam.size());
  for(int i=0; i<fParam.size(); i++){
    func.SetParameter(i,fParam[i]);
  }

  return func.GetRandom();
}

double JPetSmearingFunctions::addEnergySmearing(double zIn, double eneIn)
{
  auto fParam  = fParamEnergySmearing;
  fParam.push_back(zIn);
  fParam.push_back(eneIn);
  TF1 func("funEnergySmearing", fFunEnergySmearing.c_str(), 0., 2000.,fParam.size());

  for(int i=0; i<fParam.size(); i++){
    func.SetParameter(i,fParam[i]);
  }

  return func.GetRandom();
}

const double JPetSmearingFunctions::addTimeSmearing(double zIn, double eneIn, double timeIn)
{

  auto fParam  = fParamTimeHitSmearing;
  fParam.push_back(zIn);
  fParam.push_back(eneIn);
  fParam.push_back(timeIn);
  TF1 func("funTimeSmearing", fFunTimeHitSmearing.c_str(), -2000., 2000.,fParam.size());

  for(int i=0; i<fParam.size(); i++){
    func.SetParameter(i,fParam[i]);
  }

  return func.GetRandom();
}
