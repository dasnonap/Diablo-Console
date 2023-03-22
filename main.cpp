#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

void Menu_ui();//Start menu
void Load_game();//Load game
void New_game_diff();//New game
class Enemy;
class Character {//Class Character parent class initializing all of the variables for the Player controled classes
protected:
	string name;
	int level;
	int HP;
	int strength;
	int intelligence;
public:
	Character() {
		name = "";
		level = 0;
		HP = 0;
		strength = 0;
		intelligence = 0;
	}
	void set_name(string a) {
		name = a;
	}
	void set_level(int a) {
		level = a;
	}
	void set_HP(int a) {
		HP = a;
	}
	void set_strength(int a) {
		strength = a;
	}
	void set_intel(int a) {
		intelligence = a;
	}
	string get_name() {
		return name;
	}
	int get_level() {
		return level;
	}
	int get_strength() {
		return strength;
	}
	int get_intel() {
		return intelligence;
	}
	virtual void attack(Enemy &a) {}//Virtual attack used in inherited classes , because the have different types of attacks 
	virtual void set_rage(int a) {}
	virtual void set_mana(int a) {}
	virtual void set_agility(int a) {}
	virtual bool checkDeathp() {//To check if the hero is death
		if (HP <= 0)
			return true;
		else
			return false;
	}
	virtual void checkLVL(int p) {//To check if the hero is ready to level up
		level += p;
		if (level % 100 == 0) {

			LVL_UP_STR();
		}
	}
	void LVL_UP_STR() {//Leveling up
		int indicators, str_old, intel_old;
		double first_take_str, first_take_intel;
		str_old = strength;
		intel_old = intelligence;

		HP += 10;
		indicators = strength + intelligence;

		first_take_str = (double)strength / indicators;
		first_take_intel = (double)intelligence / indicators;
		this->set_strength((first_take_str * 5) + str_old);
		this->set_intel((first_take_intel * 5) + intel_old);
	}
	virtual void print_a() {//Printing the stats of the hero
		cout << "HP :" << HP << endl;
		cout << "Strength :" << strength << endl;
		cout << "Intelligence :" << intelligence << endl;
		if (this->get_rage() != -1)
			cout << "Rage : " << this->get_rage() << endl;
		else if (this->get_mana() != -1)
			cout << "Mana : " << this->get_mana() << endl;
		else if (this->get_agility() != -1)
			cout << "Agility :" << this->get_agility() << endl;
	}
	virtual int get_HP() {
		return 0;
	}
	virtual int get_rage() {
		return -1;
	}
	virtual int get_mana() {
		return -1;
	}
	virtual int get_agility() {
		return -1;
	}
};
class Enemy {//Class Enemy parent class initializing all of the variables for the different types of enemies
protected:
	string name;
	int HP;
	int strength;
	int intelligence;
	int pt;
public:
	Enemy() {
		name = "";
		HP = 0;
		strength = 0;
		intelligence = 0;
		pt = 0;
	}
	void set_name_enemy(string a) {
		name = a;
	}
	void set_HP_enemy(int a) {
		HP = a;
	}
	void set_strength_enemy(int a) {
		strength = a;
	}
	void set_intel_enemy(int a) {
		intelligence = a;
	}
	string get_name_enemy() {
		return name;
	}
	int get_HP_enemy() {
		return HP;
	}
	int get_strength_enemy() {
		return strength;
	}
	int get_intel_enemy() {
		return intelligence;
	}
	virtual void attack_s(Character &a, int ch) {}
	virtual void attack(Character &a) {}
	virtual int get_pt() {
		return 0;
	}
	virtual bool checkDeathe() {
		if (HP <= 0)
			return true;
		else
			return false;
	}
};
class Barbarian : public Character {

	int rage;
public:
	Barbarian() {
		name = "Barbarian";
		level = 0;
		HP = 100;
		strength = 10;
		intelligence = 3;
		rage = 0;
	}
	virtual void set_rage(int a) {
		rage = a;
	}
	virtual int get_rage() {
		return rage;
	}
	virtual int get_HP() {
		return HP;
	}
	void set_HP(int a) {
		HP = a;
	}
	int get_strength() {
		return strength;
	}
	void set_strength(int a) {
		strength = a;
	}
	int get_intel() {
		return intelligence;
	}
	void set_intel(int a) {
		intelligence = a;
	}
	virtual bool checkDeathp() {
		if (HP <= 0)
			return true;
		else
			return false;
	}
	virtual void attack(Enemy  &a) {//Attack method for the Barbarian Class
		int a1 = 0, a2 = 0, a3 = 0;
		a1 = a.get_HP_enemy();
		a2 = a.get_strength_enemy();
		a3 = a.get_intel_enemy();

		cout << "The barbarian hits" << endl;
		a1 = a1 - (strength + (0.2 * intelligence));
		a.set_HP_enemy(a1);
	}
};
class Sorcerer : public Character {
	int mana;
public:
	Sorcerer() {
		name = "Sorcerer";
		level = 0;
		HP = 70;
		strength = 3;
		intelligence = 12;
		mana = 100;
	}
	virtual void set_mana(int a) {
		mana = a;
	}
	virtual int get_mana() {
		return mana;
	}
	void set_HP(int a) {
		HP = a;
	}
	virtual int get_HP() {
		return HP;
	}
	void set_strength(int a) {
		strength = a;
	}
	int get_strength() {
		return strength;
	}
	void set_intel(int a) {
		intelligence = a;
	}
	int get_intel() {
		return intelligence;
	}
	virtual bool checkDeathp() {
		if (HP <= 0)
			return true;
		else
			return false;
	}
	virtual void attack(Enemy &a) {//Attack method of the Sorcerer class
		int a1 = 0, a2 = 0, a3 = 0, cur = mana;

		a1 = a.get_HP_enemy();
		a2 = a.get_strength_enemy();
		a3 = a.get_intel_enemy();

		cout << "The Sorcerer hits " << endl;
		a1 = a1 - (0.5 + ((cur / mana) * 0.75)) * intelligence;

		if (a1 > 0)
			cur = cur - (cur / 10);
		else
			cur = mana;

		a.set_HP_enemy(a1);
	}
};
class Bounty_Hunter : public Character {
	int agility;
public:
	Bounty_Hunter() {
		name = "Bounty Hunter";
		level = 0;
		HP = 80;
		strength = 9;
		intelligence = 6;
		agility = 10;
	}
	void set_agility(int a) {
		agility = a;
	}
	virtual int get_agility() {
		return agility;
	}
	void set_HP(int a) {
		HP = a;
	}
	virtual int get_HP() {
		return HP;
	}
	void set_str(int a) {
		strength = a;
	}
	int get_str() {
		return strength;
	}
	void set_intel(int a) {
		intelligence = a;
	}
	int get_intel() {
		return intelligence;
	}
	virtual bool checkDeathp() {
		if (HP <= 0)
			return true;
		else
			return false;
	}
	int br = 1;
	virtual void attack(Enemy &a) {//Attack method of the Bounty Hunter class
		int a1 = 0, a2 = 0, a3 = 0;

		a1 = a.get_HP_enemy();
		a2 = a.get_strength_enemy();
		a3 = a.get_intel_enemy();
		if (br % 3 == 0) {
			cout << "Bounty hunter special attack" << endl;
			a1 = a1 - (agility + (0.4 * intelligence) + (0.6 * strength));
			br++;
		}
		else {
			cout << "Bounty hunter normal attack" << endl;
			a1 = a1 - (0.8 * agility);
			br++;
		}
		a.set_HP_enemy(a1);
	}
};
class Sceleton_Heretic : public Enemy {//One class for two different types of enemies
public:
	Sceleton_Heretic() {}
	Sceleton_Heretic(int ch) {//Selecting what enemy do we want
		switch (ch) {
		case 1: {
			name = "Sceleton";
			HP = 32;
			strength = 3;
			intelligence = 0;
			pt = 50;
		}break;
		case 2: {
			name = "Heretic";
			HP = 20;
			strength = 1;
			intelligence = 4;
			pt = 50;
		}break;
		}
	}
	virtual int get_pt() {
		return this->pt;
	}
	virtual bool checkDeathe() {
		if (HP <= 0)
			return true;
		else
			return false;
	}
	virtual void attack_s(Character &a, int ch) {//Selecting the different type of battle for the Sceleton and the Heretic
		int a1 = 0, a2 = 0, a3 = 0, a4 = 0;
		a1 = a.get_HP();
		a2 = a.get_strength();
		a3 = a.get_intel();

		switch (ch) {
		case 1: {
			cout << "The sceleton hits " << endl;
			a1 = a1 - (this->strength + (a3 / 10));
			a.set_HP(a1);
		}break;
		case 2: {
			cout << "The heretic hits " << endl;
			vector <int> stats;
			stats.push_back(a1);
			stats.push_back(a2);
			stats.push_back(a3);
			if (a.get_rage() >= 0) {
				stats.push_back(a.get_rage());
			}

			sort(stats.begin(), stats.end());
			a1 = a1 - (stats.front() + this->intelligence);
			a.set_HP(a1);
		}
		}
	}
};
class Necromancer : public Enemy {
private:
	vector <Sceleton_Heretic> sc;
public:
	Necromancer() {
		name = "Necromancer";
		HP = 65;
		strength = 2;
		intelligence = 7;
		pt = 50;
	}
	void set_hp(int a) {
		HP = a;
	}
	int get_hp() {
		return HP;
	}
	int get_str() {
		return strength;
	}
	int get_intel() {
		return intelligence;
	}
	virtual int get_pt() {
		return pt;
	}
	virtual bool checkDeathe() {
		if (HP <= 0)
			return true;
		else
			return false;
	}
	int cr = 1;
	virtual void attack(Character &c) {//Attack method for the Necromancer, where on the first and on every third time he hits it spawns a Sceleton 
		int c1 = 0, s1 = 0, c2 = 0;
		Sceleton_Heretic s(1);
		c1 = c.get_HP();
		cout << cr << endl;
		if (cr == 1 || cr % 3 == 0) {

			cout << "The Necromancer spawned an Sceleton" << endl;
			sc.push_back(s);
		}
		if (sc.empty()) {
			cout << "The Necromancer hits" << endl;
			c1 = c1 - ((0 / 10) + intelligence);
			c.set_HP(c1);
		}
		else {
			while (sc.front().get_HP_enemy() > 0) {//So here the Hero fights with the spawned Sceleton until the vector is empty and then goes and fights the necromancer

				cout << "The damage is taken by the spawned Sceleton" << endl;
				c.attack(sc.front());
				cout << "The sceletons HP is : " << sc.front().get_HP_enemy() << endl;
				cout << "The Necromancer hits" << endl;
				c1 = c1 - ((sc.front().get_HP_enemy() / 10) + intelligence);
				c.set_HP(c1);

			}
			sc.erase(sc.begin());
		}
		cout << "size of vector " << sc.size() << endl;
		cout << "HP of player " << c.get_HP() << endl;
		cr++;
	}
};
class Diablo : public Sceleton_Heretic {

public:
	Diablo() {
		name = "Diablo";
		HP = 350;
		strength = 8;
		intelligence = 4;
		pt = 300;
	}
	virtual bool checkDeathe() {
		if (HP <= 0)
			return true;
		else
			return false;
	}
	virtual void attack(Character &c) {//The diablo once attacks as a Sceleton and once as a Heretic
		cout << "The Diablo attacks as a Sceleton !" << endl;
		this->attack_s(c, 1);
		cout << c.get_HP() << endl;
		cout << "The Diablo attacks as a Necromancer !" << endl;
		this->attack_s(c, 2);
		cout << c.get_HP() << endl;

	}
	virtual int get_pt() {
		return this->pt;
	}
	virtual int get_HP_enemy() {
		return this->HP;
	}
	int get_str() {
		return this->strength;
	}
	int get_intel() {
		return this->intelligence;
	}
};
class MapandM {//Class MapandM initializes the playground , the player spawn , the enemy spawn  and the movement of the player
protected:
	int y;
	int x;
	int mp[100][100];
	int px;
	int py;
public:
	MapandM() {
		x = 0;
		y = 0;
		px = 9;
		py = 0;

	}
	void Map_set(int xx, int yy, int xp, int yp) {//Sets the playground 
		x = xx;
		y = yy;
		mp[x][y];
		px = xp;
		py = yp;
		for (int i = 0; i <= y; i++) {
			for (int j = 0; j <= x; j++) {
				mp[i][j] = 0;
			}
		}
		for (int i = 0; i <= y; i++) {
			for (int j = 0; j <= x; j++) {
				if (i == 0 || j == 0) {
					mp[i][j] = 6;//Border of the map
				}
				if (i == y || j == x) {
					mp[i][j] = 6;//Border of the map
				}
			}
		}
		for (int i = 0; i <= y; i++) {
			for (int j = 0; j <= x; j++) {
				if (i == py && j == px) {
					mp[i][j] = 1;// Player spawn 

				}
			}
		}
	}
	void ene_set(int br) {// Spawns the enemies 
		
		srand(time(NULL));
		switch (br) {
		case 1: {//Easy difficulty 
			int ex = 2, ey = 2, br = 25, i;
			//Sceletons
			for (int k = 0; k < 10; k++) {
				i = rand() % 2 + 0;
				this->Spw_En((ex + k) - i, (ey + k) + i, 1);
				br--;
			}
			//Heretics
			ex = 3;
			ey = 6;
			for (int k = 0; k <= 5; k++) {
				i = rand() % 2 + 0;
				this->Spw_En((ex + k) - i, (ey + k) + i, 2);
				br--;
			}
			//Necromancer
			ex = 2;
			ey = 11;
			for (int k = 0; k <= 7; k++) {
				i = rand() % 2 + 0;
				this->Spw_En((ex + k) - i, (ey + k) + i, 3);
				br--;
			}
			// Diablo
			ex = 4;
			ey = 19;
			this->Spw_En(ex, ey, 4);
		}break;
		case 2: {// Medium Difficulty
			int ex = 2, ey = 2, br = 50, i;
			//sceletons
			srand(time(NULL));
			for (int k = 0; k < 20; k++) {
				i = rand() % 2 + 0;
				this->Spw_En((ex + k) - i, (ey + k) + i, 1);
				br--;
			}
			//heretics
			ex = 2;
			ey = 6;
			for (int k = 0; k <= 15; k++) {
				i = rand() % 2 + 0;
				this->Spw_En((ex + k) - i, (ey + k) + i, 2);
				br--;
			}
			//necromancer
			ex = 4;
			ey = 15;
			for (int k = 0; k <= 12; k++) {
				i = rand() % 2 + 0;
				this->Spw_En((ex + k) - i, (ey + k) + i, 3);
				br--;
			}
			//diablo
			ex = 10;
			ey = 34;
			this->Spw_En(ex, ey, 4);
		}break;
		case 3: {//Hard difficulty 
			
			int ex = 2, ey = 5, br = 80, i;
			//Sceletons
			for (int k = 0; k <= 20; k++) {
				i = rand() % 2 + 0;
				this->Spw_En((ex + k) + i, (ey + k) - (i*4), 1);
				br--;
			}
			//Sceletons
			ex = 20, ey = 2;
			for (int k = 0; k <= 20; k++) {
				i = rand() % 2 + 0;
				this->Spw_En((ex + k) + i, (ey + k) + (i * 4), 1);
				br--;
			}
			ex = 2;
			ey = 22;
			for (int k = 0; k <= 22; k++) {
				i = rand() % 2 + 0;
				this->Spw_En((ex + k) + i, (ey + k) - (i * 6), 2);
				br--;
			}
			ex = 11;
			ey = 45;
			for (int k = 0; k <= 15; k++) {
				i = rand() % 2 + 0;
				this->Spw_En((ex + k) + i, (ey + k) - (i * 6), 3);
				br--;
			}
			ex = 25;
			ey = 64;
			this->Spw_En(ex, ey, 4);
		}break;
		}
	}
	int player_mov(int pxx, int pyy) {//Player moving 
		int y_o = 0;
		int x_o = 0;
		for (int i = 0; i <= y; i++) {
			for (int j = 0; j <= x; j++) {
				if (i == py && j == px) {
					mp[i][j] = 0;
					y_o = i;
					x_o = j;
				}
			}
		}
		cout << "old y : " << y_o << endl;
		cout << "old x : " << x_o << endl;
		px = pxx;
		py = pyy;
		for (int i = 0; i <= y; i++) {
			for (int j = 0; j <= x; j++) {
				if (i == py && j == px) {
					if (mp[i][j] == 2) {
						return 2;
					}
					else if (mp[i][j] == 3) {
						return 3;
					}
					else if (mp[i][j] == 4) {
						return 4;
					}
					else if (mp[i][j] == 5) {
						return 5;
					}
					else if (mp[i][j] == 6) {// If you are about to exit the map it returns the player to his old position
						cout << "You are about to exit the map !!!" << endl;
						py = y_o;
						px = x_o;
						mp[py][px] = 1;

					}
					else {
						mp[i][j] = 1;
						py = i;
						px = j;
					}
				}
			}
		}
		cout << endl;
	}
	void Spw_En(int x, int y, int sp) {// Spawn Different types of enemies
		switch (sp) {
		case 1: {//spawn sceleton
			for (int i = 0; i <= this->y; i++) {
				for (int j = 0; j <= this->x; j++) {
					if (i == y && j == x) {
						this->mp[i][j] = 2;
					}
				}
			}
		}break;
		case 2: {//spawn Heretic
			for (int i = 0; i <= this->y; i++) {
				for (int j = 0; j <= this->x; j++) {
					if (i == y && j == x) {
						this->mp[i][j] = 3;
					}
				}
			}
		}break;
		case 3: {//spawn Necromancers
			for (int i = 0; i <= this->y; i++) {
				for (int j = 0; j <= this->x; j++) {
					if (i == y && j == x) {
						this->mp[i][j] = 4;
					}
				}
			}
		}break;
		case 4: {//spawn Diablos
			for (int i = 0; i <= this->y; i++) {
				for (int j = 0; j <= this->x; j++) {
					if (i == y && j == x) {
						mp[i][j] = 5;
					}
				}
			}
		}break;
		case 5: {//spawn player
			for (int i = 0; i <= this->y; i++) {
				for (int j = 0; j <= this->x; j++) {
					if (i == y && j == x) {
						mp[i][j] = 1;
					}
				}
			}
		}break;
		}
	}
	int get_px() {
		return px;
	}
	int get_py() {
		return py;
	}
	void out_of_Bounds() {
		if (px > x) {
			throw  "Out of bounds!!! Press 3 to return to your last position\n";
		}
		else if (px < 0) {
			throw  "Out of bounds!!!\n Press 4 to return to your last position\n";
		}
		else if (py > y) {
			throw  "Out of bounds!!!\n Press 1 to return to your last position\n";
		}
		else if (py < 0) {
			throw  "Out of bounds!!!\n Press 2 to return to your last position\n";
		}
	}
	int check_box() {//Checks what is the next step for the player and returns it
		int en;
		for (int i = 0; i <= this->y; i++) {
			for (int j = 0; j <= this->x; j++) {
				if (i == py && j == px) {
					if (mp[i][j] == 2) {
						cout << "Sceletons" << endl;
						en = 2;
						return en;
					}
					else if (mp[i][j] == 3) {
						cout << "Heretics" << endl;
						en = 3;
						return en;
					}
					else if (mp[i][j] == 4) {
						cout << "Necromancers" << endl;
						en = 4;
						return en;
					}
					else if (mp[i][j] == 5) {
						cout << "Diablo" << endl;
						en = 5;
						return en;
					}
					else {
						cout << "Nothing" << endl;
						return 0;
					}
				}
			}
		}
	}
	void printMap() {
		for (int i = 0; i <= y; i++) {
			for (int j = 0; j <= x; j++) {
				cout << mp[i][j];
			}
			cout << endl;
		}
	}
};
class Play : public MapandM {// Class Play where the characters fight, where it saves into a file, reads from a file
protected:
	int mpx;
	int mpy;
public:
	void attack(int en, Character *p) {
		int rage = -1;
		int str = 0;
		switch (en) {
		case 2: {
			Enemy *sc = new Sceleton_Heretic(1);
			if (p->get_rage() >= 0) {
				rage = p->get_rage();
				str = p->get_strength();
				rage = rage / 5;
				str = str + rage;
				p->set_strength(str);
				rage = 0;
			}
			do {
				if (rage >= 0) {
					p->attack(*sc);
					rage += 2;
					cout << "HP of the enemy : " << sc->get_HP_enemy() << endl;
					if (sc->checkDeathe() == true) {
						cout << "Sceleton is dead" << endl;
						p->checkLVL(sc->get_pt());
						break;
					}
					else if (p->checkDeathp() == true) {
						cout << "Player is dead" << endl;
						cout << "GAME OVER !!!" << " You can start over " << endl;
						delete p;
						Menu_ui();
						break;
					}
					else {
						sc->attack_s(*p, 1);
						rage = rage + 3;
						cout << "HP of the player : " << p->get_HP() << endl;
					}
				}
				if (p->get_mana() >= 100) {
					p->attack(*sc);
					cout << "HP of the enemy : " << sc->get_HP_enemy() << endl;
					if (sc->checkDeathe() == true) {
						cout << "Sceleton is dead" << endl;
						p->checkLVL(sc->get_pt());
						break;
					}
					else if (p->checkDeathp() == true) {
						cout << "Player is dead" << endl;
						cout << "GAME OVER !!!" << " You can start over " << endl;
						delete p;
						Menu_ui();
					}
					else {
						sc->attack_s(*p, 1);
						cout << "HP of the player : " << p->get_HP() << endl;
					}
				}
				if (p->get_agility() >= 10) {
					p->attack(*sc);
					cout << "HP of the enemy : " << sc->get_HP_enemy() << endl;
					if (sc->checkDeathe() == true) {
						cout << "Sceleton is dead" << endl;
						p->checkLVL(sc->get_pt());
						break;
					}
					else if (p->checkDeathp() == true) {
						cout << "Player is dead" << endl;
						cout << "GAME OVER !!!" << " You can start over " << endl;
						delete p;
						Menu_ui();
					}
					else {
						sc->attack_s(*p, 1);
						rage = rage + 3;
						cout << "HP of the player : " << p->get_HP() << endl;
					}
				}
			} while (sc->checkDeathe() != true || p->checkDeathp() != true);
			p->set_rage(rage);
		}break;
		case 3: {
			Enemy *sc = new Sceleton_Heretic(2);
			if (p->get_rage() >= 0) {
				rage = p->get_rage();
				str = p->get_strength();
				rage = rage / 5;
				str = str + rage;
				p->set_strength(str);
				rage = 0;
			}
			do {
				if (rage >= 0) {
					p->attack(*sc);
					rage += 2;
					cout << "HP of the enemy : " << sc->get_HP_enemy() << endl;
					if (sc->checkDeathe() == true) {
						p->checkLVL(sc->get_pt());
						cout << "Heretic is dead" << endl;
						break;
					}
					else if (p->checkDeathp() == true) {
						cout << "Player is dead" << endl;
						cout << "GAME OVER !!!" << " You can start over " << endl;
						delete p;
						Menu_ui();
					}
					else {
						sc->attack_s(*p, 2);
						rage = rage + 3;
						cout << "HP of the player : " << p->get_HP() << endl;
					}
				}
				if (p->get_mana() >= 100) {
					p->attack(*sc);
					cout << "HP of the enemy : " << sc->get_HP_enemy() << endl;
					if (sc->checkDeathe() == true) {
						cout << "Heretic is dead" << endl;
						p->checkLVL(sc->get_pt());
						break;
					}
					else if (p->checkDeathp() == true) {
						cout << "Player is dead" << endl;
						cout << "GAME OVER !!!" << " You can start over " << endl;
						delete p;
						Menu_ui();
					}
					else {
						sc->attack_s(*p, 2);
						cout << "HP of the player : " << p->get_HP() << endl;
					}
				}
				if (p->get_agility() >= 10) {
					p->attack(*sc);
					cout << "HP of the enemy : " << sc->get_HP_enemy() << endl;
					if (sc->checkDeathe() == true) {
						cout << "Heretic is dead" << endl;
						p->checkLVL(sc->get_pt());
						break;
					}
					else if (p->checkDeathp() == true) {
						cout << "Player is dead" << endl;
						cout << "GAME OVER !!!" << " You can start over " << endl;
						delete p;
						Menu_ui();
					}
					else {
						sc->attack_s(*p, 2);
						cout << "HP of the player : " << p->get_HP() << endl;
					}
				}
			} while (sc->checkDeathe() != true || p->checkDeathp() != true);
			p->set_rage(rage);
		}break;
		case 4: {
			Enemy *n = new Necromancer();
			if (p->get_rage() >= 0) {
				rage = p->get_rage();
				str = p->get_strength();
				rage = rage / 5;
				str = str + rage;
				p->set_strength(str);
				rage = 0;
			}
			do {
				if (rage >= 0) {
					p->attack(*n);
					rage += 2;
					cout << "HP of the enemy : " << n->get_HP_enemy() << endl;
					if (n->checkDeathe() == true) {
						cout << "Necromancer is dead" << endl;
						p->checkLVL(n->get_pt());
						break;
					}
					else if (p->checkDeathp() == true) {
						cout << "Player is dead" << endl;
						cout << "GAME OVER !!!" << " You can start over " << endl;
						delete p;
						Menu_ui();
					}
					else {
						n->attack(*p);
						rage = rage + 3;
						cout << "HP of the player : " << p->get_HP() << endl;
					}
				}
				if (p->get_mana() >= 100) {
					p->attack(*n);
					cout << "HP of the enemy : " << n->get_HP_enemy() << endl;
					if (n->checkDeathe() == true) {
						cout << "Necromancer is dead" << endl;
						p->checkLVL(n->get_pt());
						break;
					}
					else if (p->checkDeathp() == true) {
						cout << "Player is dead" << endl;
						cout << "GAME OVER !!!" << " You can start over " << endl;
						delete p;
						Menu_ui();
					}
					else {
						n->attack(*p);
						cout << "HP of the player : " << p->get_HP() << endl;
					}
				}
				if (p->get_agility() >= 10) {
					p->attack(*n);
					cout << "HP of the enemy : " << n->get_HP_enemy() << endl;
					if (n->checkDeathe() == true) {
						cout << "Necromancer is dead" << endl;
						p->checkLVL(n->get_pt());
						break;
					}
					else if (p->checkDeathp() == true) {
						cout << "Player is dead" << endl;
						cout << "GAME OVER !!!" << " You can start over " << endl;
						delete p;
						Menu_ui();
					}
					else {
						n->attack(*p);
						cout << "HP of the player : " << p->get_HP() << endl;
					}
				}
			} while (n->checkDeathe() != true || p->checkDeathp() != true);
			p->set_rage(rage);
		}break;
		case 5: {
			Enemy *d = new Diablo();
			if (p->get_rage() >= 0) {
				rage = p->get_rage();
				str = p->get_strength();
				rage = rage / 5;
				str = str + rage;
				p->set_strength(str);
				rage = 0;
			}
			do {
				if (rage >= 0) {
					p->attack(*d);
					rage += 2;
					cout << "HP of the enemy : " << d->get_HP_enemy() << endl;
					if (d->checkDeathe() == true) {
						cout << "Diablo is dead" << endl;
						p->checkLVL(d->get_pt());
						break;
					}
					else if (p->checkDeathp() == true) {
						cout << "Player is dead" << endl;
						cout << "GAME OVER !!!" << " You can start over " << endl;
						delete p;
						Menu_ui();
					}
					else {
						d->attack(*p);
						rage = rage + 3;
						cout << "HP of the player : " << p->get_HP() << endl;
					}
				}
				if (p->get_mana() >= 100) {
					p->attack(*d);
					cout << "HP of the enemy : " << d->get_HP_enemy() << endl;
					if (d->checkDeathe() == true) {
						cout << "Diablo is dead" << endl;
						p->checkLVL(d->get_pt());
						break;
					}
					else if (p->checkDeathp() == true) {
						cout << "Player is dead" << endl;
						cout << "GAME OVER !!!" << " You can start over " << endl;
						delete p;
						Menu_ui();
					}
					else {
						d->attack(*p);
						cout << "HP of the player : " << p->get_HP() << endl;
					}
				}
				if (p->get_agility() >= 10) {
					p->attack(*d);
					cout << "HP of the enemy : " << d->get_HP_enemy() << endl;
					if (d->checkDeathe() == true) {
						cout << "Diablo is dead" << endl;
						p->checkLVL(d->get_pt());
						break;
					}
					else if (p->checkDeathp() == true) {
						cout << "Player is dead" << endl;
						cout << "GAME OVER !!!" << " You can start over " << endl;
						delete p;
						Menu_ui();
					}
					else {
						d->attack(*p);
						cout << "HP of the player : " << p->get_HP() << endl;
					}
				}
			} while (d->checkDeathe() != true || p->checkDeathp() != true);
			p->set_rage(rage);

		}break;
		}
	}
	void setPlay(int choice) {
		switch (choice) {
		case 1: {
			this->Map_set(12, 21, 9, 1);
			this->ene_set(1);

		}break;
		case 2: {
			this->Map_set(22, 36, 9, 1);
			this->ene_set(2);
		}break;
		case 3: {
			this->Map_set(52, 66, 11, 1);
			this->ene_set(3);
		}break;
		}
	}
	void writeFile(string pl_name, Character *p) {//write the coordinates of everything on the map and save it in a file and saves the player's stats
		ofstream file;
		int br = 0;
		for (int i = 0; i <= this->y; i++) {
			for (int j = 0; j <= this->x; j++) {
				if (mp[i][j] == 1) {
					file << "PL:" << i << "," << j << ";" << endl;
				}
			}
			br++;
		}
		file.open(pl_name.c_str(), ios::trunc);
		if (file.is_open()) {
			file << br - 1 << endl;
			for (int i = 0; i <= this->y; i++) {
				for (int j = 0; j <= this->x; j++) {
					if (mp[i][j] == 1) {
						file << "PL:" << i << "," << j << ";" << endl;
					}
				}
			}
			for (int i = 0; i <= this->y; i++) {
				for (int j = 0; j <= this->x; j++) {
					if (mp[i][j] == 2) {
						file << "SC:" << i << "," << j << ";" << endl;
					}
					else if (mp[i][j] == 3) {
						file << "HE:" << i << "," << j << ";" << endl;
					}
					else if (mp[i][j] == 4) {
						file << "NE:" << i << "," << j << ";" << endl;
					}
					else if (mp[i][j] == 5) {
						file << "DI:" << i << "," << j << ";" << endl;
					}
				}
			}
		}
		else
			cout << "Unable to open a file" << endl;
		file << "HP:" << p->get_HP() << ";" << endl;
		file << "ST:" << p->get_strength() << ";" << endl;
		file << "IN:" << p->get_intel() << ";" << endl;
		file << "LV:" << p->get_level() << ";" << endl;
		if (p->get_rage() >= 0)
			file << "RA:" << p->get_rage() << ";" << endl;
		if (p->get_mana() >= 100)
			file << "MA:" << p->get_mana() << ";" << endl;
		if (p->get_agility() >= 10)
			file << "AG:" << p->get_agility() << ";" << endl;
		file.close();
	}
	void readFile(string &file_name) {//reads the coordinates and spawns everything on the map and gets the player stats
		ifstream file;
		int valuex, valuey, px = 0, py = 0;
		int sum_x = 0, sum_y = 0, hp = 0, str = 0, in = 0, buf_ab = 0, lv = 0, sum_xs = 0, sum_ys = 0, xm = 0, ym = 0, xb = 0, yb = 0;
		string s, s2, s3, buf;
		int br = 0;
		file.open(file_name.c_str());

		if (!file)
			cout << "Error opening the file !!" << endl;
		else {
			getline(file, s);
			br = stoi(s);
			while (getline(file, s)) {
				if (s.at(0) == 'P' && s.at(1) == 'L') {
					if (s.at(4) == ',') {
						s2 = s.at(3);
						s3 = s.at(5);
					}
					else {
						s2 = s.at(3);
						buf = s.at(4);
						s2 = s2 + buf;
						py = stoi(s2);
					}
					if (s.at(6) == ';') {
						py = stoi(s2);
						px = stoi(s3);
						switch (br) {
						case 21: {
							this->Map_set(12, 21, px, py);
						}break;
						case 36: {
							this->Map_set(22, 36, px, py);
						}break;
						case 66: {
							this->Map_set(52, 66, px, py);
						}break;
						}
					}
					else {
						buf = s.at(6);
						s3 = s3 + buf;
						px = stoi(s3);
						py = stoi(s2);
						switch (br) {
						case 21: {
							this->Map_set(12, 21, px, py);
						}break;
						case 36: {
							this->Map_set(22, 36, px, py);
						}break;
						case 66: {
							this->Map_set(52, 66, px, py);
						}break;
						}
					}
				}
				else if (s.at(0) == 'S' && s.at(1) == 'C' || s.at(0) == 'H' && s.at(1) == 'E' || s.at(0) == 'N' && s.at(1) == 'E' || s.at(0) == 'D' && s.at(1) == 'I') {
					if (s.at(6) == ';') {
						s2 = s.at(3);
						s3 = s.at(5);
						sum_ys = stoi(s2);
						sum_xs = stoi(s3);
					}
					else if (s.at(7) == ';') {
						if (s.at(4) == ',') {
							s2 = s.at(3);
							s3 = s.at(5);
							buf = s.at(6);

							ym = stoi(s2);
							buf = s3 + buf;
							xm = stoi(buf);
						}
						else {
							s2 = s.at(3);
							buf = s.at(4);
							s2 = s2 + buf;
							ym = stoi(s2);
							s3 = s.at(6);
							xm = stoi(s3);
						}
					}
					else if (s.at(8) == ';') {
						s2 = s.at(3);
						s3 = s.at(4);
						buf = s2 + s3;
						yb = stoi(buf);

						s2 = s.at(6);
						s3 = s.at(7);
						buf = s2 + s3;
						xb = stoi(buf);
					}
					
					
					if (s.at(0) == 'S' && s.at(1) == 'C') {
						if (s.at(6) == ';')
							this->Spw_En(sum_xs, sum_ys, 1);
						else if(s.at(7) == ';')
							this->Spw_En(xm, ym, 1);
						else if(s.at(8) == ';')
							this->Spw_En(xb, yb, 1);
					}
					else if (s.at(0) == 'H' && s.at(1) == 'E') {
						if (s.at(6) == ';')
							this->Spw_En(sum_xs, sum_ys, 2);
						else if (s.at(7) == ';')
							this->Spw_En(xm, ym, 2);
						else if (s.at(8) == ';')
							this->Spw_En(xb, yb, 2);
					}
					else if (s.at(0) == 'N' && s.at(1) == 'E') {
						if (s.at(6) == ';')
							this->Spw_En(sum_xs, sum_ys, 3);
						else if (s.at(7) == ';')
							this->Spw_En(xm, ym, 3);
						else if (s.at(8) == ';')
							this->Spw_En(xb, yb, 3);
					}
					else if (s.at(0) == 'D' && s.at(1) == 'I') {
						if (s.at(6) == ';')
							this->Spw_En(sum_xs, sum_ys, 4);
						else if (s.at(7) == ';')
							this->Spw_En(xm, ym, 4);
						else if (s.at(8) == ';')
							this->Spw_En(xb, yb, 4);
					}
				}
				else if (s.at(0) == 'H' && s.at(1) == 'P') {
					if (s.at(4) == ';') {
						s2 = s.at(3);
						hp = stoi(s2);
					}
					else if (s.at(5) == ';') {
						s2 = s.at(4);
						s3 = s.at(3);
						s3 = s3 + s2;
						hp = stoi(s3);
					}
					else if (s.at(6) == ';') {
						s2 = s.at(5);
						s3 = s.at(4);
						s3 = s3 + s2;
						buf = s.at(3);
						buf = buf + s3;
						hp = stoi(buf);
					}
				}
				else if (s.at(0) == 'S' && s.at(1) == 'T') {
					if (s.at(4) == ';') {
						s2 = s.at(3);
						str = stoi(s2);
					}
					else if (s.at(5) == ';') {
						s2 = s.at(4);
						s3 = s.at(3);
						s3 = s3 + s2;
						str = stoi(s3);
					}
					else if (s.at(6) == ';') {
						s2 = s.at(5);
						s3 = s.at(4);
						s3 = s3 + s2;
						buf = s.at(3);
						buf = buf + s3;
						str = stoi(buf);
					}
				}
				else if (s.at(0) == 'I' && s.at(1) == 'N') {
					if (s.at(4) == ';') {
						s2 = s.at(3);
						in = stoi(s2);
					}
					else if (s.at(5) == ';') {
						s2 = s.at(4);
						s3 = s.at(3);
						s3 = s3 + s2;
						in = stoi(s3);
					}
					else if (s.at(6) == ';') {
						s2 = s.at(5);
						s3 = s.at(4);
						s3 = s3 + s2;
						buf = s.at(3);
						buf = buf + s3;
						in = stoi(buf);
					}
				}
				else if (s.at(0) == 'L' && s.at(1) == 'V') {
					if (s.at(4) == ';') {
						s2 = s.at(3);
						lv = stoi(s2);
					}
					else if (s.at(5) == ';') {
						s2 = s.at(4);
						s3 = s.at(3);
						s3 = s3 + s2;
						lv = stoi(s3);
					}
					else if (s.at(6) == ';') {
						s2 = s.at(5);
						s3 = s.at(4);
						s3 = s3 + s2;
						buf = s.at(3);
						buf = buf + s3;
						lv = stoi(buf);
					}
				}
				else if (s.at(0) == 'R' && s.at(1) == 'A' || s.at(0) == 'M' && s.at(1) == 'A' || s.at(0) == 'A' && s.at(1) == 'G') {
					if (s.at(4) == ';') {
						s2 = s.at(3);
						buf_ab = stoi(s2);
					}
					else if (s.at(5) == ';') {
						s2 = s.at(4);
						s3 = s.at(3);
						s3 = s3 + s2;
						buf_ab = stoi(s3);
					}
					else if (s.at(6) == ';') {
						s2 = s.at(5);
						s3 = s.at(4);
						s3 = s3 + s2;
						buf = s.at(3);
						buf = buf + s3;
						buf_ab = stoi(buf);
					}
					if (s.at(0) == 'R' && s.at(1) == 'A') {
						Character *p = new Barbarian();
						p->set_HP(hp);
						p->set_strength(str);
						p->set_intel(in);
						p->set_level(lv);
						p->set_rage(buf_ab);
						this->play_mov(p, file_name);
					}
					else if (s.at(0) == 'M' && s.at(1) == 'A') {
						Character *so = new Sorcerer();
						so->set_HP(hp);
						so->set_strength(str);
						so->set_intel(in);
						so->set_level(lv);
						so->set_mana(buf_ab);
						this->play_mov(so, file_name);
					}
					else if (s.at(0) == 'A' && s.at(1) == 'G') {
						Character *bh = new Bounty_Hunter();
						bh->set_HP(hp);
						bh->set_strength(str);
						bh->set_intel(in);
						bh->set_level(lv);
						bh->set_agility(buf_ab);
						this->play_mov(bh, file_name);
					}
				}
			}
			file.close();
		}
	}
	void play_mov(Character* p, string pl_name) {//movement of the player on the map
		int choice;
		int hp = p->get_HP();
		int type_enemy;
		this->printMap();
		do {
			try {
				do {
					cout << " 1. Up" << endl;
					cout << " 2. Down" << endl;
					cout << " 3. Left" << endl;
					cout << " 4. Right" << endl;
					cout << " 5. Save and exit " << endl;
					cout << " 6. Stats" << endl;

					do {
						cin >> choice;
					} while (choice > 6);

					switch (choice) {

					case 1: {
						this->player_mov(px, py - 1);
						type_enemy = this->check_box();
						cout << type_enemy << endl;
						this->attack(type_enemy, p);
						this->printMap();
					}break;
					case 2: {
						this->player_mov(px, py + 1);
						type_enemy = this->check_box();
						cout << type_enemy << endl;
						this->attack(type_enemy, p);
						this->printMap();
					}break;
					case 3: {
						this->player_mov(px - 1, py);
						type_enemy = this->check_box();
						cout << type_enemy << endl;
						this->attack(type_enemy, p);
						this->printMap();
					}break;
					case 4: {
						this->player_mov(px + 1, py);
						type_enemy = this->check_box();
						cout << type_enemy << endl;
						this->attack(type_enemy, p);
						this->printMap();
					}break;
					case 5: {
						this->writeFile(pl_name, p);
						Menu_ui();
					}break;
					case 6: {
						p->print_a();
					}break;
					}
				} while (choice < 1 || choice > 6);
			}
			catch (char* c) {
				cout << c;
			}
		} while (hp > 0);
	}
};
int main()
{
	Menu_ui();

	system("pause");
	return 0;
}
void Menu_ui() {//main menu function
	int choice;
	do {
		cout << "########WELCOME##TO##DIABLO########" << endl;
		cout << " 1. New game" << endl;
		cout << " 2. Load game" << endl;
		cout << " 3. Legend" << endl;
		cout << " 4. Exit  " << endl;
		cout << "Choose your destiny !! " << "Enter your choice below !!" << endl;

		cin >> choice;

		switch (choice) {

		case 1: New_game_diff(); break;
		case 2: Load_game(); break;
		case 3: {
			cout << "1 - Player" << endl;
			cout << "2 - Sceleton" << endl;
			cout << "3 - Heretic" << endl;
			cout << "4 - Necromancer" << endl;
			cout << "5 - Diablo" << endl;
			cout << "6 - Map Border" << endl;
			Menu_ui();
		}break;
		case 4: cout << " Goodbye!!! " << endl; exit(0); break;

		}
	} while (choice < 1 || choice > 3);
}
void New_game_diff() {//new game menu
	int ch = 0, choice = 0;
	string player_name;
	Play p;
	do {
		cout << "### Choose your difficulty ###" << endl;
		cout << " 1. Easy difficulty" << endl;
		cout << " 2. Medium difficulty" << endl;
		cout << " 3. Hard difficulty" << endl;
		cout << " 4. Back to main menu" << endl;
		cin >> ch;

		switch (ch) {
		case 1: p.setPlay(1); break;
		case 2: p.setPlay(2); break;
		case 3: p.setPlay(3); break;
		case 4: Menu_ui(); break;
		}

	} while (ch < 1 || ch > 4);
	cout << "Enter you nickname : " << endl;
	fflush(stdin);
	cin >> player_name;
	fflush(stdin);
	player_name = player_name + ".txt";
	do {
		cout << "### Choose your class ###" << endl;
		cout << " 1. Barbarian class" << endl;
		cout << " 2. Sorcerer class" << endl;
		cout << " 3. Bounty Hunter class" << endl;
		cout << " 4. Back to main menu" << endl;
		cin >> choice;

		switch (choice) {
		case 1: {
			Character *b = new Barbarian;
			p.play_mov(b, player_name);
		}break;
		case 2: {
			Character *s = new Sorcerer;
			p.play_mov(s, player_name);
		} break;
		case 3: {
			Character *bh = new Bounty_Hunter;
			p.play_mov(bh, player_name);
		} break;
		case 4: cout << "Returning" << endl; break;
		}

	} while (ch < 1 || ch > 4);
}
void Load_game() {//load game menu
	string file_name;
	Play p;
	cout << "Enter the name of the saved file : " << endl;
	fflush(stdin);
	cin >> file_name;
	fflush(stdin);
	file_name = file_name + ".txt";
	try {
		p.readFile(file_name);
	}
	catch (const std::out_of_range& oor) {
		cerr << "Out of Range error: " << oor.what() << endl;
	}
}