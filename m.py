import os

os.system("python scripts/make.py")

#with open('test.gba', 'rb+') as  rom:
	#rom.seek(0x6D140)
	#evo=int.from_bytes(rom.read(4), 'little')-0x8000000
	#rom.seek(evo+40*0x42B)
	#rom.write(b'\xFA\x00\x00\x00\x2E\x04')

	#rom.seek(evo+40*0x355)
	#rom.write(b'\x00\x00\x00\x00\x00\x00')
	#rom.seek(evo+40*0x34c)
	#rom.write(b'\x00\x00\x00\x00\x00\x00')
	#rom.seek(evo+40*0x34d)
	#rom.write(b'\x00\x00\x00\x00\x00\x00')

	#rom.seek(evo+40*0x42C)
	#rom.write(b'\xFA\x00\x00\x00\x2E\x04')
'''
def clear(_from ,to):
    rom.seek(_from)
    rom.write(b'\xFF'*(to-_from+1))

with open('test.gba', 'rb+') as rom:
    clear(0x1516000, 0x1517e80)
'''