#!/usr/bin/env python

import sys
import argparse

# Parse arguments
parser = argparse.ArgumentParser()
parser.add_argument('--romfile', metavar='file', 
			help='ROM to read', default='test.gba')
parser.add_argument('--oldini', metavar='file', 
			help='Old INI to change', default='roms.ini')
parser.add_argument('--newini', metavar='file', 
			help='New INI to use', default='test.ini')
args = parser.parse_args()

def getpointer(rom,offset):
	rom.seek(offset)
	byte=rom.read(3);
	rom.seek(offset+3);
	page=rom.read(1);
	p=page[0]-8;
	byte+=bytes(p.to_bytes(1,'little'));
	ps=''.join(format(x, '02x') for x in reversed(byte))
	return (ps.upper()+'\n')

#The variables named table below are actually a dictionary structure
table={}
table['AbilityNames']=0x1C0
table['AbilityDescriptionTable']=0x1C4
table['AttackNames']=0x148
table['AttackDescriptionTable']=0x1C3EFC
table['AttackData']=0x1CC
table['AttackAnimationTable']=0xA3A44
table['ContestMoveData']=0xD85F0
table['PokemonAttackTable']=0x06930C

table2={}
table2['NumberOfAttacks']=1024
table2['NumberOfAbilities']=256


with open(args.romfile, 'rb+') as rom:
	#Get ability name pointer
	wflag=0
	with open(args.oldini, 'r') as oldlines:
		fout=open(args.newini, 'w')
		for line in oldlines:
			if wflag is 1:
				for key in table.keys():
					if line.strip().startswith(str(key)):
						line=str(key)+'='+getpointer(rom,table[key])
				for key in table2.keys():
					if line.strip().startswith(str(key)):
						line=str(key)+'='+str(table2[key])+'\n'
			if line.strip().startswith('[BPEE]'):
				wflag=1
			if line.strip().startswith('[AXVF]'):
				wflag=0
			fout.write(line)
			if line.strip().startswith('PokedexTypeTable'):
				if wflag is 1:
					fout.write('MoveTableHack=True\n')
