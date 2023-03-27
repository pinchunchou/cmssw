### HLT customization functions for 2023 Run-3 studies

customizeHLTFor2023WithJEC_v2 will include:
- new 2023 HCAL PF rechits thresholds
- new 2023 PF hadron calibration
- new 2023 Jet Energy Correction for all kind of jets: AK4CaloHLT, AK4PFHLT, AK8PFHLT, AK8CaloHLT

The difference with respect to customizeJECFor2023_noAK8CaloHLT is:
- new 2023 Jet Energy Correction includes AK8CaloHLT
- new 2023 Jet Energy Correction for AK4CaloHLT has been slightly updated


```
cmsrel CMSSW_13_0_0
cd CMSSW_13_0_0/src
cmsenv
git cms-merge-topic silviodonato:customizeHLTFor2023
scram b -j4
hltGetConfiguration (....) > hlt.py 
```

then you can call the customization function(s) by adding at the bottom of your `hlt.py`, as usual. Example:

```
from HLTrigger.Configuration.customizeHLTFor2023 import customizeHLTFor2023WithJEC_v2
process = customizeHLTFor2023WithJEC_v2(process)
```

or you can use directly
```
hltGetConfiguration (...) --customise HLTrigger/Configuration/customizeHLTFor2023.customizeHLTFor2023WithJEC_v2
```

or you can use it in cmsDriver:
```
cmsDriver.py step2 (...) --customise HLTrigger/Configuration/customizeHLTFor2023.customizeHLTFor2023WithJEC_v2
```

Example 1:
```
hltGetConfiguration /dev/CMSSW_13_0_0/GRun/V24 \
   --globaltag 126X_dataRun3_HLT_v1 \
   --data \
   --unprescale \
   --output minimal \
   --max-events 100 \
   --customise HLTrigger/Configuration/customizeHLTFor2023.customizeHLTFor2023WithJEC_v2 \
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

Example-1 extracts from ConfDB the menu `GRun/V24`, which is the last version of the GRun menu compatible with the last L1T menu of 2022, i.e. [`L1Menu_Collisions2022_v1_4_0`](https://htmlpreview.github.io/?https://github.com/cms-l1-dpg/L1MenuRun3/blob/57fcce7ecf26366084813755f769f47be58bbf5f/development/L1Menu_Collisions2022_v1_4_0/L1Menu_Collisions2022_v1_4_0.html).

Example-2 uses the version of the GRun menu available in the CMSSW release; for `CMSSW_13_0_0`, this corresponds to `GRun/V14`.

### Customization function to run the latest HLT menu on 2022 data collected with L1Menu_Collisions2022_v1_4_0

The latest version of the GRun menu in ConfDB is compatible with the first L1T menu of 2023, i.e. [`L1Menu_Collisions2023_v1_0_0`](https://htmlpreview.github.io/?https://github.com/cms-l1-dpg/L1MenuRun3/blob/57fcce7ecf26366084813755f769f47be58bbf5f/development/L1Menu_Collisions2023_v1_0_0/L1Menu_Collisions2023_v1_0_0.html).

If you want to run on 2022 data using the old [`L1Menu_Collisions2022_v1_4_0`](https://htmlpreview.github.io/?https://github.com/cms-l1-dpg/L1MenuRun3/blob/57fcce7ecf26366084813755f769f47be58bbf5f/development/L1Menu_Collisions2022_v1_4_0/L1Menu_Collisions2022_v1_4_0.html), you can customise the latest HLT GRun menu to make it compatible with the last L1T menu of 2022 using
```
--customise HLTrigger/Configuration/customizeHLTFor2023.customizeHLTFor2022L1TMenu
```
Example:
```
hltGetConfiguration /dev/CMSSW_13_0_0/GRun \
   --globaltag 126X_dataRun3_HLT_v1 \
   --data \
   --unprescale \
   --output minimal \
   --max-events 100 \
   --customise \
HLTrigger/Configuration/customizeHLTFor2023.customizeHLTFor2023WithJEC_v2,\
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
