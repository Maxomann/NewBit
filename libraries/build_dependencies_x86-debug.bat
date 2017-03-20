SET buildpath=%~dp0x86-debug

xcopy  "CMakeLists.txt" "%buildpath%\" /F /Y

cmake %buildpath%\CMakeLists.txt -G"Visual Studio 15 2017" -DPACKAGE_DIR=%buildpath%
cmake --build %buildpath%\ --config Debug
PAUSE