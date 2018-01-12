#![crate_type="staticlib"]

#[no_mangle]
pub extern "C" fn rust_print(n: i32) {
    println!("{}. Printing from Rust", n);
}
