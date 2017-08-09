#pragma once
#include "Living.h"

class Actor : public Living {
public:
	//Base class destructor is ALWAYS implicitly called...
	virtual ~Actor() override {}

public:
	void Move() override {};
	void Attack() override {};
};