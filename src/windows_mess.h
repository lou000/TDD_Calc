#pragma once
#include <QDebug>
#include <QKeyEvent>
#include "windows.h"

HWND getHWNDfromName(QString wClass, QString wName)
{
    wchar_t* name = new wchar_t[wName.length() + 1];
    wName.toWCharArray(name);
    wchar_t* clas = new wchar_t[wClass.length() + 1];
    wClass.toWCharArray(clas);

    HWND hwnd;
    if(wClass == "")
        hwnd = FindWindowEx(0, 0, 0, name);
    else if(wName == "")
        hwnd = FindWindowEx(0, 0, clas, 0);
    else
        hwnd = FindWindowEx(0, 0, clas, name);

    delete[] name;
    delete[] clas;
    return hwnd;
}

void setWindowToForeground(HWND m_hWnd)
{
    HWND hCurWnd = GetForegroundWindow();
    DWORD dwMyID = GetCurrentThreadId();
    DWORD dwCurID = GetWindowThreadProcessId(hCurWnd, NULL);
    AttachThreadInput(dwCurID, dwMyID, TRUE);
    SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
    SetWindowPos(m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOMOVE);
    SetForegroundWindow(m_hWnd);
    SetFocus(m_hWnd);
    SetActiveWindow(m_hWnd);
    AttachThreadInput(dwCurID, dwMyID, FALSE);
}

bool sendKeyToActiveWindow(Qt::Key key, Qt::KeyboardModifier mod)
{
    quint32 nativeMod = 0;
    if (mod == Qt::ShiftModifier)
        nativeMod = VK_SHIFT;
    if (mod == Qt::ControlModifier)
        nativeMod = VK_CONTROL;
    if (mod == Qt::AltModifier)
        nativeMod = VK_MENU;
    if (mod == Qt::MetaModifier)
        nativeMod = MOD_WIN;

    qint32 nativeKey;
    switch (key)
    {
    case Qt::Key_Escape:
        nativeKey = VK_ESCAPE;
        break;
    case Qt::Key_Tab:
    case Qt::Key_Backtab:
        nativeKey = VK_TAB;
        break;
    case Qt::Key_Backspace:
        nativeKey = VK_BACK;
        break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
        nativeKey = VK_RETURN;
        break;
    case Qt::Key_Insert:
        nativeKey = VK_INSERT;
        break;
    case Qt::Key_Delete:
        nativeKey = VK_DELETE;
        break;
    case Qt::Key_Pause:
        nativeKey = VK_PAUSE;
        break;
    case Qt::Key_Print:
        nativeKey = VK_PRINT;
        break;
    case Qt::Key_Clear:
        nativeKey = VK_CLEAR;
        break;
    case Qt::Key_Home:
        nativeKey = VK_HOME;
        break;
    case Qt::Key_End:
        nativeKey = VK_END;
        break;
    case Qt::Key_Left:
        nativeKey = VK_LEFT;
        break;
    case Qt::Key_Up:
        nativeKey = VK_UP;
        break;
    case Qt::Key_Right:
        nativeKey = VK_RIGHT;
        break;
    case Qt::Key_Down:
        nativeKey = VK_DOWN;
        break;
    case Qt::Key_PageUp:
        nativeKey = VK_PRIOR;
        break;
    case Qt::Key_PageDown:
        nativeKey = VK_NEXT;
        break;
    case Qt::Key_F1:
        nativeKey = VK_F1;
        break;
    case Qt::Key_F2:
        nativeKey = VK_F2;
        break;
    case Qt::Key_F3:
        nativeKey = VK_F3;
        break;
    case Qt::Key_F4:
        nativeKey = VK_F4;
        break;
    case Qt::Key_F5:
        nativeKey = VK_F5;
        break;
    case Qt::Key_F6:
        nativeKey = VK_F6;
        break;
    case Qt::Key_F7:
        nativeKey = VK_F7;
        break;
    case Qt::Key_F8:
        nativeKey = VK_F8;
        break;
    case Qt::Key_F9:
        nativeKey = VK_F9;
        break;
    case Qt::Key_F10:
        nativeKey = VK_F10;
        break;
    case Qt::Key_F11:
        nativeKey = VK_F11;
        break;
    case Qt::Key_F12:
        nativeKey = VK_F12;
        break;
    case Qt::Key_F13:
        nativeKey = VK_F13;
        break;
    case Qt::Key_F14:
        nativeKey = VK_F14;
        break;
    case Qt::Key_F15:
        nativeKey = VK_F15;
        break;
    case Qt::Key_F16:
        nativeKey = VK_F16;
        break;
    case Qt::Key_F17:
        nativeKey = VK_F17;
        break;
    case Qt::Key_F18:
        nativeKey = VK_F18;
        break;
    case Qt::Key_F19:
        nativeKey = VK_F19;
        break;
    case Qt::Key_F20:
        nativeKey = VK_F20;
        break;
    case Qt::Key_F21:
        nativeKey = VK_F21;
        break;
    case Qt::Key_F22:
        nativeKey = VK_F22;
        break;
    case Qt::Key_F23:
        nativeKey = VK_F23;
        break;
    case Qt::Key_F24:
        nativeKey = VK_F24;
        break;
    case Qt::Key_Space:
        nativeKey = VK_SPACE;
        break;
    case Qt::Key_Asterisk:
        nativeKey = VK_MULTIPLY;
        break;
    case Qt::Key_Plus:
        nativeKey = VK_ADD;
        break;
    case Qt::Key_Comma:
        nativeKey = VK_OEM_COMMA;
        break;
    case Qt::Key_Period:
        nativeKey = VK_OEM_PERIOD;
        break;
    case Qt::Key_Minus:
        nativeKey = VK_SUBTRACT;
        break;
    case Qt::Key_Slash:
        nativeKey = VK_DIVIDE;
        break;
    case Qt::Key_Backslash:
        nativeKey = VK_OEM_5;
        break;
    case Qt::Key_MediaNext:
        nativeKey = VK_MEDIA_NEXT_TRACK;
        break;
    case Qt::Key_MediaPrevious:
        nativeKey = VK_MEDIA_PREV_TRACK;
        break;
    case Qt::Key_MediaPlay:
        nativeKey = VK_MEDIA_PLAY_PAUSE;
        break;
    case Qt::Key_MediaStop:
        nativeKey = VK_MEDIA_STOP;
        break;
    case Qt::Key_VolumeDown:
        nativeKey = VK_VOLUME_DOWN;
        break;
    case Qt::Key_VolumeUp:
        nativeKey = VK_VOLUME_UP;
        break;
    case Qt::Key_VolumeMute:
        nativeKey = VK_VOLUME_MUTE;
        break;

        // numbers
    case Qt::Key_0:
    case Qt::Key_1:
    case Qt::Key_2:
    case Qt::Key_3:
    case Qt::Key_4:
    case Qt::Key_5:
    case Qt::Key_6:
    case Qt::Key_7:
    case Qt::Key_8:
    case Qt::Key_9:
        nativeKey = key;
        break;

        // letters
    case Qt::Key_A:
    case Qt::Key_B:
    case Qt::Key_C:
    case Qt::Key_D:
    case Qt::Key_E:
    case Qt::Key_F:
    case Qt::Key_G:
    case Qt::Key_H:
    case Qt::Key_I:
    case Qt::Key_J:
    case Qt::Key_K:
    case Qt::Key_L:
    case Qt::Key_M:
    case Qt::Key_N:
    case Qt::Key_O:
    case Qt::Key_P:
    case Qt::Key_Q:
    case Qt::Key_R:
    case Qt::Key_S:
    case Qt::Key_T:
    case Qt::Key_U:
    case Qt::Key_V:
    case Qt::Key_W:
    case Qt::Key_X:
    case Qt::Key_Y:
    case Qt::Key_Z:
        nativeKey = key;
    break;

    default:
        return 0;
    }
    if(nativeMod)
    {
        INPUT inputs[4];
        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = nativeMod;

        inputs[1].type = INPUT_KEYBOARD;
        inputs[1].ki.wVk = nativeKey;

        inputs[2].type = INPUT_KEYBOARD;
        inputs[2].ki.wVk = nativeKey;
        inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

        inputs[3].type = INPUT_KEYBOARD;
        inputs[3].ki.wVk = nativeMod;
        inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

        if(SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT)) != 4)
            qDebug()<<"Input error";
    }
    else
    {
        INPUT inputs[2];
        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = nativeKey;

        inputs[1].type = INPUT_KEYBOARD;
        inputs[1].ki.wVk = nativeKey;
        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

        if(SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT)) != 2)
            qDebug()<<"Input error";
    }
    return true;
}
