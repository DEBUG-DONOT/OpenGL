#pragma once
class Application
{
public:
	Application() = default;
	virtual ~Application();
	void tick();//让整个程序跑起来
	bool AppInitialization();
	static double clockTick();
private:
	void LogicTick();
	void RenderTick();
	static double currFrame;
	static double lastFrame;
	static double deltaTime;
};