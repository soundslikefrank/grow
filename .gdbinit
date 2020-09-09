file build/stm32f3-base.out 
target remote localhost:3333
load
set remote hardware-breakpoint-limit 6
set remote hardware-watchpoint-limit 4
