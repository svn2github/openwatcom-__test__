/*

 Definitions for winsock 1.1
 
 Portions Copyright (c) 1980, 1983, 1988, 1993
 The Regents of the University of California. All rights reserved.

 Portions Copyright (c) 1993 by Digital Equipment Corporation.

*/

#ifndef	_INC_WINSOCK
#define	_INC_WINSOCK

#ifndef	_INC_WINDOWS
#include <windows.h>
#endif

#ifdef	__cplusplus
extern	"C" {
#endif

typedef	unsigned char	u_char;
typedef	unsigned short	u_short;
typedef	unsigned int	u_int;
typedef	unsigned long	u_long;
typedef	u_int	SOCKET;
#ifndef	FD_SETSIZE
#define	FD_SETSIZE	64
#endif
typedef	struct fd_set {
	u_int	fd_count;
	SOCKET	fd_array[FD_SETSIZE];
} fd_set;
#define	FD_CLR(fd,set)	do {	\
	u_int	__i;	\
	for (__i = 0; __i < ((fd_set FAR*)(set))->fd_count; __i++) { \
	if (((fd_set FAR*)(set))->fd_array[__i] == fd) { \
		while (__i < ((fd_set FAR*)(set))->fd_count-1) { \
		((fd_set FAR*)(set))->fd_array[__i] = \
			((fd_set FAR*)(set))->fd_array[__i+1]; \
		__i++; \
		} \
		((fd_set FAR*)(set))->fd_count--; \
		break; \
	} \
	} \
} while(0)
#define	FD_SET(fd,set) do { \
	if (((fd_set FAR*)(set))->fd_count < FD_SETSIZE) \
	((fd_set FAR*)(set))->fd_array[((fd_set FAR*)(set))->fd_count++]=(fd);\
} while(0)
#define	FD_ZERO(set) (((fd_set FAR*)(set))->fd_count=0)
extern	int PASCAL FAR __WSAFDIsSet(SOCKET,fd_set FAR*);
#define	FD_ISSET(fd,set) __WSAFDIsSet((SOCKET)(fd),(fd_set FAR*)(set))
struct	timeval {
	long	tv_sec;
	long	tv_usec;
};
#define	timerisset(tvp) ((tvp)->tv_sec || (tvp)->tv_usec)
#define	timercmp(tvp,uvp,cmp) ((tvp)->tv_sec cmp (uvp)->tv_sec || \
		(tvp)->tv_sec == (uvp)->tv_sec && (tvp)->tv_usec cmp (uvp)->tv_usec)
#define	timerclear(tvp) (tvp)->tv_sec = (tvp)->tv_usec = 0
#define	IOCPARM_MASK	0x7f
#define	IOC_VOID	0x20000000
#define	IOC_OUT	0x40000000
#define	IOC_IN	0x80000000
#define	IOC_INOUT	(IOC_IN|IOC_OUT)
#define	_IO(x,y)	(IOC_VOID|((x)<<8)|(y))
#define	_IOR(x,y,t)	(IOC_OUT|(((long)sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y))
#define	_IOW(x,y,t)	(IOC_IN|(((long)sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y))
#define	FIONREAD	_IOR('f',127,u_long)
#define	FIONBIO	_IOW('f',126,u_long)
#define	FIOASYNC	_IOW('f',125,u_long)
#define	SIOCSHIWAT	_IOW('s',0,u_long)
#define	SIOCGHIWAT	_IOR('s',1,u_long)
#define	SIOCSLOWAT	_IOW('s',2,u_long)
#define	SIOCGLOWAT	_IOR('s',3,u_long)
#define	SIOCATMARK	_IOR('s',7,u_long)
struct	hostent {
	char	FAR *h_name;
	char	FAR* FAR *h_aliases;
	short	h_addrtype;
	short	h_length;
	char	FAR* FAR *h_addr_list;
#define	h_addr	h_addr_list[0]
};
struct	netent {
	char	FAR *n_name;
	char	FAR* FAR *n_aliases;
	short	n_addrtype;
	u_long	n_net;
};
struct	servent {
	char	FAR *s_name;
	char	FAR* FAR *s_aliases;
	short	s_port;
	char	FAR *s_proto;
};
struct	protoent {
	char	FAR *p_name;
	char	FAR* FAR *p_aliases;
	short	p_proto;
};
#define	IPPROTO_IP	0
#define	IPPROTO_ICMP	1
#define	IPPROTO_GGP	2
#define	IPPROTO_TCP	6
#define	IPPROTO_PUP	12
#define	IPPROTO_UDP	17
#define	IPPROTO_IDP	22
#define	IPPROTO_ND	77
#define	IPPROTO_RAW	255
#define	IPPROTO_MAX	256
#define	IPPORT_ECHO	7
#define	IPPORT_DISCARD	9
#define	IPPORT_SYSTAT	11
#define	IPPORT_DAYTIME	13
#define	IPPORT_NETSTAT	15
#define	IPPORT_FTP	21
#define	IPPORT_TELNET	23
#define	IPPORT_SMTP	25
#define	IPPORT_TIMESERVER	37
#define	IPPORT_NAMESERVER	42
#define	IPPORT_WHOIS	43
#define	IPPORT_MTP	57
#define	IPPORT_TFTP	69
#define	IPPORT_RJE	77
#define	IPPORT_FINGER	79
#define	IPPORT_TTYLINK	87
#define	IPPORT_SUPDUP	95
#define	IPPORT_EXECSERVER	512
#define	IPPORT_LOGINSERVER	513
#define	IPPORT_CMDSERVER	514
#define	IPPORT_EFSSERVER	520
#define	IPPORT_BIFFUDP	512
#define	IPPORT_WHOSERVER	513
#define	IPPORT_ROUTESERVER	520
#define	IPPORT_RESERVED	1024
#define	IMPLINK_IP	155
#define	IMPLINK_LOWEXPER	156
#define	IMPLINK_HIGHEXPER	158
struct	in_addr {
	union {
		struct {u_char	s_b1,s_b2,s_b3,s_b4;} S_un_b;
		struct {u_short	s_w1,s_w2;} S_un_w;
		u_long	S_addr;
	} S_un;
#define	s_addr	S_un.S_addr
#define	s_host	S_un.S_un_b.s_b2
#define	s_net	S_un.S_un_b.s_b1
#define	s_imp	S_un.S_un_w.s_w2
#define	s_impno	S_un.S_un_b.s_b4
#define	s_lh	S_un.S_un_b.s_b3
};
#define	IN_CLASSA(i)	(((long)(i) & 0x80000000)==0)
#define	IN_CLASSA_NET	0xff000000
#define	IN_CLASSA_NSHIFT	24
#define	IN_CLASSA_HOST	0x00ffffff
#define	IN_CLASSA_MAX	128
#define	IN_CLASSB(i)	(((long)(i) & 0xc0000000)==0x80000000)
#define	IN_CLASSB_NET	0xffff0000
#define	IN_CLASSB_NSHIFT	16
#define	IN_CLASSB_HOST	0x0000ffff
#define	IN_CLASSB_MAX	65536
#define	IN_CLASSC(i)	(((long)(i) & 0xe0000000)==0xc0000000)
#define	IN_CLASSC_NET	0xffffff00
#define	IN_CLASSC_NSHIFT	8
#define	IN_CLASSC_HOST	0x000000ff
#define	INADDR_ANY	(u_long)0x00000000
#define	INADDR_LOOPBACK	0x7f000001
#define	INADDR_BROADCAST	(u_long)0xffffffff	
#define	INADDR_NONE	0xffffffff
struct	sockaddr_in {
	short	sin_family;
	u_short	sin_port;
	struct in_addr	sin_addr;
	char	sin_zero[8];
};
#define	WSADESCRIPTION_LEN	256
#define	WSASYS_STATUS_LEN	128
typedef	struct WSAData {
	WORD	wVersion;
	WORD	wHighVersion;
	char	szDescription[WSADESCRIPTION_LEN+1];
	char	szSystemStatus[WSASYS_STATUS_LEN+1];
	unsigned short	iMaxSockets;
	unsigned short	iMaxUdpDg;
	char	FAR *lpVendorInfo;
} WSADATA,FAR *LPWSADATA;
#define	IP_OPTIONS	1
#define	IP_MULTICAST_IF	2
#define	IP_MULTICAST_TTL	3
#define	IP_MULTICAST_LOOP	4
#define	IP_ADD_MEMBERSHIP	5
#define	IP_DROP_MEMBERSHIP	6
#define	IP_DEFAULT_MULTICAST_TTL	1
#define	IP_DEFAULT_MULTICAST_LOOP	1
#define	IP_MAX_MEMBERSHIPS	20
struct	ip_mreq {
	struct in_addr	imr_multiaddr;
	struct in_addr	imr_interface;
};
#define	INVALID_SOCKET	(SOCKET)(~0)
#define	SOCKET_ERROR	(-1)
#define	SOCK_STREAM	1
#define	SOCK_DGRAM	2
#define	SOCK_RAW	3
#define	SOCK_RDM	4
#define	SOCK_SEQPACKET	5
#define	SO_DEBUG	0x0001
#define	SO_ACCEPTCONN	0x0002
#define	SO_REUSEADDR	0x0004
#define	SO_KEEPALIVE	0x0008
#define	SO_DONTROUTE	0x0010
#define	SO_BROADCAST	0x0020
#define	SO_USELOOPBACK	0x0040
#define	SO_LINGER	0x0080
#define	SO_DONTLINGER	(u_int)(~SO_LINGER)
#define	SO_OOBINLINE	0x0100
#define	SO_SNDBUF	0x1001
#define	SO_RCVBUF	0x1002
#define	SO_SNDLOWAT	0x1003
#define	SO_RCVLOWAT	0x1004
#define	SO_SNDTIMEO	0x1005
#define	SO_RCVTIMEO	0x1006
#define	SO_ERROR	0x1007
#define	SO_TYPE	0x1008
#define	SO_CONNDATA	0x7000
#define	SO_CONNOPT	0x7001
#define	SO_DISCDATA	0x7002
#define	SO_DISCOPT	0x7003
#define	SO_CONNDATALEN	0x7004
#define	SO_CONNOPTLEN	0x7005
#define	SO_DISCDATALEN	0x7006
#define	SO_DISCOPTLEN	0x7007
#define	SO_OPENTYPE	0x7008
#define	SO_MAXDG	0x7009
#define	SO_MAXPATHDG	0x700A
#define	SO_SYNCHRONOUS_ALERT	0x10
#define	SO_SYNCHRONOUS_NONALERT	0x20
#define	TCP_NODELAY	0x0001
#define	TCP_BSDURGENT	0x7000
#define	AF_UNSPEC	0
#define	AF_UNIX	1
#define	AF_INET	2
#define	AF_IMPLINK	3
#define	AF_PUP	4
#define	AF_CHAOS	5
#define	AF_IPX	6
#define	AF_NS	6
#define	AF_ISO	7
#define	AF_OSI	AF_ISO
#define	AF_ECMA	8
#define	AF_DATAKIT	9
#define	AF_CCITT	10
#define	AF_SNA	11
#define	AF_DECnet	12
#define	AF_DLI	13
#define	AF_LAT	14
#define	AF_HYLINK	15
#define	AF_APPLETALK	16
#define	AF_NETBIOS	17
#define	AF_MAX	18
struct	sockaddr {
	u_short	sa_family;
	char	sa_data[14];
};
struct	sockproto {
	u_short	sp_family;
	u_short	sp_protocol;
};
#define	PF_UNSPEC	AF_UNSPEC
#define	PF_UNIX	AF_UNIX
#define	PF_INET	AF_INET
#define	PF_IMPLINK	AF_IMPLINK
#define	PF_PUP	AF_PUP
#define	PF_CHAOS	AF_CHAOS
#define	PF_NS	AF_NS
#define	PF_IPX	AF_IPX
#define	PF_ISO	AF_ISO
#define	PF_OSI	AF_OSI
#define	PF_ECMA	AF_ECMA
#define	PF_DATAKIT	AF_DATAKIT
#define	PF_CCITT	AF_CCITT
#define	PF_SNA	AF_SNA
#define	PF_DECnet	AF_DECnet
#define	PF_DLI	AF_DLI
#define	PF_LAT	AF_LAT
#define	PF_HYLINK	AF_HYLINK
#define	PF_APPLETALK	AF_APPLETALK
#define	PF_MAX	AF_MAX
struct	linger {
	u_short	l_onoff;
	u_short	l_linger;
};
#define	SOL_SOCKET	0xffff
#define	SOMAXCONN	5
#define	MSG_OOB	0x1
#define	MSG_PEEK	0x2
#define	MSG_DONTROUTE	0x4
#define	MSG_MAXIOVLEN	16
#define	MSG_PARTIAL	0x8000
#define	MAXGETHOSTSTRUCT	1024
#define	FD_READ	0x01
#define	FD_WRITE	0x02
#define	FD_OOB	0x04
#define	FD_ACCEPT	0x08
#define	FD_CONNECT	0x10
#define	FD_CLOSE	0x20
#define	WSABASEERR	10000
#define	WSAEINTR	(WSABASEERR+4)
#define	WSAEBADF	(WSABASEERR+9)
#define	WSAEACCES	(WSABASEERR+13)
#define	WSAEFAULT	(WSABASEERR+14)
#define	WSAEINVAL	(WSABASEERR+22)
#define	WSAEMFILE	(WSABASEERR+24)
#define	WSAEWOULDBLOCK	(WSABASEERR+35)
#define	WSAEINPROGRESS	(WSABASEERR+36)
#define	WSAEALREADY	(WSABASEERR+37)
#define	WSAENOTSOCK	(WSABASEERR+38)
#define	WSAEDESTADDRREQ	(WSABASEERR+39)
#define	WSAEMSGSIZE	(WSABASEERR+40)
#define	WSAEPROTOTYPE	(WSABASEERR+41)
#define	WSAENOPROTOOPT	(WSABASEERR+42)
#define	WSAEPROTONOSUPPORT	(WSABASEERR+43)
#define	WSAESOCKTNOSUPPORT	(WSABASEERR+44)
#define	WSAEOPNOTSUPP	(WSABASEERR+45)
#define	WSAEPFNOSUPPORT	(WSABASEERR+46)
#define	WSAEAFNOSUPPORT	(WSABASEERR+47)
#define	WSAEADDRINUSE	(WSABASEERR+48)
#define	WSAEADDRNOTAVAIL	(WSABASEERR+49)
#define	WSAENETDOWN	(WSABASEERR+50)
#define	WSAENETUNREACH	(WSABASEERR+51)
#define	WSAENETRESET	(WSABASEERR+52)
#define	WSAECONNABORTED	(WSABASEERR+53)
#define	WSAECONNRESET	(WSABASEERR+54)
#define	WSAENOBUFS	(WSABASEERR+55)
#define	WSAEISCONN	(WSABASEERR+56)
#define	WSAENOTCONN	(WSABASEERR+57)
#define	WSAESHUTDOWN	(WSABASEERR+58)
#define	WSAETOOMANYREFS	(WSABASEERR+59)
#define	WSAETIMEDOUT	(WSABASEERR+60)
#define	WSAECONNREFUSED	(WSABASEERR+61)
#define	WSAELOOP	(WSABASEERR+62)
#define	WSAENAMETOOLONG	(WSABASEERR+63)
#define	WSAEHOSTDOWN	(WSABASEERR+64)
#define	WSAEHOSTUNREACH	(WSABASEERR+65)
#define	WSAENOTEMPTY	(WSABASEERR+66)
#define	WSAEPROCLIM	(WSABASEERR+67)
#define	WSAEUSERS	(WSABASEERR+68)
#define	WSAEDQUOT	(WSABASEERR+69)
#define	WSAESTALE	(WSABASEERR+70)
#define	WSAEREMOTE	(WSABASEERR+71)
#define	WSASYSNOTREADY	(WSABASEERR+91)
#define	WSAVERNOTSUPPORTED	(WSABASEERR+92)
#define	WSANOTINITIALISED	(WSABASEERR+93)
#define	WSAEDISCON	(WSABASEERR+101)
#define	WSAHOST_NOT_FOUND	(WSABASEERR+1001)
#define	WSATRY_AGAIN	(WSABASEERR+1002)
#define	WSANO_RECOVERY	(WSABASEERR+1003)
#define	WSANO_DATA	(WSABASEERR+1004)
#define	WSANO_ADDRESS	WSANO_DATA
#define	HOST_NOT_FOUND	WSAHOST_NOT_FOUND
#define	TRY_AGAIN	WSATRY_AGAIN
#define	NO_RECOVERY	WSANO_RECOVERY
#define	NO_DATA	WSANO_DATA
#define	NO_ADDRESS	WSANO_ADDRESS
#define	h_errno	WSAGetLastError()
SOCKET	PASCAL FAR accept(SOCKET,struct sockaddr FAR*,int FAR*);
int	PASCAL FAR bind(SOCKET,const struct sockaddr FAR*,int);
int	PASCAL FAR closesocket(SOCKET);
int	PASCAL FAR connect(SOCKET,const struct sockaddr FAR*,int);
int	PASCAL FAR ioctlsocket(SOCKET,long,u_long FAR*);
int	PASCAL FAR getpeername(SOCKET,struct sockaddr FAR*,int FAR*);
int	PASCAL FAR getsockname(SOCKET,struct sockaddr FAR*,int FAR*);
int	PASCAL FAR getsockopt(SOCKET,int,int,char FAR*,int FAR*);
u_long	PASCAL FAR htonl(u_long);
u_short	PASCAL FAR htons(u_short);
unsigned long	PASCAL FAR inet_addr(const char FAR*);
char	FAR* PASCAL FAR inet_ntoa(struct in_addr);
int	PASCAL FAR listen(SOCKET,int);
u_long	PASCAL FAR ntohl(u_long);
u_short	PASCAL FAR ntohs(u_short);
int	PASCAL FAR recv(SOCKET,char FAR*,int,int);
int	PASCAL FAR recvfrom(SOCKET,char FAR*,int,int,struct sockaddr FAR*,int FAR*);
int	PASCAL FAR select(int,fd_set FAR*,fd_set FAR*,fd_set FAR*,const struct timeval FAR*);
int	PASCAL FAR send(SOCKET,const char FAR*,int,int);
int	PASCAL FAR sendto(SOCKET,const char FAR*,int,int,const struct sockaddr FAR*,int);
int	PASCAL FAR setsockopt(SOCKET,int,int,const char FAR*,int);
int	PASCAL FAR shutdown(SOCKET,int);
SOCKET	PASCAL FAR socket(int,int,int);
struct hostent FAR* PASCAL FAR gethostbyaddr(const char FAR*,int,int);
struct hostent FAR* PASCAL FAR gethostbyname(const char FAR*);
int	PASCAL FAR gethostname(char FAR*,int);
struct servent FAR* PASCAL FAR getservbyport(int,const char FAR*);
struct servent FAR* PASCAL FAR getservbyname(const char FAR*,const char FAR*);
struct protoent FAR* PASCAL FAR getprotobynumber(int);
struct protoent FAR* PASCAL FAR getprotobyname(const char FAR*);

/* Microsoft Windows Extension function prototypes */
int	PASCAL FAR WSAStartup(WORD,LPWSADATA);
int	PASCAL FAR WSACleanup(void);
void	PASCAL FAR WSASetLastError(int);
int	PASCAL FAR WSAGetLastError(void);
BOOL	PASCAL FAR WSAIsBlocking(void);
int	PASCAL FAR WSAUnhookBlockingHook(void);
FARPROC	PASCAL FAR WSASetBlockingHook(FARPROC);
int	PASCAL FAR WSACancelBlockingCall(void);
HANDLE	PASCAL FAR WSAAsyncGetServByName(HWND,u_int,const char FAR*,const char FAR*,char FAR*,int);
HANDLE	PASCAL FAR WSAAsyncGetServByPort(HWND,u_int,int,const char FAR*,char FAR*,int);
HANDLE	PASCAL FAR WSAAsyncGetProtoByName(HWND,u_int,const char FAR*,char FAR*,int);
HANDLE	PASCAL FAR WSAAsyncGetProtoByNumber(HWND,u_int,int,char FAR*,int);
HANDLE	PASCAL FAR WSAAsyncGetHostByName(HWND,u_int,const char FAR*,char FAR*,int);
HANDLE	PASCAL FAR WSAAsyncGetHostByAddr(HWND,u_int,const char FAR*,int,int,char FAR*,int);
int	PASCAL FAR WSACancelAsyncRequest(HANDLE);
int	PASCAL FAR WSAAsyncSelect(SOCKET,HWND,u_int,long);
int	PASCAL FAR WSARecvEx(SOCKET,char FAR*,int,int FAR*);

/* Microsoft Windows Extended data types */
typedef	struct sockaddr SOCKADDR,*PSOCKADDR,FAR *LPSOCKADDR;
typedef	struct sockaddr_in SOCKADDR_IN,*PSOCKADDR_IN,FAR *LPSOCKADDR_IN;
typedef	struct linger LINGER,*PLINGER,FAR *LPLINGER;
typedef	struct in_addr IN_ADDR,*PIN_ADDR,FAR *LPIN_ADDR;
typedef	struct fd_set FD_SET,*PFD_SET,FAR *LPFD_SET;
typedef	struct hostent HOSTENT,*PHOSTENT,FAR *LPHOSTENT;
typedef	struct servent SERVENT,*PSERVENT,FAR *LPSERVENT;
typedef	struct protoent PROTOENT,*PPROTOENT,FAR *LPPROTOENT;
typedef	struct timeval TIMEVAL,*PTIMEVAL,FAR *LPTIMEVAL;
#define	WSAMAKEASYNCREPLY(buflen,error)	MAKELONG(buflen,error)
#define	WSAMAKESELECTREPLY(event,error)	MAKELONG(event,error)
#define	WSAGETASYNCBUFLEN(lParam)	LOWORD(lParam)
#define	WSAGETASYNCERROR(lParam)	HIWORD(lParam)
#define	WSAGETSELECTEVENT(lParam)	LOWORD(lParam)
#define	WSAGETSELECTERROR(lParam)	HIWORD(lParam)

#ifdef	__cplusplus
extern	}
#endif

#endif
