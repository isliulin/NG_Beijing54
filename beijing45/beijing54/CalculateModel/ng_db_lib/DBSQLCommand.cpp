#ifdef USE_SQLSERVER
#include "DBSQLCommand.h"
#include "DBSQLReader.h"
DBSQLCommand::DBSQLCommand(_ConnectionPtr &pcon):
p_con(pcon)
{
	p_reader = NULL;
	sTransIndex = 0;
}

DBSQLCommand::~DBSQLCommand(void)
{
	if(p_reader!=NULL)
	{
		delete p_reader;
	}
}

int DBSQLCommand::ExecuteNoQuery( const char* sql )
{
	int nRows = 0;
	_variant_t vRecordAffct;
	try
	{
		p_con->Execute(sql,&vRecordAffct,adCmdText);
		nRows = vRecordAffct.intVal;
	}
	catch (_com_error ex)
	{
		DBText err = ex.ErrorMessage();
		throw err;
	}

	return nRows;
}

IDataReader* DBSQLCommand::ExecuteReader(const char* sql )
{
	bool bOK = false;
	if(CreateReader())
	{
		bOK = p_reader->Query(sql);
	}
	if(bOK)
		return p_reader;
	return NULL;
}

bool DBSQLCommand::CreateReader()
{
	if(p_reader==NULL)
	{
		p_reader = new DBSQLReader(p_con);
	}
	return (p_reader!=NULL);
}

bool DBSQLCommand::BeginTransaction( void )
{
	if(p_con.GetInterfacePtr()!=NULL)
	{
		++sTransIndex;	
		if(1 == sTransIndex)
			p_con->BeginTrans();
		return true;
	}
	return false;
}

bool DBSQLCommand::RollBack( void )
{
	if(p_con.GetInterfacePtr()!=NULL)
	{
		if(1== sTransIndex)
			p_con->RollbackTrans();
		return true;
	}
	return false;
}

bool DBSQLCommand::Commit( void )
{
	if(p_con.GetInterfacePtr()!=NULL)
	{
		if(1==sTransIndex)
			p_con->CommitTrans();
		return true;
	}
	return false;
}

bool DBSQLCommand::CloseTransaction( void )
{
	if(p_con.GetInterfacePtr()!=NULL)
	{
		if(0 < sTransIndex)
			sTransIndex --;		
		return true;
	}
	return false;
}

void DBSQLCommand::SetCommandTimeout( int timeout )
{
	if(p_con.GetInterfacePtr()!=NULL)
	{
		p_con->CommandTimeout = timeout;
		p_con->ConnectionTimeout = timeout;
	}
}

bool DBSQLCommand::InsertBLOB( const char* sql, void* blob, unsigned int bloblength )
{
	byte *buf = (byte *)blob;
	SAFEARRAY *psa;
	SAFEARRAYBOUND rgsabound[1];
	rgsabound[0].lLbound = 0;
	rgsabound[0].cElements = bloblength;
	psa = SafeArrayCreate(VT_UI1,1,rgsabound);
	for(long i=0;i<bloblength;i++)
		SafeArrayPutElement(psa,&i,buf++);
	VARIANT varBlob;
	varBlob.vt = VT_ARRAY|VT_UI1;
	varBlob.parray = psa;
	_CommandPtr pCmd;
	HRESULT hr = pCmd.CreateInstance(__uuidof(Command));
	if(SUCCEEDED(hr))
	{
		pCmd->ActiveConnection = p_con;
		pCmd->CommandText = _bstr_t(sql);
		pCmd->CommandType = adCmdText;
		pCmd->Parameters->Append(pCmd->CreateParameter(_bstr_t("@1"),adVarBinary,adParamInput,-1,varBlob));
		pCmd->Execute(NULL,NULL,adCmdText);
		return true;
	}
	return false;

}
#endif
