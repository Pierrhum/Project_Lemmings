#include "WinConsole.h"

WinConsole::WinConsole()
{
    hOutput = (HANDLE)GetStdHandle( STD_OUTPUT_HANDLE );
    hInput = (HANDLE)GetStdHandle( STD_INPUT_HANDLE );
    
    LONG_PTR new_style =  WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL;
    setConsoleWindowStyle(GWL_STYLE,new_style);

    
    RECT rect;
    CONSOLE_SCREEN_BUFFER_INFO info;
    CONSOLE_FONT_INFO font_info;
    GetCurrentConsoleFont(WinConsole::hOutput, TRUE, &font_info);
    
    if(GetWindowRect(WinConsole::hwnd_console, &rect))
    {
        //SCREEN_WIDTH = rect.right - rect.left;
        //SCREEN_HEIGHT = rect.bottom - rect.top;
    }
    
    if(GetConsoleScreenBufferInfo(WinConsole::hOutput, &info)) {
        COORD coord;
        coord.X = 400;
        coord.Y = 47;

        SCREEN_WIDTH = coord.X;
        SCREEN_HEIGHT = coord.Y;
        
        buffer = new CHAR_INFO*[coord.Y];
        for(int i = 0; i < coord.Y; ++i) {
            buffer[i] = new CHAR_INFO[coord.X];
        }
        
        SetConsoleScreenBufferSize(hOutput, coord);
    }

    SetConsoleMode(hInput, fdwMode);
    FlushConsoleInputBuffer(hInput);
}

//Si le new style est à 0, la fenetre n'a absolument rien à part son contenu
LONG_PTR WinConsole::setConsoleWindowStyle(INT n_index,LONG_PTR new_style)
{
    /*The function does not clear the last error information. if last value was zero.*/
    SetLastError(NO_ERROR);
    
    hwnd_console = GetConsoleWindow();     
    
    SetConsoleTitleA("The Lemmings");
    LONG_PTR style_ptr = SetWindowLongPtr(hwnd_console,n_index,new_style);
    SetConsoleActiveScreenBuffer(hwnd_console);

    SetWindowPos(hwnd_console,0,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,SWP_NOMOVE|SWP_DRAWFRAME);

    
    //show window after updating
    ShowWindow(hwnd_console,SW_MAXIMIZE);
    

    return style_ptr;  
}
