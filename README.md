# WAIOS
This is a simple OS which support ARM v8 architecutre. It's goal is to help to understanding the Moder OS like Linux.

# Build
1. build the image.
```bash
$ ./build.sh
```
2. run image on the qemu
```bash
$ qemu-system-aarch64 -M virt -kernel Image -nographic -cpu cortex-a57 -serial mon:stdio
```
![image](https://user-images.githubusercontent.com/13994399/201265788-eefc452e-6107-4ac4-bc5f-4d20efaded44.png)

# Reading material
1. [Bare metal program](https://www.bhral.com/post/practice-waios-%EC%A0%9C%EC%9E%91-1)
2. [Simple UART driver](https://www.bhral.com/post/practice-waios-%EC%A0%9C%EC%9E%91-2)
3. [Initialize Page table](https://www.bhral.com/post/practice-waios-%EC%A0%9C%EC%9E%91-3)
4. [Implement Printk function](https://www.bhral.com/post/practice-waios-%EC%A0%9C%EC%9E%91-4)
5. [Implement dump_stack function](https://www.bhral.com/post/waios-dump_stack-%ED%95%A8%EC%88%98-%EA%B5%AC%ED%98%84)
