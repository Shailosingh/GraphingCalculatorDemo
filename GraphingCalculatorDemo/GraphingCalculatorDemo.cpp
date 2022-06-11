#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <iostream>
#include <math.h>

#define Pi (2*acos(0.0))

class Engine : public olc::PixelGameEngine
{
public:
	//Datafields
	int32_t MidpointX;
	int32_t MidpointY;

	//Constructor
	Engine()
	{
		sAppName = "Graphing Calculator Test";
	}

	/// <summary>
	/// Called at the start of the engine and is made to setup initial
	/// settings and datafields for the engine
	/// </summary>
	/// <returns>Returns false if startup failed and engine must exit. True if startup was successful</returns>
	bool OnUserCreate() override
	{
		//Draw axis lines
		MidpointX = ScreenWidth() / 2;
		DrawLine(MidpointX, 0, MidpointX, ScreenHeight(), olc::Pixel(255, 255, 255));
		MidpointY = ScreenHeight() / 2;
		DrawLine(0, MidpointY, ScreenWidth(), MidpointY, olc::Pixel(255, 255, 255));

		//Draw graph
		for (int32_t x1Pixel = 0; x1Pixel < ScreenWidth()-1; x1Pixel++)
		{
			//Get the x-coordinate after x1Pixel
			int32_t x2Pixel = x1Pixel + 1;

			//Center the x1Pixel and x2Pixel so that the midpoint of the screen is 0
			int32_t centeredX1Pixel = x1Pixel - MidpointX;
			int32_t centeredX2Pixel = x2Pixel - MidpointX;

			//Get the centered y-coordinate and then convert it to the uncentered pixel value
			int32_t y1Pixel = MidpointY - MathematicalFunction(centeredX1Pixel);
			int32_t y2Pixel = MidpointY - MathematicalFunction(centeredX2Pixel);

			//Draw line between two pixels on screen
			DrawLine(x1Pixel, y1Pixel, x2Pixel, y2Pixel, olc::Pixel(255, 0, 0));
		}

		return true;
	}

	/// <summary>
	/// Code called every frame
	/// </summary>
	/// <param name="fElapsedTime">Time elapsed om seconds since last time this function was called</param>
	/// <returns>Returns false if engine is ready to exit. True if the engine should keep going</returns>
	bool OnUserUpdate(float fElapsedTime) override
	{
		return true;
	}

private:
	/// <summary>
	/// Defines the mathematical function that shall be displayed on the screen
	/// </summary>
	/// <param name="x">The x-coordinate input</param>
	/// <returns>The y-coordinate output</returns>
	int32_t MathematicalFunction(int32_t x)
	{
		double amplitude = MidpointY / 2;
		int32_t numberOfPeriods = 3;
		double horizontalStretch = (2 * Pi * numberOfPeriods) / ScreenWidth();
		return (int32_t)(amplitude*sin(horizontalStretch*x));
	}
};

int main()
{
	//Create engine
	Engine engineObject;

	//Startup the engine
	int32_t pixelWidth = 1;
	if (engineObject.Construct(1980 / pixelWidth, 1080 / pixelWidth, pixelWidth, pixelWidth))
	{
		engineObject.Start();
	}
}
