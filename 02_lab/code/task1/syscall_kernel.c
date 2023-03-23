/*
надо запустить команду 
'strace -c wget kernel.org'
где флаг -c чтоб получить статистику использования сисколов
*/

/* the output is

URL transformed to HTTPS due to an HSTS policy
--2023-03-24 01:24:26--  https://kernel.org/
Resolving kernel.org (kernel.org)... 139.178.84.217, 2604:1380:4641:c500::1
Connecting to kernel.org (kernel.org)|139.178.84.217|:443... ^[[Aconnected.
HTTP request sent, awaiting response... 200 OK
Length: 16718 (16K) [text/html]
Saving to: ‘index.html.3’

index.html.3               100%[=====================================>]  16.33K  --.-KB/s    in 0.004s  

2023-03-24 01:24:27 (4.39 MB/s) - ‘index.html.3’ saved [16718/16718]

% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 20.22    0.001795          23        75           mmap
 11.90    0.001056          17        59           read
 10.95    0.000972          21        45        11 openat
 10.44    0.000927          28        32           write
  7.81    0.000693          17        40           close
  5.72    0.000508          24        21           mprotect
  4.25    0.000377           9        39           fstat
  3.32    0.000295           9        31           ioctl
  3.12    0.000277          16        17         7 stat
  2.53    0.000225           9        25           getpgrp
  1.88    0.000167         167         1           ftruncate
  1.79    0.000159          26         6         3 connect
  1.71    0.000152           8        17           rt_sigaction
  1.62    0.000144         144         1           utime
  1.45    0.000129           5        24           getpid
  1.39    0.000123           5        23           futex
  1.14    0.000101          25         4           munmap
  1.09    0.000097           9        10           setitimer
  0.98    0.000087          10         8           pread64
  0.92    0.000082          27         3           select
  0.90    0.000080          13         6           rt_sigprocmask
  0.78    0.000069           9         7           socket
  0.55    0.000049           9         5           brk
  0.53    0.000047           9         5           getuid
  0.39    0.000035          35         1           sendmmsg
  0.37    0.000033           8         4           lseek
  0.30    0.000027           9         3           poll
  0.27    0.000024           8         3           recvmsg
  0.21    0.000019          19         1           flock
  0.17    0.000015          15         1           sendto
  0.17    0.000015          15         1           prlimit64
  0.11    0.000010          10         1           getgroups
  0.11    0.000010          10         1           statfs
  0.10    0.000009           4         2           recvfrom
  0.09    0.000008           4         2           getsockname
  0.09    0.000008           8         1           setsockopt
  0.09    0.000008           8         1           sysinfo
  0.09    0.000008           4         2         1 arch_prctl
  0.09    0.000008           8         1           set_tid_address
  0.09    0.000008           8         1           set_robust_list
  0.09    0.000008           8         1           getrandom
  0.08    0.000007           7         1           bind
  0.07    0.000006           6         1           uname
  0.00    0.000000           0         1         1 access
  0.00    0.000000           0         1           execve
------ ----------- ----------- --------- --------- ----------------
100.00    0.008877                   535        23 total

*/