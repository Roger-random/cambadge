// Time lapse app for the Superconference 2017 camera badge

#include "cambadge.h"
#include "globals.h"

// Application states

#define state_start 0
#define state_menu 1

char* timelapse(unsigned int action)
{
  static unsigned int state;
  
  switch(action) {
    case act_name : 
      return("TIME-LAPSE");
    case act_help : 
      return("Takes time-lapse\nvideo");
    case act_start :
      state = state_start;
      return(0);
    case act_init :
    case act_powerdown :
      return(0);
  }

  // By this point, we've handled all actions other than act_poll that we
  // understand. If it's not act_poll, return zero for no-op.
  if (action!=act_poll)
  {
    return(0);
  }

  if(!tick) 
  {
    // It hasn't been 20ms since the last call.
    return(0);
  }

  switch(state)
  {
    case state_start:
      printf(cls top butcol "EXIT");
      state = state_menu;
      break;
    case state_menu:
      break;
    default:
      printf(tabx6 taby0 whi "State ERROR");
      break;
  }
  
  if(butpress & powerbut) 
  {
    // Power button has been pressed, this is our cue to leave.
    return(""); // exit with nonzero value to indicate we want to quit  
  }
  
  return(0);  
}