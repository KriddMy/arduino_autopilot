#include "AutopilotXY.h"

AutopilotXY Autopilot = AutopilotXY();

void setup() { 
  Autopilot.Init();
}

void loop() {
  Autopilot.UpdatePosition();
  Autopilot.UpdateUI();
  Autopilot.PositionPostprosses();
  Autopilot.UpdateUI();
}
