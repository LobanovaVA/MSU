#!/bin/bash

def to_string(mode, c, gamma, mu):
    return f'{mode} {c} {gamma} {mu}'

def to_name(mode, c, gamma, mu):
    return f'{mode}_{c}_{gamma}_{mu}.txt'

#mode_set = [3, 4] 
#mode_set = [5, 6] 
mode_set = [7] 

C_set = [1, 10, 100]
mu_set = [.1, .01, .001]

#comand = "python3 task_2_table.py ../../build-Task-Desktop-Debug/Task "
#comand = "python3 task_3_table.py ../../build-Task-Desktop-Debug/Task "
comand = "python3 task_4_table.py ../../build-Task-Desktop-Debug/Task "
comands = []

for mode in mode_set:
    for mu in mu_set:
        for C in C_set:
            comands.append(comand + to_string(mode, C, 1, mu) + " > " + to_name(mode, C, 1, mu))
        comands.append(comand + to_string(mode, 1, 1.4, mu) + " > " + to_name(mode, 1, 1.4, mu))

for item in comands:
  print(item)
