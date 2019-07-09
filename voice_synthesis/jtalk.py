# encoding=utf-8
import subprocess
from datetime import datetime

def voice_synthesis(input_text):
    """
    synthesis voice from input_text
    """
    open_jtalk = ['open_jtalk']
    mech = ['-x','/var/lib/mecab/dic/open-jtalk/naist-jdic']
    htsvoice = ['-m','/usr/share/hts-voice/mei/mei_normal.htsvoice']
    speed = ['-r','1.0']
    outwav = ['-ow','open_jtalk.raw']
    cmd = open_jtalk + mech + htsvoice + speed + outwav

    c = subprocess.Popen(cmd, stdin=subprocess.PIPE)
    c.stdin.write(input_text)
    c.stdin.close()
    c.wait()
    #aplay = ['aplay','-q','open_jtalk.raw']
    #wr = subprocess.Popen(aplay)


def say_datetime():
    now = datetime.now()
    text = '{}月{}日、{}時{}分{}秒'.format(
            now.month,
            now.day,
            now.hour,
            now.minute,
            now.second
    )
    voice_synthesis(text)


if __name__ == '__main__':
    say_datetime()
