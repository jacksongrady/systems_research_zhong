
tcl_input = "set_reg {"

with open('regs.txt', 'r') as file:
    data = file.read()

    lines = data.split('\n')

    for line in lines:
        if line != '' and line[0] == '(':
            arr = line.split(' ')
            tcl_input += f"{arr[1]} {arr[3]} "
tcl_input = tcl_input[:-1]
tcl_input += "}"
print(tcl_input)
