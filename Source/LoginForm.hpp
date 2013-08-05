#ifndef OPENSTEAMCLI_LOGINFORM_H
#define OPENSTEAMCLI_LOGINFORM_H

#include <Consor/Containers/FlowContainer.hpp>
#include <Consor/Containers/AlignContainer.hpp>
#include <Consor/Controls/TextBox.hpp>
#include <Consor/Controls/Button.hpp>
#include <Consor/Controls/PasswordBox.hpp>
#include <Consor/Controls/Label.hpp>
#include "Form.hpp"

#include <string>

class LoginForm : public Form
{
	Consor::FlowContainer _FlowMain, _FlowTable, _FlowLabels, _FlowControls, _FlowButtons;
	Consor::AlignContainer _FlowButtonsAlign;
	
	Consor::Label         _LabelUser, _LabelPassword;
	Consor::TextBox       _TextBoxUser;
	Consor::PasswordBox   _PasswordBoxPassword;
	Consor::Button        _ButtonLogin, _ButtonCancel;
	
	
	void _ButtonLogin_Click();
	void _ButtonCancel_Click();
public:
	LoginForm();
	std::string GetUsername();
	std::string GetPassword();
};

#endif //OPENSTEAMCLI_LOGINFORM_H
