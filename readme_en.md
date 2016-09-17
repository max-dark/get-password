About
---
`Get-password` is a small tool to recover stored passwords
hidden by asterisks.  
This program is written using `C++/WinAPI`

system requirements
---
* Windows XP SP3 or above
* [vcredist2013](https://www.microsoft.com/ru-RU/download/details.aspx?id=40784) installed

How to use
---
* run `get-password.exe`
* run the program, from which it is necessary to get your password
* set the focus to the password field
* rotate the scroll wheel
* a window will appear with your password where you can press `ctrl + c` to copy

Limitations:
---
* It works only with input fields that support `GetWindowTextLength / GetWindowText`
* for x64: the bitness of the utility must be same as the program
from which you want pull out a password.

Known that the program works with:
---
* MS Outlook 2003/2010
* Miranda IM