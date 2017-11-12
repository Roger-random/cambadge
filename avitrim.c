// AVI trim app for the Superconference 2017 camera badge

#include "cambadge.h"
#include "globals.h"

// Application states

#define state_start 0
#define state_done 1
#define state_fin 2
#define state_credits 3
#define state_end_menu 4

#define state_show05 50
#define state_wait05 51
#define state_show10 100
#define state_play10 101
#define state_show12 120
#define state_wait12 121
#define state_show16 160
#define state_wait16 161
#define state_show20 200
#define state_play20 201
#define state_show25 250
#define state_wait25 251
#define state_show40 400
#define state_play40 401
#define state_show45 450
#define state_wait45 451
#define state_show50 500
#define state_play50 501
#define state_show60 600
#define state_wait60 601
#define state_show61 610
#define state_wait61 611
#define state_show62 620
#define state_wait62 621
#define state_show63 630
#define state_wait63 631
#define state_show70 700
#define state_wait70 701
#define state_show71 710
#define state_wait71 711

static unsigned int state;
static unsigned int wait;

void waitState(unsigned int waitMax, unsigned int nextState)
{
  if(wait < waitMax)
  {
    wait++;        
  }
  else
  {
    wait = 0;
    state = nextState;
  }
}

void startShow(char* fileName, unsigned int nextState)
{
  printf(cls);
  if (openavi(fileName))
  {
    printf(tabx6 taby0 whi "openavi failed");
    state = state_done;
  }
  else
  {
    state = nextState;
  }      
}

void playState(unsigned int nextState)
{
  unsigned int i = showavi(); // show a frame
  if ((i != 0) || (avi_framenum == avi_frames - 1)) {
      FSfclose(fptr);
      state = nextState;
  }
}

char* avitrim(unsigned int action)
{
  switch(action) {
    case act_name : 
      return("PLAYFILM");
    case act_help : 
      return("Play film festival\nentry");
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
      printf(cls);
      FSchdir("\\");
      state = state_show05;
      break;
    case state_show05:
      printf(tabx3 taby4 "Hackaday");
      printf(tabx3 taby5 "Superconference");
      printf(tabx14 taby8"2017");
      state = state_wait05;
      break;
    case state_wait05:
      waitState(150, state_show10);
      break;
    case state_show10:
      startShow("10entry.avi", state_play10);
      break;
    case state_play10:
      playState(state_show12);
      break;
    case state_show12:
      printf(cls);
      printf(tabx1 taby4 "What's going on");
      printf(tabx2 taby7 "in that back alley?");
      state = state_wait12;
      break;
    case state_wait12:
      waitState(150, state_show16);
      break;
    case state_show16:
      printf(cls);
      printf(tabx7 taby6 "Workshops");
      state = state_wait16;
      break;
    case state_wait16:
      waitState(75, state_show20);
      break;
    case state_show20:
      startShow("20tentac.avi", state_play20);
      break;
    case state_play20:
      playState(state_show25);
      break;
    case state_show25:
      printf(cls);
      printf(tabx4 taby6 "Badge Hacking");
      state = state_wait25;
      break;
    case state_wait25:
      waitState(100, state_show40);
      break;
    case state_show40:
      startShow("40bdtabl.avi", state_play40);
      break;
    case state_play40:
      playState(state_show45);
      break;
    case state_show45:
      printf(cls);
      printf(tabx0 taby4 "Eat, Drink");
      printf(tabx6 taby6 "Congregate");
      printf(tabx12 taby8 "Connect");
      state = state_wait45;
      break;
    case state_wait45:
      waitState(200, state_show50);
      break;
    case state_show50:
      startShow("50food.avi", state_play50);
      break;
    case state_play50:
      playState(state_show60);
      break;
    case state_show60:
      printf(cls);
      printf(tabx2 taby3 "Learn...");
      state = state_wait60;
      break;
    case state_wait60:
      waitState(50, state_show61);
      break;
    case state_show61:
      printf(tabx5 taby5 "Hack...");
      state = state_wait61;
      break;
    case state_wait61:
      waitState(50, state_show62);
      break;
    case state_show62:      
      printf(tabx8 taby7 "Eat...");
      state = state_wait62;
      break;
    case state_wait62:
      waitState(50, state_show63);
      break;
    case state_show63:
      printf(tabx11 taby9 "Repeat!");
      state = state_wait63;
      break;
    case state_wait63:
      waitState(50, state_show70);
      break;
    case state_show70:
      printf(cls);
      printf(tabx0 taby2 "In the back alley of");
      state = state_wait70;
      break;
    case state_wait70:
      waitState(50, state_show71);
      break;
    case state_show71:
      printf(tabx3 taby5 "Hackaday");
      printf(tabx3 taby6 "Superconference");
      printf(tabx14 taby9"2017");
      state = state_wait71;
      break;
    case state_wait71:
      waitState(150, state_done);
      break;
    case state_done:
      printf(cls);
      printf(tabx13 taby11 whi "the end");
      state = state_fin;
    case state_fin:
      waitState(100, state_credits);
      break;
    case state_credits:
      printf(cls top butcol "EXIT");
      printf(bot butcol "REPLAY");
      printf(tabx0 taby4 whi "https://hackaday.io/");
      printf(tabx0 taby5 whi "project/28129-");
      printf(tabx0 taby6 whi "panning-time-lapse-");
      printf(tabx0 taby7 whi "with-supercon-2017-");
      printf(tabx0 taby8 whi "cambadge");
      state = state_end_menu;
    case state_end_menu:
      if(butpress & but1)
      {
        state = state_start;
      }
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