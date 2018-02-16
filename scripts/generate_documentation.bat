
cd ..
call env.bat 8
cd doc

echo Removing directories...
rmdir html /S /Q 

set OUTPUT=..\scripts\generate_documentation.log

echo Generating documentation...
doxygen.exe lang.doxygen 2> %OUTPUT%

cd ../scripts
