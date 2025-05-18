#include "Form1.h"

[STAThread]
int main()
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew EmployeeManager::Form1());
    return 0;
}