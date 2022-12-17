#ifdef _WIN32
    #include <windows.h>
#endif

#include <viewer/FileDialog.hpp>
#include <iostream>

namespace viewer {

    std::string openFileDialog(std::string title, std::string filters, std::string directory) {
        OPENFILENAME ofn;       // common dialog box structure
        TCHAR szFile[260] = { 0 };       // if using TCHAR macros

        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = nullptr;
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = filters.data();
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = title.empty() ? nullptr : title.data();
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = directory.empty() ? nullptr : directory.data();
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        if (GetOpenFileName(&ofn) == TRUE)
            return ofn.lpstrFile;
        return {};
    }

    std::string saveFileDialog(std::string title, std::string filters, std::string directory) {
        OPENFILENAME ofn;       // common dialog box structure
        TCHAR szFile[260] = { 0 };       // if using TCHAR macros

        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = nullptr;
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = filters.data();
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = title.empty() ? nullptr : title.data();
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = directory.empty() ? nullptr : directory.data();
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        if (GetSaveFileName(&ofn) == TRUE)
            return ofn.lpstrFile;
        return {};
    }

}