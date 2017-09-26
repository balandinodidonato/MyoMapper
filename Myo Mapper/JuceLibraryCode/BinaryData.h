/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   RobotoLight_ttf;
    const int            RobotoLight_ttfSize = 170420;

    extern const char*   RobotoMedium_ttf;
    const int            RobotoMedium_ttfSize = 172064;

    extern const char*   icon_png;
    const int            icon_pngSize = 67487;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 3;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}
