# -*- coding: utf-8 -*-

import numpy as np

bateria = 0.5
radio = 75.0
ch = 0
ch_count = 0
num_nodes = 100

area = 100

with open('nodes.txt', 'w') as file:
    for i in range(1, num_nodes+1):
        x = round(np.random.uniform(0, area), 2)
        y = round(np.random.uniform(0, area), 2)

        file.write( "{}/{}/{}/{}\n".format(i, x, y, 0) )
