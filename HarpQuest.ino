#include "Mp3Player.h"
#include "HarpString.h"

#include "GameManager.h"
#include "NormalGameState.h"
#include "CalibrationState.h"
#include "FinishGameState.h"

#include "Button.h"

HarpString harpString[] = 
{
  HarpString(A0),
  HarpString(A1),
  HarpString(A2),
  HarpString(A3),
  HarpString(A4)
};

Button btn(BUTTON_PIN);
Button adminButton(ADMIN_BUTTON_PIN);

GameManager manager;

void setup() {
  pinMode(LOCKER_PIN,OUTPUT);
  digitalWrite(LOCKER_PIN, LOW);

  Serial.begin(9600);
  
  Mp3Player::Init(Serial, MP3_BUSY_PIN);
  Mp3Player::SetVolume(SOUND_VOLUME);

  manager.Init(harpString, NUM_HARPSTRINGS);
  manager.LoadGameSequenceFromEEPROM(EEPROM_DATA_START_ADDRESS);
  manager.SetState(new NormalGameState(&manager));

  btn.AddClickCallback(CreateEventHandlerFunction([](){
    manager.SetState(new CalibrationState(&manager));
  }),CALIBRATION_MODE_TIMEOUT);

  adminButton.AddClickCallback(CreateEventHandlerFunction([](){
    manager.SetState(new FinishGameState(&manager));
  }),ADMIN_BUTTON_TIMEOUT);
}

void loop() 
{
  btn.Run();
  adminButton.Run();
  manager.Run();
}
