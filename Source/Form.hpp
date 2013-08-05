#ifndef FORM_H
#define FORM_H

#include <Consor/Control.hpp>
#include <Consor/Controls/Label.hpp>
#include <Consor/Containers/WindowContainer.hpp>

enum FormResult
{
	OK,
	Cancel
};

class Form : public Consor::WindowContainer
{
protected:
	FormResult _FormResult;
	bool _Closed;
	Consor::Label _null;
public:
	Form(Consor::Control& Client, const std::string& Title);
	virtual ~Form();

	virtual void Run();

	virtual FormResult Show(const Consor::Vector& pos = Consor::Vector(-1, -1));
	virtual void Close();
};

#endif
