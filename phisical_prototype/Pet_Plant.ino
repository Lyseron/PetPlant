int   greenLed = 8;
int   redLed = 7;
int   orangeLed = 6;
int   humiditySensor = A0;
int   waterButton = 4;
int   waterProgress = 0;

struct PlantProfile {
  const char *name;
  int        dryMax;
  int        okMax;
};

PlantProfile orchid = {
  "Orchid",
  250,
  600
};

enum   PlantState {
  DRY,
  OK,
  WET
};

void setup() {
  Serial.begin(9600);

  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(orangeLed, OUTPUT);
  pinMode(waterButton, INPUT_PULLUP);
}

void  dryPlant(int humidityValue)
{
  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, LOW);
  digitalWrite(orangeLed, LOW);
  Serial.print("Humidity value: ");
  Serial.println(humidityValue);
  Serial.print(" -> so very dry ! ");
}

void  okPlant(int humidityValue)
{
  digitalWrite(orangeLed, HIGH);
  digitalWrite(greenLed, LOW);
  digitalWrite(redLed, LOW);
  Serial.print("Humidity value: ");
  Serial.println(humidityValue);
  Serial.print(" -> perfect ! ");
}

void  wetPlant(int humidityValue)
{
  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, LOW);
  digitalWrite(orangeLed, LOW);
  Serial.print("Humidity value: ");
  Serial.println(humidityValue);
  Serial.print(" -> Too much water ! ");
}

PlantState  getPlantState(int humidityValue, PlantProfile plant)
{
  if (humidityValue <= plant.dryMax)
    return DRY;
  else if (humidityValue <= plant.okMax)
    return OK;
  else
    return WET;
}

void  showPlantState(PlantState state, int humidityValue)
{
  if (state == DRY)
    dryPlant(humidityValue);
  else if (state == OK)
    okPlant(humidityValue);
  else if (state == WET)
    wetPlant(humidityValue);
  else
  {
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, LOW);
    digitalWrite(orangeLed, LOW);
  }
}

void  showWaterBar(int waterProgress)
{
  Serial.print("Watering: ");
  Serial.print(waterProgress);
  Serial.println("%");
}

int getWaterProgress(int humidityValue, PlantProfile plant)
{
  int progress;

  progress = humidityValue * 100 / plant.dryMax;

  if (progress > 100)
    progress = 100;
  if (progress < 0)
    progress = 0;

  return progress;
}

void  waterPlant(PlantState state)
{
  int buttonState = digitalRead(waterButton);

  if (buttonState == LOW && state == DRY)
  {
    waterProgress += 5;
    if (waterProgress > 100)
      waterProgress = 100;
    // Serial.println("Watering...");
    showWaterBar(waterProgress);
  }
}

void loop() {
  int humidityValue = analogRead(humiditySensor);
  
  // int waterProgress = getWaterProgress(humidityValue, orchid);
  PlantState state = getPlantState(humidityValue, orchid);

  showPlantState(state, humidityValue);
  waterPlant(state);
  delay(500);
}
