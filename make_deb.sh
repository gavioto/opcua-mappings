#!/bin/sh
make dist
tar -xvf opcuamappings-0.1.2.tar.gz
cd opcuamappings-0.1.2
dh_make -y -l -c lgpl3 -e rykovanov.as@gmail.com -f ../opcuamappings-0.1.2.tar.gz
#cp debian -rvf opcuamappings-0.1.2
#dpkg-source --commit
dpkg-buildpackage -rfakeroot

