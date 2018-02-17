#!/bin/bash

cd ..
cd doc

echo Removing directories...
rm html

export OUTPUT=../scripts/generate_documentation.log

echo Generating documentation...
doxygen lang.doxygen 2> ${OUTPUT}

cd ../scripts
