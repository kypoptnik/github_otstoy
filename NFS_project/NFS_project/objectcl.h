#pragma once
class objectcl
{
	public:


		virtual void Render()=0;
		virtual bool Update(float a)=0;

	objectcl(void);
	~objectcl(void);
};

