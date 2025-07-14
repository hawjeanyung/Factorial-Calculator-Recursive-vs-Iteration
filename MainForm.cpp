#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Replace 'FactorialCalculatorApp' with your actual namespace
    Application::Run(gcnew FactorialCalculatorApp::MainForm());
    return 0;
}
