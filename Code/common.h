#pragma once

/**
* @brief ��begin �� end ���Ա仯
* @param pos ���Ա仯��λ�ã���Χ��[0,1]
* @return ����Ϊ (begin - end) ������
*/
template<typename Tb, typename Te>
auto LinearlyChange(Tb begin, Te end, double pos)
{
	auto delta = end - begin;
	auto result = delta * pos + begin;
	delta = result;
	return delta;
}