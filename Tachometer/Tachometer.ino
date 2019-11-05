// Centrifuge tachometer based on motor encoder
// Prints relative centrifugal force

#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

// Encoder
Encoder encoder(22, 23);

// Anglar velocity sampling
elapsedMillis angularVelocityUpdateTime; // ms
const int angularVelocityUpdateInterval = 50; // ms

// Angular velocity calculation
const int countsPerRevolution = 20; // counts
long previousPosition = 0; // counts
elapsedMillis deltaTime; // ms

// RCF calculation
const float radius = 50; // mm
const float rcfScalingFactor = 1.12e-6;

void setup() {
  Serial.begin(115200);
  //Serial.print("rpm");
  //Serial.print(' ');
  Serial.print("rcf");
  Serial.println();
}

void loop() {
  // Angular velocity sampling condition
  if (angularVelocityUpdateTime < angularVelocityUpdateInterval) return;
  angularVelocityUpdateTime = 0;

  // Angular velocity calculation
  long nextPosition = encoder.read();
  float deltaPosition = 1.0 * (nextPosition - previousPosition) / countsPerRevolution; // revolutions
  float angularVelocity = 60 * 1000.0 * deltaPosition / deltaTime; // rpm
  previousPosition = nextPosition;
  deltaTime = 0;

  // RCF calculation
  float rcf = rcfScalingFactor * radius * angularVelocity * angularVelocity;
  
  //Serial.print(angularVelocity);
  //Serial.print(' ');
  Serial.print(rcf);
  Serial.println();
}
