@echo off
echo 🚀 Building C++ Project...

if not exist build mkdir build

cd build
cmake ..
cmake --build . --config Release

echo ✅ Build completed successfully!
echo 📦 Executable location: %cd%\Release\
pause