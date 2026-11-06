
// ------------------------------------------- DEFINE & VARIABLE ---------------------------------------------- //

// Animation sequences (zero-based indices)
const uint8_t enterSequence[] = {0, 1, 2, 3};
const uint8_t exitSequence[]  = {1, 0};

// Animation timing
const unsigned long frameInterval = 300;
unsigned long lastFrameTime = 0;

// Current position in the animation sequence
uint8_t currentFrame = 0;

// Plant humidity states
enum PlantState
{
  THIRSTY,
  HEALTHY,
  TOO_WET,
  SLEEPING
};

// Animation phases
enum AnimationPhase
{
  ENTERING,
  IDLE,
  EXITING
};

// Current animation state
int currentPlantState = -1;
AnimationPhase animationPhase = IDLE;

// Store the currently displayed sprite frame
uint8_t displayedFrame = 0;

// ------------------------------------------- FUNCTION UTILS ------------------------------------------------- //

// Determine plant state based on soil moisture and light
int getPlantState()
{
  if (humidityPercent < 35)
    return (THIRSTY);
  else if (humidityPercent <= 65)
  {
    if (lightValue < 400)
      return (SLEEPING);
    else if (lightValue > 600)
      return (HEALTHY);
  }
  else
    return (TOO_WET);
}

// Display a frame for the currently selected plant state
void drawPlantFrame(uint8_t frameIndex)
{
  // Draw the frame for the current plant state
  switch (currentPlantState)
  {
    case THIRSTY:
      displaySprite(frameIndex, THIRSTY_FRAMES);
      break ;

    case HEALTHY:
      displaySprite(frameIndex, HEALTHY_FRAMES);
      break ;

    case TOO_WET:
      displaySprite(frameIndex, TOO_WET_FRAMES);
      break ;

    case SLEEPING:
      displaySprite(frameIndex, SLEEPING_FRAMES);
      break ;
  }

  // Remember the last displayed frame
  displayedFrame = frameIndex;
}


// Start the entering animation for a new state
void startAnimation(int newState)
{
  // Save the new plant state
  currentPlantState = newState;

  // Start the entering phase
  animationPhase = ENTERING;

  // Clear the previous sprite area
  tft.fillRect(15, 20, 210, 210, ILI9341_BLACK);

  // Display the first frame
  drawPlantFrame(0);

  // Prepare the second frame
  currentFrame = 1;

  // Save the starting time
  lastFrameTime = millis();
}

// Select and update the current animation

void chooseSprite()
{
  // Get the desired plant state
  int newState = getPlantState();

  // Initialize the first animation
  if (currentPlantState == -1)
  {
    startAnimation(newState);
    return ;
  }

  unsigned long currentTime = millis();

  // Check for a state change during IDLE
  if (animationPhase == IDLE && currentPlantState != newState)
  {
    // Start the exit animation
    animationPhase = EXITING;
    lastFrameTime = currentTime;
    return ;
  }

  // Wait until the next frame
  if (currentTime - lastFrameTime < frameInterval)
    return ;

  lastFrameTime = currentTime;

// ---------------- ENTERING ---------------- //

  if (animationPhase == ENTERING)
  {
    // Play the entering animation
    drawPlantFrame(enterSequence[currentFrame]);
    currentFrame++;

    // Switch to IDLE when entering is finished
    if (currentFrame >= sizeof(enterSequence))
      animationPhase = IDLE;
  }

// ---------------- IDLE ---------------- //

  else if (animationPhase == IDLE)
  {
    // Alternate between frames 2 and 3
    if (displayedFrame == 2)
      drawPlantFrame(3);
    else
      drawPlantFrame(2);
  }

// ---------------- EXITING ---------------- //

  else if (animationPhase == EXITING)
  {
    // Return progressively to the first frame
    if (displayedFrame > 0)
      drawPlantFrame(displayedFrame - 1);
    else
      // Start the new animation after exiting
      startAnimation(getPlantState());
  }
}
