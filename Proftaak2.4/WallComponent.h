#pragma once

#include "DrawComponent.h"

class StageComponent : public DrawComponent
{
public:
	StageComponent();
	~StageComponent();

	virtual void draw() override;
};