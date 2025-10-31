#![no_std]
#![no_main]

use esp_backtrace as _;
use esp_hal::{
    delay::Delay,
    gpio::{Io, Level, Output},
    prelude::*,
};
use log::info;

#[entry]
fn main() -> ! {
    let peripherals = esp_hal::init(esp_hal::Config::default());

    esp_println::logger::init_logger_from_env();

    let io = Io::new(peripherals.GPIO, peripherals.IO_MUX);
    let mut led = Output::new(io.pins.gpio5, Level::Low);

    let delay = Delay::new();

    info!("Ready");

    loop {
        led.set_high();
        info!("LED ON");
        delay.delay_millis(500);

        led.set_low();
        info!("LED OFF");
        delay.delay_millis(500);
    }
}
