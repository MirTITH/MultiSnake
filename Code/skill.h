#pragma once

class Skill
{
public:
	/**
	* @brief �������ܣ�֮����Ҫִ��Init()
	*/
	Skill();
	/**
	* @brief ��ʼ������
	* @param _energy �������������������Ҫ��Ϊ0��
	*/
	void Init(int _cd, int _energy);

	void Tick();

	/**
	* @brief ���Ӽ����������������������0�����ᳬ��total_energy
	* @param num ���ӵ�ֵ��Ϊ�����������
	*/
	void EnergyAdd(int num);

	/**
	* @brief ʹ�ü���
	* @return true �ɹ�ʹ�ü��� false �޷�ʹ�ü���
	*/
	bool Use();

	/**
	* @return ��ǰ�����Ƿ����
	*/
	bool IsAvailable();

	int energy; //���ܵ�ǰ����
	int total_energy; //����ʩ����������

	int remain_cd; //����ʣ��cd (tick)
	int total_cd; //������cd
private:
};