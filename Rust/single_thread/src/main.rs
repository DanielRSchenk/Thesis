use std::{env, io};
use rand::Rng;

fn main() {
    let args: Vec<String> = env::args().collect();
    let n = args[1].parse::<i64>().unwrap();
    let threads = &args[2];

    pi(n);
}

fn pi(n: i64) {
    let mut pi_4 = 0.0;
    let mut sign = true;
    let mut i: i64;

    for i in (1..n).step_by(2) {
        if sign {
            pi_4 += 1.0 / (i as f64);
        } else {
            pi_4 -= 1.0 / (i as f64);
        }

        sign = !sign; // Flip the sign
    }
    let pi = pi_4 * 4.0;
    println!("\nEstimated value of Pi: {:.51}", pi);
}