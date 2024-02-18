  #include "AutopilotXY.h"
  #include "ErrorHandler.h"

AutopilotXY Autopilot = AutopilotXY();
ErrorHandler ErrHandler = ErrorHandler();

void setup() { 
  Autopilot.Init();
}

void loop() {
  Autopilot.UpdatePosition();
  Autopilot.UpdateUI();
  Autopilot.PositionPostprosses();
  Autopilot.UpdateUI();
}
