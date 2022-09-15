#![no_main]
#![no_std]


use panic_halt as _;

use stm32f4xx_hal as hal;
use crate::hal::{
    gpio::{PushPull, Output, gpiod},
    interrupt,
    pac::{self, Peripherals, TIM2, TIM5, TIM4},
    timer::{Event, CounterMs, DelayMs},
    prelude::*,
};



#[doc(hidden)]
#[export_name = "main"]
pub unsafe extern "C" fn __cortex_m_rt_main_trampoline() {
    __cortex_m_rt_main()
}
fn __cortex_m_rt_main() -> ! {
    



    loop {

    }
}

