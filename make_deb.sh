#!/bin/sh
tar -xvf opcuamappings-${VERSION}.tar.gz
cd opcuamappings-${VERSION}
dh_make -y -l -c lgpl3 -e rykovanov.as@gmail.com -f ../opcuamappings-${VERSION}.tar.gz
dpkg-buildpackage -rfakeroot -nc -F

