#include "Form.hpp"
#include <Consor/WindowSystem.hpp>
#include <Consor/Util/Time.hpp>

using namespace Consor;

Form::Form(Consor::Control& Client, const std::string& Title)
	: WindowContainer(Client, Title)
{
	_FormResult = FormResult::OK;
	_Closed = false;
}

Form::~Form()
{
	Close();
}


FormResult Form::Show(const Vector& pos)
{
	WindowSystem::RegisterWindow(*this, pos);

	this->Run();
	this->Close();

	return _FormResult;
}

void Form::Close()
{
	WindowSystem::UnregisterWindow(*this);
	_Closed = true;
}

void Form::Run()
{
	while(!_Closed)
	{
		Util::Sleep(0.1);
	}
}
