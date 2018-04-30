Instructions for PGE: https://github.com/Gamer2020/PokemonGameEditor/blob/master/Docs/settingup.md

Instructions for G3T here:

To enable Megas:

	1. Open the config.h files in the src folder. In line 9, change the keystone index to the item index of your liking. Player has to posses that item in order to mega evolve. Build file after the change.
	2. In G3T, open the 'pokemon editor.ini' file in the Customization folder.
 	3. Paste this:  
		FB=Mega Evolution FC=Wish Mega Evolution FD=Primal Reversion FF=Revert Megas
		in the evolution conditions section.
	
	For Regular Stone Mega Evolution:
		a. Open the item editor. Choose an item of your choice to be used as a mega stone. Set its Special Value 1/2 (or Held Item Effect) to 139 (in decimal) or 0x8B (in hex).
		b. In the extra section of item, put the index of the target Mega Pokemon (e.g index of Mega Scizor if want your item to behave like Scizorite). Note that if you're using Kurapika's Gen3Tools you'll have to insert the ID in hex.
		c. Now, open the pokemon editor, choose the mon you want to mega evolve. Then go to the evolution tab and add an entry there by setting 'Condition To Evolve' as 'Mega evolution' and 'Evolve To' to the Mega Species (e.g Mega Scizor in case of Scizor).

	For Wish Mega Evolution:
		a. Open the pokemon editor, choose the mon you want to mega evolve. Then go to the evolution tab and add an entry there by setting 'Condition To Evolve' as 'Wish Mega evolution' and 'Evolve To' to the Mega Species (e.g Mega Rayquaza in case of Rayquaza).
		b. Set the evolution parameter (The text field next to 'Nothing required' in G3T) to the move index of Dragon Ascent.

	For Primal Reversion:
		a. Open the item editor. Choose an item of your choice to be used as a Primal Orb. Set its Special Value 1/2 (or Held Item Effect) to 141 (in decimal) or 0x8D (in hex).
		b. In the extra section of item, put the index of the target Primal Pokemon (e.g index of Primal Groudon if want your item to behave like Red Orb). Note that if you're using Kurapika's Gen3Tools you'll have to insert the ID in hex.
		c. Set the Item Quality (the one used for oran berry to determine the HP to restore) to 1 for Alpha Reversion and 2 for Omega.
		d. Now, open the pokemon editor, choose the mon you want to undego Primal Reversion. Then go to the evolution tab and add an entry there by setting 'Condition To Evolve' as 'Primal Reversion' and 'Primal To' to the Mega Species (e.g Primal Groudon in case of Groudon). And the set the evolution parameter to 1 for Alpha or 2 for Omega here too.
	5. Make sure to set back the original species as Revert Megas evolution of mega species. (Unless you want your pokemon to stay as mega forever ) (e.g Scizor as Revert Megas evolution of Mega Scizor).
	6. To activate Megas in a battle, press the start button while choosing a move. You will hear a sound and the popped out trigger brightens and the evolution happens shortly after.

Form Changes and Configuration:

	Just open up the config.h file and change the lines accordingly.
