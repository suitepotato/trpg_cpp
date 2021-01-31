#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

string warriorName;
string magicianName;

int warriorLevel = 1;
int warriorHp = 10;
int warriorMaxHp = 10;
int warriorMp = 6;
int warriorMaxMp = 6;
int warriorAttack = 0;
int warriorDefend = 0;
int warriorAttackBuff = 0; // 전투 종료 시 감소할 공격력을 의미한다.
int warriorDefendBuff = 0; // 다음 턴에 감소할 방어력을 의미한다.
int warriorFinalSkill = 0; // 산:발도가 발동하는 여부를 의미한다. 0: 사용 가능, 1: 이번에 발동, 2: 다음 턴에 발동
int warriorExp = 0;		   //

int magicianLevel = 1;
int magicianHp = 6;
int magicianMaxHp = 6;
int magicianMp = 10;
int magicianMaxMp = 10;
int magicianPower = 0;
int magicianDefend = 0;
int magicianStoneBarrior = 0;
int magicianFirewall = 0;
int magicianExp = 0;

int warriorSkillMp[10] = {0, 0, 3, 6, 0, 10, 13, 0, 0, 15};
int magicianSkillMp[11] = {0, 2, 0, 5, 8, 13, 18, 16, 28, 35, 0};

int warriorRequireExp[10] = {8, 10, 12, 14, 16, 18, 20, 22, 24, 26};
int magicianRequireExp[10] = {8, 10, 12, 14, 16, 18, 20, 22, 24, 26};

int enemyAmount = 1;
string enemyName[5] = {"0"};
int enemyHp[5] = {0};
int enemyMaxHp[5] = {10};
int enemyAttack[5] = {0};
int enemyDefend[5] = {0};
int enemyAttackDebuff[5] = {0};
int enemyDefendDebuff[5] = {0};
int enemyStunDebuff[5] = {0};
int enemyAttackTarget[5] = {0};
int enemyAttackDamage[5] = {0};
int enemyAttackCount[5] = {0};
int enemyType[5] = {0};

bool isWin = false;

void typing(string script) // 타이핑 효과 주는 함수
{
	for (int i = 0; i < script.size(); i++)
	{
		Sleep(10);
		cout << script[i];
	}
	cout << endl;
}

void checkExp()
{
	while (1)
	{
		if (warriorExp > warriorRequireExp[warriorLevel - 1])
		{
			warriorExp = warriorExp - warriorRequireExp[warriorLevel - 1];
			warriorLevel = warriorLevel + 1;
			warriorMaxHp = 5 + (warriorLevel * 5);
			warriorMaxMp = 3 + (warriorLevel * 3);
			warriorAttack = warriorLevel / 2;
			warriorDefend = (warriorLevel - 1) / 2;
			typing(warriorName + "이(가) " + to_string(warriorLevel) + "레벨로 올랐다!");
			typing(warriorName + "의 체력이 " + to_string(warriorMaxHp) + "로 올랐다!");
			typing(warriorName + "의 마나가 " + to_string(warriorMaxMp) + "로 올랐다!");
			typing(warriorName + "의 공격력이 " + to_string(warriorAttack) + "이 되었다!");
			typing(warriorName + "의 방어력이 " + to_string(warriorDefend) + "이 되었다!");
		}
		else
		{
			cout << endl;
			break;
		}
	}
	while (1)
	{
		if (magicianExp > magicianRequireExp[magicianLevel - 1])
		{
			magicianExp = magicianExp - magicianRequireExp[magicianLevel - 1];
			magicianLevel = magicianLevel + 1;
			magicianMaxHp = 3 + (magicianLevel * 3);
			magicianMaxMp = 5 + (magicianLevel * 5);
			magicianPower = (magicianLevel - 1) / 2;
			magicianDefend = magicianLevel / 2;
			typing(magicianName + "이(가) " + to_string(magicianLevel) + "레벨로 올랐다!");
			typing(magicianName + "의 체력이 " + to_string(magicianMaxHp) + "로 올랐다!");
			typing(magicianName + "의 마나가 " + to_string(magicianMaxMp) + "로 올랐다!");
			typing(magicianName + "의 공격력이 " + to_string(magicianPower) + "이 되었다!");
			typing(magicianName + "의 방어력이 " + to_string(magicianDefend) + "이 되었다!");
		}
		else
		{
			cout << endl;
			break;
		}
	}
}

void EnemySet(int type, int number, string name, int maxHp, int attack, int defend)
{
	enemyType[number] = type;
	enemyName[number] = name;
	enemyHp[number] = maxHp;
	enemyMaxHp[number] = maxHp;
	enemyAttack[number] = attack;
	enemyDefend[number] = defend;
	enemyAttackDebuff[number] = 0;
	enemyDefendDebuff[number] = 0;
	enemyStunDebuff[number] = 0;
}

void BattleReady()
{
	warriorHp = warriorMaxHp;
	warriorMp = warriorMaxMp;
	magicianHp = magicianMaxHp;
	magicianMp = magicianMaxMp;
	warriorAttack -= warriorAttackBuff;
	warriorDefend += warriorAttackBuff;
	warriorAttackBuff = 0;
	warriorDefend -= warriorDefendBuff;
	warriorDefendBuff = 0;
	warriorFinalSkill = 0;
	magicianStoneBarrior = 0;
	magicianFirewall = 0;
}

void Battle1Ready()
{
	BattleReady();
	cout << "\n들개 3마리와 조우했다!\n"
		 << endl;
	enemyAmount = 3;
	EnemySet(1, 0, "들개1", 3, 2, 0);
	EnemySet(1, 1, "들개2", 3, 2, 0);
	EnemySet(1, 2, "들개3", 3, 2, 0);
}

void Battle2Ready()
{
	BattleReady();
	cout << "\n늑대 2마리와 조우했다!\n"
		 << endl;
	enemyAmount = 2;
	EnemySet(2, 0, "늑대1", 6, 3, 0);
	EnemySet(2, 1, "늑대2", 6, 3, 0);
}

void Battle3Ready()
{
	BattleReady();
	cout << "\n해골병 3마리와 조우했다!\n"
		 << endl;
	enemyAmount = 3;
	EnemySet(3, 0, "해골병1", 12, 4, 0);
	EnemySet(3, 1, "해골병2", 8, 5, 2);
	EnemySet(3, 2, "해골병2", 15, 3, 1);
}

void Battle4Ready()
{
	BattleReady();
	cout << "\n빅좀비가 좀비 2마리를 이끌고 나타났다!\n"
		 << endl;
	enemyAmount = 3;
	EnemySet(3, 0, "1.좀비", 12, 6, 2);
	EnemySet(3, 1, "2.좀비", 18, 5, 1);
	EnemySet(3, 2, "3.빅좀비", 22, 9, 2);
}

void EnemyAttackSet(int number, int attackPercent, int attackCount)
{
	enemyAttackTarget[number] = rand() % 2 + 1;
	enemyAttackDamage[number] = attackPercent * enemyAttack[number] / 100;
	enemyAttackCount[number] = attackCount;
}

void EnemyPatternSet(int number)
{
	switch (enemyType[number])
	{
	case 1:
		switch (rand() % 2 + 1)
		{
		case 1:
			EnemyAttackSet(number, 100, 1);
			break;
		case 2:
			EnemyAttackSet(number, 50, 2);
			break;
		}
		break;
	case 2:
		switch (rand() % 2 + 1)
		{
		case 1:
			EnemyAttackSet(number, 100, 1);
			break;
		case 2:
			EnemyAttackSet(number, 34, 3); // 올림해야됨.
			break;
		}
		break;
	}
}

void HpMpShow(double percent)
{
	cout << " ";
	for (int i = 0; i < 10; i++)
	{
		if (percent >= 10)
		{
			cout << "●";
			percent -= 10;
		}
		else if (percent >= 5)
		{
			cout << "◐";
			percent -= 5;
		}
		else
		{
			cout << "○";
		}
	}
	cout << " ";
}

void WarriorSkillShow()
{
	cout << "\n"
		 << warriorName << "의 사용 가능한 스킬\n"
		 << endl;
	if (warriorLevel >= 1)
	{
		cout << "[1] 마나 충전 : LV만큼 마나를 회복한다. MP 소모 없음" << endl;
		cout << "[2] 베기 : 상대 하나에게 1d(2+공격력)의 피해를 입힌다. MP 소모 없음" << endl;
	}
	if (warriorLevel >= 2)
	{
		cout << "[3] 찌르기 : 상대 하나에게 2d(2+공격력)의 피해를 입히고, 상대의 방어력을 1턴간 25% 감소시킨다. MP 3 소모" << endl;
	}
	if (warriorLevel >= 3)
	{
		cout << "[4] 강타 : 상대 하나에게 3d(4+공격력)의 피해를 입힌다. MP 6 소모" << endl;
	}
	if (warriorLevel >= 4)
	{
		cout << "[5] 방패 들기 : 이번 턴 동안 방어력이 2d4 상승한다. MP 소모 없음" << endl;
	}
	if (warriorLevel >= 5)
	{
		cout << "[6] 연속 베기 : 모든 상대에게 2d(6+공격력)의 피해를 입힌다. MP 10 소모" << endl;
	}
	if (warriorLevel >= 6)
	{
		cout << "[7] 혼신의 일격 : 상대 하나에게 1d(20+공격력*2)의 피해를 입힌다. MP 13 소모" << endl;
	}
	if (warriorLevel >= 7)
	{
		cout << "[8] 광폭화 : 전투가 끝날 때 까지, 방어력이 0이 되고, 공격력이 감소한 방어력의 절반만큼 증가한다. MP 소모 없음" << endl;
	}
	if (warriorLevel >= 8)
	{
		cout << "[9] 도발 : 이번 턴 모든 공격의 대상이 자신이 된다. MP 소모 없음" << endl;
	}
	if (warriorLevel >= 9)
	{
		cout << "[10] 산:발도 : 다음 턴에 발동, 모든 상대에게 4d(6+공격력)의 피해를 입힌다. 연속으로 사용할 수 없다. MP 15 소모" << endl;
	}
}

void MagicianSkillShow()
{
	cout << "\n"
		 << magicianName << "의 사용 가능한 스킬\n"
		 << endl;
	if (magicianLevel >= 1)
	{
		cout << "[1] 마나 충전 : LV만큼 마나를 회복한다. MP 소모 없음" << endl;
		cout << "[2] 파이어 볼 : 상대 하나에게 1d4의 피해를 입힌다, MP 2 소모" << endl;
		cout << "[3] 힐 : 아군 모두의 체력을 LVd6만큼 회복시킨다. MP LV*3 소모" << endl;
	}
	if (magicianLevel >= 2)
	{
		cout << "[4] 아이스 스피어 : 상대 하나에게 2d4의 피해를 입히고, 상대의 공격력을 1턴간 25% 감소시킨다. MP 5 소모" << endl;
	}
	if (magicianLevel >= 3)
	{
		cout << "[5] 스톤 배리어 : 이번 턴에 입는 모든 피해를 1d4만큼 감소시킨다. 피해를 받을 때마다 주사위를 굴린다. MP 8 소모" << endl;
	}
	if (magicianLevel >= 4)
	{
		cout << "[6] 체인 라이트닝 : 모든 상대에게 1d4의 피해를 주고, 40% 확률로 기절시킨다.(기절: 1턴간 아무것도 할 수 없다.) MP 13 소모" << endl;
	}
	if (magicianLevel >= 5)
	{
		cout << "[7] 파이어 월 : 3턴간 상대가 공격할때마다 1d6의 피해를 입힌다. MP 18 소모" << endl;
	}
	if (magicianLevel >= 6)
	{
		cout << "[8] 매직 미사일 : 무작위 상대에게 2d4의 피해를 5회 입힌다. MP 16 소모" << endl;
	}
	if (magicianLevel >= 7)
	{
		cout << "[9] 헬파이어 : 모든 상대에게 6d6의 피해를 준다. MP 28 소모" << endl;
	}
	if (magicianLevel >= 8)
	{
		cout << "[10] 퍼니시먼트 : 상대 하나에게 6d12의 피해를 준다. MP 35 소모" << endl;
	}
	if (magicianLevel >= 9)
	{
		cout << "[11] 익스플로젼 : 모든 상대에게 소비한 마나 만큼의 피해를 준다. MP 전부 소모" << endl;
	}
}

int DiceRoll(int diceAmount, int diceMax)
{
	int dice = 0;
	for (int i = 0; i < diceAmount; i++)
	{
		dice += rand() % diceMax + 1;
	}
	return dice;
}

void PlayerAttack(string name, int enemy, int diceAmount, int diceMax)
{
	int damage = 0;
	if (enemyDefendDebuff[enemy - 1] > 0)
		damage = DiceRoll(diceAmount, diceMax) - (enemyDefend[enemy - 1] * 3 / 4);
	else
		damage = DiceRoll(diceAmount, diceMax) - enemyDefend[enemy - 1];

	if (damage < 0)
	{
		damage = 0;
	}

	cout << ">> " << name << "(이)는 " << enemyName[enemy - 1] << "에게 " << damage << "의 피해를 입혔다!" << endl;
	enemyHp[enemy - 1] -= damage;

	if (enemyHp[enemy - 1] < 0)
	{
		enemyHp[enemy - 1] = 0;
	}
}

void EnemyAttack(int number)
{
	int damage = 0;
	for (int i = 0; i < enemyAttackCount[number]; i++)
	{
		if (enemyAttackTarget[number] == 1)
		{
			damage = enemyAttackDamage[number] - warriorDefend;
			if (damage < 0)
			{
				damage = 0;
			}
			cout << ">> " << enemyName[number] << "(이)는 " << warriorName << "에게 " << damage << "의 피해를 입혔다!" << endl;
			warriorHp -= damage;
			if (warriorHp < 0)
			{
				warriorHp = 0;
				cout << warriorName << "(이)가 사망했습니다." << endl;
			}
		}
		else
		{
			damage = enemyAttackDamage[number] - magicianDefend;
			if (damage < 0)
			{
				damage = 0;
			}
			cout << ">> " << enemyName[number] << "(이)는 " << magicianName << "에게 " << damage << "의 피해를 입혔다!" << endl;
			magicianHp -= damage;
			if (magicianHp < 0)
			{
				magicianHp = 0;
				cout << magicianName << "(이)가 사망했습니다." << endl;
			}
		}
	}
}

void WarriorSkillUse(int skill)
{
	int enemy = 0;
	int extraDefend = 0;
	switch (skill)
	{
	case 1:
		cout << warriorName << "(이)는 마나를 " << warriorLevel << " 회복했다!" << endl;
		warriorMp += warriorLevel;
		if (warriorMp > warriorMaxMp)
			warriorMp = warriorMaxMp;
		break;
	case 2:
		while (enemy < 1 || enemy > enemyAmount)
		{
			cout << "공격할 상대를 선택하세요."
				 << "(1 ~ " << enemyAmount << ")" << endl;
			cin >> enemy;
		}
		PlayerAttack(warriorName, enemy, 1, 2 + warriorAttack);
		break;
	case 3:
		while (enemy < 1 || enemy > enemyAmount)
		{
			cout << "공격할 상대를 선택하세요."
				 << "(1 ~ " << enemyAmount << ")" << endl;
			cin >> enemy;
		}
		PlayerAttack(warriorName, enemy, 2, 2 + warriorAttack);
		enemyDefendDebuff[enemy - 1]++;
		break;
	case 4:
		while (enemy < 1 || enemy > enemyAmount)
		{
			cout << "공격할 상대를 선택하세요."
				 << "(1 ~ " << enemyAmount << ")" << endl;
			cin >> enemy;
		}
		PlayerAttack(warriorName, enemy, 3, 4 + warriorAttack);
		break;
	case 5:
		extraDefend = DiceRoll(2, 4);
		cout << warriorName << "(이)의 방어력이 " << extraDefend << " 상승했다!" << endl;
		warriorDefend += extraDefend;
		warriorDefendBuff += extraDefend;
		break;
	case 6:
		for (int i = 0; i < 5; i++)
		{
			if (enemyAmount >= i + 1)
			{
				PlayerAttack(warriorName, i + 1, 2, 6 + warriorAttack);
			}
		}
		break;
	case 7:
		while (enemy < 1 || enemy > enemyAmount)
		{
			cout << "공격할 상대를 선택하세요."
				 << "(1 ~ " << enemyAmount << ")" << endl;
			cin >> enemy;
		}
		PlayerAttack(warriorName, enemy, 1, 20 + warriorAttack * 2);
		break;
	case 8:
		cout << warriorName << "(이)의 방어력이 0이 되고, 공격력이 " << warriorDefend / 2 << " 상승했다!" << endl;
		warriorAttack += warriorDefend / 2;
		warriorAttackBuff += warriorDefend / 2;
		warriorDefend = 0;
		break;
	case 9:
		cout << warriorName << "(이)는 이번 턴 동안 모든 공격의 대상을 자신으로 만들었다!" << endl;
		for (int i = 0; i < 5; i++)
		{
			if (enemyAttackTarget[i] == 2)
			{
				enemyAttackTarget[i] = 1;
			}
		}
		break;
	case 10:
		if (warriorFinalSkill == 0)
		{
			cout << warriorName << "(이)는 산:발도를 시전했다! 다음 턴에 발동된다!" << endl;
			warriorFinalSkill = 2;
		}
		else
		{
			cout << "산:발도는 이미 시전 중이다!" << endl;
		}
		break;
	}
}

void MagicianSkillUse(int skill)
{
	int enemy = 0;
	int recover = 0;
	switch (skill)
	{
	case 1:
		cout << magicianName << "(이)는 마나를 " << magicianLevel << " 회복했다!" << endl;
		magicianMp += magicianLevel;
		if (magicianMp > magicianMaxMp)
			magicianMp = magicianMaxMp;
		break;
	case 2:
		while (enemy < 1 || enemy > enemyAmount)
		{
			cout << "공격할 상대를 선택하세요."
				 << "(1 ~ " << enemyAmount << ")" << endl;
			cin >> enemy;
		}
		PlayerAttack(magicianName, enemy, 1, 4);
		break;
	case 3:
		recover = DiceRoll(magicianLevel, 6);
		cout << "아군 전체의 체력을 " << recover << "만큼 회복했다!" << endl;
		warriorHp += recover;
		if (warriorHp > warriorMaxHp)
			warriorHp = warriorMaxHp;
		magicianHp += recover;
		if (magicianHp > magicianMaxHp)
			magicianHp = magicianMaxHp;
		break;
	case 4:
		while (enemy < 1 || enemy > enemyAmount)
		{
			cout << "공격할 상대를 선택하세요."
				 << "(1 ~ " << enemyAmount << ")" << endl;
			cin >> enemy;
		}
		PlayerAttack(magicianName, enemy, 2, 4);
		enemyAttackDebuff[enemy - 1]++;
		break;
	case 5:
		cout << magicianName << "(이)는 스톤 배리어를 사용했다!" << endl;
		magicianStoneBarrior++;
		break;
	case 6:
		for (int i = 0; i < 5; i++)
		{
			if (enemyAmount >= i + 1)
			{
				PlayerAttack(magicianName, i + 1, 1, 4);
				if (rand() % 5 <= 1) // 40% 확률
				{
					cout << enemyName[i] << "(이)는 기절했다!" << endl;
					enemyStunDebuff[i]++;
				}
			}
		}
		break;
	case 7:
		cout << magicianName << "(이)는 파이어 월을 사용했다!" << endl;
		magicianFirewall += 3;
		break;
	case 8:
		for (int i = 0; i < 5; i++)
		{
			PlayerAttack(magicianName, rand() % enemyAmount + 1, 2, 4);
		}
		break;
	case 9:
		for (int i = 0; i < 5; i++)
		{
			if (enemyAmount >= i + 1)
			{
				PlayerAttack(magicianName, i + 1, 6, 6);
			}
		}
		break;
	case 10:
		while (enemy < 1 || enemy > enemyAmount)
		{
			cout << "공격할 상대를 선택하세요."
				 << "(1 ~ " << enemyAmount << ")" << endl;
			cin >> enemy;
		}
		PlayerAttack(magicianName, enemy, 6, 12);
		break;
	case 11:
		for (int i = 0; i < 5; i++)
		{
			if (enemyAmount >= i + 1)
			{
				PlayerAttack(magicianName, i + 1, magicianMp, 1);
			}
		}
		magicianMp = 0;
		break;
	}
}

void StatShow()
{
	cout << "\n----------------------------------------------------------------------------------------------------" << endl;
	cout << "\n"
		 << warriorName << " Lv " << warriorLevel << " HP " << warriorHp << "/" << warriorMaxHp;
	HpMpShow(warriorHp / (double)warriorMaxHp * 100);
	cout << " MP " << warriorMp << "/" << warriorMaxMp;
	HpMpShow(warriorMp / (double)warriorMaxMp * 100);
	cout << "\n";
	cout << "공격력 " << warriorAttack << " 방어력 " << warriorDefend << " 증가된 공격력 " << warriorAttackBuff << " 증가된 방어력 " << warriorDefendBuff;
	if (warriorFinalSkill == 2)
	{
		cout << " 전사의 이번 행동 이후 산:발도 발동";
	}
	cout << "\n";

	cout << magicianName << " Lv " << magicianLevel << " HP " << magicianHp << "/" << magicianMaxHp;
	HpMpShow(magicianHp / (double)magicianMaxHp * 100);
	cout << " MP " << magicianMp << "/" << magicianMaxMp;
	HpMpShow(magicianMp / (double)magicianMaxMp * 100);
	cout << "\n";
	cout << "마력 " << magicianPower << " 방어력 " << magicianDefend << " ";
	if (magicianStoneBarrior > 0)
	{
		cout << magicianStoneBarrior << "턴 동안 스톤 배리어 발동 ";
	}
	if (magicianFirewall > 0)
	{
		cout << magicianFirewall << "턴 동안 파이어 월 발동 ";
	}
	cout << "\n\n";

	for (int i = 0; i < enemyAmount; i++)
	{
		cout << enemyName[i] << " HP " << enemyHp[i] << "/" << enemyMaxHp[i];
		HpMpShow(enemyHp[i] / (double)enemyMaxHp[i] * 100);
		cout << "\n";
		cout << "공격력 " << enemyAttack[i] << " 방어력 " << enemyDefend[i] << " ";
		if (enemyAttackDebuff[i] > 0)
			cout << enemyAttackDebuff[i] << "턴 동안 공격력 25% 감소 ";
		if (enemyDefendDebuff[i] > 0)
			cout << enemyDefendDebuff[i] << "턴 동안 방어력 25% 감소 ";
		if (enemyStunDebuff[i] > 0)
			cout << enemyStunDebuff[i] << "턴 동안 기절함! ";
		cout << "\n";
	}
	cout << "\n";
	for (int i = 0; i < enemyAmount; i++)
	{
		if (enemyHp[i] > 0)
		{
			if (enemyAttackDebuff[i] > 0)
			{
				if (enemyAttackTarget[i] == 1)
					cout << enemyName[i] << "(은)는 " << warriorName << "에게 " << enemyAttackDamage[i] * 3 / 4 << "의 피해를 " << enemyAttackCount[i] << "회 줄 예정입니다." << endl;
				else
					cout << enemyName[i] << "(은)는 " << magicianName << "에게 " << enemyAttackDamage[i] * 3 / 4 << "의 피해를 " << enemyAttackCount[i] << "회 줄 예정입니다." << endl;
			}
			else
			{
				if (enemyAttackTarget[i] == 1)
					cout << enemyName[i] << "(은)는 " << warriorName << "에게 " << enemyAttackDamage[i] << "의 피해를 " << enemyAttackCount[i] << "회 줄 예정입니다." << endl;
				else
					cout << enemyName[i] << "(은)는 " << magicianName << "에게 " << enemyAttackDamage[i] << "의 피해를 " << enemyAttackCount[i] << "회 줄 예정입니다." << endl;
			}
		}
	}
	cout << "\n----------------------------------------------------------------------------------------------------" << endl;
}

void MyTurn()
{
	warriorDefend -= warriorDefendBuff;
	warriorDefendBuff = 0;
	if (warriorFinalSkill > 1)
		warriorFinalSkill--;
	if (magicianStoneBarrior > 0)
		magicianStoneBarrior--;
	if (magicianFirewall > 0)
		magicianFirewall--;
	magicianSkillMp[2] = magicianLevel * 3;

	for (int i = 0; i < 5; i++)
	{
		if (enemyAttackDebuff[i] > 0)
			enemyAttackDebuff[i]--;
		if (enemyDefendDebuff[i] > 0)
			enemyDefendDebuff[i]--;
		if (enemyStunDebuff[i] > 0)
			enemyStunDebuff[i]--;
	}

	for (int i = 0; i < enemyAmount; i++)
	{
		EnemyPatternSet(i);
	}

	cout << "\n나의 턴!" << endl;
	StatShow();
	WarriorSkillShow();
	int skill = 0;
	while ((skill < 1 || skill > warriorLevel + 1))
	{
		cout << "\n"
			 << warriorName << "(이)가 사용할 스킬의 번호를 입력하세요." << endl;
		cin >> skill;
	}

	if (warriorFinalSkill == 1)
	{
		cout << "\n"
			 << warriorName << "의 산:발도 발동!\n"
			 << endl;
		for (int i = 0; i < 5; i++)
		{
			if (enemyAmount >= i + 1)
			{
				PlayerAttack(warriorName, i + 1, 4, 6 + warriorAttack);
			}
		}
	}

	if (warriorMp >= warriorSkillMp[skill - 1])
	{
		warriorMp -= warriorSkillMp[skill - 1];
		WarriorSkillUse(skill);
	}
	else
	{
		cout << "\n"
			 << warriorName << "(이)는 스킬을 사용하려 했으나 마나가 부족하여 사용하지 못했다!" << endl;
	}

	StatShow();
	MagicianSkillShow();

	skill = 0;
	while ((skill < 1 || skill > magicianLevel + 2))
	{
		cout << "\n"
			 << magicianName << "(이)가 사용할 스킬의 번호를 입력하세요." << endl;
		cin >> skill;
	}
	if (magicianMp >= magicianSkillMp[skill - 1])
	{
		magicianMp -= magicianSkillMp[skill - 1];
		MagicianSkillUse(skill);
	}
	else
	{
		cout << "\n"
			 << magicianName << "(이)는 스킬을 사용하려 했으나 마나가 부족하여 사용하지 못했다!" << endl;
	}

	StatShow();
}

void EnemyTurn()
{
	cout << "\n적의 턴!\n"
		 << endl;

	for (int i = 0; i < enemyAmount; i++)
	{
		if (enemyHp[i] > 0)
			EnemyAttack(i);
	}
}

void Battle(int exp)
{
	int winStack = 0;
	while (1)
	{
		MyTurn();
		Sleep(2000);
		winStack = 0;
		for (int i = 0; i < enemyAmount; i++)
		{
			if (enemyHp[i] == 0)
				winStack++;
		}
		if (winStack == enemyAmount)
		{
			isWin = true;
			warriorExp = warriorExp + exp;
			magicianExp = magicianExp + exp;
			break;
		}
		EnemyTurn();
		if (warriorHp == 0 || magicianHp == 0)
		{
			isWin = false;
			break;
		}
		Sleep(2000);
	}
	if (isWin)
	{
		cout << "\n승리했다!\n"
			 << endl;
		checkExp();
	}
	else
	{
		cout << "\n패배했다...\n"
			 << endl;
	}
}

void scenario_1()
{
	typing("오랜 전쟁이 지난 후, 다행히도 세계는 다시 평화로워졌습니다.");
	typing("하지만 그 평화는 오래 가지 않았죠.");
	typing("평화로운 시절을 견디지 못했던 마왕과 그를 따르는 사교들은 왕에 대항해 반란군을 조직했습니다.");
	typing("이제, 당신이 나서서 그들을 벌하고 세계에 다시 평화를 가져다 주세요!");
	typing("일어나세요!");
	cout << endl;
}

void scenario_2()
{
	typing("갑자기 나타난 들개들을 물리치고 " + warriorName + "(이)와 " + magicianName + "(이)는 계속 앞으로 나아가기로 했습니다.");
	typing("깊은 숲으로 들어서자, 지금이 한 낮이라는 것을 잊을 정도로 " + warriorName + "(이)와 " + magicianName + "(이)의 눈 앞은 어두웠어요.");
	typing("그러자 갑자기 숲 속을 지배하는 늑대들이 나타나 일행을 위협했어요!");
	cout << endl;
}

int main()
{
	srand((unsigned int)time(NULL));

	scenario_1();

	typing("전사의 이름은? (띄어쓰기 없이)");
	cin >> warriorName;
	typing("마법사의 이름은? (띄어쓰기 없이)");
	cin >> magicianName;
	typing(warriorName + "(이)와 " + magicianName + "(이)는 마왕에 맞서는 모험을 떠났어요.");

	Battle1Ready();
	Battle(9);
	if (!isWin)
	{
		return 0;
	}
	scenario_2();

	Battle2Ready();
	Battle(12);
	if (!isWin)
	{
		return 0;
	}
	Battle3Ready();
	Battle(17);
	if (!isWin)
	{
		return 0;
	}
	Battle4Ready();
	Battle(23);
	if (!isWin)
	{
		return 0;
	}
	return 0;
}
