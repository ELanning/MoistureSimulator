#include "./arduinoMocks.h"

enum MoistureStatus
{
    DRY,
    WET,
};

// Turns low level moisture sensor readings into a human readable state.
// Smooths moisture oscillations that can occur when moisture is transitioning from dry to wet and vice versa.
class MoistureSensor
{
public:
    MoistureSensor()
    {
        // Default initialization values until first `poll`.
        status = DRY;
        moisture_ = -1;
        lastSwitchTime_ = millis();
    }

    void poll(int moisture)
    {
        // Update moisture readings.
        int previousMoisture = moisture_;
        moisture_ = moisture;

        // Calculate a potentially new moisture status.
        MoistureStatus previous = calculateStatus(previousMoisture);
        MoistureStatus current = calculateStatus(moisture_);

        unsigned long currentTime = millis();
        const int timeBufferMs = 5000;

        // Sit out one cycle if an overflow is detected.
        // Neglible chance of impacting anything.
        bool overflowDetected = currentTime < lastSwitchTime_;
        if (overflowDetected)
        {
            lastSwitchTime_ = currentTime + timeBufferMs;
            return;
        }

        // Update the moisture status if enough time has passed since the last status change.
        if (previous != current && lastSwitchTime_ - currentTime > timeBufferMs)
        {
            status = current;
            lastSwitchTime_ = millis();
        }
    }

    MoistureStatus status;

private:
    MoistureStatus calculateStatus(int moisture)
    {
        // The maximum moisture value before the soil is considered dry.
        const int wetSoilValueMax = 300;
        if (moisture <= wetSoilValueMax)
            return WET;
        else
            return DRY;
    }

    // `moisture_` does not have units.
    // It is either low to indicate "wetter" (typically 300ish range),
    // or high to indicate dry (typically 500ish range).
    int moisture_;
    unsigned long lastSwitchTime_;
};
