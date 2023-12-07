"""
Convert CDXXXXX.jpg into CDXXXXX_buffer.txt
"""
import os
from glob import glob
from sys import platform
assert platform == "darwin" # make sure we are macOS


def main():
    fdir = '/Volumes/Untitled/'
    for fn in sorted(glob(f'{fdir}/*.jpg')):
        print(os.path.basename(fn))
        os.system(f'mv {fn} {fdir}/{os.path.basename(fn)[:-4]}_buffer.txt')

if __name__ == '__main__':
    main()
