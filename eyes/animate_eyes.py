#!/usr/bin/env python
"""
Displays an animated eye.
"""

import os.path
from demo_opts import get_device
from PIL import Image, ImageSequence
from luma.core.sprite_system import framerate_regulator


def main():
    regulator = framerate_regulator(fps=10)
    img_path = os.path.abspath(os.path.join(os.path.dirname(__file__),
        'images', 'zoom1.gif'))
    banana = Image.open(img_path)
    size = device.size
    posn = ((device.width - size[0]) // 2, device.height - size[1])

    while True:
        for frame in ImageSequence.Iterator(banana):
            with regulator:
                background = Image.new("RGB", device.size, "white")
                background.paste(frame.resize(size, resample=Image.LANCZOS), posn)
                device.display(background.convert(device.mode))


if __name__ == "__main__":
    try:
        device = get_device()
        main()
    except KeyboardInterrupt:
        pass
