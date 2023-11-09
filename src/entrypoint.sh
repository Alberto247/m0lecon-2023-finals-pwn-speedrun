#!/bin/bash

INTERNAL_FLAG="${FLAG:-ptm{fakeflag\}}"

echo $INTERNAL_FLAG > /flag.txt

socat -T60 "TCP-LISTEN:4444,reuseaddr,fork" "EXEC:/chall,pty,raw,stderr,echo=0"