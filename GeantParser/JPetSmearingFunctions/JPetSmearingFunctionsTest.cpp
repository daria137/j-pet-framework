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
 *  @file JPetRandomTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetSmearingFunctionsTest
#include <boost/test/unit_test.hpp>

#include <JPetSmearingFunctions/JPetSmearingFunctions.h>
#include <TRandom.h>

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE( checkSeed )
{
  UInt_t seed = 65529;
  gRandom->SetSeed(seed);
  double r1= gRandom->Rndm();

  gRandom->SetSeed(seed);
  double r2= gRandom->Rndm();

  BOOST_REQUIRE_EQUAL(r1,r2);

}

BOOST_AUTO_TEST_CASE( addZHitSmearing )
{
  UInt_t seed = 65529;
  double zIn = 5.0;
  double eneIn = 200.0;
  
  gRandom->SetSeed(seed);
  double r2 = JPetSmearingFunctions::addZHitSmearing(zIn,eneIn);
  gRandom->SetSeed(seed);
  double r1 = JPetSmearingFunctions::addZHitSmearing(zIn,eneIn);

  BOOST_REQUIRE_EQUAL(r1,r2);
}

BOOST_AUTO_TEST_CASE( addEnergySmearing )
{
  UInt_t seed = 65529;
  double zIn = 5.0;
  double eneIn = 200.0;
  
  gRandom->SetSeed(seed);
  double r2 = JPetSmearingFunctions::addEnergySmearing(zIn,eneIn);
  gRandom->SetSeed(seed);
  double r1 = JPetSmearingFunctions::addEnergySmearing(zIn,eneIn);

  BOOST_REQUIRE_EQUAL(r1,r2);
}


BOOST_AUTO_TEST_CASE( addTimeSmearing )
{
  UInt_t seed = 65529;
  double zIn = 5.0;
  double eneIn = 200.0;
  double timeIn = -590.0;
  
  gRandom->SetSeed(seed);
  double r2 = JPetSmearingFunctions::addTimeSmearing(zIn,eneIn,timeIn);
  gRandom->SetSeed(seed);
  double r1 = JPetSmearingFunctions::addTimeSmearing(zIn,eneIn,timeIn);

  BOOST_REQUIRE_EQUAL(r1,r2);
}



BOOST_AUTO_TEST_SUITE_END()

