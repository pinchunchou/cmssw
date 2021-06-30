#ifndef L1Trigger_CSCTriggerPrimitives_CSCUpgradeCathodeLCTProcessor_h
#define L1Trigger_CSCTriggerPrimitives_CSCUpgradeCathodeLCTProcessor_h

/** \class CSCUpgradeCathodeLCTProcessor
 *
 * This class simulates the functionality of the cathode LCT card. It is run by
 * the MotherBoard and returns up to two CathodeLCTs.  It can be run either in
 * a test mode, where it is passed arrays of halfstrip times,
 * or in normal mode where it determines the time and comparator
 * information from the comparator digis.
 *
 * Updates for high pileup running by Vadim Khotilovich (TAMU), December 2012
 *
 * Updates for integrated local trigger with GEMs by
 * Sven Dildick (TAMU) and Tao Huang (TAMU), April 2015
 *
 * Removing usage of outdated class CSCTriggerGeometry by Sven Dildick (TAMU)
 */

#include "L1Trigger/CSCTriggerPrimitives/interface/CSCCathodeLCTProcessor.h"

#include <vector>

class CSCUpgradeCathodeLCTProcessor : public CSCCathodeLCTProcessor {
public:
  /** Normal constructor. */
  CSCUpgradeCathodeLCTProcessor(unsigned endcap,
                                unsigned station,
                                unsigned sector,
                                unsigned subsector,
                                unsigned chamber,
                                const edm::ParameterSet& conf);

protected:
  /* is a given half-strip in a pretrigger dead zone */
  bool busyMap[CSCConstants::MAX_NUM_HALF_STRIPS_RUN2_TRIGGER][CSCConstants::MAX_CLCT_TBINS];

private:
  /** VK: use of localized dead-time zones */
  bool use_dead_time_zoning;

  /* +/- half-strips around a keystrip that are dead
     for a few BX after a CLCT was found*/
  unsigned int clct_state_machine_zone;

  /** VK: allow triggers only in +-pretrig_trig_zone around pretriggers */
  unsigned int pretrig_trig_zone;

  /** VK: whether to use corrected_bx instead of pretrigger BX */
  bool use_corrected_bx;

  /* Phase-2 version of the CLCT finder function */
  std::vector<CSCCLCTDigi> findLCTs(
      const std::vector<int> halfstrip[CSCConstants::NUM_LAYERS][CSCConstants::MAX_NUM_HALF_STRIPS_RUN2_TRIGGER])
      override;

  /* Phase2 version,  Check all half-strip pattern envelopes simultaneously, on every clock cycle, for a matching pattern */
  bool preTrigger(const PulseArray pulse, const int start_bx, int& first_bx) override;
};

#endif
