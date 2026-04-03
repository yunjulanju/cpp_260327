#pragma once

//Interface 처럼 사용할 것임.
//벗 cpp에는 interface없음.
class IRenderableComponent
{
public:
	virtual void Render() = 0;
};

