#!/bin/sh

echo $1 | \
open_jtalk \
-x /var/lib/mecab/dic/open-jtalk/naist-jdic \
-m /usr/share/hts-voice/mei/mei_normal.htsvoice \
-r 1.0 \
-ow open_jtalk.raw
