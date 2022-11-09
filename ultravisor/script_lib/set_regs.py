import sys

prog_no = sys.argv[1]

tcl_input = "set_reg {"

with open(f'../register_data/program_{prog_no}_registers.txt', 'r', errors='ignore') as file:
    data = file.read()

    lines = data.split('\n')

    for line in lines:
        if line != '' and line[0] == '(':
            arr = line.split(' ')
            tcl_input += f"{arr[1]} {arr[3]} "
tcl_input = tcl_input[:-1]
tcl_input += "}"
print(tcl_input)
