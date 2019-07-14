/////////////////////////////////////////////////////////////////////////////////////////
//	This class was originally written by Joseph Dempsey.  The original article 
//	"The "New ipconfig" and the IP Helper API" is available at: 
//  http://www.codeproject.com/internet/netcfg.asp 
//  
//  
//	2012.9.12 edit by jjj,I just remove unicode ,because when I update it to vs2008,
//	there are many errors
//	rsheikh add GetAdapterAddress function,but he use mfc CString,I chang it
///////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ADAPTER_INFO_H____
#define __ADAPTER_INFO_H____

#if defined(_WIN32) || defined(__WIN32__)

#include <windows.h>
#include <vector>

struct _IPINFO 
{
	std::string sIp;
	std::string sSubnet;
};

struct UNNAMED 
{
	BYTE		ucAddress[16];
	UINT		nLen;
};

class CIpInfoArray : public std::vector< _IPINFO > {};
class StringArray : public std::vector< std::string > {};

class CNetworkAdapter;

/////////////////////////////////////////////
// Function Prototypes
DWORD EnumNetworkAdapters(CNetworkAdapter* &pAdapters,int &AdapterCounts);

//获取当前活动的网卡
bool GetPrimaryAdapter(CNetworkAdapter* pAdapters,int AdapterCounts,int &PrimaryIndex);

//////////////////////////////////////////////////////////////////////////////////////////
//	Desc:
//		Class wrapper for a single network adapter.  A listing of these adapters
//		can be built using the EnumNetworkAdapters(...) function prototyped
//		above.
//////////////////////////////////////////////////////////////////////////////////////////
class CNetworkAdapter 
{
	public:
		CNetworkAdapter();
		~CNetworkAdapter();

		BOOL SetupAdapterInfo(void * pInfo);
		// information about the adapters name for the users
		// and its name to the system
		std::string GetAdapterName() const;
		std::string GetAdapterDescription() const;
		
			// dhcp lease access functions
		time_t	GetLeaseObtained() const;
		time_t	GetLeaseExpired() const;
		
			// access to lists of various server's ip address
		SIZE_T	GetNumIpAddrs() const;		
		SIZE_T	GetNumDnsAddrs() const;
		std::string	GetIpAddr( int nIp = 0 ) const;	
		std::string GetSubnetForIpAddr( int nIp = 0 ) const;
		std::string	GetDnsAddr( int nDns = 0 ) const;		
		std::string GetCurrentIpAddress() const;
		
			// dhcp function
		BOOL	IsDhcpUsed() const;		
		std::string	GetDchpAddr() const;

			// wins function
		BOOL	IsWinsUsed() const;
		std::string GetPrimaryWinsServer() const;
		std::string GetSecondaryWinsServer() const;

		// returns formatted MAC address in HEX punctuated with hyphens "-"
		std::string GetAdapterAddress() const;
		UNNAMED GetAdapterAddressBytes() const;	//add by jjj

		std::string	GetGatewayAddr( int nGateway = 0 ) const;
		SIZE_T	GetNumGatewayAddrs() const;

		static	std::string GetAdapterTypeString( UINT nType );
		UINT	GetAdapterType() const;

		DWORD	GetAdapterIndex() const;

	protected:
		std::string	GetStringFromArray( const StringArray* pPtr, int nIndex ) const;
			
	private:		
		std::string		m_sName;		// adapter name with the computer.  For human readable name use m_sDesc.
		std::string		m_sDesc;
		std::string		m_sPriWins;
		std::string		m_sSecWins;
		std::string		m_sDefGateway;
		std::string		m_sDhcpAddr;
		_IPINFO			m_sCurIpAddr;	// this is also in the ip address list but this is the address currently active.
		DWORD			m_dwIndex;		// machine index of the adapter.
		UINT			m_nAdapterType;	
		BOOL			m_bDhcpUsed;
		BOOL			m_bWinsUsed;		
		StringArray		m_DnsAddresses;
		CIpInfoArray	m_IpAddresses;
		StringArray		m_GatewayList;
		time_t			m_tLeaseObtained;
		time_t			m_tLeaseExpires;
		UNNAMED m_ucAddress;
};

#endif

#endif //__ADAPTER_INFO_H____