### HLT customization functions for Run-3

```
cmsrel CMSSW_13_0_0_pre4
cd CMSSW_13_0_0_pre4/src
cmsenv
git cms-merge-topic  silviodonato:customizeHLTfor2023
scram b -j4
hltGetConfiguration (....) > hlt.py 
```

then you can call the customization function(s) by adding at the bottom of your `hlt.py`, as usual. Example:

```
from HLTrigger.Configuration.customizeHLTFor2023 import customizeHCALFor2023
process = customizeHCALFor2023(process)
```

or you can use directly
```
hltGetConfiguration (...) --customise HLTrigger/Configuration/customizeHLTFor2023.customizeHCALFor2023
```

or you can use it in cmsDriver:
```
cmsDriver.py step2 (...) --customise HLTrigger/Configuration/customizeHLTFor2023.customizeHCALFor2023
```

Examples:
```
hltGetConfiguration /dev/CMSSW_13_0_0/GRun \
   --globaltag 126X_dataRun3_HLT_v1 \
   --data \
   --unprescale \
   --output minimal \
   --max-events 100 \
   --customise HLTrigger/Configuration/customizeHLTFor2023.customizeHCALFor2023 \
   --eras Run3 \
   --input /store/data/Run2022G/EphemeralHLTPhysics3/RAW/v1/000/362/720/00000/850a6b3c-6eef-424c-9dad-da1e678188f3.root \
   > hltData.py
   
cmsRun hltData.py >& log &
```

or (example from step2 of `runTheMatrix.py -l 140.003 -n --extended`)

```
cmsDriver.py step2  --process reHLT -s L1REPACK:Full,HLT:@relval2022 --conditions auto:run3_hlt_relval --data  --eventcontent FEVTDEBUGHLT --datatier FEVTDEBUGHLT --era Run3 -n 10 --filein=/store/data/Run2022G/EphemeralHLTPhysics3/RAW/v1/000/362/720/00000/850a6b3c-6eef-424c-9dad-da1e678188f3.root  --customise HLTrigger/Configuration/customizeHLTFor2023.customizeHCALFor2023

cmsRun step2_L1REPACK_HLT.py >& log &
```

### References

s12 from https://indico.cern.ch/event/1237252/contributions/5204534 
(XC coordination: https://indico.cern.ch/event/1251668)

