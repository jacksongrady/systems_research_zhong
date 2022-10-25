target extended-remote :3333
load 
monitor arm semihosting enable 
set remotetimeout 100
show remotetimeout