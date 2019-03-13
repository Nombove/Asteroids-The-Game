#include "Animation.h"



Animation::Animation(int m_fps, int m_amountOfFrames) :
	m_FPS(m_fps), m_AmountOfFrames(m_amountOfFrames)
{
}


Animation::~Animation()
{
}

void Animation::Update(float elapsedSec)
{

	m_Timer += elapsedSec;
	if (m_Timer >= (1.0f / m_FPS))
	{
		m_Timer = 0.0f;

		++m_CurrentFrame;

		if (m_CurrentFrame >= m_AmountOfFrames)
		{
			m_CurrentFrame = 0;
		}
	}
}

int Animation::GetCurrentFrame() const
{
	return m_CurrentFrame;
}
