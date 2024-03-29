/*
 * Copyright 2018 Uber Technologies, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "bbox.h"
#include "benchmark.h"
#include "h3api.h"
#include "polygon.h"

// Fixtures
GeoCoord coord = {0.6593020122281105, -2.136646587644049};

GeoCoord smallVerts[] = {{0.6593216174404631, -2.136686544190228},
                         {0.6592922488566673, -2.1367052400423},
                         {0.6592659902057862, -2.136683255590617},
                         {0.6592690997315311, -2.136642575268508},
                         {0.6592984683133152, -2.1366238782059224},
                         {0.6593247273713713, -2.136645862675915},
                         {0.6593216174404631, -2.136686544190228}};
Geofence smallGeofence;
BBox smallBBox;

GeoCoord largeVerts[] = {{0.659094230575688, -2.1371021015485354},
                         {0.6590648582999955, -2.137120785446624},
                         {0.6590386025000088, -2.1370988011284138},
                         {0.6590417185683777, -2.1370581328924323},
                         {0.6590154614299164, -2.1370361492494108},
                         {0.6590185761584009, -2.136995480477803},
                         {0.6589923176815468, -2.136973497510139},
                         {0.6589954310701313, -2.1369328282032267},
                         {0.6589691712549669, -2.13691084591109},
                         {0.6589722833036354, -2.136870176069197},
                         {0.6589460221502428, -2.1368481944527566},
                         {0.6589491328589803, -2.1368075240762017},
                         {0.658922870367441, -2.136785543135628},
                         {0.6589259797362319, -2.136744872224736},
                         {0.6588997159066284, -2.1367228919601997},
                         {0.6589028239354577, -2.13668222051529},
                         {0.658876558767872, -2.1366602409269593},
                         {0.6588796654567243, -2.136619568948354},
                         {0.6589090377185067, -2.136600875366403},
                         {0.6589121434726317, -2.136560201662654},
                         {0.6589415152070064, -2.1365415063736677},
                         {0.6589446200261924, -2.136500830944929},
                         {0.6589739912329232, -2.1364821339488738},
                         {0.6589770951169582, -2.136441456795302},
                         {0.659006465795809, -2.136422758092143},
                         {0.6590095687444818, -2.1363820792138917},
                         {0.6590389388952168, -2.136363378803596},
                         {0.6590420409083151, -2.136322698200821},
                         {0.6590714105306988, -2.1363039960833543},
                         {0.659074511608011, -2.1362633137562117},
                         {0.6591038807018073, -2.1362446099315373},
                         {0.6591069808431212, -2.1362039258801833},
                         {0.6591363494080951, -2.1361852203482696},
                         {0.6591626178344537, -2.136207200077111},
                         {0.6591919858731505, -2.136188494047296},
                         {0.6592182533686533, -2.1362104744708654},
                         {0.6592476208809147, -2.136191767943126},
                         {0.6592738874454308, -2.136213749061465},
                         {0.6593032544310998, -2.136195042035775},
                         {0.6593295200644976, -2.136217023848928},
                         {0.6593588865234161, -2.1361983163252596},
                         {0.659385151225565, -2.1362202988332704},
                         {0.6594145171575755, -2.1362015908116003},
                         {0.6594407809283439, -2.136223574014512},
                         {0.6594701463332887, -2.1362048654948134},
                         {0.6594964091725459, -2.136226849392669},
                         {0.659525774050267, -2.1362081403749165},
                         {0.659552035957882, -2.1362301249677595},
                         {0.6595489325807627, -2.1362708185614188},
                         {0.6595751931496329, -2.1362928038322995},
                         {0.6595720884311551, -2.1363334968937866},
                         {0.6595983476611981, -2.1363554828425366},
                         {0.6595952416013771, -2.1363961753715284},
                         {0.6596214994925101, -2.1364181619979767},
                         {0.6596183920913612, -2.136458853994151},
                         {0.659644648643503, -2.1364808412981295},
                         {0.6596415399010412, -2.1365215327611633},
                         {0.6596677951141098, -2.1365435207425008},
                         {0.6596646850303514, -2.1365842116720724},
                         {0.659690938904264, -2.136606200330602},
                         {0.6596878274792236, -2.1366468907263876},
                         {0.6597140800138991, -2.136668880061937},
                         {0.6597109672475924, -2.136709569923617},
                         {0.6596816023515922, -2.136728269257012},
                         {0.6596784886490965, -2.136768957391624},
                         {0.6596491232239399, -2.1367876550164606},
                         {0.6596460085854672, -2.1368283414238483},
                         {0.659616642631389, -2.1368470373401607},
                         {0.6596135270571513, -2.1368877220201696},
                         {0.6595841605743876, -2.1369064162279927},
                         {0.6595810440645967, -2.1369470991804675},
                         {0.6595516770533838, -2.1369657916798346},
                         {0.6595485596082516, -2.137006472904621},
                         {0.6595191920688248, -2.1370251636955686},
                         {0.6595160736885637, -2.137065843192512},
                         {0.6594867056211589, -2.137084532275072},
                         {0.6594835863059806, -2.1371252100440166},
                         {0.6594542177108332, -2.137143897418225},
                         {0.6594279684321879, -2.137121908235114},
                         {0.659398599310775, -2.1371405951126565},
                         {0.6593723491001167, -2.137118606624661},
                         {0.6593429794525963, -2.137137293005565},
                         {0.6593167283100556, -2.1371153052126406},
                         {0.6592873581365857, -2.137133991096931},
                         {0.6592611060622934, -2.1371120039990363},
                         {0.6592317353630313, -2.1371306893867383},
                         {0.659205482357119, -2.137108702983829},
                         {0.6591761111322224, -2.1371273878749673},
                         {0.6591498571948209, -2.137105402167002},
                         {0.6591204854444472, -2.137124086561602},
                         {0.659094230575688, -2.1371021015485354}};
Geofence largeGeofence;
BBox largeBBox;

BEGIN_BENCHMARKS();

smallGeofence.numVerts = 6;
smallGeofence.verts = smallVerts;
bboxFromGeofence(&smallGeofence, &smallBBox);

largeGeofence.numVerts = 90;
largeGeofence.verts = largeVerts;
bboxFromGeofence(&largeGeofence, &largeBBox);

BENCHMARK(pointInsideGeofenceSmall, 100000,
          { pointInsideGeofence(&smallGeofence, &smallBBox, &coord); });

BENCHMARK(pointInsideGeofenceLarge, 100000,
          { pointInsideGeofence(&largeGeofence, &largeBBox, &coord); });

BENCHMARK(bboxFromGeofenceSmall, 100000,
          { bboxFromGeofence(&smallGeofence, &smallBBox); });

BENCHMARK(bboxFromGeofenceLarge, 100000,
          { bboxFromGeofence(&largeGeofence, &largeBBox); });

END_BENCHMARKS();
