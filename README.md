# My Extra Notes

1. Workflow
  1.1 Run `./configure` in /os161/ - this sets where the /root dir is
  1.2 Go to /os161/kern/conf/ and the run something like: `./config ASST0`. This sets the kernel
  1.3 Go to `/os161/kern/compile/<ASST0>` and run `bmake depends; bmake; bmake install`
  1.4 Go to `/os161/root/` and run `sys161 kernel` to run the kernel 