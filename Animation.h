#pragma once
class Animation
{
public:
	Animation(int m_fps, int m_amountOfFrames);
	~Animation();

	void Update(float elapsedSec);
	int GetCurrentFrame() const;

private:
	int m_CurrentFrame = 0;
	int m_FPS = 0;
	int m_AmountOfFrames = 0;
	float m_Timer = 0.f; //time of one frame
};

