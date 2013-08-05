#include "LoginForm.hpp"

using namespace Consor;

LoginForm::LoginForm() :
	                  Form(_FlowMain, "Login"),
	                  _FlowMain(Consor::FlowContainer::FlowAxis::Vertical, 0),
	                  _FlowTable(Consor::FlowContainer::FlowAxis::Horizontal, 0),
	                  _FlowLabels(Consor::FlowContainer::FlowAxis::Vertical, 0),
	                  _FlowControls(Consor::FlowContainer::FlowAxis::Vertical, 0),
	                  _FlowButtons(Consor::FlowContainer::FlowAxis::Horizontal, 2),
	                  _FlowButtonsAlign(_FlowButtons, Consor::AlignContainer::Axis::Horizontal, Consor::AlignContainer::Align::Center)
{
	// the layout
	_FlowMain.AddControl(_FlowTable);
	_FlowMain.AddControl(_FlowButtonsAlign);
	
	_FlowTable.AddControl(_FlowLabels);
	{
		_FlowLabels.AddControl(_LabelUser);
		_FlowLabels.AddControl(_LabelPassword);
	}
	_FlowTable.AddControl(_FlowControls);
	{
		_FlowControls.AddControl(_TextBoxUser);
		_FlowControls.AddControl(_PasswordBoxPassword);
	}
	
	_FlowButtons.AddControl(_ButtonLogin);
	_FlowButtons.AddControl(_ButtonCancel);
	
	// the properties
	_LabelUser.SetText("User:");
	_LabelPassword.SetText("Pass:");
	
	_ButtonLogin.SetText("Login");
	_ButtonCancel.SetText("Cancel");
	
	// events
	_ButtonLogin.Click += std::bind(&LoginForm::_ButtonLogin_Click, this);
	_ButtonCancel.Click += std::bind(&LoginForm::_ButtonCancel_Click, this);
}

std::string LoginForm::GetUsername()
{
	return this->_TextBoxUser.GetText();
}

std::string LoginForm::GetPassword()
{
	return this->_PasswordBoxPassword.GetPassword();
}

void LoginForm::_ButtonLogin_Click()
{
	this->_FormResult = FormResult::OK;
	this->Close();
}

void LoginForm::_ButtonCancel_Click()
{
	this->_FormResult = FormResult::Cancel;
	this->Close();
}
