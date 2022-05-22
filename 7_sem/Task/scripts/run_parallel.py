#!/bin/bash
import os

create_all_commands = f'python3 all_comands.py > all_cmd.txt'
run_all_commands = f'cat all_cmd.txt | parallel --progress --jobs 6'

os.system(create_all_commands)
os.system(run_all_commands)
