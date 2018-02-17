#!/bin/bash

cppcheck --enable=all --inconclusive --std=posix ../model 2> check.log
