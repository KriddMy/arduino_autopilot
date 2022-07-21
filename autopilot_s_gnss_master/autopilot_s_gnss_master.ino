  #include "AutopilotXY.h"

AutopilotXY Autopilot = AutopilotXY();

void setup() { 
  Autopilot.Init();
}

void loop() {
  Autopilot.UpdatePosition();
  Autopilot.PositionPostprosses();
  Autopilot.UpdateUI();
}
