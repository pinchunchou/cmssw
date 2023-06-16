### customizeHLTFor2023 is obsolete since /dev/CMSSW_13_0_0/HLT/V115 (/dev/CMSSW_13_0_0/GRun/V100) as it includes [CMSHLT-2747](https://its.cern.ch/jira/browse/CMSHLT-2747) and we decided to keep the current 2022 JECs.
### Please use the latest /dev/CMSSW_13_0_0/GRun menu

_______________________________________________________________________________________

### Obsolete recipes:

customizeHLTFor2023_v5_fromFile includes:
- customizeHLTFor2023_onlyHCALrechits <---- apply the new HCAL rechits to all PF and calo jet modules.
- customizeJECFor2023_v5_fromFile <---- load the latest JEC obtained on April 27
- customizePFHadronCalibrationFor2023_v5_fromFile <---- load the latest JEC obtained on April 27 for both PF and calo jets

All previous JEC and PF hadron calibration are wrong because of the ECAL bug in the MC global tag.
To get the fixed ECAL tag in MC please use 126X_mcRun3_2023_forPU65_v4. For data, please use the usual global tag.

```
cmsrel CMSSW_13_0_7_patch1
cd CMSSW_13_0_7_patch1/src
cmsenv
git cms-merge-topic silviodonato:customizeHLTFor2023
scram b -j4
hltGetConfiguration (....) > hlt.py 
```

then you can call the customization function(s) by adding at the bottom of your `hlt.py`, as usual. Example:

```
from HLTrigger.Configuration.customizeHLTFor2023 import customizeHLTFor2023_v5_fromFile
process = customizeHLTFor2023_v5_fromFile(process)
```

or you can use directly
```
hltGetConfiguration (...) --customise HLTrigger/Configuration/customizeHLTFor2023.customizeHLTFor2023_v5_fromFile
```

or you can use it in cmsDriver:
```
cmsDriver.py step2 (...) --customise HLTrigger/Configuration/customizeHLTFor2023.customizeHLTFor2023_v5_fromFile
```

Example 1:
```
hltGetConfiguration /dev/CMSSW_13_0_0/GRun/V24 \
   --globaltag 130X_dataRun3_HLT_v2 \
   --data \
   --unprescale \
   --output minimal \
   --max-events 100 \
   --customise HLTrigger/Configuration/customizeHLTFor2023.customizeHLTFor2023_v5_fromFile \
   --eras Run3 \
   --input /store/data/Run2022G/EphemeralHLTPhysics3/RAW/v1/000/362/720/00000/850a6b3c-6eef-424c-9dad-da1e678188f3.root \
   > hltData.py
   
cmsRun hltData.py >& log &
```

Example 2: (taken from step2 of `runTheMatrix.py -l 140.003 -n --extended`)
```
cmsDriver.py step2 --process reHLT -s L1REPACK:Full,HLT:GRun --conditions auto:run3_hlt_relval --data --eventcontent FEVTDEBUGHLT --datatier FEVTDEBUGHLT --era Run3 -n 10 --filein=/store/data/Run2022G/EphemeralHLTPhysics3/RAW/v1/000/362/720/00000/850a6b3c-6eef-424c-9dad-da1e678188f3.root --customise HLTrigger/Configuration/customizeHLTFor2023.customizeHCALFor2023

cmsRun step2_L1REPACK_HLT.py >& log &
```

Example-1 extracts from ConfDB the menu `GRun/V24`, which is the last version of the GRun menu compatible with the last L1T menu of 2022, i.e.
[`L1Menu_Collisions2022_v1_4_0`](https://htmlpreview.github.io/?https://github.com/cms-l1-dpg/L1MenuRun3/blob/57fcce7ecf26366084813755f769f47be58bbf5f/development/L1Menu_Collisions2022_v1_4_0/L1Menu_Collisions2022_v1_4_0.html).

Example-2 uses the version of the GRun menu available in the CMSSW release; for `CMSSW_13_0_0`, this corresponds to `GRun/V14`.

### Obsolete customization functions

The OBSOLETE customization functions are:

customizeHLTFor2023_v2 (OBSOLETE):
- new 2023 HCAL PF rechits thresholds
- old 2022 HCAL rechits thresholds in CaloJets (hltTowerMakerForAll) --> WRONG! 
- new 2023 PF hadron calibration
- new 2023 Jet Energy Correction for PF jets (AK4PFHLT, AK8PFHLT)
- new 2023 Jet Energy Correction for Calo jets (AK4CaloHLT, AK8CaloHLT) obtained with the old 2022 HCAL rechits thresholds in CaloJets --> WRONG!

customizeJECFor2023_noAK8CaloHLT (OBSOLETE):
- new 2023 HCAL PF rechits thresholds
- old 2022 HCAL rechits thresholds in CaloJets (hltTowerMakerForAll) --> WRONG! 
- new 2023 PF hadron calibration
- new 2023 Jet Energy Correction for PF jets (AK4PFHLT, AK8PFHLT)
- new 2023 Jet Energy Correction for Calo jets obtained with the old 2022 HCAL rechits thresholds in CaloJets, only for AK4CaloHLT --> WRONG!


### Customization function to run the latest HLT menu on 2022 data collected with L1Menu_Collisions2022_v1_4_0

The latest version of the GRun menu in ConfDB is compatible with the latest L1T menu of 2023, i.e.
[`L1Menu_Collisions2023_v1_2_0`](https://htmlpreview.github.io/?https://github.com/cms-l1-dpg/L1MenuRun3/blob/master/development/L1Menu_Collisions2023_v1_2_0/L1Menu_Collisions2023_v1_2_0.html).

In order to modify the latest GRun menu to make it compatible with the previous L1T menu of 2023, i.e.
[`L1Menu_Collisions2023_v1_1_0`](https://htmlpreview.github.io/?https://github.com/cms-l1-dpg/L1MenuRun3/blob/master/development/L1Menu_Collisions2023_v1_1_0/L1Menu_Collisions2023_v1_1_0.html),
the following customisation can be used
```
--customise HLTrigger/Configuration/customizeHLTFor2023.customizeHLTFor2023L1TMenu_v1_1_0
```
A similar argument applies to the first L1T menu of 2023, i.e.
[`L1Menu_Collisions2023_v1_0_0`](https://htmlpreview.github.io/?https://github.com/cms-l1-dpg/L1MenuRun3/blob/master/development/L1Menu_Collisions2023_v1_0_0/L1Menu_Collisions2023_v1_0_0.html),
for which the customisation function is called `customizeHLTFor2023L1TMenu_v1_0_0`.

Example:
```
hltGetConfiguration /dev/CMSSW_13_0_0/GRun \
   --globaltag 130X_dataRun3_HLT_v2 \
   --data \
   --unprescale \
   --output minimal \
   --max-events 100 \
   --customise \
HLTrigger/Configuration/customizeHLTFor2023.customizeHLTFor2023_v5_fromFile,\
HLTrigger/Configuration/customizeHLTFor2023.customizeHLTFor2023L1TMenu_v1_1_0 \
   --eras Run3 \
   --input [input ROOT file] \
   > hltData.py
```

Similarly, if you want to run on 2022 data using the old
[`L1Menu_Collisions2022_v1_4_0`](https://htmlpreview.github.io/?https://github.com/cms-l1-dpg/L1MenuRun3/blob/57fcce7ecf26366084813755f769f47be58bbf5f/development/L1Menu_Collisions2022_v1_4_0/L1Menu_Collisions2022_v1_4_0.html),
you can customise the latest HLT GRun menu to make it compatible with the last L1T menu of 2022 using
```
--customise HLTrigger/Configuration/customizeHLTFor2023.customizeHLTFor2022L1TMenu
```
Example:
```
hltGetConfiguration /dev/CMSSW_13_0_0/GRun \
   --globaltag 130X_dataRun3_HLT_v2 \
   --data \
   --unprescale \
   --output minimal \
   --max-events 100 \
   --customise \
HLTrigger/Configuration/customizeHLTFor2023.customizeHLTFor2023_v5_fromFile,\
HLTrigger/Configuration/customizeHLTFor2023.customizeHLTFor2022L1TMenu \
   --eras Run3 \
   --input /store/data/Run2022G/EphemeralHLTPhysics3/RAW/v1/000/362/720/00000/850a6b3c-6eef-424c-9dad-da1e678188f3.root \
   > hltData.py
```



### Note

You can use separately the functions `customizeHLTFor2023.customizePFHadronCalibrationFor2023` and `customizeHLTFor2023.customizeHCALFor2023`, `customizeHLTFor2023.customizeJECFor2023_noAK8CaloHLT`, and `customizeHLTFor2023.customizeJECFor2023_v2`.

### References

 - Slide 12 from Salavat's talk: [[Indico link]](https://indico.cern.ch/event/1237252/contributions/5204534)

 - PPD coordination meeting: [[Indico link]](https://indico.cern.ch/event/1251668)

 - Changgi's slides at JetMET trigger (PF hadron calibration): [[Indico link]](https://indico.cern.ch/event/1258851/)

 - Changgi's slides at TSG (JEC): [[Indico link]](https://indico.cern.ch/event/1265018/#36-new-hlt-jec)

 - Changgi's slides at TSG, fix (PFHC, JEC, April 13): [[Indico link]](https://indico.cern.ch/event/1272814/#sc-1-6-jetsmet-pog)
