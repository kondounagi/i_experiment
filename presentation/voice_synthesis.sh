#!/bin/sh
if [ -p /dev/stdin ]; then
    cat -
else
    echo $@
fi | open_jtalk \
-x /var/lib/mecab/dic/open-jtalk/naist-jdic \
-m /usr/share/hts-voice/mei/mei_normal.htsvoice \
-r 1.0 \
-z 1 \
-ow /dev/stdout
