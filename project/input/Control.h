#pragma once
#include<map>
#include "InputID.h"

// “ü—Íƒ^ƒCƒv
enum class ContType
{
	Key,
	Mouse,
	Pad,
	MAX
};

using TrgBool = std::map<Trg, bool>;
using KeyDate = std::map<InputID, TrgBool>;

class Control
{
public:
	void operator()()
	{
		UpDate();
	}
	const KeyDate& GetCntData(void)
	{
		return data;
	}
	virtual ContType GetContType(void) = 0;
	virtual bool SetUp(int no) = 0;

private:
	virtual void UpDate(void) = 0;

protected:
	KeyDate data;
};

