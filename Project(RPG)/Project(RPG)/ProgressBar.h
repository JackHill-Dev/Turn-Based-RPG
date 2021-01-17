#pragma once
#include "RenderObject.h"

class ProgressBar
{
public:
	ProgressBar() {};
	ProgressBar(float value, float maxValue);
	~ProgressBar();
	void OnChange(float val);
	void SetObjects(RenderObject* fill, RenderObject* bg);
	void SetBarBgObj(RenderObject* bg);
	void SetBarFillObj(RenderObject* fill);
private:
	float mValue, mMaxValue;
	float mPercent;
	RenderObject* mBarBg;
	RenderObject* mBarFill;
};

