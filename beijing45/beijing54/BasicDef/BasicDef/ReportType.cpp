#include "MacroDef.h"

ReportType gReportType = TXT;
void SetReportType(ReportType eReportType)
{
	gReportType = eReportType;
}
ReportType GetReportType()
{
	return gReportType;
}