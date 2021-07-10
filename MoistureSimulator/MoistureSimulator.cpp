#include <stdio.h>
#include <windows.h>
#include "./MoistureSensor.h"

int getMoisture(int time)
{
	return 305 - time;
}

void testHappyPath()
{
	int currentTime = 0;
	MoistureSensor sensor = MoistureSensor();

	// Simulate Arduino loop function.
	while (true)
	{
		int moisture = getMoisture(currentTime);
		sensor.poll(moisture);

		switch (sensor.status) {
		case DRY:
			printf("Status is DRY\n");
			break;
		case WET:
			printf("Status is WET\n");
			break;
		}

		currentTime++;
		Sleep(1000);
	}
}

int main()
{
	testHappyPath();
}