#ifndef __UTILS__
#define __UTILS__

/**
 * This enum contains the tokens to be read from the input.
 * Each token has one type of data associated to it.
 * TIME := the time in which a certain lap starts.
 * PILOT_ID := id of the pilot for the current lap.
 * SKIP :=  it is associated to character '-', that is not associated to any var in the problem.
 * PILOT_NAME := name of the pilot for the current lap.
 * LAP := number of the lap.
 * LAP_TIME := time the pilot used to complete the current lap.
 * AVG_SPEED := avergae speed of the pilot for the current lap.
 */
enum PARSER { TIME, PILOT_ID, SKIP, PILOT_NAME, LAP, LAP_TIME, AVG_SPEED };

#endif
