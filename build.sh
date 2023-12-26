#!/bin/bash
rm -f mus2mid*.tar mus2mid*.tar.gz

MUS2MID_VERSION=$(grep "define MUS2MID_VERSION" src/main.c | cut -d'"' -f2)
cd src
tar -cvf ../mus2mid-$MUS2MID_VERSION.tar Makefile *.c *.h
cd ../
gzip mus2mid-$MUS2MID_VERSION.tar

echo "Available Now: mus2mid-$MUS2MID_VERSION.tar.gz"
