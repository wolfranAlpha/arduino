#include <SevSeg.h>

enum RouleteState {
  LOOPING,
  STOPPING,
  STOPPED
} typedef RouleteState;

enum SetDP {
  DP_ON = 0,
  DP_OFF = 1
} typedef SetDP;

SevSeg sevseg;

int stoppingCounter;
RouleteState state;
int selectedNumber;
int displayedNumber;

void refreshDisplay(int numberToDisplay, SetDP setPoint = DP_OFF, int delayTime = 75) {
  sevseg.setNumber(numberToDisplay, setPoint);
  sevseg.refreshDisplay();
  delay(delayTime);
}

void onLooping() {
  stoppingCounter = 0;
  displayedNumber = random(10);
  refreshDisplay(displayedNumber);
}

void onStopping() {
  displayedNumber = random(10);
  refreshDisplay(displayedNumber, DP_OFF, 1000 / stoppingCounter);
  
  if(--stoppingCounter <= 0) {
    state = STOPPED;
    selectedNumber = random(10);
  }
}

void onStopped() {
  displayedNumber = selectedNumber;
  refreshDisplay(displayedNumber, DP_ON);
}

void onError() {
  for (int i = 0; i < 4; i++) {
    sevseg.setChars("E");
    sevseg.refreshDisplay();
    delay(200);
  }
}

void setup() {
  byte numDigits = 1;
  byte digitPins[] = {};
  byte segmentPins[] = {4, 5, 8, 7, 6, 3, 2, 9};
  bool resistorsOnSegments = true;

  byte hardwareConfig = COMMON_CATHODE;
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);

  pinMode(13, INPUT);

  randomSeed(analogRead(0));

  stoppingCounter = 0;
  state = LOOPING;
}

void loop() {
  int shouldStop = digitalRead(13);
  
  if (shouldStop == HIGH && state == LOOPING) {
    state = STOPPING;
    stoppingCounter = 10;
  } else if (shouldStop == LOW) {
    state = LOOPING;
  }

  switch (state) {
    case LOOPING: onLooping();
      break;
    case STOPPING: onStopping();
      break;
    case STOPPED: onStopped();
      break;
    default: onError();
      break;
  }
}
