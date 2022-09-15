#![feature(prelude_import)]

#![no_main]
#![no_std]
#![feature(allocator_api)]
#[prelude_import]

extern crate core;

//#[macro_use]
extern crate compiler_builtins;
use panic_halt as _;


#[doc(hidden)]
#[export_name = "main"]
pub unsafe extern "C" fn __cortex_m_rt_main_trampoline() {
    __cortex_m_rt_main()
}
fn __cortex_m_rt_main() -> ! {
    



    loop {

    }
}

