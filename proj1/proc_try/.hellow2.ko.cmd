cmd_/home/chrisxue/OS-Lab/proj1/proc_try/hellow2.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000 -T ./scripts/module-common.lds --build-id  -o /home/chrisxue/OS-Lab/proj1/proc_try/hellow2.ko /home/chrisxue/OS-Lab/proj1/proc_try/hellow2.o /home/chrisxue/OS-Lab/proj1/proc_try/hellow2.mod.o ;  true
