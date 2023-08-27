//#include "01-02.h"
// requires /std:c++latest
// d:\install\MicrosoftVisualStudio\2022\Community\VC\Tools\MSVC\14.36.32532
// https://learn.microsoft.com/en-us/cpp/cpp/tutorial-import-stl-named-module?view=msvc-170
// cl /std:c++latest /EHsc /nologo /W4 /MTd /c "%VCToolsInstallDir%\modules\std.ixx"
// cl /FeimportExample /std:c++latest /EHsc /nologo /W4 /MTd "%VCToolsInstallDir%\modules\std.ixx" importExample.cpp

import std;

void test02()
{
	std::cout << "Import the STL library for best performance\n";
	std::vector<int> v{5, 5, 5};
	for (const auto& e : v)
	{
		std::cout << e;
	}
}

/*
void test02() {
  
}*/
