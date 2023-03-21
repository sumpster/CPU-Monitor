#!/bin/bash

clear
qmake -qt=qt5 && make -j 16 && ./monitor
