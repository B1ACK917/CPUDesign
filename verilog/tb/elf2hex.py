import argparse
import os
from itertools import zip_longest


def grouper(iterable, n, fillvalue=None):
    args = [iter(iterable)] * n
    return zip_longest(*args, fillvalue=fillvalue)


def elf2hex(bit_width, infile, outfile):
    byte_width = bit_width // 8
    if not os.path.exists("temp"):
        os.mkdir("temp")
    objcp = os.popen(
        "riscv64-unknown-elf-objcopy {} -O binary temp/{}.obj".format(infile, os.path.basename(infile))
    )
    objcp.read()
    with open("temp/{}.obj".format(os.path.basename(infile)), "rb") as elf:
        with open(outfile, "w") as hex:
            for row in grouper(elf.read(), byte_width, fillvalue=0):
                hex_row = " ".join("{:02x}".format(b) for b in row)
                hex.write(hex_row + "\n")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--infile", type=str, help="input elf file")
    parser.add_argument("--outfile", type=str, help="output hex file")
    parser.add_argument("--bit-width", type=int, help="bits per row")
    args = parser.parse_args()

    assert args.bit_width % 8 == 0, "bits per row must be a multiply of 8!"
    elf2hex(args.bit_width, args.infile, args.outfile)


if __name__ == "__main__":
    main()
