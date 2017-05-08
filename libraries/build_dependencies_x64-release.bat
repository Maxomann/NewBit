SET buildpath=%~dp0x64-release

xcopy  "CMakeLists.txt" "%buildpath%\" /F /Y

cmake %buildpath%\CMakeLists.txt -G"Visual Studio 15 2017 Win64" -DPACKAGE_DIR=%buildpath%
cmake --build %buildpath%\ --config Release
PAUSE