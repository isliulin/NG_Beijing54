#include "NGFrequencyPreselResult.h"

CNGFrequencyPreselResult::CNGFrequencyPreselResult(void)
{
}

CNGFrequencyPreselResult::~CNGFrequencyPreselResult(void)
{
}

void CNGFrequencyPreselResult::Clear()
{
	DownlinkPowerList.clear();
	DownlinkInterfercountList.clear();
	DownlinkQualityList.clear();
	DownlinkCIList.clear();
	DownlinkFreqList.clear();

	UplinkPowerList.clear();
	UplinkInterfercountList.clear();
	UplinkQualityList.clear();
	UplinkCIList.clear();
	UplinkFreqList.clear();
}

bool CNGFrequencyPreselResult::IsUpLinkValid() const
{
	return !UplinkFreqList.empty();
}

bool CNGFrequencyPreselResult::IsDownLinkValid() const
{
	return !DownlinkFreqList.empty();
}

unsigned int CNGFrequencyPreselResult::GetDownLinkSize() const
{
	return DownlinkFreqList.size();
}

unsigned int CNGFrequencyPreselResult::GetUpLinkSize() const
{
	return UplinkFreqList.size();
}