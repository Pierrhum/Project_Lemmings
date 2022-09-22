# -*- coding: utf-8 -*-
"""
Created on Tue Sep 20 21:35:56 2022

@author: Geegaz and Arc
"""

from PIL import Image
from pathlib import Path
import sys
import numpy as np

if(len(sys.argv) >= 2):
    # https://stackoverflow.com/a/54244301 -------------------------
    def closest_index(color):
        np_colors = np.array(COLORS)
        np_color = np.array(color)
        distances = np.sqrt(np.sum((np_colors-np_color)**2,axis=1))
        return np.where(distances==np.amin(distances))[0][0]
    # -----------------------------------------------------------
    COLORS = [
        (12,12,12),
        (0,55,218),
        (19,161,14),
        (58,150,221),
        (197,15,31),
        (136,23,152),
        (193,156,0),
        (204,204,204),
        (118,118,118),
        (59,120,255),
        (22,198,12),
        (97,214,214),
        (231,72,86),
        (180,0,158),
        (249,241,165),
        (242,242,242)
    ]
    colors = {
        (118, 118, 118, 255): "8", (12, 12, 12, 255) : "0",
        (0, 55, 218, 255): "1", (59, 120, 255, 255):"9",
        (19, 161, 14, 255):"2", (22, 198, 12, 255):"10",
        (58, 150, 221, 255):"3", (97, 214, 214, 255):"11",
        (197, 15, 31, 255):"4", (231, 72, 86, 255):"12",
        (136, 23, 152, 255):"5", (180, 0, 158, 255):"13",
        (193, 156, 0, 255):"6", (249, 241, 165, 255):"14",
        (204, 204, 204, 255):"7", (242, 242, 242, 255):"15",
        (255, 255, 255, 0):"-1",
        }
    for i in range(1,len(sys.argv)):
        filename = sys.argv[i]
        print("Converting", filename,"...")
        try:
            img = Image.open(filename, "r")
            txt = open(Path(filename).stem + ".txt", "w")
    
            data = img.getdata()
    
            txt.write("%s %s\n---\n" % img.size)
    
            pos: int = 0
            for pixel in data:
                rgb = (pixel[0], pixel[1], pixel[2])
                a = pixel[3]
    
                if a < 128:
                    txt.write("%s " % -1)
                else:
                    txt.write("%s " % closest_index(rgb))
                pos += 1
    
                if pos >= img.size[0]:
                    txt.write("\n")
                    pos = 0
            
            txt.close()
            img.close()
    
        except Exception as ex:
            print(ex)
        print("Successfully created "+(Path(filename).stem + ".txt"))
        
else:
    print("Usage: ", sys.argv[0], "<png_filename>")