#pragma once
class Application
{
public:
	Application() = default;
	virtual ~Application();
	void tick();//����������������
	bool AppInitialization();
	static double clockTick();
private:
	void LogicTick();
	void RenderTick();
	static double currFrame;
	static double lastFrame;
	static double deltaTime;
};